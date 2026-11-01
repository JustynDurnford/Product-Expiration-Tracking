// ProductExpirationManagerC++
// Manager.cpp
// Created on Aug 01 2026 by Justyn Durnford
// Last modified on Nov 01 2026 by Justyn Durnford
// Implementation file for the Manager class

#include "Manager.h"

#include "CSVFileReader.h"
#include "CSVFileWriter.h"
#include "Utility.h"

#include <algorithm>
using std::find;

#include <fstream>
using std::ofstream;

#include <functional>
using std::function;

#include <iostream>
using std::cin;
using std::cout;

#include <memory>
using std::addressof;

#include <stdexcept>
using std::invalid_argument;
using std::out_of_range;

#include <sstream>
using std::istringstream;

#include <string>
using std::string;
using std::getline;
using std::stoi;
using std::to_string;

#include <vector>
using std::vector;

vector<string> Manager::_getArgs(const string& line)
{
    vector<string> args;
    string arg;
    istringstream str_stream(line);
    char delimiter = ',';
    
    while (getline(str_stream, arg, delimiter))
    {
        if (arg.size() > 1 && arg[0] == ' ')
            arg = arg.substr(1);

        args.push_back(arg);
    }

    return args;
}

bool Manager::_tryDownload()
{
    // Try downloading file
    if (_csvDownloadLink.empty())
    {
        cout << "ERROR: Empty download link\n";
        return false;
    }

    cout << "Downloading file from " + _googleSheetLink + "\n";
    DownloadResultCode download_result = DownloadResultCode::FAILURE;
    download_result = downloadToFile(_csvDownloadLink, "data.csv");

    // Check download bool
    switch (download_result)
    {
        case DownloadResultCode::SUCCESS:
            cout << "File download successful.\n";
            return true;
        break;

        case DownloadResultCode::BAD_URL:
            cout << "ERROR: Invalid URL.\n";
            return false;
        break;

        case DownloadResultCode::BAD_FILE:
            cout << "ERROR: Invalid filepath.\n";
            return false;
        break;

        case DownloadResultCode::FAILURE:
            cout << "ERROR: Failed to download file.\n";
            return false;
        break;

        default:
            cout << "ERROR: Unknown.\n";
            return false;
        break;
    }
}

bool Manager::_tryReadFile()
{
    CSVFileReader in_file("info\\data.csv");

    if (!in_file.isGood())
    {
        cout << "ERROR: Could not read file \"info\\data.csv\"\n";
        cout << "This program needs a data.csv file to operate.\n";
        cout << "Would you like to create a blank one in the current directory? (yes or no)\n";
        return false;
    }
    else if (in_file.isEmpty())
    {
        cout << "data.csv file is present, but empty. Proceeding with empty file.\n";
        return false;
    }
    else
    {
        vector<string> line;
        Date currentDay(Date::getCurrentDate());

        while (in_file.isGood())
        {
            line = in_file.getValuesInLine();

            if (in_file.isGood() || in_file.isEOF())
                _productTable.addProductData(Product(line));
        }

        in_file.close();
        return true;
    }
}

bool Manager::_add(const vector<string>& args)
{
    if (args.size() == 1)
    {
        cout << "ERROR: Not enough arguments given.\n\"add\" requires a product name and 1 or more kill dates as arguments.\n";
        return false;
    }
    else if (args.size() == 2)
    {
        cout << "ERROR: Not enough arguments given.\n\"add\" requires a product name and 1 or more kill dates as arguments.\n";
        return false;
    }
    else if (args.size() > 2 && args[1].empty())
    {
        cout << "ERROR: Product Name \"\" is invalid.";
        return false;
    }
    else
    {
        string productName = args[1];
        vector<Date> killDates;

        for (size_t i = 2; i < args.size(); ++i)
        {
            Date killDate(args[i]);

            if (killDate.isNullDate())
                cout << "WARNING: Invalid date value: { " + args[i] + " } given. Value discarded.\n";
            else
                killDates.push_back(killDate);
        }

        Product product(productName, killDates);

        if (_productTable.doesProductDataExist(product))
        {
            cout << "Product named: \"" + productName + "\" already exists.\n";
            cout << "Kill dates to add: ";

            for (const Date& killDate : product.getKillDates())
                cout << killDate.toString() + " ";
            cout << '\n';

            _addNewKillDate(product, killDates);
            cout << "Added new kill dates to the existing product.\n";
            return true;
        }
        else
        {
            cout << "Product named: \"" + productName + "\" does not exist.\n";
            cout << "Adding new product.\n";

            _addNewProductData(product);
            return true;
        }
    }
}

bool Manager::_addNewProductData(const Product& product)
{
    ProductTable::iterator iter = _productTable.addProductData(product);

    if (iter == _productTable.end())
    {
        cout << "ERROR: Failed to add product: " + product.getName() + '\n';
        cout << "Check if the product already exists.\n";
        return false;
    }
    else
    {
        cout << "Product: " + product.getName() + " successfully added!\n";
        return true;
    }
}

