/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 18:18:33 by rmorel            #+#    #+#             */
/*   Updated: 2023/02/18 00:54:28 by rmorel           ###   ########.fr       */
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

namespace ft
{
template <class T>
class vector
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

		// !!!!!!!!!!!!!!! Il va falloir refaire la class std::reverse_iterator
		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

		// ########## DATA MEMBERS ##########

	private:
		T* _first;
		T* _last;
		T* _end;
		std::allocator<T> _alloc;

		// #################### CONSTRUCTOR & DESTRUCTORS ####################

	public:
		// Default constructor 
		explicit vector() : _first(), _last(), _end() { };

		// Parametric constructor
		explicit vector(size_type n, const T& value = T()) 
		{
			_first = _alloc.allocate(n);
			_end = _first + n;
			_last = _first;

			for(; n > 0; n--, _last++)
				_alloc.construct(_last, value);
		}
		// Range constructor
		// SFINAE : If we give an int to the constructor it can either be a type or a pointer, thus it will hesitate between range or parametric constructor. So we prevent the compiler to use the range iterator if the parameter is an integral
		template <class It>
		vector(It first, It last, typename ft::enable_if<!ft::is_integral<It>::value, It>::type* = 0)
		 {
			 const size_type n = std::distance(first, last);
			 this->_first = _alloc.allocate(n);
			 this->_end = this->_first + n;
			 this->_last = this->_first;
			 for(; first != last; first++, this->_last++)
				 _alloc.construct(this->_last, *first);
		 }
		// !!!!!!!!! MIGHT BE PROBLEM WITH FORWARD AND INPUT ITERATOR !!!!!!!

		//Copy constructor 
		vector(const vector<T>& x)
		{
			if (this != &x)
			{
				const size_type n = std::distance(x._first, x._last);
				_first = _alloc.allocate(n);
				_last = _first + n;
				_end = _first + n;
				std::uninitialized_copy(x._first, x._last, this->_first);
			}
		}

		// Destructor 
		~vector()
		{
			const size_type n = std::distance(_first, _end);
			for(iterator it = _first; it != _last; it++)
				_alloc.destroy(it);
			_alloc.deallocate(_first, n);
		}

		// #################### ASSIGNMENT OPERATORS  ####################

		   vector<T>& operator=(const vector<T>& x) {
			   size_type xSize = x.size();
			   size_type xCap = x.capacity();
			   size_type thisSize = this->size();
			   size_type thisCap = this->capacity();

			   if (xSize >= thisSize && xCap <= thisCap)
			   {
				   size_type i = 0;
				   iterator it = x._first;
				   for (; i != thisSize; it++, i++)
					   *(this->_first + i) = *it;
				   for (; it != x._last; it++, i++)
						_alloc.construct(this->_first + i, *it);
				   this->_last = this->_first + i;
			   }
			   else if (xSize < thisSize && xCap <= thisCap)
			   {
				   size_type i = 0;
				   iterator it = x._first;
				   for (; it != x._last; it++, i++)
						*(this->_first  + i) = *it;
				   for (; i < thisSize; i++)
					   _alloc.destroy(this->_first + i);
				   this->_last = this->_first + xSize;
			   }
			   else
			   {
				   this->clear();
				   _alloc.deallocate(this->_first, thisCap);
				   this->_first = _alloc.allocate(xCap);
				   std::uninitialized_copy(x._first, x._last, this->_first);
				   this->_last = this->_first + xSize;
				   this->_end = this->_first + xCap;
				}
			   return (*this);
		   }

		   template <class It>
		   void assign(It first, It last, typename ft::enable_if<!ft::is_integral<It>::value, It>::type* = 0) {
			   std::copy(first, last, this->_first);
		   }

		   void assign(size_type n, const T& u) {
			   size_type sz = this->size();
			   size_type cap = this->capacity();
			   if (n > cap) {
				   vector<T> tmp(n, u);
				   this->swap(tmp);
			   }
			   else {
				   if (n < sz) {
					   for (size_type i = 0; i < sz; i++)
					   {
						   this->_alloc.destroy(this->_first + i);
						   this->_alloc.construct(this->_first + i, u);
					   }
				   }
				   else {

				   }
			   }
		   }

		   allocator_type get_allocator() const { return _alloc; }

		// #################### ITERATORS ####################

		iterator begin() { return _first; }
		const_iterator begin() const { return _first; }
		iterator end() { return _last; }
		const_iterator end() const { return _last; }
		/*
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		reverse_iterator rend();
		const_reverse_iterator rend() const;

		// #################### CAPACITY ####################

		*/
		size_type size() const { return std::distance(this->_first, this->_last); }

		size_type max_size() const { return std::numeric_limits<difference_type>::max(); }

		size_type capacity() const { return std::distance(_first, _end); }

		bool empty() const {
			if (_first)
				return false;
			return true;
		}

		void reserve(size_type newCap) {
			if (newCap > this->max_size())
				throw(std::length_error("ft::vector<t>::reserve : newCap > max_size"));
			if (newCap <= this->size())
				return;
			try {
				const size_type oldSize = this->size();
				pointer newFirst = _alloc.allocate(newCap);
				pointer newLast = newFirst;

				for (size_type i = 0; i < oldSize; i++, newLast++)
				{
					_alloc.construct(newLast, *(_first + i));
					_alloc.destroy(_first + i);
				}
				_alloc.deallocate(_first, oldSize);
				_first = newFirst;
				_last = newLast;
				_end = _first + newCap;
			} catch(std::bad_alloc) {
				return ;
			}
		}

		// #################### ELEMENT ACCESS ####################

		reference operator[](size_type n) {
			return (*(this->_first + n));
		}

