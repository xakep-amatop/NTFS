#include "stdafx.h"

unsigned char       error_ntfs;
unsigned long long  count_mfts;
unsigned long long  NumberMFTRecords;

inline void FreeHardLink(PHARD_LINK * arr, unsigned short numHL, unsigned short numLast);

unsigned char *  NtfsDecodeRun(unsigned char *  DataRun, long long *DataRunOffset, unsigned long long *DataRunLength) {
  unsigned char DataRunOffsetSize; //размер поля смещения
  unsigned char DataRunLengthSize; //размер поля длины
  char i;
  DataRunOffsetSize = (*DataRun >> 4) & 0xF;//из старшего полубайта считаем размер поля смещения
  DataRunLengthSize = *DataRun & 0xF; //из младшего размер поля смещения
  *DataRunOffset = 0;
  *DataRunLength = 0;
  DataRun++; //указатель на сами данные
  //цикл распаковки длины отрезка, с каждой итерацией значение сдвигается на i-байт и      
  //прибавляется с длиной
  for (i = 0; i < DataRunLengthSize; i++) {
    *DataRunLength += ((unsigned long long)*DataRun) << (i << 3);
    DataRun++;
  }
  /* NTFS 3+ sparse files, если файл разряжен */
  if (DataRunOffsetSize) {
    //цикл распаковки смещения
    for (i = 0; i < DataRunOffsetSize - 1; i++) {
      *DataRunOffset += ((unsigned long long)(*DataRun)) << (i << 3);
      DataRun++;
    }
    //последний байт может быть знаковым, поэтому он обрабатывается отдельно
    *DataRunOffset = ((char)(*(DataRun++)) << (i << 3)) + *DataRunOffset;
  }
  //возвращаем указатель на следующий отрезок
   return DataRun;
}

unsigned char Check_NTFS(NTFS_PART_BOOT_SEC* ntfs_boot) {
  if (ntfs_boot) {
    if (!(*(unsigned long*)&ntfs_boot->chOemID ^ 0x5346544e)) {/*перевірка сигнатури ntfs "NTFS"*/
      if (ntfs_boot->bpb.wBytesPerSec < 0x100 || ntfs_boot->bpb.wBytesPerSec > 0x1000){
        error_ntfs |= 0x04; // невідповідний розмір сектора
        return 4;
      }
      //check sectors per cluster
      switch (ntfs_boot->bpb.uchSecPerClust) {
      case 1: case 2: case 4: case 8: case 16: case 32: case 64: case 128:
        break;
      default:
        error_ntfs |= 0x02; // невідповідна кількість секторів на кластер  
        return 2;
      }
      return 0;
    }
    else {
      error_ntfs |= 0x01; //  сигнатура не NTFS
      return 1;
    }
  }
  else return 8;
}

PFRAGMENT_LIST FillFramment(long long DataRunOffset, long long DataRunLength) {
  PFRAGMENT_LIST tmp = (PFRAGMENT_LIST)malloc(sizeof(FRAGMENT_LIST));
  tmp = (PFRAGMENT_LIST)malloc(sizeof(FRAGMENT_LIST));
  tmp->First_Cluster = DataRunOffset;
  tmp->Length = DataRunLength;
  tmp->next = NULL;
  return tmp;
}

