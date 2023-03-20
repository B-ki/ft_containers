/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:20:46 by rmorel            #+#    #+#             */
/*   Updated: 2023/03/20 22:16:00 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_HPP
#define RBT_HPP 

#include <exception>
#include <functional>
#include <memory>
#include <iostream>
#include "reverse_iterator.hpp"
#include "ft_utils.hpp"
#include "pair.hpp"

namespace ft
{

typedef enum e_color { black, red } t_color;

template<class Value>
struct RBTNode
{
	Value 		value;
	RBTNode* 	parent;
	RBTNode* 	left;
	RBTNode* 	right;
	t_color 	color;
	int 		bf;

	typedef RBTNode 		node_type; 
	typedef RBTNode* 		node_ptr;
	typedef const RBTNode* 	const_node_ptr;

	RBTNode() : value(), parent(NULL), left(NULL), right(NULL), color(black), bf(0) {}

	RBTNode(Value v, node_ptr p = NULL, node_ptr l = NULL, node_ptr r = NULL, t_color c = black, int bf = 0) : 
		value(v), color(c), parent(p), left(l), right(r), bf(bf) {}; 

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

	bool isRoot(node_ptr node)
	{
		if (!node->parent)
			return true;
		return false;
	}

	bool isRight(node_ptr node)
	{
		if (node->parent && node == node->parent->right)
			return true;
		return false;
	}

	bool isLeft(node_ptr node)
	{
		if (node->parent && node == node->parent->left)
			return true;
		return false;
	}
		
};

template<class Key, class Value, class KeyOfValue, class KeyCompare = std::less<Key> >
class RBT
{
		// #################### MEMBER TYPES ####################

		// Value will be a pair in map and set
		typedef Value 											value_type;
		typedef Key 											key_type;
		typedef KeyCompare 										key_compare;
		typedef KeyOfValue 										key_of_value;

		typedef typename std::allocator<value_type> 			value_allocator;
		typedef typename std::allocator<RBTNode<value_type> >   node_allocator;
		typedef typename value_allocator::size_type 			size_type;
		typedef typename value_allocator::difference_type 		difference_type;

		typedef value_type& 									reference;
		typedef const value_type& 								const_reference;
		typedef typename value_allocator::pointer 				pointer;
		typedef typename value_allocator::const_pointer 		const_pointer;

		typedef RBTNode<value_type> 							node_type;
		typedef RBTNode<value_type>* 							node_ptr;
		typedef const RBTNode<value_type>* 						const_node_ptr;

//             TO DO
/*
		typedef T* iterator; 
		typedef const T* const_iterator;

		typedef ft::reverse_iterator<iterator> 					reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> 			const_reverse_iterator;
*/

		// #################### CONSTRUCTOR & DESTRUCTORS ####################

	public:
		RBT() : root(NULL) {}; 

		~RBT()
		{
			destructorHelper(this->root);
		}

		// #################### MEMBERS ####################
		
		node_ptr 		root;
		node_allocator 	allocator;

		// #################### HELPERS ####################

	private:

		const key_type& keyOfNode(node_ptr node)
		{
			return key_of_value(node->value);
		}

		const value_type& valueOfNode(node_ptr node)
		{
			return node->value;
		}

		bool isSameKey(const node_ptr node, const key_type& key)
		{
			if (!key_compare(keyOfNode(node), key) && 
					!key_compare(key, keyOfNode(node)))
				return true;
			return false;
		}

		bool isKeyInf(const node_ptr node, const key_type& key)
		{
			return key_compare(keyOfNode(node), key);
		}

		bool isKeySup(const node_ptr node, const key_type& key)
		{
			return key_compare(key, keyOfNode(node));
		}

		node_ptr create_node(const value_type& val)
		{
			node_ptr node = node_allocator::allocate(1);
			try {
				node_allocator::construct(node, node_type(val));
				node->value = val;
			} catch (...) {
				node_allocator::deallocate(node, 1);
				throw ;
			}
			return node;
		}

		void erase_node(node_ptr node)
		{
			// No need to destroy node->value, it is called in destroy(node)
			allocator.destroy(node);
			allocator.deallocate(node, 1);		
		}

		void initializeNode(node_ptr node, value_type value = value_type())
		{
			node->value = value;
			node->parent = NULL;
			node->left = NULL;
			node->right = NULL;
			node->color = black;
			node->bf = 0;
		}

		node_ptr searchTreeHelper(node_ptr node, const key_type& key)
		{
			if (node == NULL || isSameKey(node, key))
				return node;
			if (key_compare(keyOfNode(node), key))
				return searchTreeHelper(node->left, key);
			return searchTreeHelper(node->right, key);
		}

		node_ptr deleteNodeHelper(node_ptr node, const key_type& key) {
			if (node == NULL) 
				return node;
			else if (key_compare(key, keyOfNode(node)))
				node->left = deleteNodeHelper(node->left, key);
			else if (key_compare(keyOfNode(node), key))
				node->right = deleteNodeHelper(node->right, key);
			else
			{
				//The key has been found, now we have to delete it

				//Case 1 : The node to delete is a leaf Node
				if (node->left == NULL && node->right == NULL)
				{
					erase_node(node);
					node = NULL;
				}
				//Case 2 : The node has only one child
				else if (node->left == NULL)
				{
					node_ptr temp = node;
					node = node->left;
					erase_node(temp);
				}
				else if (node->right == NULL)
				{
					node_ptr temp = node;
					node = node->right;
					erase_node(temp);
				}
				//Case 3 : The node has 2 children
				else
				{
					node_ptr temp = minimum(node->right);
					node->value = temp->value;
					node->right = deleteNodeHelper(node->right, temp->value);
				}
			}
			// Update balance logic
			updateBalance(node);
			return node;
		}

		void printHelperPerso(node_ptr node, std::string indent) {
			if (node != NULL) {
				indent += "            ";
				printHelperPerso(node->right, indent);
				std::cout << indent << node->value << "(bf=" << node->bf << ")\n";
				printHelperPerso(node->left, indent);
			}	
		}

		void destructorHelper(node_ptr node) {
			if (node != NULL) {
				destructorHelper(node->left);
				destructorHelper(node->right);
				erase_node(node);	
			}	
		}

	public: 
		node_ptr searchTree(int key) {
			return searchTreeHelper(this->root, key);
		}

		node_ptr minimum(node_ptr node) {
			while (node->left) {
				minimum(node->left);
			}
			return node;
		}

		node_ptr maximum(node_ptr node) {
			while (node->right) {
				maximum(node->right);
			}
			return node;
		}

		// The successor is the node whose key is next
		node_ptr successor(node_ptr x) {
			if (x->right != NULL)
				return minimum(x->right);
			node_ptr y = x->parent;
			while (y != NULL && isRight(x)) {
				x = y;
				y = y->parent;
			}
			return y;
		}

		// The predecessor is the node whose key is just before
		node_ptr predecessor(node_ptr x) {
			if (x->left != NULL)
				maximum(x->left);
			node_ptr y = x->parent;
			while (y != NULL && isLeft(x)) {
				x = y;
				y = y->parent;
			}
			return y;
		}

		void insert(value_type val) {
			node_ptr node = node_allocator::allocate(1);
			initializeNode(node, val);
			node_ptr y = NULL;
			node_ptr x = this->root;
			while (x != NULL) {
				y = x;
				if (node->data < x->data)
					x = x->left;
				else
					x = x->right;
			}
			node->parent = y;
			if (y == NULL)
				root = node;
			else if (node->data < y->data)
				y->left = node;
			else
				y->right = node;
			//updateBalance the node if necessary
			updateBalance(node);
		}

		node_ptr getRoot() { return this->root; }

		node_ptr deleteNode(int data) {
			return deleteNodeHelper(this->root, data);
		}

		void prettyPrint() {
			printHelperPerso(this->root, "");
		}

