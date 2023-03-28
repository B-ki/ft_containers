/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:20:46 by rmorel            #+#    #+#             */
/*   Updated: 2023/03/29 01:21:09 by rmorel           ###   ########.fr       */
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

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define MAGENTA "\033[1;35m"
# define CYAN "\033[1;36m"
# define BLACK "\033[1;38m"
# define NORMAL "\033[0m"

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
			if (other._root)
				_root = copyNodeHelper(other._root);
			else
				_root = NULL;
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
			node_ptr node = createNode(pair);
			node_ptr y = NULL;
			node_ptr x = this->_root;
			while (x != NULL)
			{
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
			if (node->parent == NULL)
			{
				this->_root = node;
				return iterator(node);
			}
			if (node->parent->parent == NULL)
				return iterator(node);
			updateBalance(node);
			return iterator(node);
		}
		
		iterator insert(iterator pos, const pair_type& pair)
		{
			node_ptr nodePos = pos.base();
			node_ptr newNode = createNode(pair);
			node_ptr y = NULL;
			node_ptr x = this->_root;
			if (nodePos == NULL)
				_root = newNode;
			else if (isKeySupToNode(nodePos, _key_of_pair(pair)) &&
					isKeyInfToNode(nodePos->successor(), _key_of_pair(pair)))
				 x = nodePos;
			while (x != NULL)
			{
				y = x;
				if (nodeCompare(newNode, x))
					x = x->left;
				else
					x = x->right;
			}
			newNode->parent = y;
			if (y == NULL)
				_root = newNode;
			else if (nodeCompare(newNode, y))
				y->left = newNode;
			else
				y->right = newNode;
			//updateBalance the node if necessary
			updateBalance(newNode);
			return iterator(newNode);
		}

		iterator deleteNode(const key_type& key)
		{
			return iterator(deleteNodeHelper(this->_root, key));
		}

		void clearTree()
		{
			destructorHelper(this->_root);
		}

		// ########## PRINTERS ##########

		void prettyPrint() const
		{
			std::cout << "--------------------------------------------\n";
			printHelperPerso(this->_root, "");
			std::cout << "--------------------------------------------\n";
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
			node->color = red;
			while (node->parent->color == red)
			{
				if (node->parent->isRight()) 
				{
					node_ptr uncle = node->parent->parent->left;
					if (uncle != NULL && uncle->color == red)
					{
						uncle->color = black;
						node->parent->color = black;
						node->parent->parent->color = red;
						node = node->parent->parent;
					}
					else 
					{
						if (node->isLeft())
						{
							node = node->parent;
							rightRotate(node);
						}
						node->parent->color = black;
						node->parent->parent->color = red;
						leftRotate(node->parent->parent);
					}
				}
				else 
				{
					node_ptr uncle = node->parent->parent->right;
					if (uncle != NULL && uncle->color == red)
					{
						uncle->color = black;
						node->parent->color = black;
						node->parent->parent->color = red;
						node = node->parent->parent;
					}
					else 
					{
						if (node->isRight())
						{
							node = node->parent;
							leftRotate(node);
						}
						node->parent->color = black;
						node->parent->parent->color = red;
						rightRotate(node->parent->parent);
					}	
				}
				if (node->parent == NULL)
					break;
			}
			getRoot()->color = black;
		}

		void rebalance(node_ptr node)
		{
			if (node->bf > 0)
			{
				if (node->right->bf < 0)
				{
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
			else if (node->bf < 0)
			{
				if (node->left->bf > 0)
				{
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

		bool isKeySupToNode(const node_ptr node, const key_type& key) const
		{
			return _comp(keyOfNode(node), key);
		}

		bool isKeyInfToNode(const node_ptr node, const key_type& key) const
		{
			return _comp(key, keyOfNode(node));
		}

		bool nodeCompare(node_ptr a, node_ptr b) const
		{
			return (_comp(keyOfNode(a), keyOfNode(b)));
		}

		node_ptr createNode(const pair_type& pair)
		{
			node_ptr node = _node_allocator.allocate(1);
			try 
			{
				_pair_allocator.construct(&node->pair, pair);
				initializeNode(node, pair);
			} 
			catch (...) 
			{
				_node_allocator.deallocate(node, 1);
				throw ;
			}
			return node;
		}

		void eraseNode(node_ptr node)
		{
			_node_allocator.destroy(node);
			_node_allocator.deallocate(node, 1);		
		}

		void initializeNode(node_ptr node, pair_type pair)
		{
			(void)pair;
			node->parent = NULL;
			node->left = NULL;
			node->right = NULL;
			node->color = red;
			node->bf = 0;
		}

		node_ptr searchTreeHelper(node_ptr node, const key_type& key) const
		{
			if (node == NULL || isSameKey(node, key))
				return node;
			if (!isKeySupToNode(node, key))
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
			else if (isKeyInfToNode(node, key))
				node->left = deleteNodeHelper(node->left, key);
			else if (isKeySupToNode(node, key))
				node->right = deleteNodeHelper(node->right, key);
			else
			{
				//The key has been found, now we have to delete it
				//Case 1 : The node to delete is a leaf Node
				if (node->left == NULL && node->right == NULL)
				{
					eraseNode(node);
					node = NULL;
				}
				//Case 2 : The node has only one child
				else if (node->left == NULL)
				{
					node_ptr temp = node;
					node = node->left;
					eraseNode(temp);
				}
				else if (node->right == NULL)
				{
					node_ptr temp = node;
					node = node->right;
					eraseNode(temp);
				}
				//Case 3 : The node has 2 children
				else
				{
					node_ptr temp = node->right->minimum();
					node->pair = temp->pair;
					node->right = deleteNodeHelper(node->right, keyOfNode(temp));
				}
			}
			// Update balance logic
			updateBalance(node);
			return node;
		}

		void printHelperPerso(node_ptr node, std::string indent) const
		{
			if (node != NULL)
			{
				indent += "            ";
				printHelperPerso(node->right, indent);
				if (node->color == red)
					std::cout << RED;
				else
					std::cout << BLUE;
				std::cout << indent << "(" << node->pair.first;
				std::cout << ", " << node->pair.second << ")\n" << NORMAL;
				printHelperPerso(node->left, indent);
			}	
		}

		void destructorHelper(node_ptr node)
		{
			if (node != NULL)
			{
				destructorHelper(node->left);
				destructorHelper(node->right);
				eraseNode(node);	
			}	
		}

		node_ptr copyNodeHelper(node_ptr nodeToCopy)
		{
			node_ptr newNode = createNode(nodeToCopy->pair);
			newNode->color = nodeToCopy->color;
			if (nodeToCopy->right)
			{
				newNode->right = copyNodeHelper(nodeToCopy->right);
				newNode->right->parent = newNode;
			}
			if (nodeToCopy->left)
			{
				newNode->left = copyNodeHelper(nodeToCopy->left);
				newNode->left->parent = newNode;
			}
			return newNode;
		}
};
}



#endif 
