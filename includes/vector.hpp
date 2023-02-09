/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 18:18:33 by rmorel            #+#    #+#             */
/*   Updated: 2023/02/09 19:49:25 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP 

#include <iterator>
#include <memory>
#include <cstdlib>
#include "iterator_traits.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"
#include <limits>
#include <new>

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
		allocator_type _alloc;

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
			 _first = _alloc.allocate(n);
			 _end = _first + n;
			 _last = _first;
			 for(; first != last; first++, _last++)
				 _alloc.construct(_last, *first);
		 }
		// !!!!!!!!! MIGHT BE PROBLEM WITH FORWARD AND INPUT ITERATOR !!!!!!!

		//Copy constructor 
		vector(const vector<T>& x)
		{
			if (this != x)
			{
				const size_type n = std::distance(_first, _end);
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
			_last = _first;
			for(; _last != _end; _last++)
				_alloc.destroy(_last);
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
				   std::copy(x._first, x._first + thisSize, this->_first);
				   std::uninitialized_copy(x._first + thisSize, x._last, this->_first + thisSize);
			   }
			   else if (xSize < thisSize && xCap <= thisCap)
			   {
				   std::copy(x._first, x._last, _first);
				   for (size_type i = xSize; i < thisSize; i++)
					   _alloc.destroy(_first + i);
			   }
			   else
			   {
				   T* newFirst = _alloc.allocate(xCap);
				   T* newLast = newFirst;
				   for (size_type i = 0; i < thisCap; i++, newLast++)
				   {
					   _alloc.construct(newLast, _first + i);
					   _alloc.destroy(_first + i);
				   }
				   _alloc.deallocate(_first, thisCap);
				   _first = newFirst;
				   _last = newLast;
				   _end = _first + xCap;
			}
			   ;

		   };
		   template <class It>
		   void assign(It first, It last);
		   void assign(size_type n, const T& u);
		   allocator_type get_allocator() const;
		  /*

		// #################### ITERATORS ####################

		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		reverse_iterator rend();
		const_reverse_iterator rend() const;

		// #################### CAPACITY ####################

		*/
		size_type size() const { return std::distance(_first, _last); }
		size_type max_size() const { return std::numeric_limits<difference_type>::max(); }
		size_type capacity() const { return std::distance(_first, _end); }
		bool empty() const {
			if (_first)
				return false;
			return true;
		}
		void reserve(size_type newCap) {
			if (newCap <= this->size())
				return;
			try {
				const size_type oldCap = this->capacity();
				T* newFirst = _alloc.allocate(newCap);
				T* newLast = newFirst;
				for (size_type i = 0; i < oldCap; i++, newLast++)
				{
					_alloc.construct(newLast, _first + i);
					_alloc.destroy(_first + i);
				}
				_alloc.deallocate(_first, oldCap);
				_first = newFirst;
				_last = newLast;
				_end = _first + newCap;
			} catch(std::bad_alloc) {
				return ;
			}
		}
		/*

		// #################### ELEMENT ACCESS ####################

		reference operator[](size_type n);
		const_reference operator[](size_type n) const;
		const_reference at(size_type n) const;
		reference at(size_type n);
		reference front();
		const_reference front() const;
		reference back();
		const_reference back() const;

		// #################### MODIFIERS ####################

		*/
		void push_back(const T& x) {
			if (_last == _end)
				reserve(this->capacity() ? this->capacity() * 2 : 1);
			_alloc.construct(_last, x);
			_last++;
		}
		void pop_back() {
			_alloc.destroy(_last);
			_last--;
		}
		iterator insert(iterator position, const T& x);
		void insert(iterator position, size_type n, const T& x);
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last);
		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);
		void swap(vector<T>&);
		void clear() {
			size_type const n = size();

			for (size_type i = 0; i < n; i++) {
				_alloc.destroy(_first + i);
			}
			_last = _first;
		}
		void resize(size_type sz, T c = T()) {
			size_type const n = size();

			if (sz < n)
			{
				for (size_type i = sz; i < n; i++)
					_alloc.destroy(_first + i);
			}
			else if (sz > n)
			{
				reserve(sz);
				for(size_type i = n; i < sz; i++)
					_alloc.construct(_first + i, c);
			}
			_last = _first + sz;
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
