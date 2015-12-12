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
#include "Flemming\Flemming.h"
#include "Flemming\Logger.h"
#include "Flemming\SharedMethods.h"
#include "Flemming\OSAPI.h"

SignatureAnalyser* Flemming::analyser = new SignatureAnalyser;
Quarantine* Flemming::quarantiner = new Quarantine;
Logger* logger = new Logger;

void Flemming::ToScan(const char* inString, bool scantype)
{
	std::vector<std::string> folders;
	std::vector<std::string> files;
	std::pair<std::vector<std::string>, std::vector<std::string>> subFilesFolders = std::make_pair(folders, files);
	std::vector<std::string> filesToQuarantine;

	switch (OSAPI::PathIs(inString))
	{
	case OSAPI::PathToFile:
		//std::cout << "Checking the file \"" << inString << "\t";
		analyser->ScanSingleFile(inString);
		break;
	case OSAPI::PathToFolder:

		subFilesFolders = OSAPI::SeeFilesFolders(inString);
		for (int i = 0; i < subFilesFolders.first.size();++i)
		{
			ToScanWoCheck(SharedMethods::getFullNameFolder(subFilesFolders.first.at(i), inString).data(), scantype);
			
		}		
			analyser->Scanfile(inString, subFilesFolders.second, scantype);

		break;
	case OSAPI::NotExist:
		//std::cout << std::endl << inString << " : There is no such file or directory.\n";
		break;
	}
}

void Flemming::ToScanWoCheck(const char* inString, bool scantype)
{
	std::vector<std::string> folders;
	std::vector<std::string> files;
	std::pair<std::vector<std::string>, std::vector<std::string>> subFilesFolders = std::make_pair(folders, files);

    subFilesFolders = OSAPI::SeeFilesFolders(inString);

		for (int i = 0; i < subFilesFolders.first.size();++i)
		{
			ToScanWoCheck(SharedMethods::getFullNameFolder(subFilesFolders.first.at(i), inString).data(), scantype);
		}
		analyser->Scanfile(inString, subFilesFolders.second, scantype);
	
}

void Flemming::outMessageToUser(const std::string& message)
{
	printf(message.data());
}

bool Flemming::isThisCommand(const std::string& message, const char* consoleArgument)
{
	return message == consoleArgument;
}

Flemming::Flemming()
{
	
}

Flemming::~Flemming()
{

}

void Flemming::ScanMemory()
{
	analyser->ScanMem();	
}

void Flemming::ScanSystemFolder()
{
	try {
		ToScan(OSAPI::getSystemDirectory().data(),false);
	}
	catch (const char* e)
	{
		std::cout << e;
	}
}

void Flemming::ToScanWithQ(const char* inString, bool scantype)
{
	ToScan(inString, scantype);

	std::vector<std::string> filesToQuarantine = logger->GetAllSuspectedFiles();
	if (!filesToQuarantine.empty())
	{
		for (int i = 0;i < filesToQuarantine.size();++i)
		{
			quarantiner->putToQuarantine(filesToQuarantine.at(i));
			//std::cout << filesToQuarantine.at(i) << std::endl;
		}
		quarantiner->CrypterQuarantineFiles();
	}
}

void Flemming::ToScanDesc(const char* inString)
{
	std::vector<std::string> folders;
	std::vector<std::string> files;
	std::pair<std::vector<std::string>, std::vector<std::string>> subFilesFolders = std::make_pair(folders, files);

	subFilesFolders = OSAPI::SeeFilesFolders(inString);

	for (int i = 0; i < subFilesFolders.first.size();++i)
	{
		ToScanDesc(SharedMethods::getFullNameFolder(subFilesFolders.first.at(i), inString).data());
	}
	analyser->ScanDescriptor(inString, subFilesFolders.second, OSAPI::charToLpcwstr);
}

bool Flemming::startWork(int argc, char** argv)
{
	switch (argc) {
	case 1:
		Flemming::outMessageToUser(wrongArgumentsNumberErrorString);
		break;
	case 2:
		if (Flemming::isThisCommand(helpArgumentString, argv[1]))
		{
			Flemming::outMessageToUser(helpOutputText);
		}
		else {
			if (Flemming::isThisCommand(infoArgumentString, argv[1]))
			{
				Flemming::outMessageToUser(infoOutputText);
			}
			else {
				if (Flemming::isThisCommand(checkArgumentString, argv[1]))
				{
					Flemming::outMessageToUser(checkNoPathErrorText);
				}
				else {
					if (Flemming::isThisCommand(checkSystemFoulderArgumentString, argv[1]))
					{
						ScanSystemFolder();
					}
					else {
						Flemming::outMessageToUser(wrongArgumentsErrorString);
					}
				}
			}
		}
		break;
	case 3:
		if (Flemming::isThisCommand(checkArgumentString, argv[1]))
		{
			ToScan(argv[2], true);
		}
		if (Flemming::isThisCommand(checkArgumentWithQuarantineString, argv[1]))
		{
			ToScanWithQ(argv[2], true);
		}
		if (Flemming::isThisCommand(fullCheckArgumentWithQuarantineString, argv[1]))
		{
			ToScanWithQ(argv[2], false);
		}
		if (Flemming::isThisCommand(fullCheckArgumentString, argv[1]))
		{
		    ToScan(argv[2], false);
		}
		if (Flemming::isThisCommand(CheckArgumentDescriptorString, argv[1]))
		{
			ToScanDesc(argv[2]);
		}
		if (Flemming::isThisCommand(checkMemoryString, argv[1]))
		{
			ScanMemory();
		}
		else
		{
			Flemming::outMessageToUser(wrongArgumentsErrorString);
		}
		break;
	default:
		Flemming::outMessageToUser(wrongArgumentsNumberErrorString);
		break;
	}
	return true;
}