PFRAGMENT_LIST DecodeData(File _file, long long num_record, PFRAGMENT_LIST mft_bits, PNTFS_PART_BOOT_SEC ntfs_boot, int(*comp)(void*, void*)) {
  PFRAGMENT_LIST FragmentListBegin = NULL, 
           FragmentListEnd = NULL;
  NTFS_ATTRIBUTE* attribute = (NTFS_ATTRIBUTE*)((unsigned char*)_file.lpBuffer + ((NTFS_MFT_FILE*)_file.lpBuffer)->wAttribOffset);
  if (attribute->uchNonResFlag) {
    unsigned char *  ptr = (unsigned char * )attribute + attribute->Attr.NonResident.wDatarunOffset;
    long long  DataRunOffset;
    unsigned long long  DataRunLength;
    long long  tmpDataRunOffset;
    tmpDataRunOffset = 0LL;
    while (*ptr != 0x00) {
      ptr = NtfsDecodeRun(ptr, &DataRunOffset, &DataRunLength);
      tmpDataRunOffset += DataRunOffset;
      AddItemList((List*)FillFramment(tmpDataRunOffset, DataRunLength), (List**)(&FragmentListBegin), (List**)(&FragmentListEnd), CompareFragments);
    }
  }
  else AddItemList((List*)FillFramment(mft_bits->First_Cluster + ((((NTFS_MFT_FILE*)_file.lpBuffer)->dwMFTRecNumber - num_record)*_file.ulNumberBytesToRead) / (ntfs_boot->bpb.wBytesPerSec*ntfs_boot->bpb.uchSecPerClust), 1LL), (List**)(&FragmentListBegin), (List**)(&FragmentListEnd), comp);
  return FragmentListBegin;
}

#define CONVERT_TYPE(type, value) (*((type*)&value)) 

void Save_MFT_bits(File * _file, PFRAGMENT_LIST* mft_bits, int(*comp_fragments)(void*, void*)) {
  NTFS_ATTRIBUTE * attribute;
  NTFS_MFT_FILE  * mft_file   = (NTFS_MFT_FILE*)(_file->lpBuffer);

  *mft_bits           = NULL;
  
  long long mft_records = 0ll; // розмір всієї MFT таблиці в кластерах
  SetPointer_Read(_file);
  if (!(*(unsigned long*)&mft_file->szSignature ^ 0x454c4946)) {/*перевірка сигнатури запису mft "FILE"*/
    do {
      attribute = (NTFS_ATTRIBUTE*)((unsigned char*)(_file->lpBuffer) + mft_file->wAttribOffset);
      mft_file->wAttribOffset += attribute->wFullLength;
    } while (attribute->dwType != TYPE_DATA); // search attribute with data
    mft_file->wAttribOffset -= attribute->wFullLength;

    *mft_bits = DecodeData(*_file, 0, NULL, NULL, comp_fragments);
    int k = 0;
  }
  else error_ntfs |= 0x10; // данные не являются записью mft
}

void ComputeNumberMFTRec(PFRAGMENT_LIST _frag) {
  while (_frag) {
    NumberMFTRecords += _frag->Length;
    _frag = _frag->next;
  }
}

inline unsigned long GetNumberBytesToRead(NTFS_PART_BOOT_SEC * ntfs){
  return  (ntfs->bpb.chClustPerMFTRecord > 0) ? 
      (ntfs->bpb.uchSecPerClust*ntfs->bpb.wBytesPerSec*ntfs->bpb.chClustPerMFTRecord) : 
      (2 << ~ntfs->bpb.chClustPerMFTRecord);
}

inline void Parse_ATTR_STANDARD_INFORMATION(info & _info){
  _info.FileListTmp->n64CreationTime = ((ATTR_STANDARD*)((char*)_info.attr_ntfs + _info.attr_ntfs->Attr.Resident.wAttrOffset))->n64Create;
  _info.was_attr |= WAS_STANDARD_INFORMATION;  
}     

inline void Parse_ATTR_ATTRIBUTE_LIST(info & _info){

}          

inline void Parse_ATTR_FILE_NAME(info & _info){
  if (_info.count_hl < _info.mft_file->wHardLinks) {
    ATTR_FILENAME* attr_filename = (ATTR_FILENAME*)((char*)_info.attr_ntfs + _info.attr_ntfs->Attr.Resident.wAttrOffset);
    if (!(_info.was_attr & (WAS_STANDARD_INFORMATION | WAS_FILENAME)))
      _info.FileListTmp->n64CreationTime = attr_filename->n64Create;
    unsigned short length   = sizeof(TCHAR)*attr_filename->chFileNameLength;
    PHARD_LINK _hl       = _info.hard_link + _info.count_hl;
    _info.was_attr        |= WAS_FILENAME;
    _hl->bNameLength     = attr_filename->chFileNameLength;
    _hl->bNameType       = attr_filename->chFileNameType;
    _hl->pwName       = (TCHAR*)malloc(length);

    memcpy(_hl->pwName, attr_filename->wFilename, length);
    _info.count_hl++;
  }
}

