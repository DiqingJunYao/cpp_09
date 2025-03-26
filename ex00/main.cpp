/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:44:26 by dyao              #+#    #+#             */
/*   Updated: 2025/03/17 19:12:43 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

void	inputMap(std::fstream &file_input, std::multimap<std::string, double> &input)
{
	std::string temp;
	std::string	temp_value;
	std::getline(file_input, temp);
	while (std::getline(file_input, temp))
	{
		if (temp.size() < 14)
			input.insert(std::make_pair(temp.substr(0, 10), -1001));
		else
		{
			size_t len = std::distance(temp.begin() + 13, temp.end());
			input.insert(std::make_pair(temp.substr(0, 10), atof(temp.substr(13, len).c_str())));
		}
	}
}

bool	dateCheck(std::multimap<std::string, double>::iterator &it)
{
	Date temp_date(it->first);
	int	day_to_check[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (temp_date.getMonth() < 1 || temp_date.getMonth() > 12 || temp_date.getDay() < 1)
		return (false);
	if (temp_date.getYear() % 4 == 0 && (temp_date.getYear() % 100 != 0 || temp_date.getYear() % 400 == 0))
		day_to_check[1] = 29;
	if (temp_date.getDay() > day_to_check[temp_date.getMonth() - 1])
		return (false);
	return (true);
}

bool	checkValue(std::multimap<std::string, double>::iterator &it)
{
	if (!dateCheck(it))
	{
		std::cerr << "Error: bad input => " << it->first << std::endl;
		return (false);
	}
	if (it->second == -1001)
	{
		std::cerr << "Error: no value find." << std::endl;
		return (false);
	}
	if (it->second < 0)
	{
		std::cerr << "Error: not a positive number." << std::endl;
		return (false);
	}
	if (it->second > 1000)
	{
		std::cerr << "Error: too large a number." << std::endl;
		return (false);
	}
	return (true);
}

double	returnVal(std::multimap<std::string, double>::iterator &it, std::fstream &data)
{
	std::string temp;
	size_t	len;
	double	pre_val;
	data.clear();
	data.seekg(0);
	std::getline(data, temp);
	while (std::getline(data, temp))
	{
		len = std::distance(temp.begin() + 11, temp.end());
		if (temp.find(it->first) != std::string::npos)
			return (atof(temp.substr(11, len).c_str()) * it->second);
		Date t_date(temp.substr(0, 10));
		Date n_date(it->first);
		if (t_date < n_date)
		{
			pre_val = atof(temp.substr(11, len).c_str());
			continue ;
		}
		return (pre_val * it->second);
	}
	return (0);
}

void	printValue(std::multimap<std::string, double> &input)
{
	double		result = 0;
	std::fstream data("data.csv");
	for (std::multimap<std::string, double>::iterator it = input.begin(); it != input.end(); it++)
	{
		if (!checkValue(it))
			continue ;
		result = returnVal(it, data);
		std::cout << it->first << " => " << it->second << " = " << result << std::endl;
	}
}

int main(int argc, char **argv)
{
	std::multimap<std::string, double> input;
	if (argc != 2)
	{
		std::cerr << "Error: could not open file." << std::endl;
		return (1);
	}	
	std::fstream file_input(argv[1]);
	if (!file_input)
	{
		std::cerr << "Error: could not open file." << std::endl;
		return (1);
	}
	if (file_input.peek() == std::ifstream::traits_type::eof())
	{
		std::cerr << "Error: empty file." << std::endl;
		return (1);
	}
	inputMap(file_input, input);
	for (std::multimap<std::string, double>::iterator it = input.begin(); it != input.end(); it++)
	{
		std::cout << it->first << " | " << it->second << std::endl;
	}
	std::cout << "\nthis is the result: \n";
	printValue(input);
	file_input.close();
}
