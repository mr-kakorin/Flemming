#ifndef _FILECONTAINER_FLEMMING
#define _FILECONTAINER_FLEMMING
#include <list>
#include "CommonHeaders.h"
#include "OSAPI.h"
#include "SharedMethods.h"
#include <memory>

class fileInfo
{
public:
	const char* fileName;
	const char* fullFileName;
	bool suspected;
	char signatureName[256];
	fileInfo(const char* a, const char* b) :fileName(a), fullFileName(b)
	{
		signatureName[256] = {};
		suspected = false;
	}
	~fileInfo(){}
};

class FileContainer {
private:

	std::list<std::shared_ptr<fileInfo>> currentSessionFiles;
	void fillListFromFolder(const char*);
	

public:

	FileContainer(const std::string&);
	~FileContainer();
	std::list<std::shared_ptr<fileInfo>> getFileList()
	{
		return currentSessionFiles;
	}
	void out();
	};
#endif

