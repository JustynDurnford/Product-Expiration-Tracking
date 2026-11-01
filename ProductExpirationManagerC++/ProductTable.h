// ProductExpirationTracker
// ProductTable.h
// Created on Feb 14 2026 by Justyn Durnford
// Last modified on Sep 30 2026 by Justyn Durnford
// Header file for the ProductTable class

#pragma once

#include "Product.h"

#include <map>

#include <string>

// Wrapper class for a std::map that contains
// Date entries for every given product name.
class ProductTable
{
	std::map<std::string, std::vector<Date>> _productMap;

	public:

	using iterator = std::map<std::string, std::vector<Date>>::iterator;
	using const_iterator = std::map<std::string, std::vector<Date>>::const_iterator;

	// Default constructor.
	// Creates an empty map.
	ProductTable() = default;

	// Returns an iterator to the product data matching the given product name.
	// Returns _productMap.end() if no such product is found.
	iterator findProductData(const std::string& productName);

	// Returns a const iterator to the product data matching the given product name.
	// Returns _productMap.cend() if no such product is found.
	std::map<std::string, std::vector<Date>>::const_iterator findProductData(const std::string& productName) const;

	// Returns an iterator to the product data matching the given product.
	// Returns _productMap.end() if no such product is found.
	iterator findProductData(const Product& product);

	// Returns a const iterator to the product data matching the given product.
	// Returns _productMap.cend() if no such product is found.
	std::map<std::string, std::vector<Date>>::const_iterator findProductData(const Product& product) const;

	// Returns an iterator to the product data matching the given product name and kill date.
	// Returns _productMap.end() if no such product is found.
	iterator findProductKillDate(const std::string& productName, Date killDate);

	// Returns a const iterator to the product data matching the given product name and kill date.
	// Returns _productMap.cend() if no such product is found.
	std::map<std::string, std::vector<Date>>::const_iterator findProductKillDate(const std::string& productName, Date killDate) const;

	// Returns an iterator to the product data matching the given product and kill date.
	// Returns _productMap.end() if no such product is found.
	iterator findProductKillDate(const Product& product, Date killDate);

	// Returns a const iterator to the product data matching the given product and kill date.
	// Returns _productMap.cend() if no such product is found.
	std::map<std::string, std::vector<Date>>::const_iterator findProductKillDate(const Product& product, Date killDate) const;

	// Returns true if product data matching the given name exists.
	// Returns false otherwise.
	bool doesProductDataExist(const std::string& productName) const;

	// Returns true if product data matching the given product exists.
	// Returns false otherwise.
	bool doesProductDataExist(const Product& product) const;

	// Returns true if product data with the given name has the given kill date.
	// Returns false otherwise.
	bool doesProductHaveKillDate(const std::string& productName, const Date& killDate) const;

	// Returns true if product data matching the given product has the given kill date.
	// Returns false otherwise.
	bool doesProductHaveKillDate(const Product& product, const Date& killDate) const;

	// Returns a Product instance from the given product data matching the given name.
	// Returns an empty product if no product was found.
	Product getProductData(const std::string& productName) const;

	// Returns a Product instance from the given iterator.
	// Returns an empty product if no product was found.
	Product getProductData(const_iterator iter) const;

	// Returns a std::vector<Date> containing all of the kill dates
	// of the product matching the given name.
	// Returns an empty std::vector<Date> if no product is found.
	std::vector<Date> getProductKillDates(const std::string& productName) const;

	// Returns the earliest kill date of the product matching the given name.
	// Returns a null date if no product is found or if the product has no kill dates.
	Date getProductFirstKillDate(const std::string& productName) const;

	// Adds a Product to the product map constructed with the given values.
	// This function does nothing if a product with the given name already exists.
	iterator addProductData(const std::string& productName, Date killDate = Date());

	// Adds a Product to the product map constructed with the given values.
	// This function does nothing if a product with the given name already exists.
	iterator addProductData(const Product& product);

	// Removes the product data with the given product values from the product map and returns a copy of it.
	// This function does nothing if a product with the given name does not exist.
	Product removeProductData(const std::string& productName);

	// Removes the product data with the given product values from the product map and returns a copy of it.
	// This function does nothing if a product with the given name does not exist.
	Product removeProductData(const Product& product);

	// Removes the product data at the given iterator from the product map and returns a copy of it.
	// This function does nothing if a product with the given name does not exist.
	Product removeProductData(iterator iter);

	// If a Product with the given name already exists:
	// > Sets the data of the product in the product map to a Product with the given values.
	// 
	// If a Product with the given name does not exist:
	// > Adds a Product to the product map constructed with the given values.
	iterator setProductData(const std::string& productName, Date killDate = Date());

	// If a Product with the given name already exists:
	// > Sets the data of the product in the product map to a Product with the given values.
	// 
	// If a Product with the given name does not exist:
	// > Adds a Product to the product map constructed with the given values.
	iterator setProductData(const Product& product);

	// Adds the given kill date to the product with the given name.
	// Returns an iterator to the product data.
	iterator addProductKillDate(const std::string& productName, Date killDate = Date());

	// Adds the given kill dates to the product with the given name.
	// Returns a vector containing all of the added kill dates.
	std::vector<Date> addProductKillDates(const std::string& productName, const std::vector<Date>& killDates);

	// Removes the given kill date from the product with the given name.
	// Returns the removed date.
	Date removeProductKillDate(const std::string& productName, Date killDate);

	// Removes the given kill date from the given product.
	// Returns the removed date.
	Date removeProductKillDate(const Product& product, Date killDate);

	// Erases the kill dates assigned to the product with the given name.
	// Returns the amount of dates erased.
	std::size_t removeProductKillDates(const std::string& productName);

	// Erases the kill dates assigned to the given product.
	// Returns the amount of dates erased.
	std::size_t removeProductKillDates(const Product& product);

	// Erases the existing kill dates of the product with the given name
	// and replaces them with the given kill date.
	// Returns an iterator to the product that the kill date is assigned to.
	// Functionally identical to setProductData(const Product& product) but added for convenience.
	iterator setProductKillDate(const std::string& productName, Date killDate = Date());

	// Erases the existing kill dates of the product with the given name
	// and replaces them with the given vector of kill dates.
	// Returns an iterator to the product that the kill dates are assigned to.
	iterator setProductKillDates(const std::string& productName, const std::vector<Date>& killDates);

	// Returns an iterator to the start of the ProductTable's map.
	iterator begin();

	// Returns a const iterator to the start of the ProductTable's map.
	const_iterator begin() const;

	// Returns an iterator to the end of the ProductTable's map.
	iterator end();

	// Returns a const iterator to the end of the ProductTable's map.
	const_iterator end() const;

	// Returns a std::vector containing all products generated by the existing product data.
	std::vector<Product> getAllProducts() const;
	
	// Checks if the product with the given name expires in the given amount of days.
	// Returns true if this is the case.
	// Returns false if the product does not exist or if it does not expire. 
	bool doesProductExpireInDays(const std::string& productName, i32 days) const;

	// Checks if the product with the given name expires in the given amount of days.
	// Returns true if this is the case.
	// Returns false if the product does not exist or if it does not expire. 
	bool doesProductExpireInDays(const_iterator iter, i32 days) const;

	// Marks the product data matching the given product name as expiring soon.
	void markProductForExpiration(const std::string& productName);

	// Marks the product data from the given iterator as expiring soon.
	void markProductForExpiration(iterator iter);

	// Empties the ProductTable of all data.
	void clear();

	// Returns the amount of products in the ProductTable.
	std::size_t size() const;

	// Returns true if the ProductTable is empty.
	bool isEmpty() const;
};