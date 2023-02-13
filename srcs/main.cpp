/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 15:44:36 by rmorel            #+#    #+#             */
/*   Updated: 2023/02/13 13:17:14 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.hpp"
#include "vector.hpp"
#include <iostream>
#include <climits>
#include <vector>

template <class T>
void print_and_empty_stack(stack<T> & c)
{
	while (!c.empty())
	{
		std::cout << "Stack[" << c.size() - 1 << "] = " << c.top() << std::endl;
		c.pop();
	}
}

template<class T>
void print(ft::vector<T> container)
{
    std::cout << "{ ";
    for (T* it = container.begin(); it != container.end(); it++)
		std::cout << *it << " ";
	std::cout << "}\n";
}

int main()
{
	stack<int> c1;
	c1.push(5);
	c1.push(6);
	c1.push(7);
	print_and_empty_stack<int>(c1);
	c1.push(INT_MAX);
	c1.push(INT_MIN);
	print_and_empty_stack<int>(c1);
	ft::vector<int> v1;
	ft::vector<int> v2(5, 6);
	ft::vector<std::string> stdv;
	stdv.push_back("Hello");
	stdv.push_back("Richard");
	stdv.push_back("Nguyen");
	ft::vector<std::string> v(stdv.begin(), stdv.end());
    std::cout << "{ ";
    for (std::string* it = stdv.begin(); it != stdv.end(); it++)
		std::cout << *it << " ";
	std::cout << "}\n";
	{
	ft::vector<int> x;
	x.push_back(1);
	x.push_back(2);
	x.push_back(3);
	ft::vector<int> y;
	y.push_back(4);
	y.push_back(5);
	y.push_back(6);
	y.push_back(7);
	ft::vector<int> z;
	z.push_back(8);
	z.push_back(9);
    std::cout << "{ ";
    for (int* it = x.begin(); it != x.end(); it++)
		std::cout << *it << " ";
	std::cout << "}\n";
    std::cout << "{ ";
    for (int* it = y.begin(); it != y.end(); it++)
		std::cout << *it << " ";
	std::cout << "}\n";
	x.swap(y);
    std::cout << "{ ";
    for (int* it = x.begin(); it != x.end(); it++)
		std::cout << *it << " ";
	std::cout << "}\n";
    std::cout << "{ ";
    for (int* it = y.begin(); it != y.end(); it++)
		std::cout << *it << " ";
	std::cout << "}\n";
    std::cout << "{ ";
    for (int* it = z.begin(); it != z.end(); it++)
		std::cout << *it << " ";
	std::cout << "}\n";
	y = x;
	z = x;
    std::cout << "{ ";
    for (int* it = x.begin(); it != x.end(); it++)
		std::cout << *it << " ";
	std::cout << "}\n";
    std::cout << "{ ";
    for (int* it = y.begin(); it != y.end(); it++)
		std::cout << *it << " ";
	std::cout << "}\n";
    std::cout << "{ ";
    for (int* it = z.begin(); it != z.end(); it++)
		std::cout << *it << " ";
	std::cout << "}\n";
	z.resize(1);
    std::cout << "{ ";
    for (int* it = z.begin(); it != z.end(); it++)
		std::cout << *it << " ";
	std::cout << "}\n";
	y.erase(y.begin() + 1);
    std::cout << "{ ";
    for (int* it = y.begin(); it != y.end(); it++)
		std::cout << *it << " ";
	std::cout << "}\n";
	y.clear();
    std::cout << "{ ";
    for (int* it = y.begin(); it != y.end(); it++)
		std::cout << *it << " ";
	std::cout << "}\n";
	}
	return 0;
}
