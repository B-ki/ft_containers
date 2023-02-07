/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:44:23 by rmorel            #+#    #+#             */
/*   Updated: 2023/02/07 17:19:34 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF_HPP
#define ENABLE_IF_HPP 

namespace ft
{

template<bool B, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T> {
	typedef T type;
};

}

#endif 
