#pragma once
#include "yara.h"
class signature_analyzer
{
public:
	signature_analyzer();
	~signature_analyzer();
	int Scanfile(const char *);
	char* SetLibrarry_file(char *);
private:
	int ScanType;
	char *Librarry_file;
	int SetScanType(int);
	
	friend int callback_function_forfile(int, void*, void*);
};

