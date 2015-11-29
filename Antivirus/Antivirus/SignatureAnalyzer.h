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
	/// brief Atavism, need to create base of signature
	

	static char signatureName[128];
	static int CALLBACK_MSG_FILE;

private:	
	static Logger* log;
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
};