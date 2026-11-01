// ProductExpirationManagerC++
// ProductTable.cpp
// Created on Feb 14 2026 by Justyn Durnford
// Last modified on Sep 30 2026 by Justyn Durnford
// Implementation file for the ProductTable class

#include "ProductTable.h"

#include <algorithm>
using std::find;
using std::sort;

#include <map>
using std::map;
using std::pair;
using std::make_pair;

#include <string>
using std::size_t;
using std::string;

#include <vector>
using std::vector;

ProductTable::iterator ProductTable::findProductData(const string& productName)
{
	return _productMap.find(productName);
}

ProductTable::const_iterator ProductTable::findProductData(const string& productName) const
{
	return _productMap.find(productName);
}

ProductTable::iterator ProductTable::findProductData(const Product& product)
{
	return _productMap.find(product.getName());
}

ProductTable::const_iterator ProductTable::findProductData(const Product& product) const
{
	return _productMap.find(product.getName());
}

ProductTable::iterator ProductTable::findProductKillDate(const string& productName, Date killDate)
{
	map<string, vector<Date>>::iterator iter(findProductData(productName));
	vector<Date>& killDates = iter->second;

	for (Date& date : killDates)
	{
		if (date == killDate)
			return iter;
	}

	return _productMap.end();
}

ProductTable::const_iterator ProductTable::findProductKillDate(const string& productName, Date killDate) const
{
	map<string, vector<Date>>::const_iterator iter(findProductData(productName));
	const vector<Date>& killDates = iter->second;

	for (const Date& date : killDates)
	{
		if (date == killDate)
			return iter;
	}

	return _productMap.end();
}

ProductTable::iterator ProductTable::findProductKillDate(const Product& product, Date killDate)
{
	map<string, vector<Date>>::iterator iter(findProductData(product));
	vector<Date>& killDates = iter->second;

	for (Date& date : killDates)
	{
		if (date == killDate)
			return iter;
	}

	return _productMap.end();
}

ProductTable::const_iterator ProductTable::findProductKillDate(const Product& product, Date killDate) const
{
	map<string, vector<Date>>::const_iterator iter(findProductData(product));
	const vector<Date>& killDates = iter->second;

	for (const Date& date : killDates)
	{
		if (date == killDate)
			return iter;
	}

	return _productMap.end();
}

bool ProductTable::doesProductDataExist(const string& productName) const
{
	return findProductData(productName) != _productMap.end();
}

bool ProductTable::doesProductDataExist(const Product& product) const
{
	return findProductData(product) != _productMap.end();
}

bool ProductTable::doesProductHaveKillDate(const string& productName, const Date& killDate) const
{
	return findProductKillDate(productName, killDate) != _productMap.end();
}

bool ProductTable::doesProductHaveKillDate(const Product& product, const Date& killDate) const
{
	return findProductKillDate(product.getName(), killDate) != _productMap.end();
}

Product ProductTable::getProductData(const string& productName) const
{
	map<string, vector<Date>>::const_iterator iter = _productMap.find(productName);

	if (iter != _productMap.end())
		return Product(iter->first, iter->second);

	return Product();
}

Product ProductTable::getProductData(const_iterator iter) const
{
	if (iter != _productMap.end())
		return Product(iter->first, iter->second);

	return Product();
}

vector<Date> ProductTable::getProductKillDates(const string& productName) const
{
	vector<Date> killDates;
	map<string, vector<Date>>::const_iterator iter = _productMap.find(productName);

	if (iter != _productMap.end())
		killDates = iter->second;

	return killDates;
}

Date ProductTable::getProductFirstKillDate(const string& productName) const
{
	map<string, vector<Date>>::const_iterator iter(_productMap.find(productName));

	if (iter != _productMap.end() && iter->second.size() != 0)
		return iter->second[0];

	return Date();
}

ProductTable::iterator ProductTable::addProductData(const string& productName, Date killDate)
{
	if (!doesProductDataExist(productName))
		return _productMap.emplace(productName, vector<Date>(1, killDate)).first;

	return _productMap.end();
}

ProductTable::iterator ProductTable::addProductData(const Product& product)
{
	if (!doesProductDataExist(product))
		return _productMap.emplace(product.getNameMarked(), product.getKillDates()).first;

	return _productMap.end();
}

Product ProductTable::removeProductData(const string& productName)
{
	map<string, vector<Date>>::iterator iter(findProductData(productName));

	if (iter != _productMap.end())
	{
		Product product(iter->first, iter->second);
		_productMap.erase(iter);
		return product;
	}

	return Product();
}

Product ProductTable::removeProductData(const Product& product)
{
	map<string, vector<Date>>::iterator iter(findProductData(product.getName()));

	if (iter != _productMap.end())
	{
		Product product(iter->first, iter->second);
		_productMap.erase(iter);
		return product;
	}

	return Product();
}

Product ProductTable::removeProductData(iterator iter)
{
	Product product(getProductData(iter));
	_productMap.erase(iter);

	return product;
}

ProductTable::iterator ProductTable::setProductData(const string& productName, Date killDate)
{
	// Removes ALL values associated with the productName key.
	_productMap.erase(productName);

	return _productMap.emplace(productName, vector<Date>(1, killDate)).first;
}

