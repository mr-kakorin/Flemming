#ifndef _SHAREDMETHODS_FLEMMING
#define _SHAREDMETHODS_FLEMMING

#include "Flemming\CommonHeaders.h"

class SharedMethods {
public:
	/**
	@brief Get fullname of file
	@param[in] fName Name of file
	@param[in] inString Path to file
	@return Full name of file with full path
	*/
	static std::string getFullNameFile(const std::string&, const char*);

	/**
	@brief Get fullname of folder
	@param[in] fName Name of folder
	@param[in] inString Path to the folder
	@return Full name of folder with full path
	*/
	static std::string getFullNameFolder(const std::string&, const char*);

};
#endif