// ProductExpirationManagerC++
// Date.h
// Created on Feb 03 2026 by Justyn Durnford
// Last modified on Aug 01 2026 by Justyn Durnford
// Header file for the Date class

#pragma once

#include "DateList.h"
#include "Month.h"

#include <cstdint>
#include <tuple>

class Date
{
    const Month* _month;
    u8 _day;
    u16 _year;

    u16 _dayIndex;

    // Calculates the day index based on the assigned month and day.
    // This index corresponds to which day of the year it is.
    // This allows for easier math operations.
    u16 _calcDayIndex() const noexcept;

    public:

    // Default constructor
    // Date set as 00/00/0000
    // _dayIndex is set to -1
    constexpr Date() : _month(&Months[0]), _day(0), _year(0), _dayIndex(-1) {}

    // Value constructor
    // Sets _month to &Months[month]
    // Sets _day to day
    // Sets _year to year
    Date(u8 month, u8 day, u16 year);

    // Copy constructor
    Date(const Date& other) = default;

    // Move constructor
    Date(Date&& other) = default;

    // std::string constructor
    // Parses the given string and assings the values.
    // This function assumes the string is the MM/DD/YYYY format.
    // If the string cannot be parsed, the date is set to 00/00/0000.
    Date(const std::string& str);

    // std::tuple constructor
    // Sets the month, day and year to the values of the tuple.
    Date(const std::tuple<u8, u8, u16>& date_tuple);

    // Copy assignment operator
    Date& operator = (const Date& other) = default;

    // Move assignment operator
    Date& operator = (Date&& other) = default;

    // std::string assignment operator
    // Parses the given string and assigns the values.
    // This function assumes the string is the MM/DD/YYYY format.
    // If the string cannot be parsed, the date is set to 00/00/0000.
    Date& operator = (const std::string& str);

    // std::tuple assignment operator
    // Sets the month, day and year to the values of the tuple.
    Date& operator = (const std::tuple<u8, u8, u16>& date_tuple);

    // Returns a pointer to the assigned month.
    const Month& getMonth() const noexcept
    { return *_month; }

    // Returns the value of the day.
    constexpr u8 getDay() const noexcept
    { return _day; }

    // Returns the value of the year.
    constexpr u16 getYear() const noexcept
    { return _year; }

    // Returns the value of the day index.
    constexpr u16 getDayIndex() const noexcept
    { return _dayIndex; }

    // Sets the value of the month to the given value.
    void setMonth(u8 month) noexcept;

    // Sets the value of the day to the given value.
    void setDay(u8 day) noexcept;

    // Sets the value of the year to the given value.
    void setYear(u16 year) noexcept;

    // Sets the value of the month to the given value.
    // Sets the value of the day to the given value.
    // Sets the value of the year to the given value.
    void setValues(u8 month, u8 day, u16 year) noexcept;

    // Copies the values from the given date to this date.
    void copyFrom(const Date& other) noexcept;

    // Copies the values from this date to the given date.
    void copyTo(Date& other) const noexcept;

    // Returns the subsequent date of the year.
    Date nextDate() const noexcept;

    // Returns the previous date of the year.
    Date lastDate() const noexcept;

    // Returns the amount of days between this date and the given date.
    i32 distanceFrom(const Date& other) const noexcept;

    // Adds the given number of days onto this one and returns this date.
    Date& addDays(u16 days) noexcept;

    // Subtracts the given number of days onto this one and returns this date.
    Date& subtractDays(u16 days) noexcept;

    // Returns a std::string representation of the date.
    std::string toString() const;

    // Parses the given string and assigns the values.
    // This function assumes the string is the MM/DD/YYYY format.
    // If the string cannot be parsed, the date is set to 00/00/0000.
    void readFromString(const std::string& str);

    // Returns a std::tuple that contains the values of the date.
    std::tuple<u8, u8, u16> toTuple() const noexcept;

    // Parses the given tuple and assigns the values to the date.
    void readFromTuple(const std::tuple<u8, u8, u16>& date_tuple) noexcept;

    // Returns true if this date is an invalid date.
    bool isNullDate() const noexcept;

    // Returns true if all of the following are true:
    // >> A._day == B._day
    // >> A._month == B._month
    // >> A._year == B._year;
    // 
    // Returns false otherwise.
    bool equals(const Date& other) const noexcept;

    // Returns true if any of the following are true:
    // >> A._day != B._day
    // >> A._month != B._month
    // >> A._year != B._year;
    // 
    // Returns false otherwise.
    bool notEquals(const Date& other) const noexcept;