bool Manager::_addNewKillDate(const Product& product, const vector<Date>& killDates)
{
    vector<Date> addedDates = _productTable.addProductKillDates(product.getName(), killDates);

    if (addedDates.empty())
    {
        cout << "ERROR: Could not add given kill dates to product: " + product.getName() + '\n';
        cout << "Make sure the product exists and it does not already have the given dates.\n";
        return false;
    }
    else
    {
        cout << "The following dates were successfully added: ";

        for (Date& date : addedDates)
            cout << date.toString() + " ";
        cout << '\n';

        return true;
    }
}

bool Manager::_remove(const vector<string>& args)
{
    if (args.size() == 1)
    {
        cout << "ERROR: Not enough arguments given.\n";
        cout << "\"remove\" requires at least a product name.\n";
        return false;
    }
    else if (args.size() == 2 && args[1] == "all")
    {
        _productTable.clear();
        cout << "Removed all products from the product table.\n";
        return true;
    }
    else
    {
        string productName = args[1];
        ProductTable::iterator iter = _productTable.findProductData(productName);

        if (iter == _productTable.end())
        {
            cout << "ERROR: Product named: " + productName + " not found.\n";
            cout << "Check that spelling is correct and that the product in fact exists with \"display\"\n";
            return false;
        }
        else if (args.size() == 2)
        {
            Product removedProduct(_productTable.removeProductData(productName));
            cout << "Product: " + removedProduct.getName() + " removed successfully.\n";
            return true;
        }
        else
        {
            vector<Date> killDates;
            vector<Date> removedDates;

            for (size_t i = 2; i < args.size(); ++i)
                killDates.push_back(Date(args[i]));

            for (Date& killDate : killDates)
            {
                Date removedDate(_productTable.removeProductKillDate(productName, killDate));

                if (!removedDate.isNullDate())
                    removedDates.push_back(removedDate);
            }

            cout << "The following killdates for the product: " + productName + " were removed: ";
            for (Date& removedDate : removedDates)
                cout << removedDate.toString() + " ";
            cout << '\n';

            return true;
        }
    }
}

bool Manager::_mark(const vector<string>& args)
{
    if (args.size() == 1)
    {
        cout << "ERROR: Not enough arguments given.\n";
        cout << "\"mark\" requires an integer value as an argument.\n";
        return false;
    }
    else
    {
        try
        {
            const i32 days = stoi(args[1]);

            // We create a copy here because markProductForExpiration can invalidate iterators.
            ProductTable _tableCopy(_productTable);

            for (ProductTable::iterator iter = _productTable.begin(); iter != _productTable.end(); ++iter)
            {
                if (_productTable.doesProductExpireInDays(iter, days))
                {
                    string name(iter->first);

                    if (!name.empty() && name.back() == '*')
                        name.pop_back();

                    cout << name << " expires on: ";

                    for (Date& killDate : iter->second)
                        cout << killDate.toString() + " ";
                    cout << '\n';

                    _tableCopy.markProductForExpiration(iter->first);
                }
            }

            _productTable = _tableCopy;
            return true;
        }
        catch (invalid_argument& error)
        {
            cout << "ERROR: Invalid argument: \"" + args[1] + "\"\n";
            cout << "Argument should be an integer value.\n";
            cout << error.what() + '\n';
            return false;
        }
    }
}

bool Manager::_display(const vector<string>& args)
{
    if (args.size() == 1)
    {
        _displayAll();
        return true;
    }
    else if (args[1].empty())
    {
        cout << "ERROR: No argument given.\nArgument should either be \"all\" or an integer value.\n";
        return false;
    }
    else if (args[1] == "all")
    {
        _displayAll();
        return true;
    }
    else
    {
        try
        {
            const i32 days = stoi(args[1]);
            _displayExpiring(days);
            return true;
        }
        catch (invalid_argument& error)
        {
            cout << "ERROR: Invalid argument: \"" + args[1] + "\"\n";
            cout << "Argument should be an integer value.\n";
            cout << error.what() + '\n';
            return false;
        }
    }
}

bool Manager::_displayAll()
{
    string message;

    if (_productTable.isEmpty())
    {
        cout << "There are no products available to display!\n";
        return false;
    }
    else
    {
        string line;
        Product product;

        for (ProductTable::iterator iter = _productTable.begin(); iter != _productTable.end(); ++iter)
        {
            product = _productTable.getProductData(iter);

            line = product.getNameMarked();
            size_t space = 60 - line.size();
            line.append(string(space, ' '));

            if (product.getKillDates().empty())
                line += "NA   ";
            else
            {
                for (const Date& date : product.getKillDates())
                    line += date.toString() + "   ";
            }

            cout << line + '\n';
        }

        if (!message.empty() && message.back() == '\n')
            message.pop_back();

        return true;
    }
}

bool Manager::_displayExpiring(i32 days)
{
    cout << "The following products expire in " + to_string(days) + "days:\n";
    Product product;

    for (ProductTable::iterator iter = _productTable.begin(); iter != _productTable.end(); ++iter)
    {
        product = _productTable.getProductData(iter);

        if (product.expiresInDays(days))
            cout << product.toString() + '\n';
    }

    return true;
}

