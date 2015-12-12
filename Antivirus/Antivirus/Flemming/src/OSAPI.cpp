#include "Flemming\OSAPI.h"

bool OSAPI::isDirectoryExists(LPCWSTR directoryNameToCheck)
{
	DWORD dwordFileAttributes = GetFileAttributes(directoryNameToCheck);
	if (dwordFileAttributes == INVALID_FILE_ATTRIBUTES) return false;
	return dwordFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
}

bool OSAPI::isFileExists(LPCWSTR fileNameToCheck)
{
	return GetFileAttributes(fileNameToCheck) != INVALID_FILE_ATTRIBUTES;
}

LPCWSTR OSAPI::charToLpcwstr(const char* stringToConvert)
{
	wchar_t* result = new wchar_t[2048];
	MultiByteToWideChar(0, 0, stringToConvert, -1, result, 2048);
	return result;
}

OSAPI::PathTo OSAPI::PathIs(const char* stringToCheck)
{
	LPCWSTR path = charToLpcwstr(stringToCheck);

	if (isDirectoryExists(path))
	{
		return PathToFolder;
	}

	if (isFileExists(path))
	{
		return PathToFile;
	}

	return NotExist;
}

std::pair<std::vector<std::string>, std::vector<std::string>> OSAPI::SeeFilesFolders(const char* inString)
{
	std::vector<std::string> folders;
	std::vector<std::string> files;
	GetFoldersAndFilesList((std::string)(inString), folders, files);
	return std::make_pair(folders, files);
}

void OSAPI::GetFoldersAndFilesList(std::string path,
	std::vector<std::string> &folders,
	std::vector<std::string> &files)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hf;
	path += "/*";
	int len;
	int slength = (int)path.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, path.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, path.c_str(), slength, buf, len);
	std::wstring stemp(buf);
	delete[] buf;
	LPCWSTR result = stemp.c_str();
	hf = FindFirstFile(result, &FindFileData);
	if (hf != INVALID_HANDLE_VALUE) {
		do {
			std::wstring wfilename(FindFileData.cFileName);
			std::string sfilename(wfilename.begin(), wfilename.end());
			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				if (sfilename != "." && sfilename != "..") {
					folders.push_back(sfilename);
				}
			}
			else {
				files.push_back(sfilename);
			}
		} while (FindNextFile(hf, &FindFileData) != 0);
		FindClose(hf);
	}
}

std::string OSAPI::getSystemDirectory() {
	const UINT size = 300; // consistent value
	TCHAR infoBuf[size];
	std::string ret;
	if (!GetWindowsDirectory(infoBuf, size)) {
		throw ERROR("failed to get windows directory");
	}
	else {
		for (int i = 0;i < size; ++i) {
			if (!infoBuf[i]) {
				break;
			}
			else {
				ret += char(infoBuf[i]);
			}
		}
	}
	return (ret + "\\");
}

