// ProductExpirationManagerC++
// Manager.h
// Created on Aug 01 2026 by Justyn Durnford
// Last modified on Nov 01 2026 by Justyn Durnford
// Header file for the Manager class

#pragma once

#include "Config.h"
#include "Date.h"
#include "Product.h"
#include "ProductTable.h"

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

// This class maintains the flow of control for the program.
class Manager
{
	ProductTable _productTable;
	std::string _googleSheetLink;
	std::string _csvDownloadLink;
	std::unordered_map<std::string, std::function<bool(Manager&, const std::vector<std::string>&)>> _functionMap;
	bool _shouldContinue = true;

	// Parses the line into a sequence of string arguments.
	std::vector<std::string> _getArgs(const std::string& line);

	// Attempt to download the csv file from online.
	bool _tryDownload();

	// Attempt to read the data.csv file.
	bool _tryReadFile();

	// Add item data to the ProductTable.
	bool _add(const std::vector<std::string>& args);

	// Add a new product to the ProductTable.
	bool _addNewProductData(const Product& product);

	// Add a new kill date to the given product in the ProductTable.
	bool _addNewKillDate(const Product& product, const std::vector<Date>& killDates);

	// Remove the given item data from the ProductTable.
	bool _remove(const std::vector<std::string>& args);

	// Mark all products that expire within the given amount of days.
	bool _mark(const std::vector<std::string>& args);

	// Master function for displaying products.
	bool _display(const std::vector<std::string>& args);

	// Displays every product.
	bool _displayAll();

	// Displays all of the products that expire within the given amount of days.
	bool _displayExpiring(i32 days);

	// Saves the edits made with the program.
	bool _save(const std::vector<std::string>& args);

	// Quits the program.
	bool _quit(const std::vector<std::string>& args);
	
	// Chooses which functions to call based on the arguments.
	bool _chooseFunction(const std::vector<std::string>& args);

	// Prompts the user to give input and waits.
	void _wait();

	public:

	// Constructs the program with the given links if they are provided.
	Manager(const Config& config);

	// Starts the manager.
	void start();
};