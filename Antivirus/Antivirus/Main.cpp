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
#include <stdio.h>
#include "Flemming\Flemming.h"
#include <direct.h>
#include <conio.h>
#include <windows.h>
#include "Flemming\OSAPI.h"
int main(int argc, char* argv[])
{
	Flemming application;
	application.startWork(argc, argv);
	
	return 0;
}
