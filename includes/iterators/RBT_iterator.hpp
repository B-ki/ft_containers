/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:57:49 by rmorel            #+#    #+#             */
/*   Updated: 2023/04/07 17:47:16 by rmorel           ###   ########.fr       */
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

template<class Value, bool IsConst>
class RBT_iterator
{
	public:
		typedef std::bidirectional_iterator_tag 						iterator_category;
		typedef std::ptrdiff_t 											difference_type;
		typedef Value 													value_type;
		typedef value_type*												pointer;
		typedef value_type&												reference;
		typedef RBTNode<value_type>										node_type;
		typedef node_type* 												node_ptr;

	protected:
		node_ptr _current;

	public:
		RBT_iterator() : _current() {}

		RBT_iterator(node_ptr ptr) : _current(ptr) {}

		RBT_iterator(const RBT_iterator<Value, IsConst>& other) : _current(other._current) {}

		RBT_iterator operator=(const RBT_iterator& other)
		{
			if (*this != other)
				_current = other._current;
			return *this;
		}

		reference operator*() const
		{
			return _current->value;
		}

		pointer operator->() const
		{
			return &(_current->value);
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

template< class Value >
bool operator==( const ft::RBT_iterator<Value, false>& lhs,
                 const ft::RBT_iterator<Value, false>& rhs )
{
	return (lhs.base() == rhs.base());
}

template< class Value >
bool operator!=( const ft::RBT_iterator<Value, false>& lhs,
                 const ft::RBT_iterator<Value, false>& rhs )
{
	return (lhs.base() != rhs.base());
}

template<class Value, bool IsConst>
class const_RBT_iterator
{
	public:
		typedef std::bidirectional_iterator_tag 						iterator_category;
		typedef std::ptrdiff_t 											difference_type;
		typedef Value 													value_type;
		typedef const value_type*										const_pointer;
		typedef const value_type&										const_reference;
		typedef RBTNode<value_type>										node_type;
		typedef node_type* 												node_ptr;

	protected:
		node_ptr _current;

	public:
		const_RBT_iterator() : _current() {}

		const_RBT_iterator(node_ptr ptr) : _current(ptr) {}

		const_RBT_iterator(const RBT_iterator<Value, IsConst>& other) : _current(other._current) {}

		const_RBT_iterator operator=(const const_RBT_iterator& other)
		{
			if (*this != other)
				_current = other._current;
			return *this;
		}

		const_reference operator*() const
		{
			return _current->value;
		}

		const_pointer operator->() const
		{
			return &(_current->value);
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

template< class Value >
bool operator==( const ft::const_RBT_iterator<Value, false>& lhs,
                 const ft::const_RBT_iterator<Value, false>& rhs )
{
	return (lhs.base() == rhs.base());
}

template< class Value >
bool operator!=( const ft::const_RBT_iterator<Value, false>& lhs,
                 const ft::const_RBT_iterator<Value, false>& rhs )
{
	return (lhs.base() != rhs.base());
}
}


#endif 