inline void Parse_ATTR_VOLUME_VERSION_OBJECT_ID(info & _info){

}

inline void Parse_ATTR_SECURITY_DESCRIPTOR(info & _info){

}

inline void Parse_ATTR_VOLUME_NAME(info & _info){

}

inline void Parse_ATTR_VOLUME_INFORMATION(info & _info){

}

inline void Parse_ATTR_DATA(info & _info){
  File _f;

  _info.FragmentListBegin = NULL;
  _info.FragmentListEnd  = NULL;
  _info.StreamListTmp    = (PSTREAM_LIST)malloc(sizeof(STREAM_LIST));
  _f.lpBuffer        = _info.attr_ntfs;
  
  DecodeData(_f, _info.num_MFT, _info.mft_bits, _info.ntfs_boot, _info.comp[2]);
  
  PNTFS_ATTRIBUTE attr_ntfs = _info.attr_ntfs;

  if (attr_ntfs->uchNonResFlag) _info.StreamListTmp->qwRealSize = attr_ntfs->Attr.NonResident.n64RealSize;
  else _info.StreamListTmp->qwRealSize = attr_ntfs->Attr.Resident.dwLength;
  if (_info.FragmentListBegin){
    _info.StreamListTmp->fragment_list   = _info.FragmentListBegin;
    _info.was_attr            |= WAS_STREAM;
    AddItemList((List*)_info.StreamListTmp, (List**)(&_info.StreamListBegin), (List**)(&_info.StreamListEnd), _info.comp[1]);
  }
  else free(_info.StreamListTmp);
}

inline void Parse_ATTR_INDEX_ROOT(info & _info){

}

inline void Parse_ATTR_INDEX_ALLOCATION(info & _info){

}

inline void Parse_ATTR_BITMAP(info & _info){

}

inline void Parse_ATTR_SYMBOLIC_LINK_REPARSE_POINT(info & _info){

}

inline void Parse_ATTR_EA_INFORMATION(info & _info){

}

inline void Parse_ATTR_EA(info & _info){

}

inline void Parse_ATTR_PROPERTY_SET(info & _info){

}

inline void Parse_ATTR_LOGGED_UTILITY_STREAM(info & _info){

}

typedef void (*parse_func)(info &); 

void (* const parse_funcs[sizeof(attr_types)])(info &) = {
  Parse_ATTR_STANDARD_INFORMATION,
  Parse_ATTR_ATTRIBUTE_LIST,
  Parse_ATTR_FILE_NAME,
  Parse_ATTR_VOLUME_VERSION_OBJECT_ID,
  Parse_ATTR_SECURITY_DESCRIPTOR,
  Parse_ATTR_VOLUME_NAME,
  Parse_ATTR_VOLUME_INFORMATION,
  Parse_ATTR_DATA,
  Parse_ATTR_INDEX_ROOT,
  Parse_ATTR_INDEX_ALLOCATION,
  Parse_ATTR_BITMAP,
  Parse_ATTR_SYMBOLIC_LINK_REPARSE_POINT,
  Parse_ATTR_EA_INFORMATION,
  Parse_ATTR_EA,
  Parse_ATTR_PROPERTY_SET,
  Parse_ATTR_LOGGED_UTILITY_STREAM
};

