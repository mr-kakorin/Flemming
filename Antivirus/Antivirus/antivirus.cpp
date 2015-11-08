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
	switch (isPathToFile(inString))
	{
	case PathToFile:
		std::cout << "Checking the file \"" << inString << "\"..." << std::endl; 
		signature_analyzer analyzer;
		analyzer.Scanfile(inString); //добавьте вывод там сами если функция возв 1 - то вирус
		//smth happens here
		std::cout << "There could be some viruses, but our program can't find them just yet :(" << std::endl; //temporary message
		break;
	case PathToFolder:
		std::cout << "Checking the foulder \"" << inString << "\"..." << std::endl;

		//smth happens here
		std::cout << "There could be some viruses, but our program can't find them just yet :(" << std::endl; //temporary message
		break;
	case NotExist:
		std::cout << "There is no such file or directory.";
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

