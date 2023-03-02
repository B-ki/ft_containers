/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:49:16 by rmorel            #+#    #+#             */
/*   Updated: 2023/03/02 16:44:31 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP 

#include "reverse_iterator.hpp"

namespace ft
{
template <class Key, class T, class Compare = std::less<Key>>
class map {
	public:

		// #################### MEMBER TYPES ####################

		typedef Key 											key_type;
		typedef T 												mapped_type;
		typedef ft::pair<const Key, T> 							value_type;
		typedef Compare 										key_compare;
		typedef typename std::allocator<ft::pair<const Key, T>> allocator_type;
		typedef typename allocator_type::size_type 				size_type;
		typedef typename allocator_type::difference_type 		difference_type;

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

};
}

#endif 
