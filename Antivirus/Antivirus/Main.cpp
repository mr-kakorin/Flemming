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

#include "antivirus.h"
#include <stdio.h>
#include <iostream>

int main(int argc, char* argv[])
{
	Antivirus application;
	
	//test// application.ToScan("D:\\Games\\Hearthstone\\");
	
	std::cout << std::endl;
	std::cout << "Antivirus Copyright (C) 2015" << std::endl;
	std::cout << "This is free software, and you are welcome to redistribute" << std::endl;
	std::cout << "program comes with ABSOLUTELY NO WARRANTY" << std::endl;
	std::cout << std::endl;

	switch (argc) {
	case 1:
		Antivirus::outMessageToUser(application.wrongArgumentsNumberErrorString);
		break;
	case 2:
		if (Antivirus::isThisCommand(application.helpArgumentString, argv[1]))
		{
			Antivirus::outMessageToUser(application.helpOutputText);
		}
		else {
			if (Antivirus::isThisCommand(application.infoArgumentString, argv[1]))
			{
				Antivirus::outMessageToUser(application.infoOutputText);
			}
			else {
				if (Antivirus::isThisCommand(application.checkArgumentString, argv[1]))
				{
					Antivirus::outMessageToUser(application.checkNoPathErrorText);
				}
				else {
					if (Antivirus::isThisCommand(application.checkSystemFoulderArgumentString, argv[1]))
					{
						//check system foulder
					}
					else {
						Antivirus::outMessageToUser(application.wrongArgumentsErrorString);
					}
				}
			}
		}
		break;
	case 3:
		if (Antivirus::isThisCommand(application.checkArgumentString, argv[1]))
		{
			application.ToScan(argv[2]);
		}
		else
		{
			Antivirus::outMessageToUser(application.wrongArgumentsErrorString);
		}
		break;
	default:
		Antivirus::outMessageToUser(application.wrongArgumentsNumberErrorString);
		break;
	}
	return 0;
}