    // Returns true if all of the following are true:
    // >> A._day < B._day
    // >> A._month <= B._month
    // >> A._year <= B._year;
    // 
    // Returns false otherwise.
    bool lessThan(const Date& other) const noexcept;

    // Returns true if all of the following are true:
    // >> A._day <= B._day
    // >> A._month <= B._month
    // >> A._year <= B._year;
    // 
    // Returns false otherwise.
    bool lessThanOrEquals(const Date& other) const noexcept;

    // Returns true if all of the following are true:
    // >> A._day > B._day
    // >> A._month >= B._month
    // >> A._year >= B._year;
    // 
    // Returns false otherwise.
    bool greaterThan(const Date& other) const noexcept;

    // Returns true if all of the following are true:
    // >> A._day >= B._day
    // >> A._month >= B._month
    // >> A._year >= B._year;
    // 
    // Returns false otherwise.
    bool greaterThanOrEquals(const Date& other) const noexcept;

    // Compares the two dates and returns a
    // std::strong_ordering describing their order.
    // 
    // Returns std::strong_ordering::less if A < B
    // Returns std::strong_ordering::greater if A > B
    // Returns std::strong_ordering::equal if A = B
    std::strong_ordering compareWith(const Date& other) const noexcept;

    // Static member function.
    // Returns the current date.
    static Date getCurrentDate() noexcept;

    // Static member function.
    // Returns true if the given year is a leap year.
    static bool isLeapYear(u16 year) noexcept;

    // Static member function.
    // Returns the amount of leap years between year 1 AD and the given year.
    static u16 leapYearsUpTo(u16 year);

    // Static member function.
    // Returns the amount of leap years between and including the given years.
    static u16 leapYearsInRange(u16 begin, u16 end);
};

// == Operator
// 
// Returns true if all of the following are true:
// >> A._day == B._day
// >> A._month == B._month
// >> A._year == B._year;
// 
// Returns false otherwise.
bool operator == (const Date& A, const Date& B);

// != Operator
// 
// Returns true if any of the following are true:
// >> A._day != B._day
// >> A._month != B._month
// >> A._year != B._year;
// 
// Returns false otherwise.
bool operator != (const Date& A, const Date& B);

// < Operator
// 
// Returns true if all of the following are true:
// >> A._day < B._day
// >> A._month <= B._month
// >> A._year <= B._year;
// 
// Returns false otherwise.
bool operator < (const Date& A, const Date& B);

// <= Operator
// 
// Returns true if all of the following are true:
// >> A._day <= B._day
// >> A._month <= B._month
// >> A._year <= B._year;
// 
// Returns false otherwise.
bool operator <= (const Date& A, const Date& B);

// > Operator
// 
// Returns true if all of the following are true:
// >> A._day > B._day
// >> A._month >= B._month
// >> A._year >= B._year;
// 
// Returns false otherwise.
bool operator > (const Date& A, const Date& B);

// >= Operator
// 
// Returns true if all of the following are true:
// >> A._day >= B._day
// >> A._month >= B._month
// >> A._year >= B._year;
// 
// Returns false otherwise.
bool operator >= (const Date& A, const Date& B);

// <=> Operator
// 
// Compares the two dates and returns a
// std::strong_ordering describing their order.
// 
// Returns std::strong_ordering::less if A < B
// Returns std::strong_ordering::greater if A > B
// Returns std::strong_ordering::equal if A = B
std::strong_ordering operator <=> (const Date& A, const Date& B);

// ++ Operator
// Increments the date by 1.
Date& operator ++ (Date& date);

// + Operator
// Adds the given number of days to the given date and returns the result.
Date operator + (Date date, u16 days);

// += Operator
// Adds the given number of days to the given date and returns the given date.
Date& operator += (Date& date, u16 days);

// -- Operator
// Decrements the date by 1.
Date& operator -- (Date& date);

// - Operator
// Subtracts the given number of days from the given date and returns the result.
Date operator - (Date date, u16 days);

// -= Operator
// Subtracts the given number of days from the given date and returns the given date.
Date& operator -= (Date& date, u16 days);

// << Operator
// Writes the given date to the given output stream.
std::ostream& operator << (std::ostream& os, const Date& date);

// >> Operator
// Reads the given date from the given input stream.
// Sets the istream's failbit to true if unsuccessful.
std::istream& operator >> (std::istream& is, Date& date);