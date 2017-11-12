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

/*��������� BOOT �������*/
#pragma pack(push, 1)
typedef struct {
  char      chJumpInstruction[3];      // ������� �������� �� ����������� ���.
  char      chOemID[4];            // ���������
  char      chDummy[4];            // 4x0
  struct NTFS_BPB {              //
  unsigned short    wBytesPerSec;        // ���������� ���� �� ������
  unsigned char    uchSecPerClust;        // ���������� �������� � ��������.
  unsigned short    wReservedSec;        // ������ ��������� ����
  unsigned char    bFats;
  unsigned short    wRoot_Entries;
  unsigned short    wUnused1;          // ������ ��������� ����
  unsigned char    uchMediaDescriptor;      // ��� ��������
  unsigned short    wUnused2;          // ������ ���� ����, sectors_per_fat
  unsigned short    wSecPerTrack;        // ���������� �������� �� �������, �� ������������ 
  unsigned short    wNumberOfHeads;        // ���������� �������, �� ������������ 
  unsigned int    dwHiddenSec;        // ���������� ������� ��������, �� ������������ 
  unsigned int    dwLarge_sectors;      // ������ ���� ����, 
  unsigned char    uchPhysical_drive;      // �� ������������ */
  unsigned char    uchCurrent_head;      // �� ������������ */
  unsigned char    uchExtended_boot_signature;  // �� ������������ */
  unsigned char    uchReserved2;        // �� ������������ */
  long long      n64TotalSec;        // ���������� �������� �� ����
  long long      n64MFTLogicalClustNum;    // ��������� ������� MFT
  long long      n64MFTMirrLogicalClustNum;  // ��������� ������� ����� MFT
  char        chClustPerMFTRecord;    // ������ MFT ������ � ���������
  unsigned char    uchReserved0[3];
  char        chClustPerIndexRecord;    // ������ ��������� ������ � ���������
  unsigned char    uchReserved1[3];
  long long      n64VolumeSerialNum;      // ���������� �������� ����� ����
  unsigned int    dwChecksum;          // 
  }        bpb;              //
  char      chBootstrapCode[426];      // �����������-��� 
  unsigned short  wSecMark;            // ����� ������������ �������, ��������� 0xaa55 
}NTFS_PART_BOOT_SEC, *PNTFS_PART_BOOT_SEC;
#pragma pack(pop)

/*��������� ���� ������ �����*/
typedef struct VOLUME_LIST {
  VOLUME_LIST* next;      /*��������� �� ��������� ���� ������ �����*/
  NTFS_PART_BOOT_SEC* boot;  /*��������� �� ��������� BOOT ������� �������� ����*/
#if defined(_WINDOWS_)
  HANDLE File;  /*�������� ���������� ����, ��� ������ ������ � ����, ���� ��������� NULL ��� �� ��� ������*/
#elif defined(_UNIX_)
  int File;
#endif
  TCHAR  name[4];        /*����� ����*/
  unsigned char   error;
} VOLUME_LIST, *PVOLUME_LIST;

/*������� ������� ������ �����
  list - ��������� �� ��������� �� ������ �����*/
#if defined(_WINDOWS_)
  LIBNTFS
#endif
  void FreeVolumes(PVOLUME_LIST * list);

#if defined(_WINDOWS_)
  LIBNTFS
#endif
void SetPointer_Read(File * _file);

/*������� �������� ������ �����, ��������� ������������ �����, �� BOOT �������� � �� �����
  volume_list - ��������� �� ��������� �� ������ �����
  compare    - ��������� �� �������, ������� ��������� ��� ��������� ��������� ���� void �� �������� ������ ����� � ���������� ��������� ��������� (������������� �����, ������������� � ���� � ������ ��������� �� ������� ���������) 
  �������� ���������� ���������� ����� �������������� � �������*/
#if defined(_WINDOWS_)
  LIBNTFS
#endif
unsigned char GetVolumeInf(PVOLUME_LIST * volume_list, int(*compare)(void*, void*));

#if defined(_WINDOWS_)
  LIBNTFS NTFS_PART_BOOT_SEC * ReadNTFS_BOOT(void ** device, TCHAR* pathway);
#elif defined(_UNIX_)
  NTFS_PART_BOOT_SEC* ReadNTFS_BOOT(int * device, const char * pathway);
#endif

/*������� ��������� ���� ��������� ������ �����
  ��������� ��� ��������� ��������� ���� void �� �������� ������ ����� � ���������� ���������
  ���� ��������� �� ������������ ���������:
  ����� ������� ������ ���������� 0
  volume1 > volume2 ������� ������ ���������� ������������� �����
  volume1 < volume2 ������� ������ ���������� ������������� �����*/
#if defined(_WINDOWS_)
  LIBNTFS 
#endif
int CompareVolumes(void* volume1, void* volume2);
#endif 
