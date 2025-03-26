/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:21:23 by dyao              #+#    #+#             */
/*   Updated: 2025/03/21 14:37:13 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

bool	check_input(std::string input)
{
	for (std::string::iterator it = input.begin(); it != input.end(); it++)
	{
		if ((*it >= 48 && *it <= 57) || *it == '+' || *it == '-' || *it == '/' || *it == '*' || *it == ' ')
			;
		else
			return (false);
	}
	return (true);
}

//my work need to test if this will work.
// void	put_in_stack(std::stack<std::string> &store, std::string &input)
// {
// 	size_t len = 0;
// 	std::string temp;
// 	std::string::iterator hold = input.begin();
// 	for (std::string::iterator it = input.begin(); it != input.end(); it++)
// 	{
// 		if (*it == ' ' || it == input.end() - 1)
// 		{
// 			len = std::distance(hold, it);
// 			temp = input.substr(std::distance(input.begin(), hold), len);
// 			store.push(temp);
// 			hold = it + 1;
// 		}
// 	}
// }

bool	check_str(std::string input)
{
	if (input.size() == 1 && (input == "+" || input == "-" || input == "*" || input == "/"))
		return (true);
	if (input.size() == 1 && isdigit(*input.begin()))
		return (true);
	if (input.size() > 1)
	{
		if (*input.begin() == '*' || *input.begin() == '/')
			return (false);
		for (std::string::iterator it = input.begin() + 1; it != input.end(); it++)
		{
			if (!isdigit(*it))
				return (false);
		}
		return (true);
	}
	return (false);
}

bool	put_in_stack(std::queue<std::string> &store, const std::string &input)
{
	size_t start = 0;
	size_t end;
	int	count_nbr = 0;
	int	count_symble = 0;

	while ((end = input.find(' ', start)) != std::string::npos)
	{
		if (end > start)
		{
			if (!check_str(input.substr(start, end - start)))
				return (false);
			if (input.substr(start, end - start) == "+" || input.substr(start, end - start) == "-"
				|| input.substr(start, end - start) == "*" || input.substr(start, end - start) == "/")
				count_symble++;
			else
				count_nbr++;
			store.push(input.substr(start, end - start));
		}
		start = end + 1;
	}
	if (start < input.size())
	{
		if (!check_str(input.substr(start)))
				return (false);
		if (input.substr(start, end - start) == "+" || input.substr(start, end - start) == "-"
			|| input.substr(start, end - start) == "*" || input.substr(start, end - start) == "/")
			count_symble++;
		else
			count_nbr++;
		store.push(input.substr(start));
	}
	if (count_nbr - 1 == count_symble)
		return (true);
	else
		return (false);
	return (true);
}

bool	calculate(std::queue<int> &temp_nbr, std::queue<std::string> &store)
{
	std::queue<int> hold;
	int temp[2];
	temp[0] = temp_nbr.front();
	temp_nbr.pop();
	temp[1] = temp_nbr.front();
	temp_nbr.pop();
	if (store.front() == "+")
	{
		hold.push(temp[0] + temp[1]);
		while (!temp_nbr.empty())
		{
			hold.push(temp_nbr.front());
			temp_nbr.pop();
		}
	}
	if (store.front() == "-")
	{
		hold.push(temp[0] - temp[1]);
		while (!temp_nbr.empty())
		{
			hold.push(temp_nbr.front());
			temp_nbr.pop();
		}
	}
	if (store.front() == "*")
	{
		hold.push(temp[0] * temp[1]);
		while (!temp_nbr.empty())
		{
			hold.push(temp_nbr.front());
			temp_nbr.pop();
		}
	}
	if (store.front() == "/")
	{
		if (temp[1] != 0)
		{
			hold.push(temp[0] / temp[1]);
			while (!temp_nbr.empty())
			{
				hold.push(temp_nbr.front());
				temp_nbr.pop();
			}
		}
		else
			return (false);
	}
	temp_nbr = hold;
	store.pop();
	return (true);
}

bool	print_result(std::queue<std::string> &store)
{
	std::queue<int> temp_nbr;
	std::string symble;
	// if (store.size() == 1)
	// {
	// 	std::cout << store.front() << std::endl;
	// 	return (true);
	// }
	while (!store.empty())
	{
		while (!store.empty() && store.front() != "+" && store.front() != "-" && store.front() != "/" && store.front() != "*")
		{
			if (atoi(store.front().c_str()) >= 10)
				return (false);
			temp_nbr.push(atoi(store.front().c_str()));
			store.pop();
		}
		if (!store.empty() && temp_nbr.size() == 1)
		{
			symble = store.front();
			store.pop();
			if (store.front() == "+" || store.front() == "-" || store.front() == "*" || store.front() == "/")
				return (false);
			temp_nbr.push(atoi(store.front().c_str()));
			store.pop();
			store.push(symble);
		}
		if (!store.empty() && !calculate(temp_nbr, store))
			return (false);
	}
	if (temp_nbr.size() != 1)
		return (false);
	else
	{
		std::cout << temp_nbr.front() << std::endl;
		return (true);
	}
}

int	main(int argc, char **argv)
{
	std::queue<std::string> store;
	std::string input;
	if (argc != 2)
	{
		std::cerr << "Error: too many or too less arguments" << std::endl;
		return (1);
	}
	input = argv[1];
	if (!check_input(input))
	{
		std::cerr << "Error: invalid input" << std::endl;
		return (1);
	}
	if (!put_in_stack(store, input))
	{
		std::cerr << "Error: invalid input" << std::endl;
		return (1);
	}
	if (!print_result(store))
	{
		std::cerr << "Error: invalid input" << std::endl;
		return (1);
	}
}
