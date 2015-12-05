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
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <shellapi.h>
#include "quarantine.h"


Quarantine::Quarantine(HWND _handle): numberOfThreats(0), handle(_handle) {};

void Quarantine::putToQuarantine(std::string pathToFile) {	
		
	std::wstring stemp = std::wstring(pathToFile.begin(), pathToFile.end());
	LPCWSTR From = stemp.c_str();
	std::wstring stemp1 = std::wstring(pathToQuarantine.begin(), pathToQuarantine.end());
	LPCWSTR To = stemp1.c_str();

	SHFILEOPSTRUCT op;
	ZeroMemory(&op, sizeof(op));
	op.hwnd = handle;
	op.wFunc = FO_MOVE;
	op.pFrom = From;
	op.pTo = To;
	op.fFlags = 0;
	SHFileOperation(&op);
	
};