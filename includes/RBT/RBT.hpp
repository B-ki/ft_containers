/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:20:46 by rmorel            #+#    #+#             */
/*   Updated: 2023/03/27 22:23:08 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_HPP
#define RBT_HPP 

#include <exception>
#include <functional>
#include <memory>
#include <iostream>
#include <stdexcept>
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

		RBT() : _root(NULL), _pair_allocator(pair_allocator()), _node_allocator(node_allocator()), _comp(key_compare()) {}; 

		RBT(const key_compare& comp) : _root(NULL), _pair_allocator(pair_allocator()), _node_allocator(node_allocator()), _comp(comp) {}; 

		RBT(const RBT<key_type, pair_type, key_of_pair, key_compare>& other) 
			: _pair_allocator(pair_allocator()),  _node_allocator(node_allocator()), _comp(key_compare())
		{
			for (iterator it = other.begin(); it != other.end(); it++)
				this->insert(*it);
		}

		~RBT()
		{
			destructorHelper(this->_root);
		}

		// #################### MEMBERS ####################

	private:
		node_ptr 		_root;
		pair_allocator  _pair_allocator;
		node_allocator 	_node_allocator;
		key_compare 	_comp;
		key_of_pair 	_key_of_pair;

	public: 

		// ########## CAPACITY ##########

		bool empty() const
		{
			if (this->_root)
				return true;
			return false;
		}

		size_type size() const 
		{
			return sizeHelper(this->_root) - 1;
		}

		size_type sizeHelper(node_ptr node) const
		{
			if (!node)
				return 1;
			return (sizeHelper(node->left) + sizeHelper(node->right));
		}

		// ########## FINDERS ##########

		iterator begin() const
		{
			iterator ret(getRoot()->minimum());
			return (ret);
		}

		iterator end() const
		{
			iterator ret(NULL);
			return (ret);
		}

		// The successor is the node whose key is next
		node_ptr successor(node_ptr x) const
		{
			if (x->right != NULL)
				return x->right->minimum();
			node_ptr y = x->parent;
			while (y != NULL && x->isRight()) {
				x = y;
				y = y->parent;
			}
			return y;
		}

		// The predecessor is the node whose key is just before
		node_ptr predecessor(node_ptr x) const
		{
			if (x->left != NULL)
				x->left->maximum();
			node_ptr y = x->parent;
			while (y != NULL && x->isLeft()) {
				x = y;
				y = y->parent;
			}
			return y;
		}

		node_ptr searchTree(key_type key) const
		{
			return searchTreeHelper(this->_root, key);
		}

		pair_type& getPair(key_type key) const
		{
			node_ptr temp = searchTree(key);

			if (temp)
				return (temp->pair);
			else
				throw (std::out_of_range("Key doesn't exists"));
		}

		node_ptr minimum(node_ptr node) const
		{
			while (node->left) {
				minimum(node->left);
			}
			return node;
		}

		node_ptr maximum(node_ptr node) const
		{
			while (node->right) {
				maximum(node->right);
			}
			return node;
		}

		node_ptr getRoot() const
		{
			return this->_root;
		}

		// ########## MODIFIERS ##########

		iterator insert(const pair_type& pair)
		{
			node_ptr node = _node_allocator.allocate(1);
			_pair_allocator.construct(&node->pair, pair);	
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

		node_ptr deleteNode(int data)
		{
			return deleteNodeHelper(this->_root, data);
		}

		// ########## PRINTERS ##########

		void prettyPrint() const
		{
			printHelperPerso(this->_root, "");
		}

		// ########## BALANCERS ##########

/* 				LEFT ROTATE
				|                        | 
				x                        y
				/ \                      / \
				a   y        ==>         x   c
				/ \                  / \
				b   c                a   b
*/
		void leftRotate(node_ptr x)
		{
			std::cout << "rightRotate node (" << x->pair.first;
			std::cout << ", " << x->pair.second << ")" << std::endl;
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
		void rightRotate(node_ptr x)
		{
			std::cout << "rightRotate node (" << x->pair.first;
			std::cout << ", " << x->pair.second << ")" << std::endl;
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

		void updateBalance(node_ptr node)
		{
			if (!node)
				return;
			// The first ancestor that has a bf < -1 || > 1 is rebalanced. There should be only one considering the fact
			// that we do this everytime we insert something.
			if (node->bf < -1 || node->bf > 1) {
				rebalance(node);
				return ;
			}
			if (node->parent != NULL) {
				if (node == node->parent->left)
					node->parent->bf--;
				if (node == node->parent->right)
					node->parent->bf++;
				if (node->parent->bf != 0)
					updateBalance(node->parent);
			}
		}

		void rebalance(node_ptr node)
		{
			if (node->bf > 0) {
				if (node->right->bf < 0) {
/*           |                     |                   |
   BF=2      a               BF=2  a                   b
              \                     \                 / \
   BF=-1       c     ==>     BF=1    b      ==>      a   c    BF=0 partout
              /                       \                          /
   BF=0      b               BF=0      c
   rightRotate              leftRotate */
					rightRotate(node->right);
					leftRotate(node);
				}
				else
/*            |                        | 
   BF=2       a                        b
               \                      / \
   BF=1         b        ==>         a   c       BF=0 partout
                 \                                        /
   BF=0           c                    
   leftRotate */
					leftRotate(node);
			}
			else if (node->bf < 0) {
				if (node->left->bf > 0) {
/*           |                           |                   |
   BF=-2     a               BF=-2       a                   b
            /                           /                   / \
   BF=1    c         ==>     BF=-1     b          ==>      a   c    BF=0 partout
            \                         /                                
   BF=0      b               BF=0    c        
   leftRotate                  rightRotate */
					leftRotate(node->left);
					rightRotate(node);
				}
				else
/*          |                        | 
   BF=-2    c                        b
           /                        / \
   BF=-1  b            ==>         a   c       BF=0 partout
   		   \                             
   BF=0     a                               
   rightRotate */
					rightRotate(node);
			}
		}

		// #################### HELPERS ####################

	private:
		key_type keyOfNode(node_ptr node) const
		{
			return key_of_pair()(node->pair);
		}

		const pair_type& pairOfNode(node_ptr node) const
		{
			return node->pair;
		}

		bool isSameKey(const node_ptr node, const key_type& key) const
		{
			if (!_comp(keyOfNode(node), key) && 
				!_comp(key, keyOfNode(node)))
				return true;
			return false;
		}

		bool isKeyInf(const node_ptr node, const key_type& key) const
		{
			return _comp(keyOfNode(node), key);
		}

		bool isKeySup(const node_ptr node, const key_type& key) const
		{
			return _comp(key, keyOfNode(node));
		}

		bool nodeCompare(node_ptr a, node_ptr b) const
		{
			return (_comp(keyOfNode(a), keyOfNode(b)));
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
			_node_allocator.destroy(node);
			_node_allocator.deallocate(node, 1);		
		}

		void initializeNode(node_ptr node, pair_type pair)
		{
			(void)pair;
			node->parent = NULL;
			node->left = NULL;
			node->right = NULL;
			node->color = black;
			node->bf = 0;
		}

		node_ptr searchTreeHelper(node_ptr node, const key_type& key) const
		{
			if (node == NULL || isSameKey(node, key))
				return node;
			if (!isKeyInf(node, key))
			{
				if (node->left)
					return searchTreeHelper(node->left, key);
				return NULL;
			}
			if (node->right)
				return searchTreeHelper(node->right, key);
			return NULL;
		}

		node_ptr deleteNodeHelper(node_ptr node, const key_type& key)
		{
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
					node_ptr temp = node->right->minimum();
					node->pair = temp->pair;
					node->right = deleteNodeHelper(node->right, temp->pair);
				}
			}
			// Update balance logic
			updateBalance(node);
			return node;
		}

		void printHelperPerso(node_ptr node, std::string indent) const
		{
			if (node != NULL) {
				indent += "            ";
				printHelperPerso(node->right, indent);
				std::cout << indent << "(" << node->pair.first;
				std::cout << ", " << node->pair.second << ") (bf=" << node->bf << ")\n";
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
