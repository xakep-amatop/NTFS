// ntfs.cpp: главный файл проекта.

#include "stdafx.h"
#include "Form1.h"

using namespace ntfs;

#include <strft.h>
#include <stdlib.h>

[STAThreadAttribute]
int main(array<System::String ^> ^args){
	//unsigned char a = error_filetime;

	// Включение визуальных эффектов Windows XP до создания каких-либо элементов управления
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Создание главного окна и его запуск
	Application::Run(gcnew Form1());
	return 0;
}