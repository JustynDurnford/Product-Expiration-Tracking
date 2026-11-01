// ProductExpirationManagerC++
// CSVFileWriter.cpp
// Created on Feb 23 2026 by Justyn Durnford
// Last modified on Mar 27 2026 by Justyn Durnford
// Implementation file for the CSVFileWriter class

#include "CSVFileWriter.h"

// <filesystem>
using std::filesystem::path;
using std::filesystem::exists;

// <fstream>
using std::ifstream;

// <string>
using std::string;

// <vector>
using std::vector;

bool CSVFileWriter::_tryOpenFile(const path& filepath)
{
    _isGood = false;

    _fout.open(filepath);

    if (_fout.is_open())
        _isGood = true;

    return _isGood;
}

CSVFileWriter::CSVFileWriter(const path& filepath)
{
    _tryOpenFile(filepath);
}

bool CSVFileWriter::openFile(const path& filepath)
{
    return _tryOpenFile(filepath);
}

bool CSVFileWriter::writeValue(const string& str)
{
    _fout << str << ',';
    _isGood = _fout.good();
    return _isGood;
}

bool CSVFileWriter::writeLine(const string& str)
{
    _fout << str << ",\n";
    _isGood = _fout.good();
    return _isGood;
}

bool CSVFileWriter::writeValues(const vector<string>& values)
{
    for (const string& value : values)
        _fout << value << ',';
    _fout << '\n';

    _isGood = _fout.good();
    return _isGood;
}

void CSVFileWriter::close()
{
    _fout.close();
    _isGood = false;
}