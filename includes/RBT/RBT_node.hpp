/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT_node.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:56:13 by rmorel            #+#    #+#             */
/*   Updated: 2023/04/05 21:53:14 by rmorel           ###   ########.fr       */
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
	Pair 		pair;
	RBTNode* 	parent;
	RBTNode* 	left;
	RBTNode* 	right;
	t_color 	color;
	int 		bf;

	typedef RBTNode 		node_type; 
	typedef RBTNode* 		node_ptr;
	typedef const RBTNode* 	const_node_ptr;

	RBTNode() : pair(), parent(NULL), left(NULL), right(NULL), color(black), bf(0) {}

	RBTNode(Pair v, node_ptr p = NULL, node_ptr l = NULL, node_ptr r = NULL, t_color c = black, int bf = 0) : 
		pair(v), color(c), parent(p), left(l), right(r), bf(bf) {}; 

	// "static" makes the member accessible out of the class, without needing 
	// to instantiate an object of the class	

	bool isRoot()
	{
		if (this->parent == NULL)
			return true;
		return false;
	}

	bool isRight()
	{
		if (this->parent && this == this->parent->right)
			return true;
		return false;
	}

	bool isLeft()
	{
		if (this->parent != NULL && this->parent->left != NULL && this == this->parent->left)
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
		while (!node->right->isNull())
			node = node->right;
		return node;
	}

	node_ptr minimum()
	{
		node_ptr node = this;
		while (!node->left->isNull())
			node = node->left;
		return node;
	}

	// Return the next node in the tree, if no next return NULL
	node_ptr successor()
	{
		node_ptr node = this;
		if (!node->right->isNull())
			return (node->right->minimum());
		node_ptr y = node->parent;
		while (node->isRight() && y != NULL)
		{
			node = y;
			y = node->parent;
		}
		if (y == NULL)
			return this->maximum()->right;
		return y;
	}
		
	// Idem
	node_ptr predecessor()
	{
		node_ptr node = this;
		if (!node->left->isNull())
			return (node->left->maximum());
		node_ptr y = node->parent;
		while (node->isLeft() && y != NULL)
		{
			node = y;
			y = node->parent;
		}
		if (y == NULL)
			return this->maximum()->right;
		return y;
	}
		
};

}
#endif 
