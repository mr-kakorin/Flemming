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
#include "Flemming\Quarantine.h"
#include "Flemming\OSAPI.h"
#include "Flemming\SharedMethods.h"
Quarantine::Quarantine(): numberOfThreats(16) {};

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

bool Quarantine::CrypterQuarantineFiles()
{	
	std::vector<std::string> files = OSAPI::SeeFilesFolders(pathToQuarantine.data()).second;
	int count = files.size();
	std::string fullName;
	char str[1024];
	bool result = true;
	for (int i = 0; i < count;++i)
	{
		fullName = SharedMethods::getFullNameFile(files.at(i), pathToQuarantine.data());		
		result = result & (crypter->CryptFile(fullName.data(),(pathToQuarantine + std::string(_itoa(HashRot13(_itoa(numberOfThreats++, str, 10)), str, 10))).data()));
	}
	return result;
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