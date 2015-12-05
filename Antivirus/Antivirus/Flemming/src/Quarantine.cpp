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
#include <fstream>
#include <windows.h>
#include <stdlib.h>
#include <vector>
#include <shellapi.h>
#include "Flemming\Quarantine.h"

Quarantine::Quarantine(HWND _handle): numberOfThreats(16), handle(_handle) {};

Crypter* Quarantine::crypter = new Crypter;

void Quarantine::putToQuarantine(std::string pathToFile) {	
	char str[128];
	std::ifstream ifs(pathToFile, std::ios::in | std::ios::binary);
	std::ofstream ofs(pathToQuarantine + _itoa(numberOfThreats++, str, 10), std::ios::out | std::ios::binary);
	ofs << ifs.rdbuf();
	ofs.close();
	ifs.close();
	remove(pathToFile.c_str());
};

bool Quarantine::CrypterQuarantineFiles
   (std::pair<std::vector<std::string>, std::vector<std::string>> getSubFilesFolders
	    (const char*),
	std::string getFullName (const std::string&, const char*))

{	
	std::vector<std::string> files = getSubFilesFolders(pathToQuarantine.data()).second;
	int count = files.size();
	std::string fullName;
	char str[1024];
	for (int i = 0; i < count;++i)
	{
		fullName = getFullName(files.at(i), pathToQuarantine.data());		
		crypter->CryptFile(fullName.data(),(pathToQuarantine + std::string(_itoa(HashRot13(_itoa(numberOfThreats++, str, 10)), str, 10))).data());
	}

}

unsigned int Quarantine::HashRot13(const char * str)
{

	unsigned int hash = 0;

	for (; *str; str++)
	{
		hash += (unsigned char)(*str);
		hash -= (hash << 13) | (hash >> 19);
	}

	return hash;

}