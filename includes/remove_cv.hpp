/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_cv.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:06:50 by rmorel            #+#    #+#             */
/*   Updated: 2023/02/07 16:11:55 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REMOVE_CV_HPP
# define REMOVE_CV_HPP 

namespace ft
{
template<class T>
	struct remove_cv {
		typedef T type;
};

template<class T>
	struct remove_cv<const T> {
		typedef T type;
};

template<class T>
	struct remove_cv<volatile T> {
		typedef T type;
};

template<class T>
	struct remove_cv<const volatile T> {
		typedef T type;
};
}

#endif 
