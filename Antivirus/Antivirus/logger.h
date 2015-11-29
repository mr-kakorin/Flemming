#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <fstream>
#include <string>

class Logger
{
	/*out file for log's*/
	const std::string logFileName;
	std::ofstream outLog;

public:

	Logger(std::string logFileName);

	/**
	@brief Returns current date and time
	@param[in] currentDateAndTimeStr
	@return Current date and time in string format
	*/
	char* getCurrentDateAndTime(char* currentDateAndTimeStr);

	/**
	@brief Open log-file

	The function open log-file stream
	*/
	void startLoging();

	/**
	@brief Close log-file

	The function close log-file stream
	*/
	void endLoging();

	/**
	@brief Write information about checked file
	@param[in] fileName Name of checked file
	@param[in] infected True if file infected
	@param[in] signatureName Name of virus signature

	Write information to log-file about checked file.
	Format: Path to file and filename, suspected/safe, date of checking file
	*/
	void writeLog(const char* fileName, bool infected, char* signatureName);

};

#endif
