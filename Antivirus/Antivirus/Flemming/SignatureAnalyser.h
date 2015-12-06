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

#ifndef _SIGNATURE_ANALYSER_H_
#define _SIGNATURE_ANALYSER_H_

#include <ctime>
#include <vector>
#include <string>
#include "Flemming\Logger.h"
#include "Flemming\ExtensionAnalyser.h"
#include "yara.h"

/**
@brief Out wrap under YARA API

This class make custom wrap under Yara library
*/
class SignatureAnalyser
{
public:	
	SignatureAnalyser();
	~SignatureAnalyser();
	/**
	@brief Start scan file
	@return  Type of result of scan file
	*/
	int Scanfile(const char *, std::vector<std::string>);
	int ScanSingleFile(const char*);
	int ScanMem();
	Logger* getLogger()
	{
		return log;
	}
private:	

	static char signatureName[128]; ///> Name of signature in string format
	//static std::string signatureName;
	static int CALLBACK_MSG_FILE; ///> Data of callback message

	static Logger* log; ///> LogFile object

	static ExtensionAnalyser* extAnalyser;
	/*
		@brief Returns full name with full path to file
	*/
	const char* getFullNameFile(const std::string&, const char*)const;
	int ScanType; ///> Type of scanning
	char *Librarry_file; ///> Atavism
	/**
	@brief Function for set type of scan
	*/
	
	/**
	@brief Call back function

	Start after full scan file, detect type of infect and write info to log-file
	*/
	static int callback_function_forfile(int, void*, void*);

	static int callback_function_formem(int, void*, void*);
};

#endif