/*
	Copyright (C) 2015 Kakorin Nikita
	Copyright (C) 2015 Zharkov Nikita
	Copyright (C) 2015 Betekhtin Artyoum
	Copyright (C) 2015 Korolev Evgeniy

	This file is part of Flemming.

	Flemming is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
*/

#include <iostream>
#include <SignatureAnalyzer.h>
#include <omp.h>

std::string SignatureAnalyzer::getFullNameFile(const std::string& fName, const char* inString)const
{
	std::string tmp = (std::string)(inString) + fName;
	return tmp;
}
Logger* SignatureAnalyzer::log = new Logger;

SignatureAnalyzer::SignatureAnalyzer()
{	
	ScanType = SCAN_FLAGS_FAST_MODE;
	Librarry_file = "C:\\Antivirus\\SignaturesDB";	
}

SignatureAnalyzer::~SignatureAnalyzer()
{

}

int SignatureAnalyzer::SetScanType(int ScanType)
{
	return (ScanType == NULL) ? NULL : SCAN_FLAGS_FAST_MODE;
}

char SignatureAnalyzer::signatureName[128] = {};
int SignatureAnalyzer::CALLBACK_MSG_FILE = 0;

int SignatureAnalyzer::callback_function_forfile(int message, void* message_data, void* user_data)
{
	CALLBACK_MSG_FILE = 0;
	if (message == CALLBACK_MSG_RULE_MATCHING)
	{
		CALLBACK_MSG_FILE = 1;
		strcpy_s(signatureName, (*((YR_RULE*)message_data)).identifier);
		return CALLBACK_ABORT;
	}		
	return CALLBACK_CONTINUE;
}

int SignatureAnalyzer::Scanfile(const char * filename, std::vector<std::string> files)
{
	yr_initialize();
	YR_RULES* rules = NULL;
	yr_rules_load(Librarry_file, &rules);
	std::string h;

#pragma omp parallel firstprivate(CALLBACK_MSG_FILE, signatureName,log, h)
	{
#pragma omp for ordered
		for (int i = 0; i < files.size(); ++i)
		{
			h = getFullNameFile(files.at(i), filename);
			yr_rules_scan_file(rules, h.data(), ScanType, callback_function_forfile, NULL, 0);
#pragma omp ordered
			log->writeLog(h.data(), (CALLBACK_MSG_FILE ==1 ? true : false), signatureName);
		}
	}
	yr_finalize();
	return CALLBACK_MSG_FILE;
}
