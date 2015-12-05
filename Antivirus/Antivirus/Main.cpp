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
#include "antivirus.h"
#include <stdio.h>
#include <omp.h>
/*
	@brief Processing of entered command

	If type one argument: Error. The antivirus must launch with one or more parametres
	Two arguments:
		It can be command: '-checksys', '-help', '-info'
		Else it error command

	Three arguments:
		It can be command '-check', third argument is path to check file or folder
		Else it error command
*/

int main(int argc, char* argv[])
{
	Antivirus application;
	double start_time, end_time;
	start_time = omp_get_wtime();
	//test//	
	//
	//	
	application.ToScan("D:\\viruses\\");
	
	//
	//application.ScanMemory();
	//test

	end_time = omp_get_wtime();
	printf("time = %f", (end_time - start_time));

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
