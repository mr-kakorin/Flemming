/*
	Copyright (C) 2015 Kakorin Nikita
	Copyright (C) 2015 Zharkov Nikita
	Copyright (C) 2015 Betekhtin Artyoum
	Copyright (C) 2015 Korolev Evgeniy

	This file is part of Antivirus.

	Antivirus is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
*/

#ifndef ANTIVIRUS
#define ANTIVIRUS

//addiction list

#include <windows.h>
#include <fstream>
#include <vector>
#include <string>
#include "yara.h"
#include <iomanip>
/**
	@brief API antivirus

	Class for working with the methods of antivirus
*/
class Antivirus
{   
	/**
		@brief Checking existence of a directory

		@param[in] directoryNameToCheck Name of a checking directory
		@return true - if the directory exists, false - if directory doesn't exists
	*/
	bool isDirectoryExists(LPCWSTR directoryNameToCheck);


	/**
		@brief Checking existence of a file

		@param[in] directoryNameToCheck Name of a checking file
		@return true - if the file exists, false - if file doesn't exists
	*/
	bool isFileExists(LPCWSTR fileNameToCheck);


	/**
		@brief Convert a string of char to LPCWSTR
		@param[in] stringToConvert a pointer to an array of chars
		@return LPCWSTR string
	*/
	LPCWSTR charToLpcwstr(const char* stringToConvert);

	
	/**
		@brief What is this enum?

		Some dedscription about this enum. TODO: make it!
	*/
	enum PathTo { 
		PathToFolder,	///< Text1
		PathToFile,		///< Text2
		NotExist 		///< Text3
	};


	/*return type of directory:file, folder,notexist */
	PathTo isPathToFile(const char* stringToCheck);

	/*open file stream*/
	void startLoging(std::ofstream &file);

	/*close file stream*/
	void endLoging(std::ofstream &file);
	
	/*write infected or not infected file*/
	void writeLog(const char* fileName, bool infected);
		
	/*out file for log's*/
	std::ofstream OutLog;

	void GetFoldersAndFilesList(std::string path,
		std::vector<std::string> &folders,
		std::vector<std::string> &files);

	class SignatureAnalyzer
	{
	public:
		SignatureAnalyzer();
		~SignatureAnalyzer();
		int Scanfile(const char *);
		char* SetLibrarry_file(char *);
	private:
		int ScanType;
		char *Librarry_file;
		int SetScanType(int);		
		friend int callback_function_forfile(int, void*, void*);
	};

	std::pair<std::vector<std::string>, std::vector<std::string>> SeeFilesFolders(const char*);

	std::string getFullNameFile(const std::string&, const char*)const;
	std::string getFullNameFolder(const std::string&, const char*)const;

	SignatureAnalyzer analiz;


public:

	Antivirus(){}
	~Antivirus(){}

	/**
		@brief  Start scan the specified directory
		@param[in] inString Path to directory for scan

		This function starts scan the directory and uses std::cout for
		write out process information.
	*/
	void ToScan(const char* inString);


	/**
		@brief Function print message in output device
		@param[in] message Text of message

		The function uses std::output now
	*/
	static void outMessageToUser(const std::string&);


	/**
		@brief Crazy function, just amazing
		@param[in] message Hm, first string
		@param[in] consoleArgument OK, second string
		@return true - if first string equals second string, else - false

		This function replaces operator '=='
	*/
	static bool isThisCommand(const std::string&, const char*);


	/**
		@brief Returns current date and time
		@param[in] currentDateAndTimeStr
		@return Current date and time in string format
	*/
	char* getCurrentDateAndTime(char* currentDateAndTimeStr);


	/*constants implementation*/
	
	const std::string helpArgumentString = "-help";

	const std::string checkArgumentString = "-check";

	const std::string checkSystemFoulderArgumentString = "-checksys";

	const std::string infoArgumentString = "-info";

	const std::string wrongArgumentsNumberErrorString = "\nWrong number of arguments. Use " + helpArgumentString + " for information.\n";

	const std::string wrongArgumentsErrorString = "\nWrong arguments. Use " + helpArgumentString + " for information.\n";

	const std::string helpOutputText = "\n" + checkArgumentString + " <path> - check file or directory\n" + 
									   checkSystemFoulderArgumentString + " - check system directory\n" +
									   infoArgumentString + " - about program\n";

	const std::string infoOutputText = "\nAntivirus ver 0.0.1 Copyright(C) 2015\n" 
									   "This is free software, and you are welcome to redistribute\n"
									   "it under certain conditions.\n" 
									   "Program comes with ABSOLUTELY NO WARRANTY.\n"
									   "AMCP SPBU 2015\n";

	const std::string checkNoPathErrorText = "Please type path to file or directory to check.\n";

};
#endif

