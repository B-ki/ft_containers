/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:57:49 by rmorel            #+#    #+#             */
/*   Updated: 2023/04/05 20:44:56 by rmorel           ###   ########.fr       */
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
		//typedef ft::conditionnal<IsConst, const pair, pair> 			pair_type;
		typedef pair_type*												pointer;
		typedef pair_type&												reference;
		typedef RBTNode<pair_type>										node_type;
		//typedef ft::conditionnal<IsConst, const node, node> 			node_type;
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
			if (_current->isNull())
				return *this;
			this->_current = this->_current->successor(); 
			return *this;
		}

		//Post-incrementation : It++
		RBT_iterator operator++(int) 
		{ 
			if (_current->isNull())
				return *this;
			RBT_iterator tmp(*this); 
			this->_current = this->_current->successor(); 
			return tmp; 
		}

		//Pre-incrementation : --It
		RBT_iterator& operator--() 
		{ 
			if (_current->isNull())
				this->_current = this->_current->right->maximum();
			else
				this->_current = this->_current->predecessor(); 
			return *this; 
		}

		//Post-incrementation : It--
		RBT_iterator operator--(int) 
		{ 
			RBT_iterator tmp(*this); 
			if (_current->isNull())
				this->_current = this->_current->right->maximum();
			else
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

}


#endif 
