/*
	Copyright (C) 2015 Kakorin Nikita
	Copyright (C) 2015 Zharkov Nikita
	Copyright (C) 2015 Betekhtin Artyoum
	Copyright (C) 2015 Korolev Evgeniy

	This file is part of Antivirus.

	Antivirus is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
*/

#include "antivirus.h"
#include <iostream>
#include <ctime>

bool Antivirus::isDirectoryExists(LPCWSTR directoryNameToCheck)
{
	DWORD dwordFileAttributes = GetFileAttributes(directoryNameToCheck);
	if (dwordFileAttributes == INVALID_FILE_ATTRIBUTES) return false;
	return dwordFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
}

bool Antivirus::isFileExists(LPCWSTR fileNameToCheck)
{
	return GetFileAttributes(fileNameToCheck) != INVALID_FILE_ATTRIBUTES;
}

LPCWSTR Antivirus::charToLpcwstr(const char* stringToConvert)
{
	wchar_t* result = new wchar_t[2048];
	MultiByteToWideChar(0, 0, stringToConvert, -1, result, 2048);
	return result;
}

Antivirus::PathTo Antivirus::isPathToFile(const char* stringToCheck)
{
	LPCWSTR path = charToLpcwstr(stringToCheck);

	if (isDirectoryExists(path))
	{
		return PathToFolder;
	}

	if (isFileExists(path))
	{
		return PathToFile;
	}

	return NotExist;
}

void Antivirus::ToScan(const char* inString)
{
	std::vector<std::string> folders;
	std::vector<std::string> files;
	
	switch (isPathToFile(inString))
	{
	case PathToFile:
		std::cout << std::endl << "Checking the file \"" << inString << "\"..." << std::endl; 

		if (analiz.Scanfile(inString))
		{
			std::cout << "File infected!\n" << std::endl;
			writeLog(inString, true);
		}
		else 
		{
			std::cout << "No viruses\n" << std::endl;
			writeLog(inString, false);
		} //temporary message
		
		break;
	case PathToFolder:

		//filling vector's of subfolders and files
		folders = SeeFilesFolders(inString).first;
	    files = SeeFilesFolders(inString).second;		
				
		for (int i = 0; i < folders.size();++i)
		{						
			ToScan(getFullNameFolder(folders.at(i),inString).data());
		}
		for (int i = 0; i < files.size(); ++i)
		{
			ToScan(getFullNameFile(files.at(i), inString).data());
		}			

		break;
	case NotExist:
		std::cout << std::endl << inString <<" : There is no such file or directory.\n";
		break;
	}
}

std::pair<std::vector<std::string>, std::vector<std::string>> Antivirus::SeeFilesFolders(const char* inString)
{
	std::vector<std::string> folders;
	std::vector<std::string> files;	
	GetFoldersAndFilesList((std::string)(inString), folders, files);
	return std::make_pair(folders,files);
}

std::string Antivirus::getFullNameFile(const std::string& fName, const char* inString)const
{
	std::string tmp = (std::string)(inString) + fName;
	return tmp;
}

std::string Antivirus::getFullNameFolder(const std::string& fName, const char* inString)const
{
	std::string tmp = (std::string)(inString) + fName + "\\";
	return tmp;
}

void Antivirus::startLoging(std::ofstream &file)
{
	file.open("Log.txt", std::ios::app);
}

void Antivirus::endLoging(std::ofstream &file)
{
	file.close();
}

char* Antivirus::getCurrentDateAndTime(char *currentDateAndTimeStr)
{
	time_t rawtime;
	tm timeinfo;
	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	asctime_s(currentDateAndTimeStr, 26, &timeinfo);
	return currentDateAndTimeStr;
}

void Antivirus::writeLog(const char* fileName, bool infected)
{
	startLoging(OutLog);
	//loging here	
	char currentDateAndTimeStr[26];	
	OutLog << fileName << (infected ? " : infected " : " : safe ") << getCurrentDateAndTime(currentDateAndTimeStr) << '\n';
	//loging here
	endLoging(OutLog);
}

void Antivirus::GetFoldersAndFilesList(std::string path,
	std::vector<std::string> &folders,
	std::vector<std::string> &files)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hf;
	path += "/*";
	int len;
	int slength = (int)path.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, path.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, path.c_str(), slength, buf, len);
	std::wstring stemp(buf);
	delete[] buf;
	LPCWSTR result = stemp.c_str();
	hf = FindFirstFile(result, &FindFileData);
	if (hf != INVALID_HANDLE_VALUE) {
		do {
			std::wstring wfilename(FindFileData.cFileName);
			std::string sfilename(wfilename.begin(), wfilename.end());
			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				if (sfilename != "." && sfilename != "..") {
					folders.push_back(sfilename);
				}
			}
			else {
				files.push_back(sfilename);
			}
		} while (FindNextFile(hf, &FindFileData) != 0);
		FindClose(hf);
	}
}

void Antivirus::outMessageToUser(const std::string& message)
{
	std::cout << message;
}

bool Antivirus::isThisCommand(const std::string& message, const char* consoleArgument)
{
	return message == consoleArgument;
}

//--------------------------------------Signature Analyzer

Antivirus::SignatureAnalyzer::SignatureAnalyzer()
{
	ScanType = SCAN_FLAGS_FAST_MODE;
	Librarry_file = "C:\\Antivirus\\SignaturesDB";
}

Antivirus::SignatureAnalyzer::~SignatureAnalyzer()
{

}

int Antivirus::SignatureAnalyzer::SetScanType(int ScanType)
{
	return (ScanType == NULL) ? NULL : SCAN_FLAGS_FAST_MODE;
}

/*
this func compile signatures.yara to db of signatures that we would use
*/
char * Antivirus::SignatureAnalyzer::SetLibrarry_file(char * filename)
{
	FILE* rule_1;

	fopen_s(&rule_1, "rule1.yara", "r");

	YR_COMPILER* cmplr = NULL;

	YR_RULES* rules = NULL;

	yr_initialize();

	yr_compiler_create(&cmplr);

	printf("%d", yr_compiler_add_file(cmplr, rule_1, NULL, "text"));

	yr_compiler_get_rules(cmplr, &rules);

	yr_rules_save(rules, filename);

	yr_rules_destroy(rules);
	yr_compiler_destroy(cmplr);
	yr_finalize();
	return filename;
}
int CALLBACK_MSG_FILE = 0;

int callback_function_forfile(int message, void* message_data, void* user_data)
{
	CALLBACK_MSG_FILE = 0;
	if (message == CALLBACK_MSG_RULE_MATCHING)
	{
		CALLBACK_MSG_FILE = 1;
		return CALLBACK_ABORT;
	}
	return CALLBACK_CONTINUE;
}

int Antivirus::SignatureAnalyzer::Scanfile(const char * filename)
{
	yr_initialize();
	YR_RULES* rules = NULL;
	yr_rules_load(Librarry_file, &rules);
	if (ERROR_CALLBACK_ERROR == yr_rules_scan_file(rules, filename, ScanType, callback_function_forfile, NULL, 0))
		printf("%d", 777);
	yr_finalize();

	return CALLBACK_MSG_FILE;
}

