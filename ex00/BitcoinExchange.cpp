/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:44:32 by dyao              #+#    #+#             */
/*   Updated: 2025/03/17 18:45:46 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

Date::Date() : _year(0), _month(0), _day(0)
{
}

Date::Date(std::string time_string)
{
	_year = atoi(time_string.substr(0, 4).c_str());
	_month = atoi(time_string.substr(5, 2).c_str());
	_day = atoi(time_string.substr(8, 2).c_str());
}

Date::Date(const Date &other) : _year(other._year), _month(other._month), _day(other._day)
{
	
}

Date &Date::operator=(const Date &other)
{
	if (this != &other)
	{
		this->_year = other._year;
		this->_month = other._month;
		this->_day = other._day;
	}
	return (*this);
}

bool	Date::operator<(const Date &other)
{
	if (this->_year < other._year)
		return (true);
	if (this->_year == other._year && this->_month < other._month)
		return (true);
	if (this->_year == other._year && this->_month == other._month && this->_day < other._day)
		return (true);
	return (false);
}

Date::~Date()
{
	
}

int	Date::getYear()
{
	return (this->_year);
}

int	Date::getMonth()
{
	return (this->_month);
}

int	Date::getDay()
{
	return (this->_day);
}
