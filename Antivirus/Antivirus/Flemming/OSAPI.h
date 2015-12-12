#ifndef _OSAPI_FLEMMING
#define _OSAPI_FLEMMING

#include "Flemming\CommonHeaders.h"
#include <windows.h>
class OSAPI {

	/**
	@brief Checking existence of a directory

	@param[in] directoryNameToCheck Name of a checking directory
	@return true - if the directory exists, false - if directory doesn't exists
	*/
	static bool isDirectoryExists(LPCWSTR directoryNameToCheck);


	/**
	@brief Checking existence of a file

	@param[in] directoryNameToCheck Name of a checking file
	@return true - if the file exists, false - if file doesn't exists
	*/
	static bool isFileExists(LPCWSTR fileNameToCheck);
		
	/**
	@brief Get folder contain
	@param[in] path Path to folder
	@param[in] folders To this vector write folder list
	@param[in] files To this vector write file list

	Scan the path and return list of folders and files in the directory
	*/
	static void GetFoldersAndFilesList(std::string path,
		std::vector<std::string> &folders,
		std::vector<std::string> &files);

public:	

	/**
	@brief Type of file from path
	*/
	static enum PathTo {
		PathToFolder,	///< The path to folder
		PathToFile,		///< The path to file
		NotExist 		///< The path to nonexist file
	};

	static std::string getSystemDirectory();

	/// Wrap under get Folders and Files list
	static std::pair<std::vector<std::string>, std::vector<std::string>> SeeFilesFolders(const char*);

	/**

	@param[in] stringToCheck Path to file
	@return Type of path to file
	*/
	static PathTo PathIs(const char* stringToCheck);

	/**
	@brief Convert a string of char to LPCWSTR
	@param[in] stringToConvert a pointer to an array of chars
	@return LPCWSTR string
	*/
	static LPCWSTR charToLpcwstr(const char* stringToConvert);
};

#endif