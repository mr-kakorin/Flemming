#include "antivirus.h"
#include <stdio.h>
#include <iostream>

int main(int argc, char* argv[])
{
	Antivirus application;
	
	//test// application.ToScan("D:\\Games\\Hearthstone\\");


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
