#include "antivirus.h"
#include <iostream>


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

const char* Antivirus::AskArguments()
{
	std::cout<<"Input path to folder or file to scan:";
	char* inString = new char[128];
	std::cin.getline(inString,127);
	return inString;
}

Antivirus::PathTo Antivirus::isPathToFile(const char* stringToCheck)
{
	LPCWSTR path = charToLpcwstr(stringToCheck);
	if (isFileExists(path))
	{
		return PathToFile;
	}	
	
	if (isDirectoryExists(path))
	{
		return PathToFolder;
	}	
	return NotExist;
}

void Antivirus::ToScan(const char* inString)
{
	switch (isPathToFile(inString))
	{
	case PathToFile:
		//smth happens here
		break;
	case PathToFolder:
		//smth happens here
		break;
	case NotExist:
		//smth happens here
		break;
	}
}

void Antivirus::startLoging(std::ofstream file)
{
	file.open("Log.txt");
}
void Antivirus::writeLog(const char* fileName)
{

}

