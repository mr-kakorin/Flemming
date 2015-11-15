#pragma once
#include "yara.h"
class SignatureAnalyzer
{
public:
	SignatureAnalyzer();
	~SignatureAnalyzer();
	int Scanfile(const char *);
	char* SetLibrarry_file(char *);
private:
	int ScanType;
	char *Librarry_file;
	int SetScanType(int);
	
	friend int callback_function_forfile(int, void*, void*);
};

