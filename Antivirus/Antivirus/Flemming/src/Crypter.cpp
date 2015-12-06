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
#include <fstream>
#include "Flemming\Crypter.h"

char Crypter::Base64Char(unsigned char b) {
	b &= 0x3F;
	if (b<26) return 'A' + b;
	if (b<52) return 'a' + (b - 26);
	if (b<62)return '0' + (b - 52);
	if (b == 62)return '+';
	return '/';
}

int Crypter::Base64Encode(char*inStr, int len, char*outStr) {
	//return length of outStr after enCode
	int i = 0; int j = 0;//i - index of inStr; j - index of outStr;
	unsigned
		char a1, a2, a3;
	unsigned char b1, b2, b3, b4;
	for (i = 0; i<len; i += 3) {
		a1 = a2 = a3 = 0;
		b1 = b2 = b3 = b4 = 0;
		a1 = inStr[i];
		if (i + 1<len)a2 = inStr[i + 1];
		if (i + 2<len)a3 = inStr[i + 2];
		b1 = a1 >> 2;
		b2 = (a2 >> 4) | ((a1 & 0x3) << 4);
		b3 = ((a2 & 0xF) << 2) | (a3 >> 6);
		b4 = a3 & 0x3F;
		outStr[j++] = Base64Char(b1);
		outStr[j++] = Base64Char(b2);
		outStr[j++] = (i + 1<len) ? Base64Char(b3) : '=';
		outStr[j++] = (i + 2<len) ? Base64Char(b4) : '=';
	}
	return j;
}

void Crypter::CryptFile(const char* inFileName, const char* outFileName)
{
	std::ifstream inFile(inFileName, std::ios_base::binary);
	
	if (!inFile) std::cout << "ne ok in" << std::endl;
	std::ofstream outFile(outFileName, std::ios_base::binary);
	if (!outFile) std::cout << "ne ok out" << std::endl;
	//std::cout << inFileName << std::endl;
	char inStr[3], outStr[4];
	int s, count = 0;
	while (inFile.peek() != EOF) {
		inFile.read(inStr, 3);
		s = inFile.gcount();
		s = Base64Encode(inStr, s, outStr);
		outFile.write(outStr, s);
	}
	inFile.close();
	outFile.close();
	remove(inFileName);	
}