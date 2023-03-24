/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT_node.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:56:13 by rmorel            #+#    #+#             */
/*   Updated: 2023/03/24 11:19:40 by rmorel           ###   ########.fr       */
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
	static node_ptr minimum(node_ptr node)
	{
		while (node->left)
			node = node->left;
		return node;
	}

	static const_node_ptr minimum(const_node_ptr node)
	{
		while (node->left)
			node = node->left;
		return node;
	}

	static node_ptr maximum(node_ptr node)
	{
		while (node->right)
			node = node->right;
		return node;
	}

	static const_node_ptr maximum(const_node_ptr node)
	{
		while (node->right)
			node = node->right;
		return node;
	}

	static bool isRoot(const_node_ptr node)
	{
		if (!node->parent)
			return true;
		return false;
	}

	static bool isRight(const_node_ptr node)
	{
		if (node->parent && node == node->parent->right)
			return true;
		return false;
	}

	static bool isLeft(const_node_ptr node)
	{
		if (node->parent && node == node->parent->left)
			return true;
		return false;
	}

	// Return the next node in the tree, if no next return NULL
	static node_ptr nodeSucessor(node_ptr node)
	{
		if (node->right)
			return (minimum(node->right));
		node_ptr y = node->parent;
		while (isRight(node) && y)
		{
			node = y;
			y = node->parent;
		}
		return y;
	}
		
	// Idem
	static node_ptr nodePredecessor(node_ptr node)
	{
		if (node->left)
			return (maximum(node->right));
		node_ptr y = node->parent;
		while (isLeft(node) && y)
		{
			node = y;
			y = node->parent;
		}
		return y;
	}
		
};

}
#endif 
