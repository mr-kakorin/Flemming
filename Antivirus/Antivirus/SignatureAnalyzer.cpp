#include <iostream>
#include <SignatureAnalyzer.h>
#include <omp.h>

std::string SignatureAnalyzer::getFullNameFile(const std::string& fName, const char* inString)const
{
	std::string tmp = (std::string)(inString) + fName;
	return tmp;
}
Logger* SignatureAnalyzer::log = new Logger;

SignatureAnalyzer::SignatureAnalyzer()
{	
	ScanType = SCAN_FLAGS_FAST_MODE;
	Librarry_file = "C:\\Antivirus\\SignaturesDB";	
}

SignatureAnalyzer::~SignatureAnalyzer()
{

}

int SignatureAnalyzer::SetScanType(int ScanType)
{
	return (ScanType == NULL) ? NULL : SCAN_FLAGS_FAST_MODE;
}

char SignatureAnalyzer::signatureName[128] = {};
int SignatureAnalyzer::CALLBACK_MSG_FILE = 0;

int SignatureAnalyzer::callback_function_forfile(int message, void* message_data, void* user_data)
{
	CALLBACK_MSG_FILE = 0;
	if (message == CALLBACK_MSG_RULE_MATCHING)
	{
		CALLBACK_MSG_FILE = 1;
		strcpy_s(signatureName, (*((YR_RULE*)message_data)).identifier);
		return CALLBACK_ABORT;
	}		
	return CALLBACK_CONTINUE;
}

int SignatureAnalyzer::Scanfile(const char * filename, std::vector<std::string> files)
{
	yr_initialize();
	YR_RULES* rules = NULL;
	yr_rules_load(Librarry_file, &rules);
	std::string h;

#pragma omp parallel num_threads(4) firstprivate(CALLBACK_MSG_FILE, signatureName,log, h)
	{
#pragma omp for ordered
		for (int i = 0; i < files.size(); ++i)
		{
			h = getFullNameFile(files.at(i), filename);
			yr_rules_scan_file(rules, h.data(), ScanType, callback_function_forfile, NULL, 0);
#pragma omp ordered
			log->writeLog(h.data(), (CALLBACK_MSG_FILE ==1 ? true : false), signatureName);
		}
	}
	yr_finalize();
	return CALLBACK_MSG_FILE;
}
