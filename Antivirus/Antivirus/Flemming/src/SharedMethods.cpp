#include "Flemming\SharedMethods.h"

std::string SharedMethods::getFullNameFile(const std::string& fName, const char* inString)
{
	std::string tmp = (std::string)(inString) + fName;
	return tmp;
}

std::string SharedMethods::getFullNameFolder(const std::string& fName, const char* inString)
{
	std::string tmp = (std::string)(inString) + fName + "\\";
	return tmp;
}

