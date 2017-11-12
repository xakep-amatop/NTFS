#include "stdafx.h"

unsigned char error_filetime;

/** Unicode string buffer for save FILETIME,
  static means that buffer visible only in this file
*/
static TCHAR Str_Buff[str_buff_size];

#ifdef _WINDOWS_

/** Function Convert_FT_ST converts structure FILETIME to structure SYSTEMFILE, visible only in this file
  \param
    _file_time  long pointer of structure FILETIME
    sys_time  long pointer of structure SYSTEMTIME 

  Pointers use less stack memory, then sum sizes of all items in structures.
  Note: But because are transfered not copy of structures, they will be changed in this function
*/
inline static void Convert_FT_ST(LPFILETIME _file_time, LPSYSTEMTIME sys_time) {
  /*Converts a file time to local file time*/
  if (!FileTimeToLocalFileTime(_file_time, _file_time)) {
    error_filetime |= 0x8; /*function FileTimeToLocalFileTime do not perform right*/
  }
  /*Converts a local file time to system time formate*/
  else if (!FileTimeToSystemTime(_file_time, sys_time)) {
    error_filetime |= 0x4; /*function FileTimeToSystemTime do not perform right, set bit in error*/
  }
}

TCHAR * const strft(FILETIME _file_time, unsigned char mode) {
  SYSTEMTIME sys_time;
  Convert_FT_ST(&_file_time, &sys_time);
  if (!(error_filetime & 0xc)) {
    unsigned char _len = 0x00; /*/ amount of keeping symbols in the buffer*/
    mode &= 0x7f;
    if (mode & 0x01) {
      /* Store date in the buffer */
      if (GetDateFormat(LOCALE_USER_DEFAULT, DATE_SHORTDATE, &sys_time, NULL, Str_Buff, str_buff_size) == -1)
        error_filetime |= 0x2;
      mode |= 0x08;
    }
    if (mode & 0x02) {
      if (mode & 0x08) {
        _len = lstrlen(Str_Buff);
        Str_Buff[_len++] = _T(' ');
      }
      /* Store (add) time to the buffer */
      if (GetTimeFormat(LOCALE_USER_DEFAULT, 0, &sys_time, NULL, (Str_Buff + _len), (str_buff_size - _len)) == -1)
        error_filetime |= 0x1;
    }
    return Str_Buff;
  }
  return NULL;
}
#elif _UNIX_
  #include <time.h>

  #define TICKS_PER_SECOND 10000000
  #define EPOCH_DIFFERENCE 11644473600LL

  inline static time_t convertWindowsTimeToUnixTime(long long input){
     return (time_t)(input / TICKS_PER_SECOND //convert from 100ns intervals to seconds;
        - EPOCH_DIFFERENCE);  //subtract number of seconds between epochs
  }
  
  TCHAR * const strft(long long _file_time) {
    time_t _filetime = convertWindowsTimeToUnixTime(_file_time);
    #ifdef _UNICODE
    wcsftime(Str_Buff, 20, L"%Y-%m-%d %H:%M:%S", localtime(&_filetime));
    #else    
    strftime(Str_Buff, 20, "%Y-%m-%d %H:%M:%S", localtime(&_filetime));
    #endif
    return Str_Buff;
  }
  
#endif
