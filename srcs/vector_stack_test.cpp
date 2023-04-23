/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_stack_test.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:46:52 by rmorel            #+#    #+#             */
/*   Updated: 2023/04/23 11:28:46 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse_iterator.hpp"
#include "stack.hpp"
#include "vector.hpp"
#include <iostream>
#include <climits>
#include <linux/limits.h>
#include <vector>
#include <stack>
#include "tests.hpp"

#ifndef NS
# define NS std
#endif

template <class T>
void print_and_empty_stack(NS::stack<T> & c)
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
void print_vector(const NS::vector<T> & c)
{
	std::cout << "Vector [size = " << c.size() << "] = ";
	std::cout << "{ ";
	for (typename NS::vector<T>::const_iterator it = c.begin(); it != c.end(); it++)
		std::cout << *it << " ";
	std::cout << "}\n";
}

std::ostream & operator<<(std::ostream & o, A const & rhs)
{
	o << rhs.getInt();
	return (o);
}

void vector_stack_test(void)
{
	std::clock_t start = std::clock();
	{
		NS::stack<int> c1;
		c1.push(5);
		c1.push(6);
		c1.push(7);
		print_and_empty_stack<int>(c1);
		c1.push(INT_MAX);
		c1.push(INT_MIN);
		print_and_empty_stack<int>(c1);
		NS::vector<int> v1;
		NS::vector<int> v2(5, 6);
		NS::vector<std::string> stdv;
		stdv.push_back("Hello");
		stdv.push_back("Richard");
		stdv.push_back("Nguyen");
		NS::vector<std::string> v(stdv.begin(), stdv.end());
		std::cout << "{ ";
		for (NS::vector<std::string>::iterator it = stdv.begin(); it != stdv.end(); it++)
			std::cout << *it << " ";
		std::cout << "}\n";
	}
	std::clock_t end = std::clock();
	double elapsed_time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	std::cout << "Elapsed time VECTOR BASIC TESTS : " << NAME << " = " << elapsed_time << " seconds\n";
	start = std::clock();
	{
		NS::vector<A> x;
		x.push_back(1);
		x.push_back(2);
		x.push_back(3);
	}
	{
		std::cout << "\n########## OPERATORS ##########\n\n";
		NS::vector<A> x;
		x.push_back(1);
		x.push_back(2);
		x.push_back(3);
		NS::vector<A> y;
		y.push_back(4);
		y.push_back(5);
		y.push_back(6);
		y.push_back(7);
		NS::vector<A> z;
		z.push_back(1);
		z.push_back(2);
		print_vector(x);
		print_vector(y);
		print_vector(z);
		y = x;
		z = x;
		std::cout << "y = x && z = x\n";
		print_vector(x);
		print_vector(y);
		print_vector(z);
	}
	end = std::clock();
	elapsed_time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	std::cout << "Elapsed time VECTOR OPERATORS : " << NAME << " = " << elapsed_time << " seconds\n";
	start = std::clock();
	{
		std::cout << "\n########## MODIFIERS ##########\n\n";
		NS::vector<A> x;
		x.push_back(1);
		x.push_back(2);
		x.push_back(3);
		NS::vector<A> y;
		y.push_back(4);
		y.push_back(5);
		y.push_back(6);
		y.push_back(7);
		std::cout << "Vector x : ";
		print_vector(x);
		std::cout << "Vector y : ";
		print_vector(y);
		std::cout << "Swap x, y\n";
		x.swap(y);
		std::cout << "Vector x : ";
		print_vector(x);
		std::cout << "Vector y : ";
		print_vector(y);
		std::cout << "x.popback()\n";
		x.pop_back();
		print_vector(x);
		x.push_back(INT_MAX);
		std::cout << "x.push_back(INT_MAX)\n";
		print_vector(x);
		std::cout<< "x.erase(x.begin +1)\n";
		x.erase(x.begin() + 1);
		std::cout << "Vector x : ";
		print_vector(x);
		std::cout<< "x.erase(x.begin + 3)\n";
		x.erase(x.begin() + 3);
		std::cout << "Vector x : ";
		print_vector(x);
		std::cout << "NOTE : Even though x.begin() + 3 is already destroyed, erase destroy the last element\n";
		std::cout<< "x.erase(x.begin)\n";
		x.erase(x.begin());
		std::cout << "Vector x : ";
		print_vector(x);
		std::cout << "Vector y :\n";
		print_vector(y);
		std::cout << "y.erase begin + 1\n";
		y.erase(y.begin() + 1);
		print_vector(y);
		std::cout << "y.erase begin to begin + 1\n";
		y.erase(y.begin(), y.begin() + 1);
		print_vector(y);
		std::cout << "y.clear()\n";
		y.clear();
		print_vector(y);
	}
	end = std::clock();
	elapsed_time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	std::cout << "Elapsed time MODIFIERS : " << NAME << " = " << elapsed_time << " seconds\n";
	start = std::clock();
	{
		std::cout << "\n########## RESIZE ##########\n\n";
		NS::vector<int> x;

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
		NS::vector<int> x;

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
		NS::vector<int> x;

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
	end = std::clock();
	elapsed_time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	std::cout << "Elapsed time SIZE : " << NAME << " = " << elapsed_time << " seconds\n";
	start = std::clock();
	{
		std::cout << "\n########## VECTOR CAPACITY ##########\n\n";
		NS::vector<A> x;
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
	end = std::clock();
	elapsed_time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	std::cout << "Elapsed time VECTOR CAPACITY : " << NAME << " = " << elapsed_time << " seconds\n";
	start = std::clock();
	{
		std::cout << "\n########## VECTOR ELEMENT ACCESS ##########\n\n";
		NS::vector<A> x;
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
		const NS::vector<A> y(x);
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
	end = std::clock();
	elapsed_time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	std::cout << "Elapsed time VECTOR ELEMENT ACCESS : " << NAME << " = " << elapsed_time << " seconds\n";
	start = std::clock();
	{
		std::cout << "\n########## VECTOR MODIFIERS ##########\n\n";
		NS::vector<A> x;
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
		std::cout << "cap = " << x.capacity() << ", size = " << x.size() << std::endl;
		x.resize(5);
	}
	end = std::clock();
	elapsed_time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	std::cout << "Elapsed time VECTOR MODIFERS 2 : " << NAME << " = " << elapsed_time << " seconds\n";
	start = std::clock();
	{
		std::cout << "\n########## INSERT ##########\n\n";
		NS::vector<int> x;

		x.push_back(1);
		x.push_back(2);
		x.push_back(3);
		x.push_back(4);
		x.push_back(5);
		x.erase(x.begin());
		x.erase(x.begin());
		x.erase(x.begin());
		std::cout << "cap = " << x.capacity() << ", size = " << x.size() << std::endl;
		std::cout << x.back() << std::endl;
		print_vector(x);
		x.insert(x.begin(), 1lu, 9);
		print_vector(x);
		x.insert(x.begin() + 2, 10);
		print_vector(x);
		x.insert(x.end(), 11);
		print_vector(x);
		NS::vector<int> y;

		std::cout << "cap = " << y.capacity() << ", size = " << y.size() << std::endl;
		print_vector(y);
		y.push_back(1);
		y.push_back(2);
		y.push_back(3);
		y.push_back(4);	
		std::cout << "cap = " << y.capacity() << ", size = " << y.size() << std::endl;
		print_vector(y);
		std::cout << "y.insert(end(), 5)\n";
		y.insert(y.end(), 5);
		print_vector(y);
		std::cout << "y.insert(end(), 6)\n";
		y.insert(y.end(), 6);
		print_vector(y);
		x.erase(x.begin());
		x.erase(x.begin());
		std::cout << "Vector x : ";
		print_vector(x);
		std::cout << "cap = " << x.capacity() << ", size = " << x.size() << std::endl;
		std::cout << "x.insert(x.begin(), 2lu, 3)\n";
		x.insert(x.begin(), 2lu, 3);
		std::cout << "cap = " << x.capacity() << ", size = " << x.size() << std::endl;
		print_vector(x);
		std::cout << "cap = " << x.capacity() << ", size = " << x.size() << std::endl;
		std::cout << "x.insert(x.end(), 2lu, 3)\n";
		x.insert(x.end(), 2lu, 3);
		print_vector(x);
		std::cout << "cap = " << x.capacity() << ", size = " << x.size() << std::endl;
		std::cout << "x.insert(x.end(), 2lu, 4)\n";
		x.insert(x.end(), 2lu, 4);
		print_vector(x);
	}
	{
		std::cout << "\n########## INSERT2  ##########\n\n";
		NS::vector<int> y;

		y.reserve(8);
		y.push_back(1);
		y.push_back(2);
		y.push_back(3);
		y.push_back(4);	
		NS::vector<int> w;
		NS::vector<int> x;
		NS::vector<int> z;
		w = y;
		x = y;
		z = y;
		w.push_back(5);
		std::cout << "w : cap = " << w.capacity() << ", size = " << w.size() << std::endl;
		std::cout << "x : cap = " << x.capacity() << ", size = " << x.size() << std::endl;
		std::cout << "y : cap = " << y.capacity() << ", size = " << y.size() << std::endl;
		std::cout << "z : cap = " << z.capacity() << ", size = " << z.size() << std::endl;
		print_vector(w);
		print_vector(x);
		print_vector(y);
		print_vector(z);
		w.insert(w.begin(), 2lu, 7);
		x.insert(x.begin() + 2, 4lu, 7);
		y.insert(y.end(), 4lu, 7);
		z.insert(z.begin(), 4lu, 7);
		print_vector(w);
		print_vector(x);
		print_vector(y);
		print_vector(z);
		NS::vector<A> a;
		a.insert(a.begin(), A(45));
		a.insert(a.begin(), A(75));
		a.insert(a.begin() + 1, A(21));
		a.insert(a.end() - 1, A(27));
		a.insert(a.end(), A(18));
		print_vector(a);
		a.insert(a.begin(), A(45));
		a.insert(a.begin(), A(75));
		a.insert(a.begin(), A(21));
		a.insert(a.begin(), A(27));
		a.insert(a.begin(), A(18));
		print_vector(a);
	}
	end = std::clock();
	elapsed_time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	std::cout << "Elapsed time VECTOR INSERT : " << NAME << " = " << elapsed_time << " seconds\n";
	start = std::clock();
	{
		std::cout << "\n########## ASSIGN  ##########\n\n";
		NS::vector<A> x;
		x.assign(10, A());
		std::cout << "x : cap = " << x.capacity() << ", size = " << x.size() << std::endl;
		print_vector(x);
		NS::vector<A> y;

		y.reserve(8);
		y.push_back(A(1));
		y.push_back(A(2));
		y.push_back(A(3));
		y.push_back(A(4));	
		std::cout << "y : cap = " << y.capacity() << ", size = " << y.size() << std::endl;
		print_vector(y);
		y.assign(6, A(8));
		std::cout << "y : cap = " << y.capacity() << ", size = " << y.size() << std::endl;
		print_vector(y);
		NS::vector<A> z;
		z = y;
		std::cout << "z : cap = " << z.capacity() << ", size = " << z.size() << std::endl;
		print_vector(z);
		z.assign(2, 6);
		std::cout << "z : cap = " << z.capacity() << ", size = " << z.size() << std::endl;
		print_vector(z);
	}
	end = std::clock();
	elapsed_time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	std::cout << "Elapsed time VECTOR ASSIGN : " << NAME << " = " << elapsed_time << " seconds\n";
	{
		std::cout << "\n########## INSERT FREE  ##########\n\n";
		NS::vector<int> myvector (3,100);
        NS::vector<int>::iterator it;

		it = myvector.begin();
		it = myvector.insert ( it , 200 );

		print_vector(myvector);
		myvector.insert (it,2,300);

		// "it" no longer valid, get a new one:
		it = myvector.begin();

		NS::vector<int> anothervector (2,400);
		myvector.insert (it+2,anothervector.begin(),anothervector.end());

		int myarray [] = { 501,502,503 };
		myvector.insert (myvector.begin(), myarray, myarray+3);

		std::cout << "myvector contains:";
		for (it=myvector.begin(); it<myvector.end(); it++)
			std::cout << ' ' << *it;
		std::cout << '\n';

	}
	start = std::clock();
	{
		std::cout << "\n########## REVERSE_ITERATOR  ##########\n\n";
		NS::vector<A> x;
		for (int i = 0; i < 10; i++)
				x.push_back(A(i));
		std::cout << "x : cap = " << x.capacity() << ", size = " << x.size() << std::endl;
		print_vector(x);
		NS::vector<A>::reverse_iterator r = x.rbegin();
		std::cout << "*r :  " << *r << "\n";
		for (int i = 0; r != x.rend(); r++, i++)
		{
			std::cout << "i = " << i << ", *r = " << *r;
			if (i)
				std::cout << ", r.base = " << *(r.base()) << ", ";
		}
		std::cout << std::endl;
	}
	end = std::clock();
	elapsed_time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	std::cout << "Elapsed time VECTOR REVERSE_ITERATOR : " << NAME << " = " << elapsed_time << " seconds\n";
	start = std::clock();
	{
		std::cout << "\n########## LOGICAL OPERATORS ##########\n\n";

		NS::vector<int> x;
		x.push_back(1);
		x.push_back(2);
		x.push_back(3);
		x.push_back(4);
		NS::vector<int> y;
		y = x;
		x.push_back(5);
		x.erase(x.end() - 1);
		std::cout << "x : ";
		print_vector(x);
		std::cout << "y : ";
		print_vector(y);
		std::cout << "x = y ? " << (x == y) << std::endl;
	}
	end = std::clock();
	elapsed_time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	std::cout << "Elapsed time LOGICAL OPERATORS : " << NAME << " = " << elapsed_time << " seconds\n";
	return ;
}