ProductTable::iterator ProductTable::setProductData(const Product& product)
{
	// Removes ALL values associated with the productName key.
	_productMap.erase(product.getName());

	return _productMap.emplace(product.getName(), product.getKillDates()).first;
}

ProductTable::iterator ProductTable::addProductKillDate(const string& productName, Date killDate)
{
	map<string, vector<Date>>::iterator iter(findProductData(productName));

	if (iter != _productMap.end())
	{
		vector<Date>::iterator vec_iter(find(iter->second.begin(), iter->second.end(), killDate));

		if (vec_iter == iter->second.end())
		{
			iter->second.push_back(killDate);
			sort(iter->second.begin(), iter->second.end());	

			return iter;
		}
	}

	return _productMap.end();
}

vector<Date> ProductTable::addProductKillDates(const string& productName, const vector<Date>& killDates)
{
	map<string, vector<Date>>::iterator iter(findProductData(productName));
	vector<Date> killDatesToAdd;

	if (iter != _productMap.end())
	{
		for (size_t i = 0; i < killDates.size(); ++i)
		{
			// Does the kill date already exist?
			// If not, add it to the date vector.
			if (find(iter->second.begin(), iter->second.end(), killDates[i]) == iter->second.end())
				killDatesToAdd.push_back(killDates[i]);
		}

		for (size_t i = 0; i < killDatesToAdd.size(); ++i)
			iter->second.push_back(killDatesToAdd[i]);

		sort(iter->second.begin(), iter->second.end());
	}

	return killDatesToAdd;
}

Date ProductTable::removeProductKillDate(const string& productName, Date killDate)
{
	map<string, vector<Date>>::iterator iter(findProductKillDate(productName, killDate));

	if (iter != _productMap.end())
	{
		vector<Date>::iterator date_iter(find(iter->second.begin(), iter->second.end(), killDate));
		if (date_iter != iter->second.end())
		{
			Date date(*date_iter);
			iter->second.erase(date_iter);
			return date;
		}
	}
	
	return Date();
}

Date ProductTable::removeProductKillDate(const Product& product, Date killDate)
{
	map<string, vector<Date>>::iterator iter(findProductKillDate(product, killDate));

	if (iter != _productMap.end())
	{
		vector<Date>::iterator date_iter(find(iter->second.begin(), iter->second.end(), killDate));
		if (date_iter != iter->second.end())
		{
			Date date(*date_iter);
			iter->second.erase(date_iter);
			return date;
		}
	}

	return Date();
}

size_t ProductTable::removeProductKillDates(const string& productName)
{
	return _productMap.erase(productName);
}

size_t ProductTable::removeProductKillDates(const Product& product)
{
	return _productMap.erase(product.getName());
}

ProductTable::iterator ProductTable::setProductKillDate(const string& productName, Date killDate)
{
	map<string, vector<Date>>::iterator iter(findProductData(productName));

	if (iter != _productMap.end())
	{
		iter->second.clear();
		iter->second.push_back(killDate);
		return iter;
	}

	return _productMap.end();
}

ProductTable::iterator ProductTable::setProductKillDates(const string& productName, const vector<Date>& killDates)
{
	map<string, vector<Date>>::iterator iter(findProductData(productName));

	if (iter != _productMap.end())
	{
		iter->second = killDates;
		sort(iter->second.begin(), iter->second.end());
		return iter;
	}

	return _productMap.end();
}

ProductTable::iterator ProductTable::begin()
{
	return _productMap.begin();
}

ProductTable::const_iterator ProductTable::begin() const
{
	return _productMap.begin();
}

ProductTable::iterator ProductTable::end()
{
	return _productMap.end();
}

ProductTable::const_iterator ProductTable::end() const
{
	return _productMap.end();
}

vector<Product> ProductTable::getAllProducts() const
{
	vector<Product> products;

	for (auto iter = _productMap.begin(); iter != _productMap.end(); ++iter)
		products.push_back(Product(iter->first, iter->second));

	return products;
}

bool ProductTable::doesProductExpireInDays(const string& productName, i32 days) const
{
	if (!doesProductDataExist(productName))
		return false;

	Product product(getProductData(productName));

	if (product.expiresInDays(days))
		return true;

	return false;
}

bool ProductTable::doesProductExpireInDays(const_iterator iter, i32 days) const
{
	Product product(getProductData(iter));

	if (product.expiresInDays(days))
		return true;

	return false;
}

void ProductTable::markProductForExpiration(const std::string& productName)
{
	iterator iter = findProductData(productName);

	if (iter != _productMap.end())
	{
		Product product(removeProductData(iter));
		product.mark();
		addProductData(product);
	}
}

void ProductTable::markProductForExpiration(iterator iter)
{
	if (iter != _productMap.end())
	{
		Product product(removeProductData(iter));
		product.mark();
		addProductData(product);
	}
}

void ProductTable::clear()
{
	_productMap.clear();
}

size_t ProductTable::size() const
{
	return _productMap.size();
}

bool ProductTable::isEmpty() const
{
	return _productMap.begin() == _productMap.end();
}