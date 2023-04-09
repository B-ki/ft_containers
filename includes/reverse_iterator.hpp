/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:06:48 by rmorel            #+#    #+#             */
/*   Updated: 2023/04/09 01:16:36 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP 

#include "iterator_traits.hpp"

namespace ft
{

template <class It>
class reverse_iterator 
{
	public :
		typedef It 														iterator_type;
		typedef typename ft::iterator_traits<It>::iterator_category 	iterator_category;
		typedef typename ft::iterator_traits<It>::difference_type 		difference_type;
		typedef typename ft::iterator_traits<It>::value_type 			value_type;
		typedef typename ft::iterator_traits<It>::pointer 				pointer;
		typedef typename ft::iterator_traits<It>::reference 			reference;

	protected:
		iterator_type _current;

	public:
		reverse_iterator() : _current(NULL) {}

		explicit reverse_iterator(It itr) : _current(itr) {}

		reverse_iterator(const reverse_iterator& other) : _current(other._current) {}
		
		template <typename Iter>
		reverse_iterator(const reverse_iterator<Iter>& other) : _current(other.base()) {}

		template<class U>
		reverse_iterator& operator=(const reverse_iterator<U>& rhs)
		{
			_current = rhs.base();
			return *this;
		}

		//Pre-incrementation : ++It
		reverse_iterator& operator++()
		{ 
			--_current; 
			return *this;
		}

		//Post-incrementation : It++
		reverse_iterator operator++(int) 
		{ 
			reverse_iterator tmp(*this); 
			++(*this); 
			return tmp; 
		}

		//Pre-incrementation : --It
		reverse_iterator& operator--() 
		{ 
			++this->_current; 
			return *this; 
		}

		//Post-incrementation : It--
		reverse_iterator operator--(int) 
		{ 
			reverse_iterator tmp(*this);
			--(*this); return tmp;
		}

		reverse_iterator& operator+=(difference_type n)
		{
			_current = _current - n;
			return *this;
		}

		reverse_iterator& operator-=(difference_type n)
		{
			_current = _current + n;
			return *this;
		}

		reverse_iterator operator+(difference_type n) const
		{
			return reverse_iterator(base() - n);
		}

		reverse_iterator operator-(difference_type n) const
		{
			return reverse_iterator(base() + n);
		}

		iterator_type base() const
		{
			return _current;
		}

		reference operator*() const
		{
			It tmp = _current;

			return *--tmp;
		}

		pointer operator->() const
		{
			It tmp = _current;
			return &(*--tmp);
		}			

		reference operator[](difference_type n) const
		{
			return *(*this + n);
		}

};

}

template< class It >
bool operator==( const ft::reverse_iterator<It>& lhs,
                 const ft::reverse_iterator<It>& rhs )
{
	return (lhs.base() == rhs.base());
}

template< class It >
bool operator!=( const ft::reverse_iterator<It>& lhs,
                 const ft::reverse_iterator<It>& rhs )
{
	return (lhs.base() != rhs.base());
}

template< class It >
bool operator<( const ft::reverse_iterator<It>& lhs,
                const ft::reverse_iterator<It>& rhs )
{
	return (lhs.base() > rhs.base());
}

template< class It >
bool operator<=( const ft::reverse_iterator<It>& lhs,
                 const ft::reverse_iterator<It>& rhs )
{
	return (lhs.base() >= rhs.base());
}

template< class It >
bool operator>( const ft::reverse_iterator<It>& lhs,
                const ft::reverse_iterator<It>& rhs )
{
	return (lhs.base() < rhs.base());
}

template< class It >
bool operator>=( const ft::reverse_iterator<It>& lhs,
                 const ft::reverse_iterator<It>& rhs )
{
	return (lhs.base() <= rhs.base());
}

//          Overloading operators for 2 different operatortypes

template< class Iterator1, class Iterator2 >
bool operator==( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs )
{
	return (lhs.base() == rhs.base());
}

template< class Iterator1, class Iterator2 >
bool operator!=( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs )
{
	return (lhs.base() != rhs.base());
}

template< class Iterator1, class Iterator2 >
bool operator<( const ft::reverse_iterator<Iterator1>& lhs,
                const ft::reverse_iterator<Iterator2>& rhs )
{
	return (lhs.base() > rhs.base());
}

template< class Iterator1, class Iterator2 >
bool operator<=( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs )
{
	return (lhs.base() >= rhs.base());
}

template< class Iterator1, class Iterator2 >
bool operator>( const ft::reverse_iterator<Iterator1>& lhs,
                const ft::reverse_iterator<Iterator2>& rhs )
{
	return (lhs.base() < rhs.base());
}

template< class Iterator1, class Iterator2 >
bool operator>=( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs )
{
	return (lhs.base() <= rhs.base());
}

#endif 
