/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:14:01 by rmorel            #+#    #+#             */
/*   Updated: 2023/02/09 11:48:37 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP 

#include "remove_cv.hpp"

namespace ft
{

template<class T, T v>
struct integral_constant
{
    static const T 					value = v;
    typedef T 						value_type;
	// type now mean integral_constant type
    typedef integral_constant<T, v> type;
	// operator to access value_type, not necessary here
	
    operator value_type() { 
		return value;
	}
};

typedef ft::integral_constant<bool, true> true_type;
typedef ft::integral_constant<bool, false> false_type;

}

namespace ft
{

template <typename T>
struct is_integral : false_type {};

template <>
struct is_integral<bool> : true_type {};

template <>
struct is_integral<char> : true_type {};

template <>
struct is_integral<unsigned char> : true_type {};

template <>
struct is_integral<signed char> : true_type {};

template <>
struct is_integral<short> : true_type {};

template <>
struct is_integral<unsigned short> : true_type {};

template <>
struct is_integral<int> : true_type {};

template <>
struct is_integral<unsigned int> : true_type {};

template <>
struct is_integral<long> : true_type {};

template <>
struct is_integral<unsigned long> : true_type {};

}

#endif 
