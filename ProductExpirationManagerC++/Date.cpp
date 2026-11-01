// ProductExpirationManagerC++
// Date.cpp
// Created on Feb 06 2026 by Justyn Durnford
// Last modified on Aug 01 2026 by Justyn Durnford
// Implementation file for the Date class

#include "Date.h"

#include <ctime>
using std::time_t;
using std::tm;
using std::time;

#include <iostream>
using std::cout;
using std::ios;
using std::istream;
using std::ostream;

// <compare>
using std::strong_ordering;

// <string>
using std::size_t;
using std::string;
using std::stoi;
using std::to_string;

// <tuple>
using std::tuple;
using std::get;
using std::make_tuple;

u16 Date::_calcDayIndex() const noexcept
{
	if (_month->isValidMonth())
		return _month->getStartIndex() + _day - 1;

	return -1;
}

Date::Date(u8 month, u8 day, u16 year)
{
	setValues(month, day, year);
}

Date::Date(const string& str)
{
	readFromString(str);
}

Date::Date(const tuple<u8, u8, u16>& date_tuple)
{
	readFromTuple(date_tuple);
}

Date& Date::operator = (const string& str)
{
	readFromString(str);
	return *this;
}

Date& Date::operator = (const tuple<u8, u8, u16>& date_tuple)
{
	readFromTuple(date_tuple);
	return *this;
}

void Date::setDay(u8 day) noexcept
{
	_day = day;
	_dayIndex = _calcDayIndex();
}

void Date::setMonth(u8 month) noexcept
{
	if (month > SCAST<u8>(0) && month <= SCAST<u8>(12))
		_month = &Months[month];
	else
		_month = &Months[0];

	_dayIndex = _calcDayIndex();
}

void Date::setYear(u16 year) noexcept
{
	_year = year;
}

void Date::setValues(u8 month, u8 day, u16 year) noexcept
{
	_day = day;
	setMonth(month);
	_year = year;

	_dayIndex = _calcDayIndex();
}

void Date::copyFrom(const Date& other) noexcept
{
	_day = other._day;
	_month = other._month;
	_year = other._year;
	_dayIndex = other._dayIndex;
}

void Date::copyTo(Date& other) const noexcept
{
	other._day = _day;
	other._month = _month;
	other._year = _year;
	other._dayIndex = _dayIndex;
}

Date Date::nextDate() const noexcept
{
	if (!isLeapYear(_year))
	{
		if (_month == &Months[2] && _day == 28)
			return Date(3, 1, _year);
	}

	if (_dayIndex == 365)
	{
		Date date(*this);
		date.setYear(_year + 1);
		return date;
	}

	Date date(DateList[_dayIndex + 1]);
	date.setYear(_year);

	return date;
}

Date Date::lastDate() const noexcept
{
	// Check for leap year
	if (!isLeapYear(_year))
	{
		if (_month == &Months[3] && _day == 1)
			return Date(2, 28, _year);
	}

	if (_dayIndex == 0)
	{
		Date date(*this);
		date.setYear(_year - 1);
		return date;
	}

	Date date(DateList[_dayIndex - 1]);
	date.setYear(_year);

	return date;
}

i32 Date::distanceFrom(const Date& other) const noexcept
{
	i32 year_dist = 0;
	i32 day_dist = 0;

	year_dist = SCAST<i32>(other._year) - SCAST<i32>(_year);

	if (year_dist > 0)
	{
		i32 correctedDayIndex = SCAST<i32>(other._dayIndex) + (SCAST<i32>(year_dist) * 365);
		day_dist = correctedDayIndex - SCAST<i32>(_dayIndex);

		u16 leapYears = leapYearsInRange(_year, other._year);

		// Check if leap day has already passed for this year.
		if (isLeapYear(_year) && _month->getIndex() < 2)
			++leapYears;

		return day_dist + leapYears;
	}

	day_dist = SCAST<i32>(other._dayIndex) - SCAST<i32>(_dayIndex);
	return day_dist;
}

Date& Date::addDays(u16 days) noexcept
{
	if (_dayIndex + days > 365)
	{
		u16 year = _year + (days % 366);
		*this = DateList[SCAST<size_t>(days) - SCAST<size_t>(365 - _dayIndex)];
		_year = year;
		return *this;
	}

	u16 year = _year;
	*this = DateList[SCAST<size_t>(_dayIndex + days)];
	_year = year;

	return *this;
}

Date& Date::subtractDays(u16 days) noexcept
{
	if (_dayIndex < days)
	{
		u16 year = _year - (days % 366);
		*this = DateList[SCAST<size_t>(365) - SCAST<size_t>(days - _dayIndex)];
		_year = year;
		return *this;
	}

	u16 year = _year;
	*this = DateList[SCAST<size_t>(_dayIndex - days)];
	_year = year;

	return *this;
}

string Date::toString() const
{
	if (_dayIndex == -1)
		return "NA";

	string str;
	str.reserve(10);

	if (_month->isNullMonth())
		str += "00";
	else
		str += _month->getIndexAsString();

	str += '/';

	if (_day < 10)
		str += '0';
	str += to_string(_day);
	str += '/';

	str += to_string(_year);

	return str;
}

