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

#include <string>
#include "Flemming\ExtensionAnalyser.h"

ExtensionAnalyser::ExtensionAnalyser() :
	significantExtensions(
{
	"application",
	"apk",
	"bat",
	"bin",
	"cgi",
	"cmd",
	"com",
	"cpp",
	"cpl",	
	"js",
	"exe",
	"gadget",
	"gtp",
	"hta",
	"inf",
	"jar",
	"lnk",
	"msi",
	"msh1xml",
	"msh2xml",
	"mshxml",
	"msh1",
	"msh2",
	"msh",
	"msu",
	"msp",
	"msc",
	"pif",
	"ps1",
	"psc1",
	"psc2",
	"ps1xml",
	"ps2xml",
	"pwz",
	"scr",
	"scf",
	"thm",
	"vb",
	"vbe",
	"vbs",
	"url",
	"website",
	"wsc",
	"wsf",
	"wsh",
	"ws",
}) {};

bool ExtensionAnalyser::checkExtension(const char* filename) {

	/*Getting reversed extension*/
	std::string extension = "";
	int pointerIndex = strlen(filename) - 1;
	char currentSymb = filename[strlen(filename) - 1];
	while (currentSymb != '.' && currentSymb != '\\' && pointerIndex != 0) {
		extension += currentSymb;
		currentSymb = filename[--pointerIndex];
	}
	if (currentSymb == '\\') return true; //check files without extension
										  /*Reversing extension*/
	int n = extension.length();
	for (int i = 0; i < n / 2; ++i)
	{
		std::swap(extension[i], extension[n - i - 1]);
	}

	/*Check if extension is suspicious*/
	for (int i = 0; i < significantExtensions.size(); ++i) {
		if (extension == significantExtensions[i]) return true;
	}
	return false;

};