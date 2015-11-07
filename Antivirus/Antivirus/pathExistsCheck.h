#ifndef _PATH_EXISTS_CHECK_
#define _PATH_EXISTS_CHECK_

#include <windows.h>

bool isDirectoryExists(LPCWSTR directoryNameToCheck);

bool isFileExists(LPCWSTR fileNameToCheck);

LPCWSTR charToLpcwstr(const char* stringToConvert);

#endif