/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:57:49 by rmorel            #+#    #+#             */
/*   Updated: 2023/03/21 16:57:24 by rmorel           ###   ########.fr       */
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

template<class PairType, bool IsConst>
class RBT_iterator
{
	public:
		typedef std::bidirectional_iterator_tag 						iterator_category;
		typedef std::ptrdiff_t 											difference_type;
		typedef PairType 												pair_type;
		typedef ft::conditionnal<IsConst, const pair_type, pair_type> 	value_type;
		typedef value_type*												pointer;
		typedef value_type&												reference;
		typedef RBTNode<PairType>										node;
		typedef ft::conditionnal<IsConst, const node, node> 			node_type;
		typedef node_type* 												node_ptr;

	protected:
		node_ptr _current;

	public:
		RBT_iterator() : _current() {}

		RBT_iterator(node_ptr ptr) : _current(ptr) {}

		RBT_iterator(const RBT_iterator<PairType, IsConst>& other) : _current(other._current) {}

		RBT_iterator operator=(const RBT_iterator& other)
		{
			if (*this != other)
				_current = other._current;
			return *this;
		}

		reference operator*() const
		{
			return _current->data;
		}

		pointer operator->() const
		{
			return &(_current->data);
		}			

		//Pre-incrementation : ++It
		RBT_iterator& operator++()
		{ 
			this->_current = nodeSucessor(_current); 
			return *this;
		}

		//Post-incrementation : It++
		RBT_iterator operator++(int) 
		{ 
			RBT_iterator tmp(*this); 
			this->_current = nodeSucessor(_current); 
			return tmp; 
		}

		//Pre-incrementation : --It
		RBT_iterator& operator--() 
		{ 
			this->_current = nodePredecessor(_current); 
			return *this; 
		}

		//Post-incrementation : It--
		RBT_iterator operator--(int) 
		{ 
			RBT_iterator tmp(*this); 
			this->_current = nodePredecessor(_current); 
			return *tmp; 
		}

};

template< class PairType >
bool operator==( const ft::RBT_iterator<PairType, false>& lhs,
                 const ft::RBT_iterator<PairType, false>& rhs )
{
	return (lhs._current == rhs._current);
}

template< class PairType >
bool operator!=( const ft::RBT_iterator<PairType, false>& lhs,
                 const ft::RBT_iterator<PairType, false>& rhs )
{
	return (lhs._current != rhs._current);
}

}


#endif 
