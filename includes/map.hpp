/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:49:16 by rmorel            #+#    #+#             */
/*   Updated: 2023/04/23 14:22:20 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP 

#include "reverse_iterator.hpp"
#include "is_integral.hpp"
#include "pair.hpp"
#include "ft_utils.hpp"
#include "equal.hpp"
#include "RBT.hpp"
#include <iostream>
#include <functional>
#include <limits>

namespace ft
{

template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<Key, T> > >
class map {

		// #################### MEMBER TYPES ####################
	public:
		typedef Key 												key_type;
		typedef T 													mapped_type;
		typedef ft::pair<Key, T> 									value_type;

		typedef Compare 											key_compare;
		typedef typename std::allocator<ft::pair<Key, T> > 			allocator_type;
		typedef typename allocator_type::size_type 					size_type;
		typedef typename allocator_type::difference_type 			difference_type;

		typedef value_type& 										reference;
		typedef const value_type& 									const_reference;
		typedef typename allocator_type::pointer 					pointer;
		typedef typename allocator_type::const_pointer 				const_pointer;

	private:
		// RED and BLACK TREE :
		typedef RBT<key_type, value_type, ft::SelectFirst<value_type>, key_compare> 	tree_type; 

	public:
		typedef typename tree_type::iterator						iterator; 
		typedef typename tree_type::const_iterator					const_iterator; 
		typedef typename tree_type::reverse_iterator				reverse_iterator; 
		typedef typename tree_type::const_reverse_iterator			const_reverse_iterator; 

		// #################### MEMBER CLASSES ####################

		class value_compare : public binary_function<value_type, value_type, bool>
		{
			// ##### MEMBER TYPES #####
			friend class map;
			typedef typename binary_function<value_type, value_type, bool>::result_type result_type;
			typedef typename binary_function<value_type, value_type, bool>::first_argument_type first_argument_type;
			typedef typename binary_function<value_type, value_type, bool>::second_argument_type second_argument_type;

			// ##### CONSTRUCTOR #####
			public:
				value_compare(key_compare pred) : comp(pred) {}

			// ##### OPERATOR #####
				bool operator()(const value_type&left, const value_type& right) const
				{
					return comp(left.first, right.first);
				}

			// ##### PROTECTED MEMBER #####
			protected:
				key_compare comp;
		};

		// #################### MEMBERS ####################

	private:
		tree_type _RBT;

		// #################### CONSTRUCTOR & DESTRUCTORS ####################

	public:
		map() : _RBT() {}

		explicit map (const Compare& comp,
				const Allocator& alloc = Allocator()) : _RBT(comp, alloc) {}

		template<class It>
		map(It first, It last, const Compare& comp = Compare(), 
				const Allocator& alloc = Allocator(),
				typename ft::enable_if<!ft::is_integral<It>::value, It>::type* = 0) : 
			_RBT(first, last, comp, alloc) {}

		map (const map& other) : _RBT(other._RBT) {}

		~map() {}

		map& operator=(const map& other)
		{
			if (*this != other)
				_RBT = other._RBT;
			return *this;
		}

		allocator_type get_allocator() const { return allocator_type(); }

		// #################### ELEMENT ACCESS ####################

		// Return std::out_of_range is key is not in the _RBT
		T& at(const Key& key) 
		{
			return (_RBT.getValue(key)).second;
		}

		const T& at(const Key& key) const
		{
			return (_RBT.getValue(key)).second;
		}

		// insert value_type(key, T()) if key does not exists
		T& operator[](const Key& key)
		{
			return insert(ft::make_pair(key, T())).first->second;
		}

		// #################### ITERATORS ####################

		iterator begin() { return _RBT.begin(); }

		const_iterator begin() const { return _RBT.cbegin(); }

		iterator end() { return _RBT.end(); }

		const_iterator end() const { return _RBT.cend(); }
	
		reverse_iterator rbegin() { return _RBT.rbegin(); }

		const_reverse_iterator rbegin() const { return _RBT.crbegin(); }

		reverse_iterator rend() { return _RBT.rend(); }

		const_reverse_iterator rend() const { return _RBT.crend(); }

		// #################### CAPACITY ####################

		bool empty() const
		{
			return _RBT.empty();
		}

		size_type size() const
		{
			return _RBT.size();
		}

		size_type max_size() const
		{
			return _RBT.max_size();
		}

		// #################### MODIFIERS ####################

		void clear()
		{
			_RBT.clearTree();
		}

		ft::pair<iterator, bool> insert(const value_type& value)
		{
			return _RBT.insert(value);
		}

		// We have an RBT, so we just insert normally
		iterator insert(iterator pos, const value_type& value)
		{
			return _RBT.insert(pos, value);
		}

		template<class It>
		void insert(It first, It last,
				typename ft::enable_if<!ft::is_integral<It>::value, It>::type* = 0)
		{
			for (It it = first; it != last; it++)
				_RBT.insert(*it);	
		}

		void erase(iterator pos)
		{
			_RBT.erase(pos);
		}

		void erase(iterator first, iterator last)
		{
			while (first != last)
				_RBT.erase(first++);
		}

		size_type erase(const Key& key)
		{
			return _RBT.erase(key);
		}

		void swap(map& other)
		{
			_RBT.swap(other._RBT);
		}

		// #################### LOOKUP ####################

		size_type count(const Key& key) const
		{
			if (_RBT.searchTree(key) != NULL)
				return 1;
			return 0;
		}

		iterator find(const Key& key)
		{
			return _RBT.find(key);
		}

		const_iterator find(const Key& key) const
		{
			return _RBT.find(key);
		}

		ft::pair<iterator, iterator> equal_range(const Key& key)
		{
			return ft::make_pair(_RBT.lowerBound(key), _RBT.upperBound(key));
		}

		ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const
		{
			return ft::make_pair(_RBT.lowerBound(key), _RBT.upperBound(key));
		}

		iterator lower_bound(const Key& key)
		{
			return _RBT.lowerBound(key);
		}

		const_iterator lower_bound(const Key& key) const
		{
			return _RBT.lowerBound(key);
		}

		iterator upper_bound(const Key& key)
		{
			return _RBT.upperBound(key);
		}

		const_iterator upper_bound(const Key& key) const
		{
			return _RBT.upperBound(key);
		}

		// #################### OBSERVERS ####################

		key_compare key_comp() const
		{
			return key_compare();
		}

		value_compare value_comp() const
		{
			return value_compare(key_comp());
		}

	public:
		// #################### HELPERS ####################
		
		void printRBT(void)
		{
			_RBT.prettyPrint();
			_RBT.checkRbt();
		}

		void checkRBT(void)
		{
			_RBT.checkRbt();
		}

};

	// #################### NON-MEMBER FUNCTIONS ####################

template<class Key, class T, class Compare, class Alloc> 
inline bool operator==(const map<Key, T, Compare, Alloc>& m1,
		const map<Key, T, Compare, Alloc>& m2)
{
	return m1.size() == m2.size() && ft::equal(m1.begin(), m1.end(), m2.begin());
}

template<class Key, class T, class Compare, class Alloc> 
bool operator!=(const map<Key, T, Compare, Alloc>& m1,
		const map<Key, T, Compare, Alloc>& m2)
{
	return !(m1 == m2);
}

template<class Key, class T, class Compare, class Alloc>
bool operator<(const map<Key, T, Compare, Alloc>& m1,
		const map<Key, T, Compare, Alloc>& m2)
{
	return ft::lexicographical_compare(m1.begin(), m1.end(), m2.begin(), m2.end());
}

template<class Key, class T, class Compare, class Alloc>
bool operator>=(const map<Key, T, Compare, Alloc>& m1,
		const map<Key, T, Compare, Alloc>& m2)
{
	return !(m1 < m2);
}

template<class Key, class T, class Compare, class Alloc>
bool operator>(const map<Key, T, Compare, Alloc>& m1,
		const map<Key, T, Compare, Alloc>& m2)
{
	return m2 < m1;
}

template<class Key, class T, class Compare, class Alloc> 
bool operator<=(const map<Key, T, Compare, Alloc>& m1,
		const map<Key, T, Compare, Alloc>& m2)
{
	return !(m1 > m2);
}

template<class Key, class T, class Compare, class Alloc> 
void swap(const map<Key, T, Compare, Alloc>& m1,
		const map<Key, T, Compare, Alloc>& m2)
{
	m1.swap(m2);
}

}

#endif 
