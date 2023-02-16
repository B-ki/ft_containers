/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 15:44:36 by rmorel            #+#    #+#             */
/*   Updated: 2023/02/16 20:03:01 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.hpp"
#include "vector.hpp"
#include <iostream>
#include <climits>
#include <ostream>
#include <vector>

#ifndef NAMESPACE
# define NAMESPACE std
#endif

	template <class T>
void print_and_empty_stack(stack<T> & c)
{
	while (!c.empty())
	{
		std::cout << "Stack[" << c.size() - 1 << "] = " << c.top() << std::endl;
		c.pop();
	}
}

class A 
{
	public:
	A(void) : _i(new int(0)) {};
	A(const int &n) : _i(new int(n))  {};
	A(A const & src) : _i(new int(*src._i)) {};
	~A(void) { delete _i; };

	A& operator=(const A &rhs) {
		if (this != &rhs) {
			*_i = *rhs._i;
		}
		return (*this);
	}
	int getInt(void) const { return *_i; }
	void setInt(const int n) { *_i = n; }

	private:
		int* _i;
};

template <class T>
void print_vector(const NAMESPACE::vector<T> & c)
{
	std::cout << "{ ";
	for (typename NAMESPACE::vector<T>::const_iterator it = c.begin(); it != c.end(); it++)
		std::cout << *it << " ";
	std::cout << "}\n";
}

std::ostream & operator<<(std::ostream & o, A const & rhs)
{
	o << rhs.getInt();
	return (o);
}


int main()
{
	{
		stack<int> c1;
		c1.push(5);
		c1.push(6);
		c1.push(7);
		print_and_empty_stack<int>(c1);
		c1.push(INT_MAX);
		c1.push(INT_MIN);
		print_and_empty_stack<int>(c1);
		NAMESPACE::vector<int> v1;
		NAMESPACE::vector<int> v2(5, 6);
		NAMESPACE::vector<std::string> stdv;
		stdv.push_back("Hello");
		stdv.push_back("Richard");
		stdv.push_back("Nguyen");
		NAMESPACE::vector<std::string> v(stdv.begin(), stdv.end());
		std::cout << "{ ";
		for (NAMESPACE::vector<std::string>::iterator it = stdv.begin(); it != stdv.end(); it++)
			std::cout << *it << " ";
		std::cout << "}\n";
	}
	{
		NAMESPACE::vector<A> x;
		x.push_back(1);
		x.push_back(2);
		x.push_back(3);
	}
	{
		NAMESPACE::vector<A> x;
		x.push_back(1);
		x.push_back(2);
		x.push_back(3);
		NAMESPACE::vector<A> y;
		y.push_back(4);
		y.push_back(5);
		y.push_back(6);
		y.push_back(7);
		NAMESPACE::vector<A> z;
		z.push_back(8);
		z.push_back(9);
		std::cout << "x.front() : " << x.front() << " x.back() : " << x.back() << " x.at(0) : " << x.at(0) << " x.at(2) : " << x.at(2) << std::endl;
		print_vector(x);
		print_vector(y);
		x.swap(y);
		print_vector(x);
		print_vector(y);
		print_vector(z);
		NAMESPACE::vector<A> w;
		z.pop_back();
		print_vector(z);
		z.push_back(INT_MAX);
		print_vector(z);
		NAMESPACE::vector<A> u;
		u.push_back(1);
		u.push_back(2);
		y = x;
		u = x;
		print_vector(x);
		print_vector(y);
		print_vector(z);
		w.push_back(10);
		w.push_back(11);
		w.push_back(12);
		w.push_back(13);
		w.push_back(14);
		print_vector(w);
		std::cout << w.size() << " is w size and capacity is " << w.capacity() << std::endl;
		std::cout << y.size() << " is y size and capacity is " << y.capacity() << std::endl;
		w = y;
		w.erase(w.begin() + 1);
		print_vector(w);
		w.erase(w.begin() + 3);
		print_vector(w);
		w.erase(w.begin());
		print_vector(w);
		print_vector(z);
		std::cout << "z.resize(1)\n";
		z.resize(1);
		print_vector(z);
		std::cout << "Vector y :\n";
		print_vector(y);
		std::cout << "Erasing begin + 1\n";
		y.erase(y.begin() + 1);
		print_vector(y);
		std::cout << "Erasing begin\n";
		y.erase(y.begin());
		print_vector(y);
		std::cout << "Erasing begin\n";
		y.erase(y.begin());
		print_vector(y);
		std::cout << "Erasing begin\n";
		y.erase(y.begin());
		print_vector(y);
		z.erase(z.begin());
		std::cout << "Z before erasing begin to begin :\n";
		print_vector(z);
		std::cout << "Erasing z begin to begin :\n";
		z.erase(z.begin(), z.begin());
		print_vector(z);
		std::cout << "Clear\n";
		y.clear();
		print_vector(y);
		std::cout << "x.front() : " << x.front() << " x.back() : " << x.back() << " x.at(0) : " << x.at(0) << " x.at(2) : " << x.at(2) << std::endl;
	}
	{
		std::cout << "\n########## VECTOR CAPACITY ##########\n\n";
		NAMESPACE::vector<A> x;
		print_vector(x);
		std::cout << "x size : " << x.size() << ", x.capacity : " << x.capacity() << ", x empty : " << x.empty() << ", x max_size : " << x.max_size() << std::endl;
		x.push_back(1);
		x.push_back(2);
		x.push_back(3);
		print_vector(x);
		std::cout << "x size : " << x.size() << ", x.capacity : " << x.capacity() << ", x empty : " << x.empty() << ", x max_size : " << x.max_size() << std::endl;
		x.clear();
		print_vector(x);
		std::cout << "x size : " << x.size() << ", x.capacity : " << x.capacity() << ", x empty : " << x.empty() << ", x max_size : " << x.max_size() << std::endl;
	}
	{
		std::cout << "\n########## VECTOR ELEMENT ACCESS ##########\n\n";
		NAMESPACE::vector<A> x;
		// Should segfault : x[0];
		// Should throw std::out_of_range : at[0];
		x.push_back(1);
		x.push_back(2);
		x.push_back(3);
		// Should segfault : x[3];
		// Should throw std::out_of_range : at[3];
		print_vector(x);
		std::cout << "at(0) to a(2) : " << x.at(0) << x.at(1) << x.at(2) << std::endl;
		std::cout << "x[0] to x[2] : " << x[0] << x[1] << x[2] << std::endl;
		std::cout << "x front and back " << x.front() << x.back();

		std::cout << "\nConst vector :\n";
		const NAMESPACE::vector<A> y(x);
		// Should segfault : x[0];
		// Should throw std::out_of_range : at[0];
		// Should segfault : x[3];
		// Should throw std::out_of_range : at[3];
		print_vector(y);
		std::cout << "at(0) to a(2) : " << y.at(0) << y.at(1) << y.at(2) << std::endl;
		std::cout << "y[0] to y[2] : " << y[0] << y[1] << y[2] << std::endl;
		std::cout << "y front and back " << y.front() << y.back() << std::endl;
		// Should not compile : y.front()++;
		std::cout << "x.front().getInt() : " << x.front().getInt() << " and x.front().setInt(2) (should compile and work)\n";
		x.front().setInt(2);
		std::cout << "y.front().getInt() : " << y.front().getInt() << "\n";
		// Should not compile, because the vector is const but setInt is not const :  y.front().setInt(2);
	}
	{
		std::cout << "\n########## VECTOR MODIFIERS ##########\n\n";
		NAMESPACE::vector<A> x;
		x.push_back(1);
		x.push_back(2);
		x.push_back(3);
		print_vector(x);
		std::cout << "x.erase(x.begin())\n";
		x.erase(x.begin());
		print_vector(x);
		// Invalid read with this : std::cout << "x.erase(x.begin() + 2)\n x.begin() + 2 = ";
		x.erase(x.begin()+2);
		print_vector(x);
		// Really strange, with std and ft it still erases something even if the pointer lead to nothing
		std::cout << "x.erase(x.begin() + 3)\n";
		x.erase(x.begin()+3);
		print_vector(x);
		std::cout << std::endl;
		std::cout << "Push_back 4, 5, 6, print, pop_back, then print :\n";
		x.push_back(4);
		x.push_back(5);
		x.push_back(6);
		print_vector(x);
		x.pop_back();
		print_vector(x);
		//x.resize(5, A(7));
	}
	{
		std::cout << "\n########## RESIZE ##########\n\n";
		NAMESPACE::vector<int> x;

		x.push_back(1);
		x.push_back(1);
		x.push_back(1);
		x.push_back(1);
		std::cout << "cap = " << x.capacity() << ", size = " << x.size() << std::endl;
		print_vector(x);
		x.resize(9, 12);
		std::cout << "cap = " << x.capacity() << ", size = " << x.size() << std::endl;
		print_vector(x);
	}
	{
		std::cout << "\n########## RESIZE ##########\n\n";
		NAMESPACE::vector<int> x;

		x.push_back(1);
		x.push_back(1);
		x.push_back(1);
		x.push_back(1);
		x.erase(x.begin());
		x.erase(x.begin());
		std::cout << "cap = " << x.capacity() << ", size = " << x.size() << std::endl;
		print_vector(x);
		x.resize(3);
		std::cout << "cap = " << x.capacity() << ", size = " << x.size() << std::endl;
		print_vector(x);	
	}
	{
		std::cout << "\n########## RESIZE ##########\n\n";
		NAMESPACE::vector<int> x;

		x.push_back(1);
		x.push_back(1);
		x.push_back(1);
		x.push_back(1);
		std::cout << "cap = " << x.capacity() << ", size = " << x.size() << std::endl;
		print_vector(x);
		x.resize(3);
		std::cout << "cap = " << x.capacity() << ", size = " << x.size() << std::endl;
		print_vector(x);	
	}
	return 0;
}
