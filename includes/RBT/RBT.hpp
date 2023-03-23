/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:20:46 by rmorel            #+#    #+#             */
/*   Updated: 2023/03/23 18:07:42 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_HPP
#define RBT_HPP 

#include <exception>
#include <functional>
#include <memory>
#include <iostream>
#include "RBT_iterator.hpp"
#include "RBT_node.hpp"
#include "reverse_iterator.hpp"
#include "ft_utils.hpp"
#include "pair.hpp"

namespace ft
{

template<class Key, class Pair, class KeyOfPair, class KeyCompare = std::less<Key> >
class RBT
{
		// #################### MEMBER TYPES ####################

	public:
		typedef Pair 											pair_type;
		typedef Key 											key_type;
		typedef KeyCompare 										key_compare;
		typedef KeyOfPair 										key_of_pair;

		typedef typename std::allocator<pair_type> 				pair_allocator;
		typedef typename std::allocator<RBTNode<pair_type> >    node_allocator;
		typedef typename pair_allocator::size_type 				size_type;
		typedef typename pair_allocator::difference_type 		difference_type;

		typedef pair_type& 										reference;
		typedef const pair_type& 								const_reference;
		typedef typename pair_allocator::pointer 				pointer;
		typedef typename pair_allocator::const_pointer 			const_pointer;

		typedef RBTNode<pair_type> 								node_type;
		typedef RBTNode<pair_type>* 							node_ptr;
		typedef const RBTNode<pair_type>* 						const_node_ptr;

		typedef RBT_iterator<pair_type, false> 					iterator; 
		typedef RBT_iterator<pair_type, true> 					const_iterator;

		typedef ft::reverse_iterator<iterator> 					reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> 			const_reverse_iterator;

		// #################### CONSTRUCTOR & DESTRUCTORS ####################

		RBT() : _root(NULL), _allocator(node_allocator()), _comp(key_compare()) {}; 

		RBT(const key_compare& comp) : _root(NULL), _allocator(node_allocator()), _comp(comp) {}; 

		RBT(const RBT<key_type, pair_type, key_of_pair, key_compare>& other) 
			: _allocator(node_allocator()), _comp(key_compare())
		{
			for (iterator it = other.begin(); it != other.end(); it++)
				this->insert(it);
		}
				
		~RBT()
		{
			destructorHelper(this->_root);
		}

		// #################### MEMBERS ####################
		
	private:
		node_ptr 		_root;
		node_allocator 	_allocator;
		key_compare 	_comp;

	public: 

		node_ptr getRoot()
		{
			return this->_root;
		}

		node_ptr searchTree(int key) {
			return searchTreeHelper(this->_root, key);
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

		iterator begin()
		{
			return (minimum(getRoot()));
		}

		iterator end()
		{
			return (maximum(getRoot())++);
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

		iterator insert(const pair_type& pair) {
			node_ptr node = _allocator.allocate(1);
			initializeNode(node, pair);
			node_ptr y = NULL;
			node_ptr x = this->_root;
			while (x != NULL) {
				y = x;
				if (nodeCompare(node, x))
					x = x->left;
				else
					x = x->right;
			}
			node->parent = y;
			if (y == NULL)
				_root = node;
			else if (nodeCompare(node, y))
				y->left = node;
			else
				y->right = node;
			//updateBalance the node if necessary
			updateBalance(node);
			return iterator(node);
		}

		node_ptr deleteNode(int data) {
			return deleteNodeHelper(this->_root, data);
		}

		void prettyPrint() {
			printHelperPerso(this->_root, "");
		}

/* 				LEFT ROTATE
                  |                        | 
                  x                        y
                 / \                      / \
                a   y        ==>         x   c
                   / \                  / \
                  b   c                a   b
*/
		void leftRotate(node_ptr x) {
			std::cout << "leftRotate node " << x->data << std::endl;
			node_ptr y = x->right;
			x->right = y->left;
			if (y->left != NULL)
				y->left->parent = x;
			y->parent = x->parent;
			if (x->parent == NULL)
				this->_root = y;
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
/* 				RIGHT ROTATE
                  |                        | 
                  x                        y
                 / \                      / \
                y   c        ==>         a   x
               / \                          / \
              a   b                        b   c
*/

		void rightRotate(node_ptr x) {
			std::cout << "rightRotate node " << x->data << std::endl;
			node_ptr y = x->left;
			x->left = y->right;
			if (y->right != NULL)
				y->right->parent = x;
			y->parent = x->parent;
			if (x->parent == NULL)
				this->_root = y;
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
/*
                  |                     |                   |
        BF=2      a               BF=2  a                   b
                   \                     \                 / \
        BF=-1       c     ==>     BF=1    b      ==>      a   c    BF=0 partout
                   /                       \                          /
        BF=0      b               BF=0      c
                       rightRotate              leftRotate
*/
					rightRotate(node->right);
					leftRotate(node);
				}
				else
/*
                  |                        | 
       BF=2       a                        b
                   \                      / \
       BF=1         b        ==>         a   c       BF=0 partout
                     \                                        /
       BF=0           c                    
                          leftRotate
*/
					leftRotate(node);
			}
			else if (node->bf < 0) {
				if (node->left->bf > 0) {
/*
                  |                           |                   |
        BF=-2     a               BF=-2       a                   b
                 /                           /                   / \
        BF=1    c         ==>     BF=-1     b          ==>      a   c    BF=0 partout
                 \                         /                                
        BF=0      b               BF=0    c        
                       leftRotate                  rightRotate
*/
					leftRotate(node->left);
					rightRotate(node);
				}
				else
/*
                  |                        | 
         BF=-2    c                        b
                 /                        / \
        BF=-1   b            ==>         a   c       BF=0 partout
               /                             
      BF=0    a                               
                         rightRotate
*/
					rightRotate(node);
			}
		}
	// #################### HELPERS ####################

	private:
		key_type& keyOfNode(node_ptr node)
		{
			return key_of_pair()(node->data);
		}

		const pair_type& pairOfNode(node_ptr node)
		{
			return node->pair;
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

		bool nodeCompare(node_ptr a, node_ptr b)
		{
			return (key_compare(keyOfNode(a), keyOfNode(b)));
		}

		node_ptr create_node(const pair_type& val)
		{
			node_ptr node = node_allocator::allocate(1);
			try {
				node_allocator::construct(node, node_type(val));
				node->pair = val;
			} catch (...) {
				node_allocator::deallocate(node, 1);
				throw ;
			}
			return node;
		}

		void erase_node(node_ptr node)
		{
			// No need to destroy node->pair, it is called in destroy(node)
			_allocator.destroy(node);
			_allocator.deallocate(node, 1);		
		}

		void initializeNode(node_ptr node, pair_type pair = pair_type())
		{
			node->value = pair;
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
					node->pair = temp->pair;
					node->right = deleteNodeHelper(node->right, temp->pair);
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
				std::cout << indent << node->pair << "(bf=" << node->bf << ")\n";
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


};
}



#endif 
