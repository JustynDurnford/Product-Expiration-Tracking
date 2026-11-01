// ProductExpirationManagerC++
// Product.h
// Created on Feb 13 2026 by Justyn Durnford
// Last modified on Oct 16 2026 by Justyn Durnford
// Header file for the Product class

#pragma once

#include "Date.h"

class Product
{
	std::string _name;
	std::vector<Date> _killDates;
	bool _isMarked;

	public:

	// Default constructor.
	// Sets the name and killDate vector as empty.
	Product();

	// Primary constructor
	// Sets the name of the product to the given string.
	// Sets the kill date of the product to the given date.
	Product(const std::string& name, Date killDate);

	// Secondary constructor
	// Sets the name of the product to the given string.
	// Sets the kill dates of the product to the given vector of dates.
	Product(const std::string& name, const std::vector<Date>& killDates);

	// CSV line constructor.
	// Parses the given csv line into the product.
	Product(const std::vector<std::string>& csvLine);

	// Returns the name of the product.
	const std::string& getName() const;

	// Returns the name of the product with a trailing '*' if it is marked.
	std::string getNameMarked() const;

	// Returns the product's vector of kill dates.
	const std::vector<Date>& getKillDates() const;

	// Returns the earliest kill date of the product.
	Date getKillDate(std::size_t index) const;

	// Sets the name of the product to the givn string.
	void setName(const std::string& name);

	// Adds the given kill date to the product's vector of kill dates.
	// The kill dates are sorted from earliest to latest.
	std::vector<Date>::iterator addKillDate(Date killDate);

	// Erases the product's vector of kill dates and replaces it with the given kill date.
	std::vector<Date>::iterator setKillDate(std::size_t index, Date killDate);

	// Returns true if the product will expire within the given amount of days.
	bool expiresInDays(i32 days);

	// Returns a std::string representation of the product.
	std::string toString() const;

	// Parses the given csv line into the product.
	// Returns true if the operation was successful.
	bool readFromCSVLine(const std::vector<std::string>& csvLine);

	// Returns a CSV line representation of the product.
	std::string toCSVLine() const;

	// Returns true if this is a valid product.
	// Returns false otherwise.
	constexpr bool isValid() const noexcept
	{ return _killDates.empty(); }

	// Returns true if this is an invalid product.
	// Returns false otherwise.
	constexpr bool isNull() const noexcept
	{ return !_killDates.empty(); }

	// Returns true if the product is marked to expire soon.
	constexpr bool isMarked() const noexcept
	{ return _isMarked; }

	// Marks the product as expiring soon.
	void mark();

	// Unmarks the product.
	void unmark();
};