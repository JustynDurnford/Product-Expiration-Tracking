// ProductExpirationManagerC++
// CSVFileReader.cpp
// Created on Feb 11 2026 by Justyn Durnford
// Last modified on Oct 17 2026 by Justyn Durnford
// Implementation file for the CSVFileReader class

#include "CSVFileReader.h"

// <filesystem>
using std::filesystem::path;
using std::filesystem::exists;

// <fstream>
using std::ifstream;

#include <sstream>
using std::istringstream;

// <string>
using std::string;
using std::getline;

// <vector>
using std::vector;

bool CSVFileReader::_tryOpenFile(const path& filepath)
{
    _isGood = false;

    if (exists(filepath))
    {
        _fin.open(filepath);

        if (_fin.is_open())
            _isGood = true;
    }

    return _isGood;
}

CSVFileReader::CSVFileReader(const path& filepath)
{
    _tryOpenFile(filepath);
}

bool CSVFileReader::isEmpty()
{
    return _fin.peek() == ifstream::traits_type::eof();
}

bool CSVFileReader::openFile(const path& filepath)
{
    return _tryOpenFile(filepath);
}

string CSVFileReader::readValue()
{
    string str;
    _fin >> str;

    _isGood = _fin.good();
    return str;
}

string CSVFileReader::readLine()
{
    string str;
    getline(_fin, str);

    _isGood = _fin.good();
    return str;
}

vector<string> CSVFileReader::getValuesInLine()
{
    string line = readLine();
    string value;
    istringstream istr(line);
    vector<string> values;

    while (getline(istr, value, ','))
        values.push_back(value);

    // Special case if line ends with comma (empty last field)
    if (!line.empty() && line.back() == ',')
        values.push_back("");

    _isGood = _fin.good();
    return values;
}

void CSVFileReader::close()
{
    _fin.close();
    _isGood = false;
}