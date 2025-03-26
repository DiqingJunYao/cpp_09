/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:49:54 by dyao              #+#    #+#             */
/*   Updated: 2025/03/26 11:31:03 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

bool	check_input(int argc, char **argv)
{
	for (size_t i = 1; i < argc; i++)
	{
		for (size_t j = 0; argv[i][j] != '\0'; j++)
		{
			if (!isdigit(argv[i][j]))
				return (false);
		}
	}
	return (true);
}

bool	put_in_vec(int argc, char **argv, std::vector<int> &store)
{
	std::vector<int>::iterator it;
	for (size_t i = 1; i < argc; i++)
	{
		if (i == 1)
			store.push_back(atoi(argv[i]));
		else
		{
			if ((it = std::find(store.begin(), store.end(), atoi(argv[i]))) != store.end())
				return (false);
			else
				store.push_back(atoi(argv[i]));
		}
	}
	return (true);
}

void	sort_vec(std::vector<int> &store)
{
	std::vector<int> first_array;
	std::vector<int> second_array;
	std::vector<int> result_array;
	for (size_t i = 0; i < store.size(); i++)
	{
		if (i % 2 == 0)
			first_array.push_back(store[i]);
		else
			second_array.push_back(store[i]);
	}
	if (second_array.size() > 5)
	{
		sort_vec(first_array);
		sort_vec(second_array);
	}
	if (second_array.size() <= 5)
	{
		std::sort(first_array.begin(), first_array.end());
		std::sort(second_array.begin(), second_array.end());
	}
	size_t i = 0, j = 0;
	while (i < first_array.size() && j < second_array.size())
	{
		if (first_array[i] < second_array[j])
		{
			result_array.push_back(first_array[i]);
			i++;
		}
		else
		{
			result_array.push_back(second_array[j]);
			j++;
		}
	}
	while (i < first_array.size())
		result_array.push_back(first_array[i++]);
	while (j < second_array.size())
		result_array.push_back(second_array[j++]);
	store = result_array;
}

void	sort_start_vec(std::vector<int> &store)
{
	double	time_counter;
	// std::cout << "Before: ";
	// for (std::vector<int>::iterator it = store.begin(); it != store.end(); it++)
	// 	std::cout << *it << " ";
	// std::cout << std::endl;
	std::clock_t start_time = std::clock();
	sort_vec(store);
	std::clock_t end_time = std::clock();
	time_counter = (double)(end_time - start_time) * 1000 / CLOCKS_PER_SEC;
	// std::cout << "After: ";
	// for (std::vector<int>::iterator it = store.begin(); it != store.end(); it++)
	// 	std::cout << *it << " ";
	// std::cout << std::endl;
	std::cout	<< "Time to process a range of " << store.size()
				<< " elements with std::vector : " << time_counter
				<< " ms" << std::endl;
}

bool	put_in_list(int argc, char **argv, std::list<int> &store)
{
	std::list<int>::iterator it;
	for (size_t i = 1; i < argc; i++)
	{
		if (i == 1)
			store.push_back(atoi(argv[i]));
		else
		{
			if ((it = std::find(store.begin(), store.end(), atoi(argv[i]))) != store.end())
				return (false);
			else
				store.push_back(atoi(argv[i]));
		}
	}
	return (true);
}

void	sort_list(std::list<int> &store)
{
	if (store.size() == 1)
		return ;
	std::list<int> first_array;
	std::list<int> second_array;
	size_t	 i = 0;
	for (std::list<int>::iterator it = store.begin(); it != store.end(); it++)
	{
		if (i % 2 == 0)
		first_array.push_back(*it);
		else
		second_array.push_back(*it);
		i++;
	}
	if (second_array.size() > 5)
	{
		sort_list(first_array);
		sort_list(second_array);
	}
	if (second_array.size() <= 5)
	{
		second_array.sort();
		first_array.sort();
	}
	std::list<int>::iterator it_1 = first_array.begin();
	std::list<int>::iterator it_2 = second_array.begin();
	
	//my way
	// std::list<int> result_array;
	// while (it_1 != first_array.end() && it_2 != second_array.end())
	// {
	// 	if (it_1 != first_array.end() && it_2 != second_array.end() && (*it_1 < *it_2))
	// 	{
	// 		result_array.push_back(*it_1);
	// 		it_1++;
	// 	}
	// 	if (it_1 != first_array.end() && it_2 != second_array.end() && (*it_1 > *it_2))
	// 	{
	// 		result_array.push_back(*it_2);
	// 		it_2++;
	// 	}
	// }
	// while (it_2 != second_array.end())
	// {
	// 	result_array.push_back(*it_2);
	// 	it_2++;
	// }
	// while (it_1 != first_array.end())
	// {
	// 	result_array.push_back(*it_1);
	// 	it_1++;
	// }
	// store = result_array;

	
	store.clear();
	while (it_1 != first_array.end() && it_2 != second_array.end()) {
		if (*it_1 <= *it_2) {
			store.push_back(*it_1);
			++it_1;
		} else {
			store.push_back(*it_2);
			++it_2;
		}
	}
	while (it_1 != first_array.end())
	{
		store.push_back(*it_1);
		++it_1;
	}
	while (it_2 != second_array.end())
	{
		store.push_back(*it_2);
		++it_2;
	}
}

void	sort_start_list(std::list<int> &store)
{
	double	time_counter;
	// std::cout << "Before: ";
	// for (std::list<int>::iterator it = store.begin(); it != store.end(); it++)
	// 	std::cout << *it << " ";
	// std::cout << std::endl;
	std::clock_t start_time = std::clock();
	sort_list(store);
	std::clock_t end_time = std::clock();
	time_counter = (double)(end_time - start_time) * 1000 / CLOCKS_PER_SEC;
	// std::cout << "After: ";
	// for (std::list<int>::iterator it = store.begin(); it != store.end(); it++)
	// 	std::cout << *it << " ";
	// std::cout << std::endl;
	std::cout	<< "Time to process a range of " << store.size()
				<< " elements with std::list : " << time_counter
				<< " ms" << std::endl;
}

int main(int argc, char **argv)
{
	{
		std::vector<int> store;
		if (!check_input(argc, argv))
		{
			std::cerr << "Error: invalid input!" << std::endl;
			return (1);
		}
		if (!put_in_vec(argc, argv, store))
		{
			std::cerr << "Error: duplicate input!" << std::endl;
			return (1);
		}
		sort_start_vec(store);
	}
	{
		std::list<int> store;
		if (!check_input(argc, argv))
		{
			std::cerr << "Error: invalid input!" << std::endl;
			return (1);
		}
		if (!put_in_list(argc, argv, store))
		{
			std::cerr << "Error: duplicate input!" << std::endl;
			return (1);
		}
		sort_start_list(store);
	}
}
