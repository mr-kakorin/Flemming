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
#include "Flemming\Logger.h"

Logger::Logger(const std::string inputLogFileName) : logFileName(inputLogFileName) {}
Logger::Logger()
{
	char current_work_dir[FILENAME_MAX];
	_getcwd(current_work_dir, sizeof(current_work_dir));	
	std::cout << logFileName;
}
char* Logger::getCurrentDateAndTime(char *currentDateAndTimeStr)
{
	time_t rawtime;
	tm timeinfo;
	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	asctime_s(currentDateAndTimeStr, 26, &timeinfo);
	return currentDateAndTimeStr;
}

void Logger::startLoging()
{
	outLog.open(logFileName, std::ios::app);
}

void Logger::endLoging()
{
	outLog.close();
}

void Logger::writeLog(const char* fileName, bool infected, char* signatureName)
{
	startLoging();
	//loging here	
	char currentDateAndTimeStr[26];
	outLog << fileName << (infected ? " SUSPECTED_ON " : " SAFE") << signatureName << " " << getCurrentDateAndTime(currentDateAndTimeStr);
	//loging here
	endLoging();
}

std::vector<std::string> Logger::GetAllSuspectedFiles()
{
	std::vector<std::string> allSuspectedFiles;
	std::string str;	
	char mode[32] = {};
	std::ifstream inLog(logFileName);
	char s;
	while (inLog.peek()!=EOF)
	{
	   inLog >> str;
		
	   inLog >> mode;
	
	   if (mode[1] == 'U') 
	   {
		 
		   allSuspectedFiles.push_back(str);
	   }
		
		while ((s=inLog.get()) != '\n')	{}
	}
	inLog.close();

	return allSuspectedFiles;
}