		const_reference operator[](size_type n) const {
			return (*(this->_first + n));
		}

		reference at(size_type n) {
			if (!(n < size()))
				throw std::out_of_range ("");
			return (*(this->_first + n));
		}

		const_reference at(size_type n) const {
			if (!(n < size()))
				throw std::out_of_range ("");
			return (*(this->_first + n));
		}

		reference front() {
			return (*this->_first);
		}

		const_reference front() const {
			return (*this->_first);
		}

		reference back() {
			return (*(this->_last - 1));
		}

		const_reference back() const {
			return (*(this->_last - 1));
		}

		// #################### MODIFIERS ####################

		void push_back(const T& x) {
			if (_last == _end)
				reserve(this->capacity() ? this->capacity() * 2 : 1);
			_alloc.construct(_last, x);
			_last++;
		}

		void pop_back() {
			if (_first)
			{
				_alloc.destroy(_last - 1);
				_last--;
			}
		}

		iterator insert(iterator position, const T& x) {
			size_type oldCap = this->capacity();

			if (oldCap == this->size()) {
				pointer newFirst = _alloc.allocate(oldCap + 1);
				size_type i = 0;

				for (; this->_first + i != position; i++)
					_alloc.construct(newFirst + i, *(this->_first + i));
				_alloc.construct(newFirst + i, x);
				i++;
				for (; i != oldCap + 1; i++)
					_alloc.construct(newFirst + i, *(this->_first + i - 1));
				this->clear();
				_alloc.deallocate(this->_first, oldCap);
				this->_first = newFirst;
				this->_last = newFirst + oldCap + 1;
				this->_end = this->_last;
			}
			else {
				if (position == _last)
					_alloc.construct(position, x);
				else {
					_alloc.construct(this->_last, *(this->_last - 1));
					for(iterator it = this->_last - 1; it != position; it--)
						*it = *(it - 1);
					*position = x;
				}
				this->_last++;
			}
			return (position);
		}

		void insert(iterator pos, size_type n, const T& x) {
			size_type oldCap = this->capacity();

			if (oldCap < this->size() + n) {
				size_type newCap = (oldCap + n ? (oldCap + n) * 2 : 1);
				pointer newFirst = _alloc.allocate(newCap);
				pointer tmp;

				tmp = std::uninitialized_copy(this->_first, pos, newFirst);
				tmp = std::uninitialized_fill_n(tmp, n, x);
				tmp = std::uninitialized_copy(pos, this->_last, tmp);
				this->clear();
				_alloc.deallocate(this->_first, oldCap);
				this->_first = newFirst;
				this->_last = tmp;
				this->_end = this->_first + newCap;
			}
			else {
				/*
				pointer oldLast = this->_last;

				this->resize(n + this->size());
				std::copy_backward(pos, oldLast, this->_last);
				std::fill_n(pos, n, x);
				*/
				difference_type cop = ((this->_last - pos) - n > 0 ? (this->_last - pos) - n : 0);
				if (pos + n + cop < this->_end)
					std::uninitialized_copy(pos + cop, pos + cop + n, pos + n + cop);
				if (cop > 0)
					std::copy(pos, pos + cop, pos + n);
				size_type fill = (n < (size_type)(this->_last - pos) ? n : this->_last - pos);
				if (pos != this->_last)
					std::fill_n(pos, fill, x);
				if (pos + n > this->_last)
					std::uninitialized_fill_n(this->_last, n - fill, x);
				this->_last += n;
			}
		}

		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last);

		iterator erase(iterator position) {
			return (erase(position, position + 1));
		}

		iterator erase(iterator first, iterator last) {
			difference_type dist = std::distance(first, last);

			if (dist <= 0)
				return (last);
			std::copy(first + dist, this->_last, first);
			for(iterator it = _last - dist; it != this->_last; it++)
				_alloc.destroy(it);
			this->_last -= dist;
			return (last);
		}

		void swap(vector<T>& other) {
			T* _tmpFirst = this->_first;
			T* _tmpLast = this->_last;
			T* _tmpEnd = this->_end;

			this->_first = other._first;
			this->_last = other._last;
			this->_end = other._end;
			other._first = _tmpFirst;
			other._last = _tmpLast;
			other._end = _tmpEnd;
		}

		void clear() {
			size_type const n = size();

			for (size_type i = 0; i < n; i++) {
				_alloc.destroy(_first + i);
			}
			_last = _first;
		}

		void resize(size_type n, T c = T()) {
			size_type const sz = size();
			size_type const cap = capacity();

			if (n > cap)
			{
				reserve(n);
				for(size_type i = sz; i < n; i++)
					_alloc.construct(this->_first + i, c);
			}
			else if (sz > n)
			{
				for (size_type i = n; i < sz; i++)
					_alloc.destroy(this->_first + i);
			}
			else 
			{
				for (size_type i = sz; i < n; i++)
					_alloc.construct(this->_first + i, c);
			}
			_last = _first + n;
		}
		/*

		template <class T>
		bool operator==(const vector<T>& x, const vector<T>& y);
		template <class T>
		bool operator< (const vector<T>& x, const vector<T>& y);
		template <class T>
		bool operator!=(const vector<T>& x, const vector<T>& y);
		template <class T>
		bool operator> (const vector<T>& x, const vector<T>& y);
		template <class T>
		bool operator>=(const vector<T>& x, const vector<T>& y);
		template <class T>
		bool operator<=(const vector<T>& x, const vector<T>& y);

		// #################### SPECIALIZED ALGORITHM ####################

		template <class T>
		void swap(vector<T>& x, vector<T>& y);
		*/
};
}

#endif 
