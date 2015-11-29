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

#include <ctime>
#include <vector>
#include <string>
#include "logger.h"
#include "yara.h"

/**
@brief Out wrap under YARA API

This class make custom wrap under Yara library
*/
class SignatureAnalyzer
{
public:	
	SignatureAnalyzer();
	~SignatureAnalyzer();
	/**
	@brief Start scan file
	@return  Type of result of scan file
	*/
	int Scanfile(const char *, std::vector<std::string> files);
	
	static char signatureName[128]; ///> Name of signature in string format
	static int CALLBACK_MSG_FILE; ///> Data of callback message

private:	
	static Logger* log; ///> LogFile object
	/*
		@brief Returns full name with full path to file
	*/
	std::string getFullNameFile(const std::string&, const char*)const;
	int ScanType; ///> Type of scanning
	char *Librarry_file; ///> Atavism
	/**
	@brief Function for set type of scan
	*/
	int SetScanType(int);
	/**
	@brief Call back function

	Start after full scan file, detect type of infect and write info to log-file
	*/
	static int callback_function_forfile(int, void*, void*);
};