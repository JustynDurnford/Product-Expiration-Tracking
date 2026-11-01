// ProductExpirationManagerC++
// Product.h
// Created on Feb 13 2026 by Justyn Durnford
// Last modified on Oct 17 2026 by Justyn Durnford
// Implementation file for the Product class

#include "Product.h"

#include <algorithm>
using std::find;
using std::sort;

// <string>
using std::size_t;
using std::string;

// <vector>
using std::vector;

Product::Product() : _isMarked{ false }
{}

Product::Product(const string& name, Date killDate) : _isMarked{ false }
{
	_name = name;

	if (!name.empty() && name.back() == '*')
	{
		_name.pop_back();
		_isMarked = true;
	}

	_killDates.push_back(killDate);
}

Product::Product(const string& name, const vector<Date>& killDates) : _isMarked{ false }
{
	_name = name;

	if (!name.empty() && name.back() == '*')
	{
		_name.pop_back();
		_isMarked = true;
	}

	_killDates = killDates;
	sort(_killDates.begin(), _killDates.end());
}

Product::Product(const vector<string>& csvLine) : _isMarked{ false }
{
	readFromCSVLine(csvLine);
}

const string& Product::getName() const
{
	return _name;
}

string Product::getNameMarked() const
{
	string name(_name);

	if (_isMarked)
		name.push_back('*');

	return name;
}

const vector<Date>& Product::getKillDates() const
{
	return _killDates;
}

Date Product::getKillDate(size_t index) const
{
	return _killDates[index];
}

void Product::setName(const string& name)
{
	_name = name;
}

vector<Date>::iterator Product::addKillDate(Date killDate)
{
	if (find(_killDates.begin(), _killDates.end(), killDate) != _killDates.end())
	{
		_killDates.push_back(killDate);
		sort(_killDates.begin(), _killDates.end());
		return find(_killDates.begin(), _killDates.end(), killDate);
	}

	return _killDates.end();
}

vector<Date>::iterator Product::setKillDate(size_t index, Date killDate)
{
	if (index < _killDates.size())
	{
		_killDates[index] = killDate;
		sort(_killDates.begin(), _killDates.end());
		return find(_killDates.begin(), _killDates.end(), killDate);
	}

	return _killDates.end();
}

bool Product::expiresInDays(i32 days)
{
	Date currentDay = Date::getCurrentDate();

	for (Date& date : _killDates)
	{
		i32 distance = currentDay.distanceFrom(date);

		if (distance < days && !date.isNullDate())
			return true;
	}

	return false;
}

string Product::toString() const
{
	string str(getName());

	if (_isMarked)
		str += '*';

	str += ": ";

	if (_killDates.empty())
		str += "NA";
	else if (_killDates[0].isNullDate())
		str += "NA";
	else
	{
		for (size_t i = 0; i < _killDates.size(); ++i)
		{
			if (!_killDates[i].isNullDate())
				str += _killDates[i].toString();
			else
				return str;

			if (i < _killDates.size() - 1 && !_killDates[i + 1].isNullDate())
				str += ", ";
		}
	}

	return str;
}

bool Product::readFromCSVLine(const vector<string>& csvLine)
{
	try
	{
		if (csvLine.size() >= 4)
		{
			string name(csvLine[0]);
			string dateStr;

			if (!name.empty())
			{
				_name = name;

				if (!name.empty() && name.back() == '*')
				{
					_name.pop_back();
					_isMarked = true;
				}

				for (size_t i = 3; i < csvLine.size(); ++i)
				{
					dateStr = csvLine[i];

					if (!dateStr.empty() && dateStr != "NA")
						_killDates.push_back(dateStr);
				}

				return true; 
			}
		}
	}
	catch (...) { return false; }

	return false;
}

string Product::toCSVLine() const
{
	string csvLine;
	csvLine.append(getNameMarked());
	csvLine.append(",,,");

	if (_killDates.empty())
		csvLine.append("NA");
	else
	{
		for (size_t i = 0; i < _killDates.size(); ++i)
			csvLine.append(_killDates[i].toString());
	}

	return csvLine;
}

void Product::mark()
{
	_isMarked = true;
}

void Product::unmark()
{
	_isMarked = false;
}
