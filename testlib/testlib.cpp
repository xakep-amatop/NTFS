#include <stdlib.h>
#include <stdio.h>

#include <stdafx.h>

PVOLUME_LIST a;

PFILE_LIST read_mft(TCHAR * const _letter) {
		PVOLUME_LIST tmp = a;

		while(tmp && wcscmp(tmp->name, _letter)){
			tmp = tmp->next;
		}

		if (tmp){
			PFILE_LIST fl;
			if (tmp && tmp->boot) {
				if (!Check_NTFS(tmp->boot)) {
					INT32(*comp[3])(VOID*, VOID*);
					comp[0] = CompareFiles;
					comp[1] = CompareStreams;
					comp[2] = CompareFragments;
					fl = ReadMFT(tmp->File, tmp->boot, 1024, comp);
				}
			}
			return fl;
		}
}

int main(){
	GetVolumeInf(&a, CompareVolumes);
	PFILE_LIST _mft = read_mft(_T("C:\\"));

	FILE * out = fopen("out.txt", "w");

	PFILE_LIST  tmp_list = _mft;

	while (tmp_list){
		fprintf(out,"%lu:\t%", tmp_list->dwMFT_Number);
		if (tmp_list->pHard_link){
			const unsigned int len	= tmp_list->pHard_link->bNameLength;
			const wchar_t * start	= tmp_list->pHard_link->pwName;
			wchar_t * ptr			= (wchar_t*)start; 
			while (ptr != len + start + 1){
				fputwc(*ptr, out);
				++ptr;
			}
		}
		fputwc(L'\n', out);
		fflush(out);
		tmp_list = tmp_list->next;
	}
	fclose(out);
	unsigned char k = error_ntfs;
	k++;
}