//                  |                        | 
//                  x                        y
//                 / \                      / \
//                a   y        ==>         x   c
//                   / \                  / \
//                  b   c                a   b

		void leftRotate(node_ptr x) {
			std::cout << "leftRotate node " << x->data << std::endl;
			node_ptr y = x->right;
			x->right = y->left;
			if (y->left != NULL)
				y->left->parent = x;
			y->parent = x->parent;
			if (x->parent == NULL)
				this->root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->left = x;
			x->parent = y;

			// BF = height(RightSubTree) - height(LeftSubTree)
			x->bf = x->bf - 1 - std::max(0, y->bf);
			y->bf = y->bf - 1 + std::min(0, x->bf);
		}

//                  |                        | 
//                  x                        y
//                 / \                      / \
//                y   c        ==>         a   x
//               / \                          / \
//              a   b                        b   c

		void rightRotate(node_ptr x) {
			std::cout << "rightRotate node " << x->data << std::endl;
			node_ptr y = x->left;
			x->left = y->right;
			if (y->right != NULL)
				y->right->parent = x;
			y->parent = x->parent;
			if (x->parent == NULL)
				this->root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->right = x;
			x->parent = y;
			
			x->bf = x->bf + 1 - std::min(0, y->bf);
			y->bf = y->bf + 1 + std::max(0, x->bf);
		}

	void updateBalance(node_ptr node) {
		//std::cout << "updateBalance node " << node->data << ", bf = " << node->bf << std::endl;
		if (!node)
			return;
		// The first ancestor that has a bf < -1 || > 1 is rebalanced. There should be only one considering the fact
		// that we do this everytime we insert something.
		if (node->bf < -1 || node->bf > 1) {
			//std::cout << "Rebalancing node " << node->data << std::endl;
			rebalance(node);
			//prettyPrint();
			return ;
		}
		if (node->parent != NULL) {
			//std::cout << "Node parent : data = " << node->parent->data << ", bf = " << node->parent->bf << std::endl;
			if (node == node->parent->left)
				node->parent->bf--;
			if (node == node->parent->right)
				node->parent->bf++;
			//std::cout << "Node parent : data = " << node->parent->data << ", bf = " << node->parent->bf << std::endl;
			if (node->parent->bf != 0)
				updateBalance(node->parent);
		}
	}

		void rebalance(node_ptr node) {
			if (node->bf > 0) {
				if (node->right->bf < 0) {
//                  |                     |                   |
//        BF=2      a               BF=2  a                   b
//                   \                     \                 / \
//        BF=-1       c     ==>     BF=1    b      ==>      a   c    BF=0 partout
//                   /                       \                          /
//        BF=0      b               BF=0      c
//                       rightRotate              leftRotate
					rightRotate(node->right);
					leftRotate(node);
				}
				else
//                  |                        | 
//       BF=2       a                        b
//                   \                      / \
//       BF=1         b        ==>         a   c       BF=0 partout
//                     \                                        /
//       BF=0           c                    
//                          leftRotate
					leftRotate(node);
			}
			else if (node->bf < 0) {
				if (node->left->bf > 0) {
//                  |                           |                   |
//        BF=-2     a               BF=-2       a                   b
//                 /                           /                   / \
//        BF=1    c         ==>     BF=-1     b          ==>      a   c    BF=0 partout
//                 \                         /                                /
//        BF=0      b               BF=0    c        
//                       leftRotate                  rightRotate
					leftRotate(node->left);
					rightRotate(node);
				}
				else
//                  |                        | 
//         BF=-2    c                        b
//                 /                        / \
//        BF=-1   b            ==>         a   c       BF=0 partout
//               /                             
//      BF=0    a                               
//                         rightRotate
					rightRotate(node);
			}
		}

};
}



#endif 
