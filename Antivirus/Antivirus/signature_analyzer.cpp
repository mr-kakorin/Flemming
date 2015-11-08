#include "signature_analyzer.h"



signature_analyzer::signature_analyzer()
{
	ScanType = 0;
	Librarry_file = "signaturesDB";
}


signature_analyzer::~signature_analyzer()
{

}



int signature_analyzer::SetScanType(int ScanType)
{
	
	return (ScanType==NULL)? NULL : SCAN_FLAGS_FAST_MODE;

}


char * signature_analyzer::SetLibrarry_file(char * filename) // Ќ”∆Ќќ ƒќЅј¬»“№ ћЌќ∆≈—“¬ќ ѕ–ќ¬≈–ќ  Ќј ќЎ»Ѕ »!!!!
{
	FILE* rule_1;
	YR_CALLBACK_FUNC callback;
	fopen_s(&rule_1, "clamav.yara", "r");

	YR_COMPILER* cmplr = NULL; // компил€тор правил в специальный вид

	YR_RULES* rules = NULL;

	yr_initialize();

	yr_compiler_create(&cmplr); // нужно только при первом запуске дл€ компил€ции всех правил в специальный вид

	yr_compiler_add_file(cmplr, rule_1, NULL, NULL);// нужно только при первом запуске дл€ компил€ции всех правил в специальный вид

	yr_compiler_get_rules(cmplr, &rules);// нужно только при первом запуске дл€ компил€ции всех правил в специальный вид


	yr_rules_save(rules, filename);// нужно только при первом запуске дл€ компил€ции всех правил в специальный вид

	yr_rules_destroy(rules); // нужно только при первом запуске дл€ компил€ции всех правил в специальный вид
	yr_compiler_destroy(cmplr); // нужно только при первом запуске дл€ компил€ции всех правил в специальный вид
    yr_finalize();
	return filename;
}
int CALLBACK_MSG_FILE = 0;
int callback_function_forfile(int message, void* message_data, void* user_data)

{
	CALLBACK_MSG_FILE = 0;
	if (message == CALLBACK_MSG_RULE_MATCHING) CALLBACK_MSG_FILE = 1;

	return message;
}
int signature_analyzer::Scanfile(const char * filename)   // Ќ”∆Ќќ ƒќЅј¬»“№ ћЌќ∆≈—“¬ќ ѕ–ќ¬≈–ќ  Ќј ќЎ»Ѕ »!!!!
{
	
	yr_initialize();
	YR_RULES* rules = NULL;
    yr_rules_load(Librarry_file, &rules); // загружаем этот скомпиленный файл правил специальный

	yr_rules_scan_file(rules, filename, ScanType,callback_function_forfile, NULL, 0);
	yr_finalize();

	return CALLBACK_MSG_FILE;


}

