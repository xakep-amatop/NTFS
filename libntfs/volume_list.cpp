#include "stdafx.h"

/*если бит 0 установлен ошибка в CloseHandle
  если бит 1 установлен ошибка в CreateFile
  если бит 2 установлен ошибка в ReadFile
  если бит 3 установлен ошибка в SetFilePointer
  если бит 4 установлен несоответсвие количества считаных данных и количества в запросе на считывание*/
unsigned char error_volume;

int CompareVolumes(void* volume1, void* volume2) {
	return -1;
}

void FreeVolumes(PVOLUME_LIST * list) {
	PVOLUME_LIST tmp;
	while ((PVOLUME_LIST)*list) {
		tmp = (PVOLUME_LIST)*list;
		*list = ((PVOLUME_LIST)*list)->next;
		if (tmp->boot)
			free(tmp->boot);
		if (tmp->name)
			free(tmp->name);
		if (tmp->File)
#if defined(_WINDOWS_)
			CloseHandle(tmp->File);
#elif defined(_UNIX_)
			close(tmp->File);
#endif
		free(tmp);
	}
}

#if defined(_WINDOWS_)
void SetPointer_Read(File * _file) {
	if (SetFilePointer(_file->hFile, _file->llDistanceToMove.n32.low, &(_file->llDistanceToMove.n32.high), _file->MoveMethod) == INVALID_SET_FILE_POINTER)
		error_volume |= 0x8;
	if (!ReadFile(_file->hFile, _file->lpBuffer, _file->ulNumberBytesToRead, &(_file->ulNumberOfBytesRead), NULL)){
		perror("ReadFile:");
		error_volume |= 0x4;
	}
	else if (_file->ulNumberBytesToRead != _file->ulNumberOfBytesRead)	error_volume |= 0x10;
}

/*Функция чтения BOOT сектора тома
  device  - указатель на дескриптор открытого тома, NULL если ошибка
  pathway - имя тома который нужно открыть
  Функция возвращает указатель на структуру BOOT сектора*/
NTFS_PART_BOOT_SEC* ReadNTFS_BOOT(void ** device, TCHAR* pathway) {
	File A;
	A.MoveMethod			= FILE_BEGIN;
	A.llDistanceToMove.n64	= 0ll;
	A.lpBuffer				= (NTFS_PART_BOOT_SEC*)malloc(sizeof(NTFS_PART_BOOT_SEC));
	A.ulNumberBytesToRead	= sizeof(NTFS_PART_BOOT_SEC);
	if (!A.lpBuffer) return NULL;
	*device					= CreateFile(pathway, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,	NULL, OPEN_EXISTING, 0, NULL);
	if (*device == INVALID_HANDLE_VALUE) {
		error_volume |= 0x2;
		free(A.lpBuffer);
		return NULL;
	}
	A.hFile = *device;
	SetPointer_Read(&A);
	if (error_volume & 0xfd) {
		if (!CloseHandle(*device))
			error_volume |= 0x1;
		free(A.lpBuffer);
		return NULL;

	}
	return (NTFS_PART_BOOT_SEC*)(A.lpBuffer);
}

unsigned char GetVolumeInf(PVOLUME_LIST * volume_list, int (*compare)(void*, void*)) {
	unsigned char number_volumes = 0;
	TCHAR buf[] = _T("\\\\.\\ :");
	PVOLUME_LIST current_volume, volume_list_end = NULL;
	unsigned int BitDevices = GetLogicalDrives();
	for (unsigned char i = 0; BitDevices && i < 32; i++) {
		if (BitDevices & 0x01) {
			TCHAR vol_name = _T('A') + i;
			current_volume = (PVOLUME_LIST)calloc(1, sizeof(VOLUME_LIST));
			buf[4] = vol_name;
			memcpy(current_volume->name, buf+4,sizeof(TCHAR)*2);
			current_volume->name[2] = TCHAR('\\');
			current_volume->name[3] = TCHAR('\0');
			current_volume->boot = ReadNTFS_BOOT(&(current_volume->File), buf);
			current_volume->error = error_volume;
			error_volume ^= error_volume;
			AddItemList((List*)current_volume, (List**)volume_list, (List**)&volume_list_end, compare);
			number_volumes++;
		}
		BitDevices = (BitDevices >> 1);
	}
	return number_volumes;
}

#elif defined(_UNIX_)
void SetPointer_Read(File * _file) {
	off_t offset = _file->llDistanceToMove.n64; 
	if (lseek(_file->hFile, _file->llDistanceToMove.n64, _file->MoveMethod) == -1)
		error_volume |= 0x8;
	if ((_file->ulNumberOfBytesRead = read(_file->hFile, _file->lpBuffer, _file->ulNumberBytesToRead)) == -1)
		error_volume |= 0x4;
	else if (_file->ulNumberBytesToRead != _file->ulNumberOfBytesRead)      error_volume |= 0x10;
}

NTFS_PART_BOOT_SEC* ReadNTFS_BOOT(int * device, const char * pathway) {
	File A;
	A.MoveMethod = SEEK_SET;
	A.llDistanceToMove.n64 = 0LL;
	A.lpBuffer = (NTFS_PART_BOOT_SEC*)malloc(sizeof(NTFS_PART_BOOT_SEC));
	A.ulNumberBytesToRead = sizeof(NTFS_PART_BOOT_SEC);
	if (!A.lpBuffer) return NULL;
	*device = open(pathway, O_RDONLY);
	if (*device == -1) {
		error_volume |= 0x2;
		free(A.lpBuffer);
		return NULL;
	}
	A.hFile = *device;
	SetPointer_Read(&A);
	if (error_volume & 0xfd) {
		if (close(*device) == -1)
			error_volume |= 0x1;
		free(A.lpBuffer);
		return NULL;
	}
	return (NTFS_PART_BOOT_SEC*)(A.lpBuffer);
}

unsigned char GetVolumeInf(PVOLUME_LIST * volume_list, int (*compare)(void*, void*)) {
	unsigned char number_volumes = 0;
	
	return number_volumes;
}

#endif
