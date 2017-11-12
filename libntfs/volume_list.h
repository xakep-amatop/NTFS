#ifndef __volume_list_h__
#define __volume_list_h__

#ifdef LIBNTFS_EXPORTS
  #define LIBNTFS __declspec(dllexport)
#else
  #define LIBNTFS __declspec(dllimport)
#endif

#if defined(_WINDOWS_)
  LIBNTFS
#endif
  extern unsigned char error_volume;

typedef union {
  struct {
    long low;
    long high;
  } n32;
  long long n64;
} QWORD;

typedef struct {
#if defined(_WINDOWS_)
  void * hFile;
#elif defined(_UNIX_)
  int hFile;
#endif
  QWORD llDistanceToMove;
  unsigned int MoveMethod;
  void * lpBuffer;
  unsigned int  ulNumberBytesToRead;
#if defined(_WINDOWS_)
  DWORD  ulNumberOfBytesRead;
#else
  unsigned int  ulNumberOfBytesRead;
#endif
} File;

/*Структура BOOT сектора*/
#pragma pack(push, 1)
typedef struct {
  char      chJumpInstruction[3];      // Команда перехода на загрузочный код.
  char      chOemID[4];            // Сигнатура
  char      chDummy[4];            // 4x0
  struct NTFS_BPB {              //
  unsigned short    wBytesPerSec;        // Количество байт на сектор
  unsigned char    uchSecPerClust;        // Количество секторов в кластере.
  unsigned short    wReservedSec;        // Должно равняться нулю
  unsigned char    bFats;
  unsigned short    wRoot_Entries;
  unsigned short    wUnused1;          // Должно равняться нулю
  unsigned char    uchMediaDescriptor;      // Тип носителя
  unsigned short    wUnused2;          // должен быть ноль, sectors_per_fat
  unsigned short    wSecPerTrack;        // количество секторов на дорожку, не используется 
  unsigned short    wNumberOfHeads;        // количество головок, не используется 
  unsigned int    dwHiddenSec;        // количество скрытых секторов, не используется 
  unsigned int    dwLarge_sectors;      // должен быть ноль, 
  unsigned char    uchPhysical_drive;      // не используется */
  unsigned char    uchCurrent_head;      // не используется */
  unsigned char    uchExtended_boot_signature;  // не используется */
  unsigned char    uchReserved2;        // не используется */
  long long      n64TotalSec;        // Количество секторов на томе
  long long      n64MFTLogicalClustNum;    // Стартовый кластер MFT
  long long      n64MFTMirrLogicalClustNum;  // Стартовый кластер копии MFT
  char        chClustPerMFTRecord;    // Размер MFT записи в кластерах
  unsigned char    uchReserved0[3];
  char        chClustPerIndexRecord;    // Размер индексной записи в кластерах
  unsigned char    uchReserved1[3];
  long long      n64VolumeSerialNum;      // уникальный серийный номер тома
  unsigned int    dwChecksum;          // 
  }        bpb;              //
  char      chBootstrapCode[426];      // загрузочный-код 
  unsigned short  wSecMark;            // конец загрузочного сектора, сигнатура 0xaa55 
}NTFS_PART_BOOT_SEC, *PNTFS_PART_BOOT_SEC;
#pragma pack(pop)

/*структура узла списка томов*/
typedef struct VOLUME_LIST {
  VOLUME_LIST* next;      /*указатель на следующий узел списка томов*/
  NTFS_PART_BOOT_SEC* boot;  /*указатель на структуру BOOT сектора текущего тома*/
#if defined(_WINDOWS_)
  HANDLE File;  /*открытый дескриптор тома, для чтетия данных с тома, если равняется NULL том не был открыт*/
#elif defined(_UNIX_)
  int File;
#endif
  TCHAR  name[4];        /*метка тома*/
  unsigned char   error;
} VOLUME_LIST, *PVOLUME_LIST;

/*Функция очистки списка томов
  list - указатель на указатель на список томов*/
#if defined(_WINDOWS_)
  LIBNTFS
#endif
  void FreeVolumes(PVOLUME_LIST * list);

#if defined(_WINDOWS_)
  LIBNTFS
#endif
void SetPointer_Read(File * _file);

/*функция создания списка томов, получения дескрипторов томов, их BOOT секторов и их меток
  volume_list - указатель на указатель на список томов
  compare    - указатель на функцию, которая принимает два аргумента указателя типа void на элементы списка томов и возвращает результат сравнения (отрицательное число, положительное и ноль в случае равенства за заданым критерием) 
  Функкция возвращает количество томов присутствующих в системе*/
#if defined(_WINDOWS_)
  LIBNTFS
#endif
unsigned char GetVolumeInf(PVOLUME_LIST * volume_list, int(*compare)(void*, void*));

#if defined(_WINDOWS_)
  LIBNTFS NTFS_PART_BOOT_SEC * ReadNTFS_BOOT(void ** device, TCHAR* pathway);
#elif defined(_UNIX_)
  NTFS_PART_BOOT_SEC* ReadNTFS_BOOT(int * device, const char * pathway);
#endif

/*функция сравнения двух элементов списка томов
  принимает два аргумента указателя типа void на элементы списка томов и возвращает результат
  если структуры за определенным критерием:
  равны функция должна возвращать 0
  volume1 > volume2 функция должна возвращать положительное число
  volume1 < volume2 функция должна возвращать отрицательное число*/
#if defined(_WINDOWS_)
  LIBNTFS 
#endif
int CompareVolumes(void* volume1, void* volume2);
#endif 
