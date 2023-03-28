/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:49:16 by rmorel            #+#    #+#             */
/*   Updated: 2023/03/28 22:25:32 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP 

#include "reverse_iterator.hpp"
#include "pair.hpp"
#include "ft_utils.hpp"
#include "RBT.hpp"
#include <iostream>
#include <functional>
#include <limits>

namespace ft
{

template <class Key, class T, class Compare = std::less<Key> >
class map {

		// #################### MEMBER TYPES ####################
	public:
		typedef Key 												key_type;
		typedef T 													mapped_type;
		typedef ft::pair<Key, T> 									pair_type;

		typedef Compare 											key_compare;
		typedef typename std::allocator<ft::pair<Key, T> > 			allocator_type;
		typedef typename allocator_type::size_type 					size_type;
		typedef typename allocator_type::difference_type 			difference_type;

		typedef pair_type& 											reference;
		typedef const pair_type& 									const_reference;
		typedef typename allocator_type::pointer 					pointer;
		typedef typename allocator_type::const_pointer 				const_pointer;

	private:
		// RED and BLACK TREE :
		typedef RBT<key_type, pair_type, ft::SelectFirst<pair_type>, key_compare> 	tree_type; 

//             TO DO
	public:
		typedef typename tree_type::iterator						iterator; 
		typedef typename tree_type::const_iterator					const_iterator; 
		typedef typename tree_type::reverse_iterator				reverse_iterator; 
		typedef typename tree_type::const_reverse_iterator			const_reverse_iterator; 

		// #################### MEMBER CLASSES ####################

		class pair_compare : public binary_function<pair_type, pair_type, bool>
		{
			// ##### MEMBER TYPES #####
			friend class map;
			typedef typename binary_function<pair_type, pair_type, bool>::result_type result_type;
			typedef typename binary_function<pair_type, pair_type, bool>::first_argument_type first_argument_type;
			typedef typename binary_function<pair_type, pair_type, bool>::second_argument_type second_argument_type;

			// ##### CONSTRUCTOR #####
			public:
				pair_compare(key_compare pred) : comp(pred) {}

			// ##### OPERATOR #####
				bool operator()(const pair_type&left, const pair_type& right) const
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

		explicit map (const Compare& comp) : _RBT(comp) {}

		template<class InputIt>
		map(InputIt first, InputIt last, 
				const Compare& comp = Compare()) : _RBT(first, last, comp) {}

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
			return (_RBT.getPair(key)).second;
		}

		const T& at(const Key& key) const
		{
			return (_RBT.getPair(key)).second;
		}

		// insert pair_type(key, T()) if key does not exists
		T& operator[](const Key& key)
		{
			if (!_RBT.searchTree(key))
				return (*_RBT.insert(ft::make_pair(key, T()))).second;
			return (_RBT.getPair(key)).second;
		}

		// #################### ITERATORS ####################

		/*
		iterator begin() { return _RBT.min(); }

		const_iterator begin() const { return _RBT.min(); }

		iterator end() { return _RBT.max(); }

		const_iterator end() const { return _RBT.max(); }
	
		reverse_iterator rbegin() { return _RBT.rmax(); }

		const_reverse_iterator rbegin() const { return _RBT.rmax(); }

		reverse_iterator rend() { return _RBT.rmin(); }

		const_reverse_iterator rend() const { return _RBT.rmin(); }
		*/

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
			return std::numeric_limits<difference_type>::max();
		}

		// #################### MODIFIERS ####################

		void clear()
		{
			_RBT.clearTree();
		}

		ft::pair<iterator, bool> insert(const pair_type& pair)
		{
			iterator it = _RBT.insert(pair);
			bool ret = true;

			if (it.base() == NULL)
				ret = false;
			return ft::make_pair(it, ret);
		}

		// We have an RBT, so we just insert normally
		iterator insert(iterator pos, const pair_type& pair)
		{
			return _RBT.insert(pos, pair);
		}

		template<class InputIt>
		void insert(InputIt first, InputIt last)
		{
			for (InputIt it = first; it != last; it++)
				_RBT.insert(*it);	
		}

		iterator erase(iterator pos)
		{
			return _RBT.erase(pos);
		}

		iterator erase(iterator first, iterator last)
		{
			return _RBT.erase(first, last);
		}

		size_type erase(const Key& key)
		{
			iterator it = _RBT.deleteNode(key);
			if (it.base() != NULL)
				return 1;
			return 0;
		}

		void swap(map& other)
		{
			_RBT.swap(other._RBT);
		}

		// #################### LOOKUP ####################

		size_type count(const Key& key) const
		{
			return _RBT.count(key);
		}

		/*
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
			return _RBT.equal_range(key);
		}

		ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const
		{
			return _RBT.equal_range(key);
		}

		iterator lower_bound(const Key& key)
		{
			return _RBT.lower_bound(key);
		}

		const_iterator lower_bound(const Key& key)
		{
			return _RBT.lower_bound(key);
		}

		iterator upper_bound(const Key& key)
		{
			return _RBT.upper_bound(key);
		}

		const_iterator upper_bound(const Key& key)
		{
			return _RBT.upper_bound(key);
		}
		*/

		// #################### OBSERVERS ####################

		key_compare key_comp() const
		{
			return key_compare();
		}

		pair_compare pair_comp() const
		{
			return pair_compare(key_comp());
		}

	public:
		// #################### HELPERS ####################
		
		void printRBT(void)
		{
			_RBT.prettyPrint();
		}

};

	// #################### NON-MEMBER FUNCTIONS ####################

/*
template<class Key, class T, class Compare = std::less<Key> > 
std::ostream& operator<<(std::ostream& o, const map<Key, T, Compare>& m)
{
	o << m.printRBT();
	return o;
}
*/
}

#endif 
