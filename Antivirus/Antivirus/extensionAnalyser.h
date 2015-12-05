#ifndef _EXTENSION_ANALYSER_H_
#define _EXTENSION_ANALYSER_H_

#include <vector>
#include <string> 

class ExtensionAnalyser {

	const std::vector<std::string> significantExtensions;

public:

	ExtensionAnalyser();

	/*Return true if file extension is suspicious*/
	bool checkExtension(const char* filename);

};

#endif