bool Manager::_save(const vector<string>& args)
{
    CSVFileWriter fout("info\\data.csv");
    vector<string> csvLines;

    for (ProductTable::iterator iter = _productTable.begin(); iter != _productTable.end(); ++iter)
    {
        Product product(_productTable.getProductData(iter));
        csvLines.push_back(product.toCSVLine());
    }

    for (size_t i = 0; i < csvLines.size(); ++i)
    {
        // Last line, don't write newline character.
        if (i == csvLines.size() - 1)
            fout.writeValue(csvLines[i]);
        else
            fout.writeLine(csvLines[i]);
    }

    cout << "Product info saved to info\\data.csv!\n";
    fout.close();

    return true;
}

bool Manager::_quit(const vector<string>& args)
{
    _shouldContinue = false;
    return _save(args);
}

bool Manager::_chooseFunction(const vector<string>& args)
{
    if (args.empty())
    {
        cout << "ERROR: No arguments given.\n";
        return false;
    }
    else
    {
        string func_str(args[0]);

        try
        {
            function<bool(Manager&, const vector<string>&)> func = _functionMap.at(func_str);
            return func(*this, args);
        }
        catch (out_of_range& error)
        {
            cout << "ERROR: No operation with the given name \"" + args[0] + "\" exists.\n";
            cout << error.what() + '\n';
            return false;
        }
    }
}

void Manager::_wait()
{
    string line;
    vector<string> args;

    cout << '\n';
    cout << "Select from the following options: \n\n";
    cout << "add, [NEW_PRODUCT_NAME], [KILL_DATE]:    Add a product with the given name and kill date.\n";
    cout << "add, [OLD_PRODUCT_NAME], [KILL_DATE]:    Add a kill date to the existing product with the given name.\n";
    cout << "remove, [PRODUCT_NAME]:                  Remove the product with the given name.\n";
    cout << "remove, [PRODUCT_NAME], [KILL_DATE]:     Remove the given date from the product with the given name.\n";
    cout << "remove, all:                             Remove every product from the program.\n";
    cout << "display, all:                            Print every product.\n";
    cout << "display, [DAYS]:                         Print all products that expire in the given days from today.\n";
    cout << "mark, [DAYS]:                            Mark all products that expire within the given amount of days with \'*\'\n";
    cout << "save:                                    Save the product data that you have worked on so far.\n";
    cout << "quit:                                    End the program.\n";
    cout << '\n';

    getline(cin, line);
    cout << '\n';
    args = _getArgs(line);

    _chooseFunction(args);
}

Manager::Manager(const Config& config)
{
    if (!config.getGoogleSheetUrl().empty() && !config.getDownloadUrl().empty())
    {
        _googleSheetLink = config.getGoogleSheetUrl();
        _csvDownloadLink = config.getDownloadUrl();
    }

    _functionMap["add"] = function<bool(Manager&, const vector<string>&)>(&Manager::_add);
    _functionMap["display"] = function<bool(Manager&, const vector<string>&)>(&Manager::_display);
    _functionMap["mark"] = function<bool(Manager&, const vector<string>&)>(&Manager::_mark);
    _functionMap["remove"] = function<bool(Manager&, const vector<string>&)>(&Manager::_remove);
    _functionMap["save"] = function<bool(Manager&, const vector<string>&)>(&Manager::_save);
    _functionMap["quit"] = function<bool(Manager&, const vector<string>&)>(&Manager::_quit);
}

void Manager::start()
{
    if (_tryDownload() == true)
    {

    }
    else
    {
        cout << "ERROR: Unable to download csv file from " << _csvDownloadLink << '\n';
        cout << "Proceeding with existing data.csv file.\n";
    }

    if (_tryReadFile() == true)
    {
        cout << "data.csv loaded successfully! Proceeding with program!\n";
    }
    else
    {
        cout << "ERROR: Could not read file \"info\\data.csv\"\n";
        cout << "This program needs a data.csv file to operate.\n";
        cout << "Would you like to create a blank one in the current directory? (yes or no)\n";

        string line;

        while (line != "yes" && line != "no")
        {
            getline(cin, line);

            if (line == "yes")
            {
                cout << "Creating blank data.csv file...\n";
                ofstream fout("info\\data.csv");

                if (fout.good())
                {
                    cout << "data.csv created succesfully! Proceeding with program!\n";
                    _tryReadFile();
                    fout.close();
                    return;
                }
                else
                {
                    cout << "ERROR: Could not create file data.csv.\n";
                    cout << "Press any key to exit the program.\n";
                    cin.get();
                    _shouldContinue = false;
                    return;
                }
            }
            else if (line == "no")
            {
                _shouldContinue = false;
                return;
            }
            else
            {
                cout << "ERROR: Please enter yes or no\n";
            }
        }
    }

    while (_shouldContinue)
        _wait();
}