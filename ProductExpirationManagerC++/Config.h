// ProductExpirationManagerC++
// Config.h
// Created on Oct 01 2026 by Justyn Durnford
// Last modified on Oct 01 2026 by Justyn Durnford
// Header file for the Config class

#pragma once

#include <string>

// Class for storing config settings.
class Config
{
	std::string _sheetUrl;
	std::string _downloadUrl;

	// Checks if the line read from "info/config.ini" is valid.
	std::string _getUrlFromLine(const std::string& line) const;

	public:

	// Default constructor.
	// Reads the sheet and download urls from "info/config.ini"
	Config();

	// Returns the google sheet url
	const std::string& getGoogleSheetUrl() const
	{ return _sheetUrl; }

	const std::string& getDownloadUrl() const
	{ return _downloadUrl; }
};