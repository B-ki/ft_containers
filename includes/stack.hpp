/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 09:38:36 by rmorel            #+#    #+#             */
/*   Updated: 2023/04/20 19:58:00 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP 

#include <vector>

namespace ft

{

template <class T, class Container = std::vector<T> >
class stack {
	public:

		// #################### MEMBER TYPES ####################

		typedef typename Container::value_type 		value_type;
		typedef typename Container::size_type 		size_type;
		typedef typename Container::reference 		reference;
		typedef typename Container::const_reference const_reference;
		typedef Container 							container_type;

		// #################### CONSTRUCTOR & DESTRUCTORS ####################

		explicit stack(const Container& cont = Container()) : c(cont) {}

		stack(const stack& other) : c(other.c) {}

		~stack() {}

		// #################### OPERATORS ####################

		stack& operator=(const stack& rhs)
		{
			if (this != rhs)
				c = rhs.c;
			return (*this);
		}

	protected:

		Container c;

	public:

		// #################### CAPACITY ####################

		bool empty() const { return c.empty(); }
		size_type size() const { return c.size(); }

		// #################### ELEMENT ACCESS ####################

		value_type& top() { return c.back(); }
		const value_type& top() const { return c.back(); }

		// #################### MODIFIERS ####################

		void push(const value_type& x) { c.push_back(x); }
		void pop() { c.pop_back(); }

		friend bool operator==(const stack<T, Container>& x,
				const stack<T, Container>& y)
		{
			return x.c == y.c;
		}

		friend bool operator<(const stack<T, Container>& x,
				const stack<T, Container>& y)
		{
			return x.c < y.c;
		}

};

template <class T, class Container>
bool operator!=(const stack<T, Container>& x, const stack<T, Container>& y)
{
	return !(x == y);
}

template <class T, class Container>
bool operator> (const stack<T, Container>& x, const stack<T, Container>& y)
{
	return (y < x);
}

template <class T, class Container>
bool operator>=(const stack<T, Container>& x, const stack<T, Container>& y)
{
	return !(x < y);
}
template <class T, class Container>
bool operator<=(const stack<T, Container>& x, const stack<T, Container>& y)
{
	return !(y < x);
}

}

#endif 
