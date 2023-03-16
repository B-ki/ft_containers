/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:49:16 by rmorel            #+#    #+#             */
/*   Updated: 2023/03/16 16:06:35 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP 

#include "reverse_iterator.hpp"
#include "pair.hpp"
#include "ft_utils.hpp"
#include "RBT.hpp"

namespace ft
{
template <class Key, class T, class Compare = std::less<Key> >
class map {
	public:

		// #################### MEMBER TYPES ####################

		typedef Key 												key_type;
		typedef T 													mapped_type;
		typedef ft::pair<const Key, T> 								value_type;

		typedef Compare 											key_compare;
		typedef typename std::allocator<ft::pair<const Key, T> > 	allocator_type;
		typedef typename allocator_type::size_type 					size_type;
		typedef typename allocator_type::difference_type 			difference_type;

		typedef value_type& 										reference;
		typedef const value_type& 									const_reference;
		typedef typename allocator_type::pointer 					pointer;
		typedef typename allocator_type::const_pointer 				const_pointer;

//             TO DO
/*
		typedef T* iterator; 
		typedef const T* const_iterator;

		typedef ft::reverse_iterator<iterator> 						reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> 				const_reverse_iterator;
*/

		// RED and BLACK TREE :
		typedef RBT<key_type,
				value_type, 
				SelectFirst<ft::pair<key_type, value_type> >,
				value_compare> 										tree_type; 

		// #################### MEMBER CLASSES ####################

		class value_compare : public binary_function<value_type, value_type, bool>
		{
			// ##### MEMBER TYPES #####
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

		// #################### CONSTRUCTOR & DESTRUCTORS ####################

		map() : RBT() {}

		explicit map (const Compare& comp) : RBT(), value_compare(comp) {}

		template<class InputIt>
		map(InputIt first, InputIt last, 
				const Compare& comp = Compare()) : RBT(first, last), value_compare(comp) {}

		map (const map& other) : RBT(other.RBT), value_compare(other.value_compare) {}

		~map()
		{
			~RBT();
			~value_compare();
		}

		map& operator=(const map& other)
		{
			if (*this != other)
				RBT = other.RBT;
			return *this;
		}

		allocator_type get_allocator() const { return allocator_type(); }

		// #################### ELEMENT ACCESS ####################

		// Return std::out_of_range is key is not in the RBT
		T& at(const Key& key)
		{
			return RBT(key);
		}

		const T& at(const Key& key) const
		{
			return RBT(key);
		}

		// insert value_type(key, T()) if key does not exists
		T& operator[](const Key& key)
		{
			if (!RBT(key))
				RBT.insert(key, T());
			return RBT(key);
		}

		// #################### ITERATORS ####################

		/*
		iterator begin() { return RBT.min(); }

		const_iterator begin() const { return RBT.min(); }

		iterator end() { return RBT.max(); }

		const_iterator end() const { return RBT.max(); }
	
		reverse_iterator rbegin() { return RBT.rmax(); }

		const_reverse_iterator rbegin() const { return RBT.rmax(); }

		reverse_iterator rend() { return RBT.rmin(); }

		const_reverse_iterator rend() const { return RBT.rmin(); }
		*/

		// #################### CAPACITY ####################

		bool empty() const
		{
			return RBT.empty();
		}

		size_type size() const
		{
			return RBT.size();
		}

		size_type max_size() const
		{
			return RBT.max_size();
		}

		// #################### MODIFIERS ####################

		void clear()
		{
			RBT.clear();
		}

		/*
		ft::pair<iterator, bool> insert(const value_type& value)
		{
			return RBT.insert(value);
		}

		iterator insert(iterator pos, const value_type& value)
		{
			return RBT.insert(pos, value);
		}
		*/

		template<class InputIt>
		void insert(InputIt first, InputIt last)
		{
			return RBT.insert(first, last);
		}

		/*
		iterator erase(iterator pos)
		{
			return RBT.erase(pos);
		}

		iterator erase(iterator first, iterator last)
		{
			return RBT.erase(first, last);
		}
		*/

		size_type erase(const Key& key)
		{
			return RBT.erase(key);
		}

		void swap(map& other)
		{
			RBT.swap(other.RBT);
		}

		// #################### LOOKUP ####################

		size_type count(const Key& key) const
		{
			return RBT.count(key);
		}

		/*
		iterator find(const Key& key)
		{
			return RBT.find(key);
		}

		const_iterator find(const Key& key) const
		{
			return RBT.find(key);
		}

		ft::pair<iterator, iterator> equal_range(const Key& key)
		{
			return RBT.equal_range(key);
		}

		ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const
		{
			return RBT.equal_range(key);
		}

		iterator lower_bound(const Key& key)
		{
			return RBT.lower_bound(key);
		}

		const_iterator lower_bound(const Key& key)
		{
			return RBT.lower_bound(key);
		}

		iterator upper_bound(const Key& key)
		{
			return RBT.upper_bound(key);
		}

		const_iterator upper_bound(const Key& key)
		{
			return RBT.upper_bound(key);
		}
		*/

		// #################### OBSERVERS ####################

		key_compare key_comp() const
		{
			return key_compare();
		}

		value_compare value_comp() const
		{
			return value_compare(key_comp());
		}

	private:
		tree_type RBT;
};

	// #################### NON-MEMBER FUNCTIONS ####################


}

#endif 
