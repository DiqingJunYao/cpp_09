/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:44:29 by dyao              #+#    #+#             */
/*   Updated: 2025/03/17 18:46:15 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>

class Date
{
private:
	int	_year;
	int	_month;
	int	_day;
public:
	Date();
	Date(std::string time_string);
	Date(const Date &other);
	Date	&operator=(const Date &other);
	bool	operator<(const Date &other);
	~Date();

	//getter
	int	getYear(void);
	int	getMonth(void);
	int	getDay(void);
};

#endif
