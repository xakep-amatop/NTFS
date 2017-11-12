#ifndef _FILETIME_to_String_
#define _FILETIME_to_String_

#include "stdafx.h"
/** str_buff_size constant is size of string buffer
*/
#define str_buff_size 0x20


#ifdef LIBNTFS_EXPORTS
<<<<<<< HEAD
  #define LIBNTFS __declspec(dllexport)
#else
  #define LIBNTFS __declspec(dllimport)
#endif

/*this value contains bit mask of error
  if bit 0 is set function GetTimeFormat fails
  if bit 1 is set function GetDateFormat fails
  if bit 2 is set function FileTimeToSystemTime fails
  if bit 3 is set function FileTimeToLocalFileTime fails
*/
#if defined(_WINDOWS_)
  LIBNTFS
#endif
  extern unsigned char error_filetime;

/** Function strft convert structure FILETIME to string
  \param
    _file_time  structure FILETIME has to convert to string
    mode    mode of output, if bit 1 in unsigned char mode is set, then write date in string buffer
          if bit 2 in unsigned char mode is set, then add time to string buffer
  \return
    pointer to string buffer
*/
#if  defined(_UNIX_)
  TCHAR * const strft(long long _file_time);
#elif defined(_WINDOWS_)
  LIBNTFS TCHAR * const strft(long long _file_time, unsigned char mode);
=======
	#define LIBNTFS __declspec(dllexport)
#else
	#define LIBNTFS __declspec(dllimport)
#endif

/*this value contains bit mask of error
	if bit 0 is set function GetTimeFormat fails
	if bit 1 is set function GetDateFormat fails
	if bit 2 is set function FileTimeToSystemTime fails
	if bit 3 is set function FileTimeToLocalFileTime fails
*/
#if defined(_WINDOWS_)
	LIBNTFS
#endif
	extern unsigned char error_filetime;

/** Function strft convert structure FILETIME to string
	\param
		_file_time	structure FILETIME has to convert to string
		mode		mode of output, if bit 1 in unsigned char mode is set, then write date in string buffer
					if bit 2 in unsigned char mode is set, then add time to string buffer
	\return
		pointer to string buffer
*/
#if  defined(_UNIX_)
	TCHAR * const strft(long long _file_time);
#elif defined(_WINDOWS_)
	LIBNTFS TCHAR * const strft(long long _file_time, unsigned char mode);
>>>>>>> 04369cdac075e42751460c7ba74939ade78eb23a
#endif
#endif
