#include "Flemming\FileContainer.h"

FileContainer::FileContainer(const std::string& path)
{
	if (OSAPI::PathIs(path.data()) == OSAPI::PathToFolder)
	{
		fillListFromFolder(path.data());
	}
}

void FileContainer::fillListFromFolder(const char* folderName)
{
	std::vector<std::string> files = OSAPI::SeeFilesFolders(folderName).second;
	std::vector<std::string> folders = OSAPI::SeeFilesFolders(folderName).first;
	
	int count = files.size();
	for (int i = 0; i < count; ++i)
	{
		currentSessionFiles.push_back(std::shared_ptr<fileInfo>(new fileInfo(files.at(i).data(), (SharedMethods::getFullNameFile(std::string(files.at(i)), folderName)).data())));
	}
	count = folders.size();
	
	for (int i = 0; i < count; ++i)
	{
		fillListFromFolder((std::string(folderName) + '\\' + folders.at(i)).data());		
		//need to fix it in more reliable manner
	}
}

FileContainer::~FileContainer()
{
	//in process. (it does not needed coz of list<smart pointer> ?)
}

void FileContainer::out()
{
	for (std::list<std::shared_ptr<fileInfo>>::iterator it = currentSessionFiles.begin(); it != currentSessionFiles.end(); ++it)
	{
		std::cout << *it << std::endl;
	}
}