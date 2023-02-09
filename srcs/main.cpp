/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 15:44:36 by rmorel            #+#    #+#             */
/*   Updated: 2023/02/09 18:58:51 by rmorel           ###   ########.fr       */
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

template<typename C>
void print(C const& container)
{
    std::cout << "{ ";
    for (typename std::vector<typename C::value_type>::const_iterator it = container.begin(); it != container.end(); it++)
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
	std::vector<std::string> stdv;
	stdv.push_back("Hello");
	stdv.push_back("Richard");
	stdv.push_back("Nguyen");
	ft::vector<std::string> v(stdv.begin(), stdv.end());
	print(stdv);
	std::vector<int> x;
	x.push_back(1);
	x.push_back(2);
	x.push_back(3);
	std::vector<int> y;
	y.push_back(4);
	y.push_back(5);
	y.push_back(6);
	y.push_back(7);
	std::vector<int> z;
	z.push_back(8);
	z.push_back(9);
	print(x);
	print(y);
	print(z);
	y = x;
	z = x;
	print(x);
	print(y);
	print(z);

	return 0;
}
