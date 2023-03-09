/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:29:20 by rmorel            #+#    #+#             */
/*   Updated: 2023/03/09 20:39:09 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_HPP
#define FT_UTILS_HPP 

namespace ft
{

template <class ArgumentType, class ResultType>
struct unary_function
	{
		typedef ArgumentType 	argument_type;
		typedef ResultType 		result_type;
	};

template <class Arg1, class Arg2, class Result>
struct binary_function
	{
		typedef Arg1 	first_argument_type;
		typedef Arg2 	second_argument_type;
		typedef Result 	result_type;
	};

template <class Pair>
struct SelectFirst : public unary_function<Pair, typename Pair::first_type>
{
	typedef typename unary_function<Pair, typename Pair::first_type>::result_type result_type;

	result_type& operator()(Pair& p) const
	{
		return (p.first_type);
	}

	result_type& operator()(const Pair& p) const
	{
		return (p.first_type);
	}
};

template <class T>
struct Identity : public unary_function<T, T>
{
	typedef typename unary_function<T, T>::result_type result_type;

	result_type& operator()(T& value) const
	{
		return (value);
	}

	result_type& operator()(const T& value) const
	{
		return (value);
	}
};

}

#endif 
