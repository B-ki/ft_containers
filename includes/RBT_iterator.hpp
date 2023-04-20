/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:57:49 by rmorel            #+#    #+#             */
/*   Updated: 2023/04/20 15:51:06 by rmorel           ###   ########.fr       */
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

template<class Value>
class RBT_iterator
{
	public:
		typedef std::bidirectional_iterator_tag 	iterator_category;
		typedef std::ptrdiff_t 						difference_type;
		typedef Value 								value_type;
		typedef value_type*							pointer;
		typedef value_type&							reference;
		typedef RBTNode<value_type>					node_type;
		typedef node_type* 							node_ptr;

	private:
		node_ptr _current;

	public:
		RBT_iterator() : _current() {}

		RBT_iterator(node_ptr ptr) : _current(ptr) {}

		RBT_iterator(const RBT_iterator& other) : _current(other._current) {}

		/*
		template<class U>
		RBT_iterator& operator=(const RBT_iterator<U>& other)
		{
			_current = other.base();
			return *this;
		}*/

		~RBT_iterator() {}

		node_ptr base() const
		{
			return this->_current;
		}

		RBT_iterator& operator=(const RBT_iterator& other)
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

		bool operator==(const RBT_iterator& rhs) const
		{
			return this->_current == rhs._current;
		}

		bool operator!=(const RBT_iterator& rhs) const
		{
			return this->_current != rhs._current;
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

		RBT_iterator operator+(difference_type n) const
		{
			difference_type i = 0;
			node_ptr tmp = this->_current;
			while (i++ < n)
				tmp = tmp->successor();
			return tmp;
		}

		RBT_iterator operator-(difference_type n) const
		{
			difference_type i = 0;
			node_ptr tmp = this->_current;
			while (i++ < n)
				tmp = tmp->predecessor();
			return tmp;
		}

};

template< class Value >
bool operator==( const ft::RBT_iterator<Value>& lhs,
                 const ft::RBT_iterator<Value>& rhs )
{
	return (lhs.base() == rhs.base());
}

template< class Value >
bool operator!=( const ft::RBT_iterator<Value>& lhs,
                 const ft::RBT_iterator<Value>& rhs )
{
	return (lhs.base() != rhs.base());
}

template<class Value>
class const_RBT_iterator
{
	public:
		typedef std::bidirectional_iterator_tag 	iterator_category;
		typedef std::ptrdiff_t 						difference_type;
		typedef Value 								value_type;
		typedef const value_type*					pointer;
		typedef const value_type&					reference;
		typedef RBTNode<value_type>					node_type;
		typedef node_type* 							node_ptr;

	protected:
		node_ptr _current;

	public:
		const_RBT_iterator() : _current() {}

		const_RBT_iterator(node_ptr ptr) : _current(ptr) {}

		const_RBT_iterator(const const_RBT_iterator& other) :
			_current(other._current) {}

		node_ptr base() const
		{
			return this->_current;
		}

		template<class U>
		const_RBT_iterator(const RBT_iterator<U>& other) :
			_current(other.base()) {}

		const_RBT_iterator& operator=(const const_RBT_iterator& other)
		{
			if (*this != other)
				_current = other._current;
			return *this;
		}

		template<class U>
		const_RBT_iterator& operator=(const const_RBT_iterator<U>& other)
		{
			_current = other.base();
			return *this;
		}

		bool operator==(const const_RBT_iterator& rhs) const
		{
			return this->_current == rhs._current;
		}

		bool operator!=(const const_RBT_iterator& rhs) const
		{
			return this->_current != rhs._current;
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

		const_RBT_iterator operator+(difference_type n) const
		{
			difference_type i = 0;
			node_ptr tmp = this->_current;
			while (i++ < n)
				tmp = tmp->successor();
			return tmp;
		}

		const_RBT_iterator operator-(difference_type n) const
		{
			difference_type i = 0;
			node_ptr tmp = this->_current;
			while (i++ < n)
				tmp = tmp->predecessor();
			return tmp;
		}

};

template< class Value >
bool operator==( const ft::const_RBT_iterator<Value>& lhs,
                 const ft::const_RBT_iterator<Value>& rhs )
{
	return (lhs.base() == rhs.base());
}

template< class V1, class V2 >
bool operator!=( const ft::const_RBT_iterator<V1>& lhs,
                 const ft::const_RBT_iterator<V2>& rhs )
{
	return (lhs.base() != rhs.base());
}

}

#endif 
