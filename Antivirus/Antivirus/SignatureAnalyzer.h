#include <ctime>
#include <vector>
#include <string>
#include "logger.h"
#include "yara.h"

/**
@brief Out wrap under YARA API

This class make custom wrap under Yara library
*/
class SignatureAnalyzer
{
public:	
	SignatureAnalyzer();
	~SignatureAnalyzer();
	/**
	@brief Start scan file
	@return  Type of result of scan file
	*/
	int Scanfile(const char *, std::vector<std::string> files);

	int ScanMem();
private:	

	static char signatureName[128]; ///> Name of signature in string format
	static int CALLBACK_MSG_FILE; ///> Data of callback message

	static Logger* log; ///> LogFile object
	/*
		@brief Returns full name with full path to file
	*/
	std::string getFullNameFile(const std::string&, const char*)const;
	int ScanType; ///> Type of scanning
	char *Librarry_file; ///> Atavism
	/**
	@brief Function for set type of scan
	*/
	int SetScanType(int);
	/**
	@brief Call back function

	Start after full scan file, detect type of infect and write info to log-file
	*/
	static int callback_function_forfile(int, void*, void*);

	static int callback_function_formem(int, void*, void*);
};