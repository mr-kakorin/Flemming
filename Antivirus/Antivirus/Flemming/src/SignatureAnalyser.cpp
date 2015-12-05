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
#include "Flemming\SignatureAnalyser.h"

const char* SignatureAnalyser::getFullNameFile(const std::string& fName, const char* inString)const
{
	char buf[128];
	strcpy(buf, inString);
	strcat(buf, fName.data());
	return buf;
}

Logger* SignatureAnalyser::log = new Logger;
ExtensionAnalyser* SignatureAnalyser::extAnalyser = new ExtensionAnalyser;

SignatureAnalyser::SignatureAnalyser()
{	
	ScanType = SCAN_FLAGS_FAST_MODE;
	Librarry_file = "C:\\Antivirus\\SignaturesDB";	
}

SignatureAnalyser::~SignatureAnalyser()
{

}


char SignatureAnalyser::signatureName[128] = {};
int SignatureAnalyser::CALLBACK_MSG_FILE = 0;

int SignatureAnalyser::callback_function_forfile(int message, void* message_data, void* user_data)
	{		
		CALLBACK_MSG_FILE = 0;
		strcpy_s(signatureName, "");
		if (!message_data) return CALLBACK_MSG_SCAN_FINISHED;		
		if (message == CALLBACK_MSG_RULE_MATCHING)
		{
			CALLBACK_MSG_FILE = 1;			
			strcpy_s(signatureName, (*((YR_RULE*)message_data)).identifier);
			return CALLBACK_ABORT;
		}
		return CALLBACK_CONTINUE;
}

int SignatureAnalyser::Scanfile(const char * pathToFile, std::vector<std::string> files)
{
	yr_initialize();
	YR_RULES* rules = NULL;
	yr_rules_load(Librarry_file, &rules);
	std::string h;
	const char* str;
	int count = files.size();
		for (int i = 0; i < count; ++i)
		{			
			//if (extAnalyser->checkExtension(files.at(i).data()))
			//{
				str = getFullNameFile(files.at(i), pathToFile);
				yr_rules_scan_file(rules, str, ScanType, callback_function_forfile, NULL, 0);
				log->writeLog(str, (CALLBACK_MSG_FILE ? true : false), signatureName);
				
			//}
		}	
	yr_finalize();
	return CALLBACK_MSG_FILE;
}

int SignatureAnalyser::callback_function_formem(int message, void* message_data, void* user_data)
{
	if (!message_data) return CALLBACK_MSG_SCAN_FINISHED;
	CALLBACK_MSG_FILE = 0;	
	if (message == CALLBACK_MSG_RULE_MATCHING)
	{
		CALLBACK_MSG_FILE = 1;
		
		return CALLBACK_ABORT;
	}
	
	return CALLBACK_CONTINUE;
}

int SignatureAnalyser::ScanMem()
{
	yr_initialize();
	YR_RULES* rules = NULL;
	yr_rules_load(Librarry_file, &rules);
	uint8_t* buffer = new uint8_t[1024];
	yr_rules_scan_mem(rules, buffer, 1024, 0, callback_function_formem, NULL, 0);
	yr_finalize();
	return 0;
}

int SignatureAnalyser::ScanSingleFile(const char * pathToFile)
{
	yr_initialize();
	YR_RULES* rules = NULL;
	yr_rules_load(Librarry_file, &rules);
	yr_rules_scan_file(rules, pathToFile, ScanType, callback_function_forfile, NULL, 0);
	yr_finalize();
	log->writeLog(pathToFile, (CALLBACK_MSG_FILE == 1 ? true : false), signatureName);
	return CALLBACK_MSG_FILE;
}