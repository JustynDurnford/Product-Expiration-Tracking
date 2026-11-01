// ProductExpirationManagerC++
// Config.cpp
// Created on Oct 01 2026 by Justyn Durnford
// Last modified on Oct 01 2026 by Justyn Durnford
// Implementation file for Config.h

#include "Config.h"

#include <fstream>
using std::ifstream;

#include <string>
using std::size_t;
using std::string;
using std::getline;

string Config::_getUrlFromLine(const string& line) const
{
	const size_t pos = line.find('=');

	if (pos != string::npos && line.size() - pos > 2)
		return line.substr(pos + 2);
	else
		return "";
}

Config::Config()
{
	ifstream fin("info/config.txt");

	if (fin.good() && fin.peek() != ifstream::traits_type::eof())
	{
		string line1, line2;

		getline(fin, line1);

		if (fin.good() && !fin.eof())
		{
			getline(fin, line2);

			string sheetUrl = _getUrlFromLine(line1);
			string downloadUrl = _getUrlFromLine(line2);

			if (!sheetUrl.empty() && !downloadUrl.empty())
			{
				_sheetUrl = sheetUrl;
				_downloadUrl = downloadUrl;
			}
		}
	}
}
