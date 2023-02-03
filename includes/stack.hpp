/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 09:38:36 by rmorel            #+#    #+#             */
/*   Updated: 2023/02/03 13:56:11 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP 

#include <vector>

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
};

template <class T, class Container>
bool operator==(const stack<T, Container>& x, const stack<T, Container>& y)
{
	return (x == y);
}

template <class T, class Container>
bool operator<(const stack<T, Container>& x, const stack<T, Container>& y)
{
	return (x < y);
}

template <class T, class Container>
bool operator!=(const stack<T, Container>& x, const stack<T, Container>& y)
{
	return (x != y);
}

template <class T, class Container>
bool operator> (const stack<T, Container>& x, const stack<T, Container>& y)
{
	return (x > y);
}

template <class T, class Container>
bool operator>=(const stack<T, Container>& x, const stack<T, Container>& y)
{
	return (x >= y);
}
template <class T, class Container>
bool operator<=(const stack<T, Container>& x, const stack<T, Container>& y)
{
	return (x <= y);
}

#endif 
