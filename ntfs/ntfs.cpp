// ntfs.cpp: ������� ���� �������.

#include "stdafx.h"
#include "Form1.h"

using namespace ntfs;

#include <strft.h>
#include <stdlib.h>

[STAThreadAttribute]
int main(array<System::String ^> ^args){
	//unsigned char a = error_filetime;

	// ��������� ���������� �������� Windows XP �� �������� �����-���� ��������� ����������
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// �������� �������� ���� � ��� ������
	Application::Run(gcnew Form1());
	return 0;
}