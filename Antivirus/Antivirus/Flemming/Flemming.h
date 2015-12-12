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

#ifndef _Flemming_H_
#define _Flemming_H_

//addiction list

#include "Flemming\CommonHeaders.h"
#include "Flemming\SignatureAnalyser.h"
#include "Flemming\Quarantine.h"

/**
@brief API Flemming

Class for working with the methods of Flemming
*/
class Flemming
{
	static SignatureAnalyser* analyser;

	static Quarantine* quarantiner;

	
	void ToScanWoCheck(const char*,bool);
	
	/**
	@brief  Start scan the specified directory
	@param[in] inString Path to directory for scan

	This function starts scan the directory and uses std::cout for
	write out process information.
	*/
	void ToScan(const char* inString, bool);
	void ToScanDesc(const char* inString);
	void ToScanWithQ(const char* inString, bool);
	void ScanSystemFolder();
	void ScanMemory();



	/*constants implementation*/
	const std::string checkNoPathErrorText = "Please type path to file or directory to check.\n";

	const std::string checkArgumentWithQuarantineString = "-check-q";

	const std::string checkMemoryString = "-check-mem";

	const std::string fullCheckArgumentWithQuarantineString = "-check-q-f";

	const std::string fullCheckArgumentString = "-check-f";

	const std::string CheckArgumentDescriptorString = "-check-fd";

	// The command for show help information
	const std::string helpArgumentString = "-help";
	/// The command for start check file or folder
	const std::string checkArgumentString = "-check";
	/// The command for start check system folders
	const std::string checkSystemFoulderArgumentString = "-checksys";
	/// The command for show information about programm
	const std::string infoArgumentString = "-info";

	/// Text of error with arguments number
	const std::string wrongArgumentsNumberErrorString = "\nWrong number of arguments. Use " + helpArgumentString + " for information.\n";

	/// Text of error with argument
	const std::string wrongArgumentsErrorString = "\nWrong arguments. Use " + helpArgumentString + " for information.\n";

	/// Help text
	const std::string helpOutputText = '\n' + checkArgumentString + " <path> - check file or directory\n" +
		checkSystemFoulderArgumentString + " - check system directory\n" +
		infoArgumentString + " - about program\n" +
		checkArgumentWithQuarantineString + "<path> - check file or directory\n" +
		checkMemoryString + "check running processes\n" +
		CheckArgumentDescriptorString + "check puckers and crypters\n";

	/// Information about programm
	const std::string infoOutputText = "\nFlemming ver 0.0.1 Copyright(C) 2015\n"
		"This is free software, and you are welcome to redistribute\n"
		"it under certain conditions.\n"
		"Program comes with ABSOLUTELY NO WARRANTY.\n"
		"AMCP SPBU 2015\n";
	/// Text of error if path to file is not exists


public:

	Flemming();
	~Flemming();

	/*
	@brief Processing of entered command

	If type one argument: Error. The Flemming must launch with one or more parametres
	Two arguments:
	It can be command: '-checksys', '-help', '-info'
	Else it error command

	Three arguments:
	It can be command '-check', third argument is path to check file or folder
	Else it error command
	*/
	bool startWork(int, char**);
	/**
	@brief Function print message in output device
	@param[in] message Text of message

	The function uses std::output now
	*/
	static void outMessageToUser(const std::string&);

	/**
	@brief Check equal of two string
	@param[in] message First string
	@param[in] consoleArgument Second string
	@return true - if first string equals second string, else - false

	This function replaces operator '==' for two string
	*/
	static bool isThisCommand(const std::string&, const char*);
};

#endif

