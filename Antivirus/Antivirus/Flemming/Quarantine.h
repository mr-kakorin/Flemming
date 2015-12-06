/*
	Copyright (C) 2015 Kakorin Nikita
	Copyright (C) 2015 Zharkov Nikita
	Copyright (C) 2015 Betekhtin Artyoum
	Copyright (C) 2015 Korolev Evgeniy
	
	This file is part of Flemming.
	
	Flemming is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
*/

#ifndef _QUARANTINE_H_
#define _QUARANTINE_H_

#include <string>
#include <windows.h>
#include "Flemming\Crypter.h"

/**
@brief Class for placing files to quarantine
*/
class Quarantine {
	
	/**
	@brief Number of files in quarantine
	*/
	long numberOfThreats;
	
	/**
	@brief Path to quarantine folder
	*/
	const std::string pathToQuarantine = "C:\\Antivirus\\Quarantine\\";
	
	/**
	@brief
	*/
	HWND handle;
	
	/**
	@brief Class to encrypt files for quarantine
	*/
	static Crypter* crypter;
	
	/**
	@brief
	@param[in]
	@return
	*/
	unsigned int HashRot13(const char*);

public:
	
	Quarantine(HWND);

	/**
	@brief Put infected file to quarantine
	@param[in] path to infected file
	*/
	void putToQuarantine(std::string pathToFile);

	/**
	@brief
	@param[in]
	@param[in]
	@param[in]
	@param[in]
	@return
	*/
	bool CrypterQuarantineFiles(std::pair<std::vector<std::string>, std::vector<std::string>>
		(const char*),
		std::string(const std::string&, const char*)
		
		);
};

#endif
