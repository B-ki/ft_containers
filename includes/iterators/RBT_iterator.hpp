/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:57:49 by rmorel            #+#    #+#             */
/*   Updated: 2023/04/06 18:25:38 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_ITERATOR_HPP
#define RBT_ITERATOR_HPP 

#include "enable_if.hpp"
#include "iterator_traits.hpp"
#include <iterator>
#include "RBT_node.hpp"

namespace ft
{

template<class Pair, bool IsConst>
class RBT_iterator
{
	public:
		typedef std::bidirectional_iterator_tag 						iterator_category;
		typedef std::ptrdiff_t 											difference_type;
		typedef Pair 													pair_type;
		typedef pair_type*												pointer;
		typedef pair_type&												reference;
		typedef RBTNode<pair_type>										node_type;
		typedef node_type* 												node_ptr;

	protected:
		node_ptr _current;

	public:
		RBT_iterator() : _current() {}

		RBT_iterator(node_ptr ptr) : _current(ptr) {}

		RBT_iterator(const RBT_iterator<Pair, IsConst>& other) : _current(other._current) {}

		RBT_iterator operator=(const RBT_iterator& other)
		{
			if (*this != other)
				_current = other._current;
			return *this;
		}

		reference operator*() const
		{
			return _current->pair;
		}

		pointer operator->() const
		{
			return &(_current->pair);
		}			

		//Pre-incrementation : ++It
		RBT_iterator& operator++()
		{ 
			this->_current = this->_current->successor(); 
			return *this;
		}

		//Post-incrementation : It++
		RBT_iterator operator++(int) 
		{ 
			RBT_iterator tmp(*this); 
			this->_current = this->_current->successor(); 
			return tmp; 
		}

		//Pre-incrementation : --It
		RBT_iterator& operator--() 
		{ 
			this->_current = this->_current->predecessor(); 
			return *this; 
		}

		//Post-incrementation : It--
		RBT_iterator operator--(int) 
		{ 
			RBT_iterator tmp(*this); 
			this->_current = this->_current->predecessor(); 
			return tmp; 
		}

		node_ptr base() const
		{
			return this->_current;
		}

};

template< class Pair >
bool operator==( const ft::RBT_iterator<Pair, false>& lhs,
                 const ft::RBT_iterator<Pair, false>& rhs )
{
	return (lhs.base() == rhs.base());
}

template< class Pair >
bool operator!=( const ft::RBT_iterator<Pair, false>& lhs,
                 const ft::RBT_iterator<Pair, false>& rhs )
{
	return (lhs.base() != rhs.base());
}

template<class Pair, bool IsConst>
class const_RBT_iterator
{
	public:
		typedef std::bidirectional_iterator_tag 						iterator_category;
		typedef std::ptrdiff_t 											difference_type;
		typedef Pair 													pair_type;
		typedef const pair_type*										const_pointer;
		typedef const pair_type&										const_reference;
		typedef RBTNode<pair_type>										node_type;
		typedef node_type* 												node_ptr;

	protected:
		node_ptr _current;

	public:
		const_RBT_iterator() : _current() {}

		const_RBT_iterator(node_ptr ptr) : _current(ptr) {}

		const_RBT_iterator(const RBT_iterator<Pair, IsConst>& other) : _current(other._current) {}

		const_RBT_iterator operator=(const const_RBT_iterator& other)
		{
			if (*this != other)
				_current = other._current;
			return *this;
		}

		const_reference operator*() const
		{
			return _current->pair;
		}

		const_pointer operator->() const
		{
			return &(_current->pair);
		}			

		//Pre-incrementation : ++It
		const_RBT_iterator& operator++()
		{ 
			this->_current = this->_current->successor(); 
			return *this;
		}

		//Post-incrementation : It++
		const_RBT_iterator operator++(int) 
		{ 
			const_RBT_iterator tmp(*this); 
			this->_current = this->_current->successor(); 
			return tmp; 
		}

		//Pre-incrementation : --It
		const_RBT_iterator& operator--() 
		{ 
			this->_current = this->_current->predecessor(); 
			return *this; 
		}

		//Post-incrementation : It--
		const_RBT_iterator operator--(int) 
		{ 
			const_RBT_iterator tmp(*this); 
			this->_current = this->_current->predecessor(); 
			return tmp; 
		}

		node_ptr base() const
		{
			return this->_current;
		}

};

template< class Pair >
bool operator==( const ft::const_RBT_iterator<Pair, false>& lhs,
                 const ft::const_RBT_iterator<Pair, false>& rhs )
{
	return (lhs.base() == rhs.base());
}

template< class Pair >
bool operator!=( const ft::const_RBT_iterator<Pair, false>& lhs,
                 const ft::const_RBT_iterator<Pair, false>& rhs )
{
	return (lhs.base() != rhs.base());
}
}


#endif 
