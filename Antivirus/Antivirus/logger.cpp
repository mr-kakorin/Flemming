#include "logger.h"

Logger::Logger(const std::string inputLogFileName) : logFileName(inputLogFileName) {}
#include <fstream>
#include <ctime>
#include "logger.h"

Logger::Logger(const std::string inputLogFileName): logFileName(inputLogFileName) {}

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
	outLog << fileName << (infected ? " : suspected on " : " : safe ") << (signatureName != NULL ? signatureName : "") << " " << getCurrentDateAndTime(currentDateAndTimeStr);
	//loging here
	endLoging();
}