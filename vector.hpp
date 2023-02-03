/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 18:18:33 by rmorel            #+#    #+#             */
/*   Updated: 2023/02/03 21:18:07 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP 

#include <allocator>

template <class T>>
class vector {
	public:

		// #################### MEMBER TYPES ####################

		typedef T value_type;
		typedef std::allocator<t>::value_type allocator_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;

		typedef typename std::allocator<T>::reference reference;
		typedef typename std::allocator<T>::const_reference const_reference;
		typedef typename std::allocator<T>::pointer pointer;
		typedef typename std::allocator<T>::const_pointer const_pointer;

		typedef T* iterator; 
		typedef const T* const_iterator;

		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	private:
		size_type capacity;
		size_type nelems;


		// #################### CONSTRUCTOR & DESTRUCTORS ####################

		explicit vector(const Allocator& = Allocator());
		explicit vector(size_type n, const T& value = T(), const Allocator& = Allocator());

		template <class InputIterator>
		vector(InputIterator first, InputIterator last,	const Allocator& = Allocator());

		vector(const vector<T, Allocator>& x);

		~vector();
		vector<T,Allocator>& operator=(const vector<T,Allocator>& x);
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
		void swap(vector<T,Allocator>&);
		void clear();

		template <class T, class Allocator>
			bool operator==(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
		template <class T, class Allocator>
			bool operator< (const vector<T,Allocator>& x, const vector<T,Allocator>& y);
		template <class T, class Allocator>
			bool operator!=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
		template <class T, class Allocator>
			bool operator> (const vector<T,Allocator>& x, const vector<T,Allocator>& y);
		template <class T, class Allocator>
			bool operator>=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);
		template <class T, class Allocator>
			bool operator<=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);

		// #################### SPECIALIZED ALGORITHM ####################
		
		template <class T, class Allocator>
			void swap(vector<T,Allocator>& x, vector<T,Allocator>& y);
}

#endif 
