#include "antivirus.h"
#include <stdio.h>
#include <iostream>

int main(int argc, char* argv[])
{
	Antivirus application;
	if (argc > 1)
	{			
		application.ToScan(argv[1]);
	}
	else
	{	
		std::cout << std::endl << "Antivirus ver. 0.0.1" << std::endl;
		while (true)
		{
			application.ToScan(application.AskArguments());
		}
	}
	return 0;
}