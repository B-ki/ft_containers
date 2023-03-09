/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:49:16 by rmorel            #+#    #+#             */
/*   Updated: 2023/03/09 21:55:29 by rmorel           ###   ########.fr       */
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

		typedef value_type& 									reference;
		typedef const value_type& 								const_reference;
		typedef typename allocator_type::pointer 				pointer;
		typedef typename allocator_type::const_pointer 			const_pointer;

//             TO DO
/*
		typedef T* iterator; 
		typedef const T* const_iterator;
*/

		typedef ft::reverse_iterator<iterator> 					reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> 			const_reverse_iterator;

		typedef RBT<key_type,
				value_type, 
				SelectFirst<ft::pair<key_type, value_type> >,
				key_compare> 									tree_type; 

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
					return comp(left, right);
				}

			// ##### PROTECTED MEMBER #####
			protected:
				key_compare comp;
		};

		// #################### CONSTRUCTOR & DESTRUCTORS ####################

		map() : RBT() {}

		explicit map (const Compare& comp) : RBT() {}

		template<class InputIt>



		// #################### ELEMENT ACCESS ####################

		// #################### ITERATORS ####################

		// #################### CAPACITY ####################

		// #################### MODIFIERS ####################

		// #################### LOOKUP ####################

		// #################### OBSERVERS ####################

		// #################### OBSERVERS ####################
		
	private:
		tree_type RBT;
};

	// #################### NON-MEMBER FUNCTIONS ####################


}

#endif 
