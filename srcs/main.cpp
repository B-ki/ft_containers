/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 15:44:36 by rmorel            #+#    #+#             */
/*   Updated: 2023/02/07 15:01:00 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.hpp"
#include "vector.hpp"
#include <iostream>
#include <climits>
#include <vector>

template <typename T>
void print_container(T const& coll)
{
	typename T::const_iterator pos;
	typename T::const_iterator end(coll.end());

	for (pos = coll.begin(); pos != end; ++pos)
		std::cout << *pos << " ";
	std::cout << std::endl;
}

template <class T>
void print_and_empty_stack(stack<T> & c)
{
	while (!c.empty())
	{
		std::cout << "Stack[" << c.size() - 1 << "] = " << c.top() << std::endl;
		c.pop();
	}
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
	std::vector<std::string> stdv = {"Hello", "Richard", "Nguyen"};
	ft::vector<std::string> v(stdv.begin(), stdv.end());
	ft::vector<std::string> v2(std::move(v));



	return 0;
}
