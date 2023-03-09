/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 18:18:33 by rmorel            #+#    #+#             */
/*   Updated: 2023/03/09 22:01:53 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP 

#include <algorithm>
#include <cstddef>
#include <exception>
#include <iterator>
#include <memory>
#include <cstdlib>
#include "iterator_traits.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"
#include <limits>
#include <new>
#include <iostream>
#include <stdexcept>
#include <streambuf>
#include "reverse_iterator.hpp"
#include "equal.hpp"

namespace ft
{

template <class T>
class vector_base
{
		// #################### CONSTRUCTOR & DESTRUCTORS ####################
	public:
		explicit vector_base(typename std::allocator<T>::size_type n) : _first(), _last(), _end(), _alloc()
		{
			if (n > 0)
				_first = _alloc.allocate(n);
			// Si n > max_size, allocate peut throw (ex : std::distance(end, begin))
			_last = _first;
			_end = _first + n;
		}

		~vector_base()
		{
			if (_first)
				_alloc.deallocate(_first, _end - _first);
		}
		// ########## DATA MEMBERS ##########


		T* _first;
		T* _last;
		T* _end;
		std::allocator<T> _alloc;
};

template <class T>
void swapVectorBase(vector_base<T>& a, vector_base<T>& b)
{
	std::swap(a._first, b._first);
	std::swap(a._last, b._last);
	std::swap(a._end, b._end);
	std::swap(a._alloc, b._alloc);
}

template <class T>
class vector : private vector_base<T>
{
	public:

		// #################### MEMBER TYPES ####################

		typedef T value_type;
		//allocator_type est le type value_type retournee par std::allocator<T>
		typedef typename std::allocator<value_type> allocator_type;

		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename allocator_type::size_type size_type;
		typedef typename allocator_type::difference_type difference_type;

		typedef value_type& reference;
		typedef const value_type& const_reference;

		typedef T* iterator; 
		typedef const T* const_iterator;

		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

		// #################### DATA MEMBERS ####################

		using vector_base<T>::_first;
		using vector_base<T>::_last;
		using vector_base<T>::_end;
		using vector_base<T>::_alloc;

		// #################### CONSTRUCTOR & DESTRUCTORS ####################
	public:
		// Default constructor 
		explicit vector() : vector_base<T>(0) { };


		// Parametric constructor
		explicit vector(size_type n, const T& value = T()) : vector_base<T>(n) 
	{
		std::uninitialized_fill_n(_first, n, value);
		_last = _first + n;
	}

		// Range constructor
		// SFINAE : If we give an int to the constructor it can either be a type or a pointer, 
		// thus it will hesitate between range or parametric constructor. So we prevent the 
		// compiler to use the range iterator if the parameter is an integral
		template <class It>
		vector(It first, It last, 
				typename ft::enable_if<!ft::is_integral<It>::value, It>::type* = 0) : vector_base<T>(std::distance(first, last))
	{
		std::uninitialized_copy(first, last, _first);
		_last = _first + std::distance(first, last);
	}

		//Copy constructor 
		vector(const vector<T>& x) : vector_base<T>(x.size())
	{
		std::uninitialized_copy(x._first, x._last, _first);
		_last = _first + x.size();
	}

		// Destructor 
		~vector()
		{
			clear();
		}

		// #################### ASSIGNMENT OPERATORS  ####################

		vector<T>& operator=(const vector<T>& x)
		{
			// Normalement la STL utilise adressof pour comparer lhs et rhs (et pas == car trop 
			// long de comparer tout le vecteur), mais addressof est du C++11
			if (this == &x)
				return *this;

			size_type xSize = x.size();
			size_type xCap = x.capacity();
			size_type thisSize = size();
			size_type thisCap = capacity();

			if (xSize >= thisSize && xCap <= thisCap)
			{
				std::copy(x._first, x._first + thisSize, _first);
				std::uninitialized_copy(x._first + thisSize, x._last, _last);
				_last = _first + xSize;
			}
			else if (xSize < thisSize && xCap <= thisCap)
			{
				std::copy(x._first, x._last, _first);
				for (size_type i = xSize; i < thisSize; i++)
					_alloc.destroy(_first + i);
				_last = _first + xSize;
			}
			else
			{
				vector<T> tmp(x);
				swap(tmp);
			}
			return (*this);
		}

		template <class It>
			void assign(It first, It last, typename ft::enable_if<!ft::is_integral<It>::value, It>::type* = 0)
			{
				size_type sz = size();
				size_type cap = capacity();
				size_type n = std::distance(first, last);
				if (n > cap)
				{
					vector<T> tmp(first, last);
					swap(tmp);
				}
				else
				{
					if (n < sz)
					{
						std::copy(first, last, _first);
						for (iterator it = _first + n; it != _last; it++)
							_alloc.destroy(it);
					}
					else
					{
						std::copy(first, first + sz, _first);
						std::uninitialized_copy(first + sz, last, _last);
					}
					_last = _first + n;
				}
			}

		void assign(size_type n, const T& u)
		{
			size_type sz = size();
			size_type cap = capacity();
			if (n > cap)
			{
				vector<T> tmp(n, u);
				swap(tmp);
			}
			else
			{
				if (n < sz)
				{
					std::fill(_first, _first + n, u);
					for (iterator it = _first + n; it != _last; it++)
						_alloc.destroy(it);
				}
				else
				{
					std::fill(_first, _last, u);
					std::uninitialized_fill(_last, _first + n, u);
				}
				_last = _first + n;
			}
		}

		allocator_type get_allocator() const { return _alloc; }

		// #################### ITERATORS ####################

		iterator begin() { return iterator(_first); }

		const_iterator begin() const { return const_iterator(_first); }

		iterator end() { return iterator(_last); }

		const_iterator end() const { return const_iterator(_last); }

		reverse_iterator rbegin() { return reverse_iterator(_last); }

		const_reverse_iterator rbegin() const { return const_reverse_iterator(_last); }

		reverse_iterator rend() { return reverse_iterator(_first); }

		const_reverse_iterator rend() const { return const_reverse_iterator(_first); }

		// #################### CAPACITY ####################

		size_type size() const { return (_last - _first); }

		size_type max_size() const { return _alloc.max_size(); }

		size_type capacity() const { return (_end - _first); }

		bool empty() const { return !size(); }

		void reserve(size_type newCap)
		{
			if (newCap > max_size())
				throw(std::length_error("ft::vector<t>::reserve : newCap > max_size"));
			if (newCap <= capacity())
				return;

			vector_base<T> tmp(newCap);

			tmp._last = std::uninitialized_copy(_first, _last, tmp._first);
			clear();
			ft::swapVectorBase(*this, tmp);	
		}

		// #################### ELEMENT ACCESS ####################

		reference operator[](size_type n)
		{
			return (*(_first + n));
		}

		const_reference operator[](size_type n) const
		{
			return (*(_first + n));
		}

		reference at(size_type n)
		{
			if (!(n < size()))
				throw std::out_of_range ("");
			return (*(_first + n));
		}

		const_reference at(size_type n) const
		{
			if (!(n < size()))
				throw std::out_of_range ("");
			return (*(_first + n));
		}

		reference front()
		{
			return (*_first);
		}

		const_reference front() const
		{
			return (*_first);
		}

		reference back()
		{
			return (*(_last - 1));
		}

		const_reference back() const
		{
			return (*(_last - 1));
		}

		// #################### MODIFIERS ####################

		void push_back(const T& x)
		{
			if (_last == _end)
				reserve(capacity() ? capacity() * 2 : 1);
			_alloc.construct(_last, x);
			_last++;
		}

		void pop_back()
		{
			if (_first)
			{
				_alloc.destroy(_last - 1);
				_last--;
			}
		}

		iterator insert(const_iterator position, const T& x)
		{
			insert(position, 1lu, x);
			iterator pos = (iterator)position;
			return (pos);
		}

		void insert(const_iterator position, size_type n, const T& x)
		{
			iterator pos = (iterator)position;
			size_type oldCap = capacity();

			if (oldCap < size() + n)
			{
				size_type newCap = (oldCap + n ? (oldCap + n) * 2 : 1);
				vector<T> tmpVector;
				tmpVector.reserve(newCap);

				tmpVector._last = std::uninitialized_copy(_first, pos, tmpVector._first);
				tmpVector._last= std::uninitialized_fill_n(tmpVector._last, n, x);
				tmpVector._last = std::uninitialized_copy(pos, _last, tmpVector._last);
				swap(tmpVector);
			}
			else
			{
				iterator oldLast = _last;
				iterator cop = (_last - n) - pos > 0 ? (_last - n) : pos;
				iterator fill = (pos + n) > _last ? _last : (pos + n);
				std::uninitialized_fill(fill, (pos + n), x);
				_last += ((pos + n) - fill);
				_last = std::uninitialized_copy(cop, oldLast, (cop + n));
				std::copy_backward(pos, cop, oldLast);
				std::fill(pos, fill, x);
			}
		}

		template <class InputIterator>
			void insert(const_iterator position, InputIterator first, InputIterator last)
			{
				iterator pos = (iterator)position;
				size_type oldCap = capacity();
				size_type n = std::distance(first, last);

				if (oldCap < size() + n)
				{
					size_type newCap = (oldCap + n ? (oldCap + n) * 2 : 1);
					vector<T> tmpVector;
					tmpVector.reserve(newCap);

					tmpVector._last = std::uninitialized_copy(_first, pos, tmpVector._first);
					tmpVector._last = std::uninitialized_copy(first, last, tmpVector._last);
					tmpVector._last = std::uninitialized_copy(pos, _last, tmpVector._last);
					swap(tmpVector);
				}
				else
				{
					iterator oldLast = _last;
					iterator startOwnCopy = (_last - n) - pos > 0 ? (_last - n) : pos;
					iterator endTargetCopy = (pos + n) > _last ? _last : (pos + n);
					std::uninitialized_copy(first + (endTargetCopy - pos), last, endTargetCopy);
					_last += last - first + pos - endTargetCopy;
					std::uninitialized_copy(startOwnCopy, oldLast, (startOwnCopy + n));
					_last += oldLast - startOwnCopy;
					std::copy_backward(pos, startOwnCopy, oldLast);
					std::copy(endTargetCopy, first + (endTargetCopy - pos), pos);
				}

			}

		iterator erase(iterator position)
		{
			return (erase(position, position + 1));
		}

		iterator erase(iterator first, iterator last)
		{
			difference_type dist = std::distance(first, last);

			if (dist <= 0)
				return (last);
			std::copy(first + dist, _last, first);
			for(iterator it = _last - dist; it != _last; it++)
				_alloc.destroy(it);
			_last -= dist;
			return (last);
		}

		void swap(vector<T>& other)
		{
			T* _tmpFirst = _first;
			T* _tmpLast = _last;
			T* _tmpEnd = _end;

			_first = other._first;
			_last = other._last;
			_end = other._end;
			other._first = _tmpFirst;
			other._last = _tmpLast;
			other._end = _tmpEnd;
		}

		void clear()
		{
			size_type const n = size();

			for (size_type i = 0; i < n; i++)
			{
				_alloc.destroy(_first + i);
			}
			_last = _first;
		}

		void resize(size_type n, T c = T())
		{
			size_type const sz = size();

			reserve(n);
			if (sz > n)
			{
				for (size_type i = n; i < sz; i++)
					_alloc.destroy(_first + i);
			}
			else 
				std::uninitialized_fill_n(_first + sz, n - sz, c);
			_last = _first + n;
		}
};
		// #################### NON MEMBER FUNCTIONS ####################

template <class T>
bool operator==(const vector<T>& x, const vector<T>& y)
{
	if (x.size() != y.size())
		return false;
	return ft::equal(x.begin(), x.end(), y.begin());
}

template <class T>
bool operator!=(const vector<T>& x, const vector<T>& y)
{
	if (x.size() != y.size())
		return true;
	return !ft::equal(x.begin(), x.end(), y.begin());
}

template <class T>
bool operator> (const vector<T>& x, const vector<T>& y)
{
	return ft::lexicographical_compare(y.begin(), y.end(), x.begin(), x.end());
}

template <class T>
bool operator< (const vector<T>& x, const vector<T>& y)
{
	return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

template <class T>
bool operator>=(const vector<T>& x, const vector<T>& y)
{
	return !ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

template <class T>
bool operator<=(const vector<T>& x, const vector<T>& y)
{
	return !ft::lexicographical_compare(y.begin(), y.end(), x.begin(), x.end());
}

// #################### SPECIALIZED ALGORITHM ####################

template <class T>
void swap(vector<T>& x, vector<T>& y)
{
	x.swap(y);
}

}

#endif 
