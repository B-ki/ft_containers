/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 18:18:33 by rmorel            #+#    #+#             */
/*   Updated: 2023/02/07 17:26:19 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP 

#include <iterator>
#include <memory>
#include <cstdlib>
#include <type_traits>
#include "iterator_traits.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"

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
		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

		// ########## DATA MEMBERS ##########

	private:
		T* _start;
		T* _end;
		T* _closing;
		allocator_type _alloc;

		// #################### CONSTRUCTOR & DESTRUCTORS ####################

	public:
		// Default constructor 
		explicit vector() : _start(), _end(), _closing() { };
		// Parametric constructor

		explicit vector(size_type n, const T& value = T()) 
		{
			_start = _alloc.allocate(n);
			_end = _start + n;
			_closing = _start;

			for(; n > 0; n--, _closing++)
				_alloc.construct(_closing, value);
		}
		// Range constructor
		// SFINAE : If we give an int to the constructor it can either be a type or a pointer, thus it will hesitate between range or parametric constructor. So we prevent the compiler to use the range iterator if the parameter is an integral
		template <class InputIterator, ft::enable_if<ft::is_integral<T>::value != true, bool> = true>
		vector(InputIterator first, InputIterator last)
		 {
			 const size_type n = std::distance(first, last);
			 _start = _alloc.allocate(n);
			 _closing = _start + n;
			 _end = _start;
			 for(; first != last; first++, _end++)
				 _alloc.construct(_end, *first);
		 }
		//Copy constructor 
		vector(const vector<T>& x)
		{
			if (this != x)
			{
				const size_type n = std::distance(_start, _closing);
				_start = _alloc.allocate(n);
				_closing = _start + n;
				_end = _start;
				for(size_type i = 0; i < n; _end++)
					_alloc.construct(_end, *(x._start + i));
			}
		}
		// Destructor 
		~vector()
		{
			const size_type n = std::distance(_start, _closing);
			_end = _start;
			for(; _end != _closing; _end++)
				_alloc.destroy(_end);
			_start = _alloc.deallocate(n);
		}
		/*

		   vector<T,Allocator>& operator=(const vector<T>& x);
		   template <class InputIterator>
		   void assign(InputIterator first, InputIterator last);
		   void assign(size_type n, const T& u);
		   allocator_type get_allocator() const;

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

		size_type size() const;
		size_type max_size() const;
		void resize(size_type sz, T c = T());
		size_type capacity() const;
		bool empty() const;
		void reserve(size_type n);

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

		void push_back(const T& x);
		void pop_back();
		iterator insert(iterator position, const T& x);
		void insert(iterator position, size_type n, const T& x);
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last);
		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);
		void swap(vector<T>&);
		void clear();

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
