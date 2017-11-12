#ifndef __ntfs_h__
#define __ntfs_h__

#include "stdafx.h"

#ifdef LIBNTFS_EXPORTS
  #define LIBNTFS __declspec(dllexport)
#else
  #define LIBNTFS __declspec(dllimport)
#endif

#if defined(_WINDOWS_)
  LIBNTFS 
#endif
  extern unsigned char    error_ntfs;
#if defined(_WINDOWS_)
  LIBNTFS 
#endif
  extern unsigned long long  count_mfts; // for progress bar
#if defined(_WINDOWS_)
  LIBNTFS 
#endif
  extern unsigned long long  NumberMFTRecords;

enum status_attribute{
  WAS_NOTHING               = 0x00,
  WAS_STANDARD_INFORMATION  = 0x01,
  WAS_FILENAME              = 0x02,
  WAS_STREAM                = 0x04,
};

typedef struct info{
  PSTREAM_LIST          StreamListBegin; 
  PSTREAM_LIST          StreamListEnd;
  PSTREAM_LIST          StreamListTmp;

  PFRAGMENT_LIST        FragmentListBegin; 
  PFRAGMENT_LIST        FragmentListEnd;
  PFRAGMENT_LIST        mft_bits;

  PHARD_LINK            hard_link;

  PNTFS_ATTRIBUTE       attr_ntfs;

  PNTFS_MFT_FILE        mft_file;

  PNTFS_PART_BOOT_SEC   ntfs_boot;

  PFILE_LIST            FileListBegin;
  PFILE_LIST            FileListEnd;
  PFILE_LIST            FileListTmp;

  int  (*comp[3])(void*, void*);

  long long             num_MFT;
  unsigned char         was_attr;
  unsigned short        count_hl;
} info;


typedef struct HARD_LINK {
  unsigned char      bNameType;
  unsigned char      bNameLength;
  wchar_t*        pwName;
} HARD_LINK, *PHARD_LINK;

typedef struct HARD_LINK_LIST {
  HARD_LINK * next;
  HARD_LINK   _hl;
}HARD_LINK_LIST, * PHARD_LINK_LIST;

typedef struct FRAGMENT_LIST {
  FRAGMENT_LIST*  next;
  long long    First_Cluster;
  unsigned long long  Length;
}FRAGMENT_LIST, *PFRAGMENT_LIST;

typedef struct STREAM_LIST {
  STREAM_LIST*  next;
  long long  qwRealSize;
  FRAGMENT_LIST*  fragment_list;
} STREAM_LIST, *PSTREAM_LIST;

typedef struct FILE_LIST {
  FILE_LIST*  next;
  unsigned long  dwMFT_Number;
  unsigned short  wAttribute;
  unsigned short  wHardLinks;
  HARD_LINK*  pHard_link;
  long long  n64CreationTime;
  STREAM_LIST*  stream_list;
}FILE_LIST, *PFILE_LIST;

/*LIST OF FUNCTIONS PROTOTYPES*/

/**/
#if defined(_WINDOWS_)
  LIBNTFS 
#endif
  NTFS_PART_BOOT_SEC* ReadNTFS_BOOT(void ** device, TCHAR* pathway);

#if defined(_WINDOWS_)
  LIBNTFS 
#endif
  unsigned char Check_NTFS(NTFS_PART_BOOT_SEC* ntfs_boot);

/**/
#if defined(_WINDOWS_)
  LIBNTFS 
#endif
  PFILE_LIST ReadMFT(HANDLE device, NTFS_PART_BOOT_SEC* ntfs_boot, unsigned int buffer_size, int(*comp[3])(void*, void*));

/*������� ��������� ���� �������� ������� NTFS, ���������� ������ ������ ���������� �������
  stream1 - ��������� �� ��������� ������ 1
  stream2 - ��������� �� ��������� ������ 2
  ������� ���������� <0 ���� ����� ������� ��������� ������ 1 ������ ������ ������� ��������� ������ 2
  ������� ���������� >0 ���� ����� ������� ��������� ������ 1 ������ ������ ������� ��������� ������ 2
  ������� ����������  0 ���� ����� ������� ��������� ������ 1 �����  ������ ������� ��������� ������ 2*/
#if defined(_WINDOWS_)
  LIBNTFS 
#endif
  int CompareStreams(void* stream1, void* stream2);

/*������� ��������� ���� �������� ���������� NTFS
  fragment1 - ��������� �� �������� 1
  fragment2 - ��������� �� �������� 2
  ������� ���������� <0 ���� ����� ��������� 1 ������ ������ ��������� 2
  ������� ���������� >0 ���� ����� ��������� 1 ������ ������ ��������� 2
  ������� ����������  0 ���� ����� ��������� 1 �����  ������ ��������� 2*/
#if defined(_WINDOWS_)
  LIBNTFS 
#endif
  int CompareFragments(void* fragment1, void* fragment2);

/*������� ��������� ���� �������� ������
  file1 - ��������� �� ��������� FILE_LIST ����� 1
  file2 - ��������� �� ��������� FILE_LIST ����� 2
  ������� ���������� <0 ���� ����� ������ MFT �a��� 1 ������ ������ ������ MFT �a��� 2
  ������� ���������� >0 ���� ����� ������ MFT �a��� 1 ������ ������ ������ MFT �a��� 2
  ������� ����������  0 ���� ����� ������ MFT �a��� 1 �����  ������ ������ MFT �a��� 2*/
#if defined(_WINDOWS_)
  LIBNTFS 
#endif
  int CompareFiles(void* file1, void* file2);

/*������� ������� ������ ����������
  list - ��������� �� ��������� �� ������ ����������
  ����� ������ list = NULL*/
#if defined(_WINDOWS_)
  LIBNTFS 
#endif
  void FreeFragments(PFRAGMENT_LIST * list);

/*������� ������� ������ �������
  list - ��������� �� ��������� �� ������ �������
  ����� ������ list = NULL*/
#if defined(_WINDOWS_)
  LIBNTFS
#endif
  void FreeStreams(PSTREAM_LIST * list);

/*������� ������� ������ ������
  list - ��������� �� ��������� �� ������ ������
  ����� ������ list = NULL*/
#if defined(_WINDOWS_)
  LIBNTFS
#endif
  void FreeFiles(PFILE_LIST * list);
#endif
