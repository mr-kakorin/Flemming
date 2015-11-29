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

#include <windows.h>
#include <stdlib.h>
#include "quarantine.h"

LPCWSTR Quarantine::charToLpcwstr(const char* stringToConvert)
{
	wchar_t* result = new wchar_t[2048];
	MultiByteToWideChar(0, 0, stringToConvert, -1, result, 2048);
	return result;
}

Quarantine::Quarantine():numberOfThreats(0){};

void Quarantine::putToQuarantine(const char* pathToFile) {
	LPCWSTR sourceFile = charToLpcwstr(pathToFile);
	char str[2048];
	LPCWSTR destination = charToLpcwstr(strcat("C:\\Antivirus\\Quarantine\\", _itoa(numberOfThreats, str, 10)));
	MoveFile(sourceFile,destination);
	DeleteFile(sourceFile);
	++numberOfThreats;
};