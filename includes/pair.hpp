/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:44:43 by rmorel            #+#    #+#             */
/*   Updated: 2023/03/08 17:23:12 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
#define PAIR_HPP 

#include <utility>
namespace ft
{
template <class T1, class T2>
struct pair
{
	typedef T1 first_type;
	typedef T2 second_type;

	T1 first;
	T2 second;

	// #################### CONSTRUCTORS & DESTRUCTORS ####################

	pair(void) : first(), second() {}

	pair(const T1& x, const T2& y) : first(x), second(y) {};

	template < class U1, class U2 >
	pair(const pair<U1, U2>& p) : first(p.first), second(p.second) {};

	// #################### ASSIGNMENT OPERATORS  ####################

	pair<T1, T2>& operator=(const pair& other) {
		if (*this != other) {
			first = other.first;
			second = other.second;
		}
	}

	// #################### MEMBER FUNCTIONS  ####################

	pair<T1, T2> make_pair (T1 t, T2 u) {
		pair<T1, T2> ret(t, u);
		return ret;
	}
};

		// #################### NON MEMBER FUNCTIONS ####################

		template <class T1, class T2>
		bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
			return lhs.first == rhs.first && lhs.second == rhs.second;
		}


		template <class T1, class T2>
		bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
			return lhs.first != rhs.first || lhs.second != rhs.second;
		}

		template <class T1, class T2>
		bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
			if (lhs.first < rhs.first)
				return true;
			else if (rhs.first < lhs.first)
				return false;
			else {
				if (lhs.second < rhs.second)
					return true;
				else
					return false;
			}
		}

		template <class T1, class T2>
		bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
			return !(rhs < lhs);
		}

		template <class T1, class T2>
		bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
			return rhs < lhs;
		}

		template <class T1, class T2>
		bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
			return !(lhs < rhs);
		}

}

#endif 
