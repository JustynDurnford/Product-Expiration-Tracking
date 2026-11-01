// ProductExpirationManagerC++
// Month.h
// Created on Mar 13 2026 by Justyn Durnford
// Last modified on Mar 27 2026 by Justyn Durnford
// Header file for the Month class

#pragma once

#include "Defines.h"

#include <compare>
#include <iostream>
#include <string>
#include <vector>

class Month
{
	const u8 _index;
	const u8 _days;
	const u16 _startIndex;
	const std::string _name;

	public:

	// Default constructor
	// Sets the month to the "Null Month".
	Month() : _index(SCAST<u8>(0)), _days(SCAST<u8>(0)), _startIndex(SCAST<u16>(-1)), _name("Null") {}

	// Value constructor
	// Sets _index to the given index value.
	// Sets _days to the given days value.
	// Sets _startIndex to the given startIndex value.
	// Sets _name to the given name value.
	Month(u8 index, u8 days, u16 startIndex, const std::string& name)
		: _index(index), _days(days), _startIndex(startIndex), _name(name) {}

	// Returns the index of the month.
	constexpr u8 getIndex() const noexcept 
	{ return _index; }

	// Returns the days the month has.
	constexpr u8 getDays() const noexcept
	{ return _days; }

	// Returns the day index of the first day of the month.
	constexpr u16 getStartIndex() const noexcept
	{ return _startIndex; }

	// Returns the name of the month.
	constexpr const std::string& getName() const noexcept
	{ return _name; }

	// Returns the index of the nth day of the month.
	constexpr u16 getIndexOfDay(u8 n) const noexcept
	{ return SCAST<u16>(n) + _startIndex; }

	// Returns true if the month is valid.
	// Returns false otherwise.
	constexpr bool isValidMonth() const noexcept
	{ return (_index > SCAST<u8>(0) && _index <= SCAST<u8>(12)); }

	// Returns true if the month is not valid.
	// Returns false otherwise.
	constexpr bool isNullMonth() const noexcept
	{ return (_index == SCAST<u8>(0) || _index > SCAST<u8>(12)); }

	// Returns true if this month is the same as the other month.
	// Returns false otherwise.
	constexpr bool equals(const Month& other) const noexcept
	{ return _index == other._index; }

	// Returns true if this month is not the same as the other month.
	// Returns false otherwise.
	constexpr bool notEquals(const Month& other) const noexcept
	{ return _index != other._index; }

	// Returns true if this month is before the other month.
	// Returns false otherwise. 
	constexpr bool lessThan(const Month& other) const noexcept
	{ return _index < other._index; }

	// Returns true if this month is before the other month or is the same.
	// Returns false otherwise. 
	constexpr bool lessThanOrEquals(const Month& other) const noexcept
	{ return _index <= other._index; }

	// Returns true if this month is after the other month.
	// Returns false otherwise. 
	constexpr bool greaterThan(const Month& other) const noexcept
	{ return _index > other._index; }

	// Returns true if this month is after the other month or is the same.
	// Returns false otherwise. 
	constexpr bool greaterThanOrEquals(const Month& other) const noexcept
	{ return _index > other._index; }

	// Returns a std::strong_ordering describing the relationship of the two months.
	constexpr std::strong_ordering compareWith(const Month& other) const noexcept
	{ return _index <=> other._index; }

	// Returns a std::string of the month's index in the MM format.
	std::string getIndexAsString() const;

	// Returns the month after this one.
	const Month& nextMonth() const noexcept;

	// Returns the month before this one.
	const Month& lastMonth() const noexcept;
};

// Returns true if this month is the same as the other month.
// Returns false otherwise.
constexpr bool operator == (const Month& A, const Month& B)
{ return A.equals(B); }

// Returns true if this month is not the same as the other month.
// Returns false otherwise.
constexpr bool operator != (const Month& A, const Month& B)
{ return A.notEquals(B); }

// Returns true if this month is before the other month.
// Returns false otherwise. 
constexpr bool operator < (const Month& A, const Month& B)
{ return A.lessThan(B); }

// Returns true if this month is before the other month or is the same.
// Returns false otherwise. 
constexpr bool operator <= (const Month& A, const Month& B)
{ return A.lessThanOrEquals(B); }

// Returns true if this month is after the other month.
// Returns false otherwise. 
constexpr bool operator > (const Month& A, const Month& B)
{ return A.greaterThan(B); }

// Returns true if this month is after the other month or is the same.
// Returns false otherwise. 
constexpr bool operator >= (const Month& A, const Month& B)
{ return A.greaterThanOrEquals(B); }

// Returns a std::strong_ordering describing the relationship of the two months.
constexpr std::strong_ordering operator <=> (const Month& A, const Month& B)
{ return A.compareWith(B); }

// Writes the given month to the given output stream.
std::ostream& operator << (std::ostream& os, const Month& month);

extern const std::vector<Month> Months;