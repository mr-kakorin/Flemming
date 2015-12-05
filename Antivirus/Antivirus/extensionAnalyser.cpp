#include <string>
#include "extensionAnalyser.h"

#include <iostream>

ExtensionAnalyser::ExtensionAnalyser() :
	significantExtensions(
{
	"apk",
	"bat",
	"bin",
	"cgi",
	"com",
	"cpp",
	"js",
	"exe",
	"gadget",
	"gtp",
	"hta",
	"jar",
	"msi",
	"msu",
	"pif",
	"ps1",
	"pwz",
	"scr",
	"thm",
	"vb",
	"vbe",
	"vbs",
	"wsf"
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