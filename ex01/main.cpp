/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:21:23 by dyao              #+#    #+#             */
/*   Updated: 2025/04/03 17:29:35 by dyao             ###   ########.fr       */
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

bool	calculate_stack(std::string::iterator &it, std::stack<int> &store)
{
	int	a = 0;
	int	b = 0;
	if (store.size() > 1)
	{
		b = store.top();
		store.pop();
		a = store.top();
		store.pop();
	}
	else
		return (false);
	if (*it == '+')
		store.push(a + b);
	if (*it == '-')
		store.push(a - b);
	if (*it == '*')
		store.push(a * b);
	if (*it == '/')
	{
		if (b == 0)
			return (false);
		store.push(a / b);
	}
	std::cout << "this is the top element after calculation: " << store.top() << std::endl;
	return (true);
}

bool	calculate_result(std::stack<int> &store, std::string input)
{
	int	length = 0;
	int	length_1 = 0;

	std::string::iterator it = input.begin();
	std::string::iterator it2 = input.begin();
	while (it != input.end())
	{
		if (*it == ' ')
		{
			it++;
			continue;
		}
		it2 = it;
		while (it2 != input.end() && *it2 != ' ')
			it2++;
		length = std::distance(input.begin(), it);
		length_1 = std::distance(it, it2);
		if (!check_str(input.substr(length, length_1)))
			return (false);
		if ((*it == '+' || *it == '*' || *it == '/' || *it == '-') && length_1 == 1)
		{
			if (!calculate_stack(it, store))
				return (false);
		}
		else
			store.push(atoi(input.substr(length, length_1).c_str()));
		it = it2;
	}
	if (store.size() == 1)
		std::cout << "The result is " << store.top() << std::endl;
	else
		return (false);
	return (true);
}

int	main(int argc, char **argv)
{
	std::stack<int> store;
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
	if (!calculate_result(store, input))
	{
		std::cerr << "Error: invalid input" << std::endl;
		return (1);
	}
}
