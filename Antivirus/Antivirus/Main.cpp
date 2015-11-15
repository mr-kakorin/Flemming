#include "antivirus.h"
#include <stdio.h>
#include <iostream>
int main(int argc, char* argv[])
{
	Antivirus application;
	SignatureAnalyzer analiz;	

	switch (argc) {
	case 1:
		std::cout << application.wrongArgumentsNumberErrorString;
		break;
	case 2:
		if (argv[1] == application.helpArgumentString)
		{
			std::cout << application.helpOutputText;
		}
		else {
			if (argv[1] == application.infoArgumentString)
			{
				std::cout << application.infoOutputText;
			}
			else {
				if (argv[1] == application.checkArgumentString)
				{
					std::cout << application.checkNoPathErrorText;
				}
				else {
					if (argv[1] == application.checkSystemFoulderArgumentString)
					{
						//check system foulder
					}
					else {
						std::cout << application.wrongArgumentsErrorString;
					}
				}
			}
		}
		break;
	case 3:
		if (argv[1] == application.checkArgumentString)
		{
			application.ToScan(argv[2],analiz);
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