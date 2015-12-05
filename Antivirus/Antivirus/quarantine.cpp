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

#include <stdio.h>
#include <string>
#include "quarantine.h"

Quarantine::Quarantine():numberOfThreats(0){};

void Quarantine::putToQuarantine(const char* pathToFile) {
	char str[2048];
	rename(pathToFile,strcat("C:\\Antivirus\\Quarantine\\", _itoa(numberOfThreats, str, 10)));
	++numberOfThreats;
};