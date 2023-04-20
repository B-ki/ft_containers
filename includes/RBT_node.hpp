/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT_node.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:56:13 by rmorel            #+#    #+#             */
/*   Updated: 2023/04/20 15:25:57 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_NODE_HPP
#define RBT_NODE_HPP 

#include "stddef.h"

namespace ft
{

typedef enum e_color { black, red } t_color;

template<class Pair>
struct RBTNode
{
	Pair 		value;
	RBTNode* 	parent;
	RBTNode* 	left;
	RBTNode* 	right;
	t_color 	color;

	typedef RBTNode 		node_type; 
	typedef RBTNode* 		node_ptr;
	typedef const RBTNode* 	const_node_ptr;

	RBTNode() : value(), parent(NULL), left(NULL), right(NULL), color(black) {}

	RBTNode(Pair v, node_ptr p = NULL, node_ptr l = NULL, node_ptr r = NULL, t_color c = black) : 
		value(v), color(c), parent(p), left(l), right(r) {}; 

	// "static" makes the member accessible out of the class, without needing 
	// to instantiate an object of the class	

	bool isRoot()
	{
		if (this->parent->isNull())
			return true;
		return false;
	}

	bool isRight()
	{
		if (!this->parent->isNull() && this == this->parent->right)
			return true;
		return false;
	}

	bool isLeft()
	{
		if (!this->parent->isNull() && this == this->parent->left)
			return true;
		return false;
	}

	bool isNull()
	{
		if (parent == NULL && left == right)
			return true;
		return false;
	}

	node_ptr maximum()
	{
		node_ptr node = this;
		if (node->isNull())
			return node;
		while (!node->right->isNull())
			node = node->right;
		return node;
	}

	node_ptr minimum()
	{
		node_ptr node = this;
		if (node->isNull())
			return node;
		while (!node->left->isNull())
			node = node->left;
		return node;
	}

	// Return the next node in the tree, if no next return NULL
	node_ptr successor()
	{
		node_ptr node = this;
		if (!node->right->isNull())
			return node->right->minimum();
		node_ptr y = node->parent;
		while (!y->isNull() && node->isRight())
		{
			node = y;
			y = node->parent;
		}
		return y;
	}
		
	// Idem
	node_ptr predecessor()
	{
		node_ptr node = this;
		if (!node->left->isNull())
			return node->left->maximum();
		node_ptr y = node->parent;
		while (!y->isNull() && node->isLeft())
		{
			node = y;
			y = node->parent;
		}
		return y;
	}
		
};

}
#endif 