PFILE_LIST ReadMFT(
#if defined(_WINDOWS_)
    HANDLE
#elif defined(_UNIX_)
    int
#endif
  device, NTFS_PART_BOOT_SEC* ntfs_boot, unsigned int buffer_size, int (*comp[3])(void*, void*)) {

  info _info;
  File _file;

  _info.FileListBegin         = NULL;
  _info.FileListEnd           = NULL;
  _info.FileListTmp           = NULL;
  _info.ntfs_boot             = ntfs_boot;
  _info.comp[1]               = comp[1];
  _info.comp[2]               = comp[2];
  _info.comp[3]               = comp[3];

  _file.hFile                 = device;
  _file.ulNumberBytesToRead   = GetNumberBytesToRead(ntfs_boot);
  
  _file.llDistanceToMove.n64  = (ntfs_boot->bpb.n64MFTMirrLogicalClustNum*ntfs_boot->bpb.uchSecPerClust*ntfs_boot->bpb.wBytesPerSec);

  //_file.llDistanceToMove.n64  = (ntfs_boot->bpb.n64MFTLogicalClustNum*ntfs_boot->bpb.uchSecPerClust*ntfs_boot->bpb.wBytesPerSec);
  _file.lpBuffer              = (unsigned char*)malloc(sizeof(unsigned char)*buffer_size);
#if defined(_WINDOWS_)
  _file.MoveMethod            = FILE_BEGIN;
#elif defined(_UNIX_)
  _file.MoveMethod            = SEEK_SET;
#endif

  if (!_file.lpBuffer) {
    error_ntfs |= 0x08;
    return _info.FileListBegin;
  }
  _info.mft_file        = (NTFS_MFT_FILE*)_file.lpBuffer;
  _info.mft_bits        = NULL;
  
  Save_MFT_bits(&_file, &_info.mft_bits, _info.comp[2]);

  //AddItemList((List*)FillFramment(((((NTFS_MFT_FILE*)_file.lpBuffer)->dwMFTRecNumber - 0)*_file.ulNumberBytesToRead) / (ntfs_boot->bpb.wBytesPerSec*ntfs_boot->bpb.uchSecPerClust), 1LL), 
  //      (List**)(_info.mft_bits), 
  //      (List**)(_info.mft_bits), 
  //      _info.comp[2]);

  ComputeNumberMFTRec(_info.mft_bits);

  //NumberMFTRecords = (NumberMFTRecords*ntfs_boot->bpb.uchSecPerClust*ntfs_boot->bpb.wBytesPerSec)/ _file.ulNumberBytesToRead; // variable for future progress bar
  if (error_ntfs || error_volume) {
    free(_file.lpBuffer);
    return _info.FileListBegin;
  }

  _info.mft_file = (NTFS_MFT_FILE*)_file.lpBuffer;
  count_mfts = 0;

  while (_info.mft_bits) {
    // loop all fragments of MFT record
    _file.llDistanceToMove.n64 = ntfs_boot->bpb.uchSecPerClust*ntfs_boot->bpb.wBytesPerSec*_info.mft_bits->First_Cluster; // номер першого байту чергового фрагменту таблиці mft
    char stop = FALSE;
    while (TRUE) {
      // read from disk and save next packet MFT records to buffer
      SetPointer_Read(&_file);
      if (error_volume) {
        free(_file.lpBuffer);
        return _info.FileListBegin;
      }

      // loop all MFT record in buffer mft_record
      for (unsigned int i = 0; i < (unsigned int)buffer_size / _file.ulNumberBytesToRead; i++) {
        _info.mft_file = (NTFS_MFT_FILE*)((unsigned char*)_file.lpBuffer + i * _file.ulNumberBytesToRead); //
        if (*(unsigned long*)&_info.mft_file->szSignature ^ 0x454c4946) {
          stop = TRUE;
          break;
        }
        if (_info.mft_file->wFlags & 0x01) {
          _info.FileListTmp                = (PFILE_LIST)malloc(sizeof(FILE_LIST));
          _info.FileListTmp->next          = NULL;
          _info.StreamListBegin            = NULL;
          _info.StreamListEnd              = NULL;
          _info.StreamListTmp              =NULL;
          _info.FileListTmp->stream_list   = NULL;

          _info.FileListTmp->wHardLinks   =_info.mft_file->wHardLinks;
          _info.FileListTmp->dwMFT_Number  = _info.mft_file->dwMFTRecNumber;
          _info.hard_link          = (HARD_LINK*)malloc(sizeof(HARD_LINK)*(_info.mft_file->wHardLinks));
          _info.count_hl           ^= _info.count_hl;
          _info.was_attr               ^= _info.was_attr;

          // loop all attributes in MFT record 
          while (TRUE) {
            _info.attr_ntfs = (NTFS_ATTRIBUTE*)((unsigned char*)_file.lpBuffer + _info.mft_file->wAttribOffset);
            _info.FileListTmp->wAttribute = _info.attr_ntfs->wFlags;
            if (_info.attr_ntfs->dwType == 0xffffffff)  break;
            parse_funcs[(_info.attr_ntfs->dwType >> 4) - 1](_info);
            _info.mft_file->wAttribOffset += _info.attr_ntfs->wFullLength;
          }
          count_mfts++;
          if (_info.was_attr & 0x02) {
            if (_info.count_hl != _info.mft_file->wHardLinks) {
              HARD_LINK* hl = (HARD_LINK*)malloc(sizeof(HARD_LINK)*_info.count_hl);
              for (register unsigned short i = 0; i < _info.count_hl; i++) 
                hl[i] = _info.hard_link[i];
              FreeHardLink(&_info.hard_link, _info.mft_file->wHardLinks, _info.mft_file->wHardLinks);
              _info.hard_link = hl;
            }
            _info.FileListTmp->pHard_link = _info.hard_link;
            _info.FileListTmp->wHardLinks = _info.count_hl;
          }
          else {
            if (!(_info.was_attr & 0x03))
              _info.FileListTmp->n64CreationTime = 0LL;
            _info.FileListTmp->pHard_link = NULL;
          }
          if (_info.was_attr & 0x04)
            _info.FileListTmp->stream_list = _info.StreamListBegin;
          AddItemList((List*)_info.FileListTmp, (List**)&_info.FileListBegin, (List**)&_info.FileListEnd, comp[0]);
        }
        if (_info.mft_file->dwMFTRecNumber == 0xf) i = 24; // think about dividing this loop
      }
      _file.llDistanceToMove.n64 += buffer_size;
      if (stop) break;
    }
    _info.mft_bits = _info.mft_bits->next; // перехід на наступний елемент списку фрагментів mft
  }
  free(_file.lpBuffer);
  return _info.FileListBegin;
}

