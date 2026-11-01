// ProductExpirationManagerC++
// CSVFileReader.h
// Created on Feb 10 2026 by Justyn Durnford
// Last modified on Sep 30 2026 by Justyn Durnford
// Header file for the CSVFileReader class

#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

// Wrapper class for an ifstream designed for reading CSV files.
class CSVFileReader
{
    std::ifstream _fin;
    bool _isGood;

    // Attempts to open the given file with the _fin ifstream.
    // Returns true if successful.
    // Returns false otherwise.
    bool _tryOpenFile(const std::filesystem::path& filepath);

    public:

    // Attempts to open the given file with the _fin ifstream.
    // Call member function isGood() to check if this was successful.
    CSVFileReader(const std::filesystem::path& filepath);

    // Returns true if _fin.good() returned true in the last operatrion.
    // Returns false otherwise.
    constexpr bool isGood() const noexcept
    { return _isGood; }

    // Returns true if the end of the file has been reached.
    // Returns false otherwise.
    bool isEOF() const noexcept
    { return _fin.eof(); }

    // Returns true if the file is empty.
    // Returns false otherwise.
    bool isEmpty();

    // Attempts to open the given file with the _fin ifstream.
    // Returns true if successful.
    // Returns false otherwise.
    bool openFile(const std::filesystem::path& filepath);

    // Reads the next comma seperated value from the file and returns it.
    std::string readValue();

    // Reads the entire current line from the file and returns it.
    std::string readLine();

    // Reads all comma seperated values of the current line and returns them.
    std::vector<std::string> getValuesInLine();

    // Closes the file and _fin ifstream.
    void close();
};