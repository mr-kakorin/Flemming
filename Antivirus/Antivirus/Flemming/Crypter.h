#ifndef _CRYPTER_FLEEMING
#define _CRYPTER_FLEEMING

class Crypter {

public:
	Crypter() {};
	~Crypter() {};
	char Base64Char(unsigned char);
	int Base64Encode(char*inStr, int len, char*outStr);
	void CryptFile(const char*, const char*); 
};

#endif