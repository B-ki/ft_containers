/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:33:22 by rmorel            #+#    #+#             */
/*   Updated: 2023/04/09 01:04:51 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP 

#include <iterator>

namespace ft
{

// Les traits permettent d'avoir des informations concernant un type pendant la 
// compilation. Ils definissent les regles que doivent respecter un type. 
// Par exemple ici, 5 typedef sont obligatoires pour les iterateurs.
// Les traits sont une convention en C++, declares en tant que struct.

template<class Iterator>
struct iterator_traits
{
	typedef typename Iterator::iterator_category 	iterator_category;
	typedef typename Iterator::value_type 			value_type;
	typedef typename Iterator::difference_type 		difference_type;
	typedef typename Iterator::pointer 				pointer;
	typedef typename Iterator::reference 			reference;
};

// Specialisation de la classe si jamais le type passe n'est pas un iterateur mais un pointeur
template<class T>
struct iterator_traits<T*>
{
	typedef std::random_access_iterator_tag 	iterator_category;
	typedef T 									value_type;
	typedef std::ptrdiff_t 						difference_type;
	typedef T* 									pointer;
	typedef T& 									reference;
};

template<class T>
struct iterator_traits<const T*>
{
	typedef std::random_access_iterator_tag 	iterator_category;
	typedef T 									value_type;
	typedef std::ptrdiff_t 						difference_type;
	typedef const T* 									pointer;
	typedef const T& 									reference;
};

}

#endif 
