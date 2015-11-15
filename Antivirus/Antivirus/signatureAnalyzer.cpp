#include "signatureAnalyzer.h"

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
	return (ScanType==NULL)? NULL : SCAN_FLAGS_FAST_MODE;
}

/*
this func compile signatures.yara to db of signatures that we would use
*/
char * SignatureAnalyzer::SetLibrarry_file(char * filename)
{
	FILE* rule_1;
	
	fopen_s(&rule_1, "rule1.yara", "r");

	YR_COMPILER* cmplr = NULL; 

	YR_RULES* rules = NULL;

	yr_initialize();

	yr_compiler_create(&cmplr); 

	printf("%d", yr_compiler_add_file(cmplr, rule_1, NULL, "text"));

	yr_compiler_get_rules(cmplr, &rules);
	
	yr_rules_save(rules, filename);

	yr_rules_destroy(rules); 
	yr_compiler_destroy(cmplr); 
    yr_finalize();
	return filename;
}
int CALLBACK_MSG_FILE = 0;
int callback_function_forfile(int message, void* message_data, void* user_data)
{
	CALLBACK_MSG_FILE = 0;	
	if (message == CALLBACK_MSG_RULE_MATCHING)
	{
		CALLBACK_MSG_FILE = 1;
		return CALLBACK_ABORT;
	}
	return CALLBACK_CONTINUE;
}

int SignatureAnalyzer::Scanfile(const char * filename)  
{	
	yr_initialize();
	YR_RULES* rules = NULL;
    yr_rules_load(Librarry_file, &rules);
	if (ERROR_CALLBACK_ERROR == yr_rules_scan_file(rules, filename, ScanType, callback_function_forfile, NULL, 0))
		printf("%d", 777);
	yr_finalize();

	return CALLBACK_MSG_FILE;
}

