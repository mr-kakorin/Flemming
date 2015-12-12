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

#ifndef _CRYPTER_FLEEMING
#define _CRYPTER_FLEEMING

#include "Flemming\CommonHeaders.h"

/**
@brief Encryption class

Class for encrypting files for quarantine
*/
class Crypter {
	/**
	@brief Convert char to Base64 system
	@param[in] char to convert
	@return char in Base64
	*/
	char Base64Char(unsigned char);

	/**
	@brief Convert string to Base64 system
	@param[in] string to convert
	@param[in] length of input string
	@param[in] string for result
	@return length of converted string
	*/
	int Base64Encode(char*inStr, int len, char*outStr);
public:
	Crypter() {};
	~Crypter() {};

	/**
	@brief Convert file to Base64 system
	@param[in] path to file to convert
	@param[in] path to file for result
	*/
	bool CryptFile(const char* inFileName, const char* outFileName);
};

#endif