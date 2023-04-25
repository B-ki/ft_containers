/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:27:26 by rmorel            #+#    #+#             */
/*   Updated: 2023/04/25 17:55:46 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_HPP
#define TESTS_HPP 

#include <sstream>
#include <string>
#include <list>
#include <iostream>
#include "pair.hpp"
#include "map.hpp"
#include "vector.hpp"
#include "set.hpp"
#include <set>
#include <map>
#include <cstdlib>
#include <ctime>

#ifndef NS
#define NS std
#endif

#if USING_FT == 1
#define NAME "ft"
#else 
#define NAME "std"
#endif

void RBT_test();
void vector_stack_test();
void map_iterator();
void map_insert_erase();
void map_bounds();
void map_swap();
void set_test();

template<typename T>
std::string printPair(const T& map_iterator, bool nl = true)
{
	std::cout << "(" << map_iterator->first << ", " 
		<< map_iterator->second << ")";
	if (nl)
		std::cout << std::endl;
	return ("");
}

template<class T>
class foo
{
	public:
		foo() : obj(new T()) {}
		foo(T value) : obj(new T(value)) {}
		foo(const foo<T>& other) : obj(new T(other.getObj())) {}
		~foo() { delete obj; }
		foo& operator=(const foo<T>& other)
		{
			if (this != &other)
				*obj = other.getObj();
			return *this;
		}

	private:
		T* obj;
	public:
		T& getObj(void) const { return *obj; }
};

template<class T>
std::ostream& operator<<(std::ostream& o, foo<T>& bar)
{
	o << bar.getObj();
	return o;
}

#endif 
