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

void Antivirus::ToScan(const char* inString, SignatureAnalyzer analiz)
{
	std::vector<std::string> folders;
	std::vector<std::string> files;
	std::string tmp;
	switch (isPathToFile(inString))
	{
	case PathToFile:
		std::cout << "Checking the file \"" << inString << "\"..." << std::endl; 

		if (analiz.Scanfile(inString))
			std::cout << "File infected!\n" << std::endl;	
		else {
			std::cout << "No viruses\n" << std::endl;
		} //temporary message
		break;
	case PathToFolder:
		GetFoldersAndFilesList((std::string)(inString), folders, files);
		//std::cout << "Checking the foulder \"" << inString << "\"..." << std::endl;
				
		for (int i = 0; i < folders.size();++i)
		{
			tmp = inString + folders.at(i) + "\\";
			ToScan(tmp.data(), analiz);
		}
		for (int i = 0; i < files.size(); ++i)
		{
			tmp = inString+files.at(i);
			ToScan(tmp.data(), analiz);
		}			
		break;
	case NotExist:
		std::cout << inString <<" : There is no such file or directory.\n";
		break;
	}
}

void Antivirus::startLoging(std::ofstream &file)
{
	file.open("Log.txt");
}

void Antivirus::endLoging(std::ofstream &file)
{
	file.close();
}

char* getCurrentDateAndTime(char *currentDateAndTimeStr)
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
	OutLog << fileName << (infected ? " : infected" : " : safe") << getCurrentDateAndTime(currentDateAndTimeStr) << '\n';
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