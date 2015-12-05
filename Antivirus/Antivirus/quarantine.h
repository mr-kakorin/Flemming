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

#ifndef _QUARANTINE_H_
#define _QUARANTINE_H_

#include <string>
#include <windows.h>

class Quarantine {

	long numberOfThreats;
	const std::string pathToQuarantine = "C:\\Antivirus\\Quarantine";
	HWND handle;
public:
	Quarantine(HWND);

	void putToQuarantine(std::string pathToFile);
};

#endif