int CompareFragments(void* fragment1, void* fragment2) {
  long long tmp = ((PFRAGMENT_LIST)fragment1)->First_Cluster - ((PFRAGMENT_LIST)fragment2)->First_Cluster;
  return (int)*((int*)&tmp + 1);
}

int CompareStreams(void* stream1, void* stream2) {
  long long tmp = ((PSTREAM_LIST)stream1)->fragment_list->First_Cluster - ((PSTREAM_LIST)stream2)->fragment_list->First_Cluster;
  return (int)*((int*)&tmp + 1);
}

int CompareFiles(void* file1, void* file2) {
  return ((PFILE_LIST)file1)->dwMFT_Number - ((PFILE_LIST)file2)->dwMFT_Number;
}

inline void FreeHardLink(PHARD_LINK * arr, unsigned short numHL, unsigned short numLast) {
  for (register unsigned short i = numLast; i < numHL; i++)
    free((*arr[i]).pwName);
  free(*arr);
  *arr = NULL;
}

void FreeFragments(PFRAGMENT_LIST * list) {
  PFRAGMENT_LIST tmp = NULL;
  while (*list) {
    tmp = *list;
    *list = (*list)->next;
    free(tmp);
  }
  *list = NULL;
}

void FreeStreams(PSTREAM_LIST * list) {
  PSTREAM_LIST tmp = NULL;
  while (*list) {
    tmp = *list;
    *list = (*list)->next;
    FreeFragments(&(tmp->fragment_list));
    free(tmp);
  }
  *list = NULL;
}

void FreeFiles(PFILE_LIST * list) {
  PFILE_LIST tmp = NULL;
  while (*list) {
    tmp = *list;
    *list = (*list)->next;
    FreeStreams(&(tmp->stream_list));
    FreeHardLink(&(tmp->pHard_link), tmp->wHardLinks, 0);
    free(tmp);
  }
  *list = NULL;
}
