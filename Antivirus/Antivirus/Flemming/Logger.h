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

#ifndef _LOGGER_H_
#define _LOGGER_H_

#include "Flemming\CommonHeaders.h"
#include <direct.h>
/**
	@brief Object for work with log files

	API for log file
*/
class Logger
{
	std::string logFileName; ///>  Name of log-file in String format
	std::ofstream outLog; ///> Stream for out log-file

public:

	/**
		@brief LogObject constructor
		@param[in] logFileName Name of logfile in string format
	*/
	Logger(std::string logFileName);
	/**
		@brief Default Constructor
	*/
	Logger();
	
	/**
	@brief Returns current date and time
	@param[in] currentDateAndTimeStr
	@return Current date and time in string format
	*/
	char* getCurrentDateAndTime(char* currentDateAndTimeStr);

	/**
	@brief Open log-file
	The function open log-file stream
	*/
	void startLoging();

	/**
	@brief Close log-file
	The function close log-file stream
	*/
	void endLoging();

	/**
	@brief Write information about checked file
	@param[in] fileName Name of checked file
	@param[in] infected True if file infected
	@param[in] signatureName Name of virus signature
	Write information to log-file about checked file.
	Format: Path to file and filename, suspected/safe, date of checking file
	*/
	void writeLog(const char* fileName, bool infected, char* signatureName);

	std::vector<std::string> GetAllSuspectedFiles();
};

#endif
