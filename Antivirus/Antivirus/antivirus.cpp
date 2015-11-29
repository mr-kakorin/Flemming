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
#include <iostream>
#include "antivirus.h"
#include <ctime>

SignatureAnalyzer* Antivirus::analyzer = new SignatureAnalyzer;

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
	std::pair<std::vector<std::string>, std::vector<std::string>> subFilesFolders = std::make_pair(folders, files);

	switch (isPathToFile(inString))
	{
	case PathToFile:
		std::cout << "Checking the file \"" << inString << "\t";
		break;
	case PathToFolder:

		subFilesFolders = SeeFilesFolders(inString);

		for (int i = 0; i < subFilesFolders.first.size();++i)
		{
			ToScan(getFullNameFolder(subFilesFolders.first.at(i), inString).data());
		}		
			analyzer->Scanfile(inString, subFilesFolders.second);	
		break;
	case NotExist:
		//std::cout << std::endl << inString << " : There is no such file or directory.\n";
		break;
	}
}

std::pair<std::vector<std::string>, std::vector<std::string>> Antivirus::SeeFilesFolders(const char* inString)
{
	std::vector<std::string> folders;
	std::vector<std::string> files;
	GetFoldersAndFilesList((std::string)(inString), folders, files);
	return std::make_pair(folders, files);
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
	printf(message.data());
}

bool Antivirus::isThisCommand(const std::string& message, const char* consoleArgument)
{
	return message == consoleArgument;
}

Antivirus::Antivirus()
{
	
}

Antivirus::~Antivirus()
{

}