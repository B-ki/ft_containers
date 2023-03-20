/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:44:23 by rmorel            #+#    #+#             */
/*   Updated: 2023/03/21 00:06:09 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF_HPP
#define ENABLE_IF_HPP 

namespace ft
{

// ######### ENABLE_IF ###########

template<bool B, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T> {
	typedef T type;
};

// ######### CONDITIONNAL ###########

template<bool B, class T = void, class U = void>
struct conditionnal {};

template<class T, class U>
struct conditionnal<true, T, U> { typedef T type; };

template<class T, class U>
struct conditionnal<false, T, U> { typedef U type; };

}

#endif 
