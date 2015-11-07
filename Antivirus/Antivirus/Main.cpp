#include "antivirus.h"
#include <stdio.h>


int main(int argc, char* argv[])
{
	Antivirus application;

	if (argc > 1)
	{			
		application.ToScan(argv[1]);
	}
	else
	{		
		while (true)
		{
			application.ToScan(application.AskArguments());
		}
	}
	return 0;
}