void Date::readFromString(const string& str)
{
	_day = 0;
	_month = &Months[0];
	_year = 0;
	_dayIndex = -1;

	try
	{
		size_t month_ind = 0;
		size_t day_ind = str.find('/');
		size_t year_ind = str.find('/', day_ind + 1);

		string month_str(str.substr(month_ind, day_ind - month_ind));
		string day_str(str.substr(day_ind + 1, year_ind - day_ind - 1));
		string year_str(str.substr(year_ind + 1));

		_day = stoi(day_str);
		_year = stoi(year_str);

		i32 month = stoi(month_str);
		if (month > 0 && month <= 12)
			_month = &Months[month];

		_dayIndex = _calcDayIndex();
	}
	catch (...)
	{
		_day = 0;
		_month = &Months[0];
		_year = 0;
		_dayIndex = -1;
	}
}

tuple<u8, u8, u16> Date::toTuple() const noexcept
{
	if (_month->isNullMonth())
		return make_tuple(0, _day, _year);

	return make_tuple(_month->getIndex(), _day, _year);
}

void Date::readFromTuple(const tuple<u8, u8, u16>& date_tuple) noexcept
{
	u8 month = get<0>(date_tuple);
	
	if (month > SCAST<u8>(0) && month <= SCAST<u8>(12))
		_month = &Months[month];
	else
		_month = &Months[0];

	_day = get<1>(date_tuple);
	_year = get<2>(date_tuple);

	_dayIndex = _calcDayIndex();
}

bool Date::isNullDate() const noexcept
{
	return (_month->isNullMonth() || _day == 0);
}

bool Date::equals(const Date& other) const noexcept
{
	if (_dayIndex == other._dayIndex && _year == other._year)
		return true;

	return false;
}

bool Date::notEquals(const Date& other) const noexcept
{
	if (_dayIndex != other._dayIndex || _year != other._year)
		return true;

	return false;
}

bool Date::lessThan(const Date& other) const noexcept
{
	if (_year != other._year)
		return _year < other._year;
	if (*_month != *other._month)
		return *_month < *other._month;
	return _day < other._day;
}

bool Date::lessThanOrEquals(const Date& other) const noexcept
{
	if (_year < other._year)
		return true;
	if (_year > other._year)
		return false;

	// _year == other._year
	if (*_month < *other._month)
		return true;
	if (*_month > *other._month)
		return false;

	// _year == other._year
	// _month == other._month
	return _day <= other._day;
}

bool Date::greaterThan(const Date& other) const noexcept
{
	if (_year != other._year)
		return _year > other._year;
	if (*_month != *other._month)
		return *_month > *other._month;
	return _day > other._day;
}

bool Date::greaterThanOrEquals(const Date& other) const noexcept
{
	if (_year > other._year)
		return true;
	if (_year < other._year)
		return false;

	// _year == other._year
	if (*_month > *other._month)
		return true;
	if (*_month < *other._month)
		return false;

	// _year == other._year
	// _month == other._month
	return _day >= other._day;
}

strong_ordering Date::compareWith(const Date& other) const noexcept
{
	if (_year < other._year)
		return strong_ordering::less;
	if (_year > other._year)
		return strong_ordering::greater;

	// _year == other._year
	if (*_month < *other._month)
		return strong_ordering::less;
	if (*_month > *other._month)
		return strong_ordering::greater;

	// _year == other._year
	// _month == other._month
	if (_day < other._day)
		return strong_ordering::less;
	if (_day > other._day)
		return strong_ordering::greater;

	return strong_ordering::equal;
}

Date Date::getCurrentDate() noexcept
{
	const time_t now = time(nullptr);
	tm cal_time;
	localtime_s(&cal_time, &now);

	return Date(cal_time.tm_mon + 1, cal_time.tm_mday, cal_time.tm_year + 1900);
}

bool Date::isLeapYear(u16 year) noexcept
{
	return (year % 4 == 0 && year % 100 != 0 || year % 400 == 0);
}

u16 Date::leapYearsUpTo(u16 year)
{
	if (year <= 1)
		return 0;

	// Every 4th year - Every 100th year + Every 400th year
	return (year / 4) - (year / 100) + (year / 400);
}

u16 Date::leapYearsInRange(u16 begin, u16 end)
{
	return leapYearsUpTo(begin) - leapYearsUpTo(end - 1);
}

bool operator == (const Date& A, const Date& B)
{
	return A.equals(B);
}

bool operator != (const Date& A, const Date& B)
{
	return A.notEquals(B);
}

bool operator < (const Date& A, const Date& B)
{
	return A.lessThan(B);
}

bool operator <= (const Date& A, const Date& B)
{
	return A.lessThanOrEquals(B);
}

bool operator > (const Date& A, const Date& B)
{
	return A.greaterThan(B);
}

bool operator >= (const Date& A, const Date& B)
{
	return A.greaterThanOrEquals(B);
}

strong_ordering operator <=> (const Date& A, const Date& B)
{
	return A.compareWith(B);
}

Date& operator ++ (Date& date)
{
	date = date.nextDate();
	return date;
}

Date operator + (Date date, u16 days)
{
	Date newDate(date);
	newDate.addDays(days);
	return newDate;
}

Date& operator += (Date& date, u16 days)
{
	date.addDays(days);
	return date;
}

Date& operator -- (Date& date)
{
	date = date.lastDate();
	return date;
}

Date operator - (Date date, u16 days)
{
	Date newDate(date);
	newDate.subtractDays(days);
	return newDate;
}

Date& operator -= (Date& date, u16 days)
{
	date.subtractDays(days);
	return date;
}

ostream& operator << (ostream& os, const Date& date)
{
	os << date.toString();
	return os;
}

istream& operator >> (istream& is, Date& date)
{
	string dateStr;
	is >> dateStr;
	date.readFromString(dateStr);

	if (date.isNullDate())
		is.setstate(ios::failbit);

	return is;
}