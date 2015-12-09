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
#include "Flemming\Flemming.h"
#include "Flemming\Logger.h"
#include <ctime>

SignatureAnalyser* Flemming::analyser = new SignatureAnalyser;
Quarantine* Flemming::quarantiner = new Quarantine(GetConsoleWindow());

bool Flemming::isDirectoryExists(LPCWSTR directoryNameToCheck)
{
	DWORD dwordFileAttributes = GetFileAttributes(directoryNameToCheck);
	if (dwordFileAttributes == INVALID_FILE_ATTRIBUTES) return false;
	return dwordFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
}

bool Flemming::isFileExists(LPCWSTR fileNameToCheck)
{
	return GetFileAttributes(fileNameToCheck) != INVALID_FILE_ATTRIBUTES;
}

LPCWSTR Flemming::charToLpcwstr(const char* stringToConvert)
{
	wchar_t* result = new wchar_t[2048];
	MultiByteToWideChar(0, 0, stringToConvert, -1, result, 2048);
	return result;
}

Flemming::PathTo Flemming::isPathToFile(const char* stringToCheck)
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
Logger* logger = new Logger;

void Flemming::ToScan(const char* inString, bool scantype)
{
	std::vector<std::string> folders;
	std::vector<std::string> files;
	std::pair<std::vector<std::string>, std::vector<std::string>> subFilesFolders = std::make_pair(folders, files);
	std::vector<std::string> filesToQuarantine;
	switch (isPathToFile(inString))
	{
	case PathToFile:
		//std::cout << "Checking the file \"" << inString << "\t";
		analyser->ScanSingleFile(inString);
		break;
	case PathToFolder:

		subFilesFolders = SeeFilesFolders(inString);
		for (int i = 0; i < subFilesFolders.first.size();++i)
		{
			ToScanWoCheck(getFullNameFolder(subFilesFolders.first.at(i), inString).data(), scantype);
			
		}		
			analyser->Scanfile(inString, subFilesFolders.second, scantype);


		break;
	case NotExist:
		//std::cout << std::endl << inString << " : There is no such file or directory.\n";
		break;
	}
}

void Flemming::ToScanWoCheck(const char* inString, bool scantype)
{
	std::vector<std::string> folders;
	std::vector<std::string> files;
	std::pair<std::vector<std::string>, std::vector<std::string>> subFilesFolders = std::make_pair(folders, files);

    subFilesFolders = SeeFilesFolders(inString);

		for (int i = 0; i < subFilesFolders.first.size();++i)
		{
			ToScanWoCheck(getFullNameFolder(subFilesFolders.first.at(i), inString).data(), scantype);
		}
		analyser->Scanfile(inString, subFilesFolders.second, scantype);
	
}

std::pair<std::vector<std::string>, std::vector<std::string>> Flemming::SeeFilesFolders(const char* inString)
{
	std::vector<std::string> folders;
	std::vector<std::string> files;
	GetFoldersAndFilesList((std::string)(inString), folders, files);
	return std::make_pair(folders, files);
}

std::string Flemming::getFullNameFile(const std::string& fName, const char* inString)
{
	std::string tmp = (std::string)(inString) + fName;
	return tmp;
}

std::string Flemming::getFullNameFolder(const std::string& fName, const char* inString)
{
	std::string tmp = (std::string)(inString) + fName + "\\";
	return tmp;
}

void Flemming::GetFoldersAndFilesList(std::string path,
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

void Flemming::outMessageToUser(const std::string& message)
{
	printf(message.data());
}

bool Flemming::isThisCommand(const std::string& message, const char* consoleArgument)
{
	return message == consoleArgument;
}

Flemming::Flemming()
{
	
}

Flemming::~Flemming()
{

}

void Flemming::ScanMemory()
{
	analyser->ScanMem();	
}

std::string Flemming::getSystemDirectory() {
	const UINT size = 300; // consistent value
	TCHAR infoBuf[size];
	std::string ret;
	if (!GetWindowsDirectory(infoBuf, size)) {
		throw ERROR("failed to get windows directory");
	}
	else {
		for (int i = 0;i < size; ++i) {
			if (!infoBuf[i]) {
				break;
			}
			else {
				ret += char(infoBuf[i]);
			}
		}
	}
	return (ret + "\\");
}

void Flemming::ScanSystemFolder()
{
	try {
		ToScan(getSystemDirectory().data(),false);
	}
	catch (const char* e)
	{
		std::cout << e;
	}
}

void Flemming::ToScanWithQ(const char* inString, bool scantype)
{
	ToScan(inString, scantype);

	std::vector<std::string> filesToQuarantine = logger->GetAllSuspectedFiles();
	if (!filesToQuarantine.empty())
	{
		for (int i = 0;i < filesToQuarantine.size();++i)
		{
			quarantiner->putToQuarantine(filesToQuarantine.at(i));
			//std::cout << filesToQuarantine.at(i) << std::endl;
		}
		quarantiner->CrypterQuarantineFiles(SeeFilesFolders, getFullNameFile);
	}
}

void Flemming::ToScanDesc(const char* inString)
{
	std::vector<std::string> folders;
	std::vector<std::string> files;
	std::pair<std::vector<std::string>, std::vector<std::string>> subFilesFolders = std::make_pair(folders, files);

	subFilesFolders = SeeFilesFolders(inString);

	for (int i = 0; i < subFilesFolders.first.size();++i)
	{
		ToScanDesc(getFullNameFolder(subFilesFolders.first.at(i), inString).data());
	}
	analyser->ScanDescriptor(inString, subFilesFolders.second, charToLpcwstr);
}