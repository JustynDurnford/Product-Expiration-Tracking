// ProductExpirationManagerC++
// CSVFileWriter.h
// Created on Feb 23 2026 by Justyn Durnford
// Last modified on Oct 17 2026 by Justyn Durnford
// Header file for the CSVFileWriter class

#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

// Wrapper class for an ifstream designed for writing CSV files.
class CSVFileWriter
{
	std::ofstream _fout;
	bool _isGood;

    // Attempts to open the given file with the _fout ofstream.
    // Returns true if successful.
    // Returns false otherwise.
	bool _tryOpenFile(const std::filesystem::path& filepath);

	public:

    // Attempts to open the given file with the _fout fstream.
    // Call member function isGood() to check if this was successful.
    CSVFileWriter(const std::filesystem::path& filepath);

    // Returns true if _fout.good() returned true in the last operatrion.
    // Returns false otherwise.
    constexpr bool isGood() const noexcept
    { return _isGood; }

    // Attempts to open the given file with the _fout ofstream.
    // Returns true if successful.
    // Returns false otherwise.
    bool openFile(const std::filesystem::path& filepath);

    // Writes the string to the file as a comma seperated value.
    // Returns true if the operation was successful.
    // Returns false otherwise.
    bool writeValue(const std::string& str);

    // Writes the given string line to the file as a comma seperated value.
    // Returns true if the operation was successful.
    // Returns false otherwise.
    bool writeLine(const std::string& str);

    // Reads all given comma seperated to the file.
    bool writeValues(const std::vector<std::string>& values);

    // Closes the file and _fout ofstream.
    void close();
};