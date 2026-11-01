// ProductExpirationManagerC++
// Month.cpp
// Created on Mar 13 2026 by Justyn Durnford
// Last modified on Mar 27 2026 by Justyn Durnford
// Implementation file for the Month class

#include "Month.h"

// #include <ostream>
using std::ostream;

// #include <string>
using std::string;
using std::to_string;

// #include <vector>
using std::vector;

string Month::getIndexAsString() const
{
	if (_index >= SCAST<u8>(13))
		return "00";

	string str;

	if (_index < SCAST<u8>(10))
		str += '0';
	str += to_string(_index);

	return str;
}

const Month& Month::nextMonth() const noexcept
{
	if (_index == SCAST<u8>(12))
		return Months[1];

	return Months[_index + 1];
}

const Month& Month::lastMonth() const noexcept
{
	if (_index == SCAST<u8>(1))
		return Months[12];

	return Months[_index - 1];
}

ostream& operator << (ostream& os, const Month& month)
{
	os << month.getName();
	return os;
}

const vector<Month> Months =
{
	{ Month(0, 0, -1, "Null") },
	{ Month(1, 31, 0, "January") }, 
	{ Month(2, 29, 31, "February") },
	{ Month(3, 31, 60, "March") },
	{ Month(4, 30, 91, "April") }, 
	{ Month(5, 31, 121, "May") },
	{ Month(6, 30, 152, "June") },
	{ Month(7, 31, 182, "July") }, 
	{ Month(8, 31, 213, "August") },
	{ Month(9, 30, 244, "September") },
	{ Month(10, 31, 274, "October") },
	{ Month(11, 30, 305, "November") },
	{ Month(12, 31, 335, "December") }
};