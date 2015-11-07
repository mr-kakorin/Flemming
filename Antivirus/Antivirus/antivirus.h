#ifndef ANTIVIRUS
#define ANTIVIRUS

//addiction list

#include <windows.h>


class Antivirus
{   
	bool isDirectoryExists(LPCWSTR directoryNameToCheck);

	bool isFileExists(LPCWSTR fileNameToCheck);

	LPCWSTR charToLpcwstr(const char* stringToConvert);

	enum PathTo{ PathToFile, PathToFolder, NotExist };

	/*return type of directory:file, folder,notexist */
	PathTo isPathToFile(const char* stringToCheck);

public:

	Antivirus(){}
	~Antivirus(){}

	/*check exist path and give next instructions*/
	void ToScan(const char* inString);

	/*if app started w\o arguments of console ask user to input path*/
	const char* AskArguments();
};


#endif

