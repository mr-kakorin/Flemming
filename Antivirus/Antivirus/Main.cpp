#include "antivirus.h"
#include <stdio.h>
#include <iostream>

int main(int argc, char* argv[])
{
	Antivirus application;
	std::cout << std::endl;
	switch (argc){
	case 1:
		std::cout << application.wrongArgumentsNumberErrorString;
		break;
	case 2:
		if (strcmp(argv[1], application.helpArgumentString) == 0)
		{
			std::cout << application.helpOutputText;
		}
		if (strcmp(argv[1], application.infoArgumentString) == 0)
		{
			std::cout << application.infoOutputText;
		}
		if (strcmp(argv[1], application.checkArgumentString) == 0)
		{
			std::cout << application.checkNoPathErrorText;
		}
		if (strcmp(argv[1], application.checkSystemFoulderArgumentString) == 0)
		{
			//check system foulder
		}
		break;
	case 3:
		if (strcmp(argv[1], application.checkArgumentString) == 0)
		{
			application.ToScan(argv[2]);
		}
		else
		{
			std::cout << application.wrongArgumentsErrorString;
		}
		break;
	default:
		std::cout << application.wrongArgumentsNumberErrorString;
		break;
	}
	return 0;
}