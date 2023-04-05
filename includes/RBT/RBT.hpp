/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:20:46 by rmorel            #+#    #+#             */
/*   Updated: 2023/04/05 12:44:57 by rmorel           ###   ########.fr       */
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

		RBT() : _root(NULL), _pair_allocator(pair_allocator()), _node_allocator(node_allocator()), _comp(key_compare())
		{
			_sentinel.parent = NULL;
			_sentinel.left = reinterpret_cast<node_ptr>(&_root);
			_sentinel.right = reinterpret_cast<node_ptr>(&_root);
			_NULL_NODE = createNullNode();
		}; 

		RBT(const key_compare& comp) : _root(NULL), _pair_allocator(pair_allocator()), _node_allocator(node_allocator()), _comp(comp) 
		{
			_sentinel.parent = NULL;
			_sentinel.left = reinterpret_cast<node_ptr>(&_root);
			_sentinel.right = reinterpret_cast<node_ptr>(&_root);
			_NULL_NODE = createNullNode();
		}; 

		RBT(const RBT<key_type, pair_type, key_of_pair, key_compare>& other) 
			: _pair_allocator(pair_allocator()),  _node_allocator(node_allocator()), _comp(key_compare())
		{
			_sentinel.parent = NULL;
			_sentinel.left = reinterpret_cast<node_ptr>(&_root);
			_sentinel.right = reinterpret_cast<node_ptr>(&_root);
			_NULL_NODE = createNullNode();
			if (other._root)
				_root = copyNodeHelper(other._root, other);
			else
				_root = NULL;
		}

		~RBT()
		{
			destructorHelper(this->_root);
			_node_allocator.deallocate(_NULL_NODE, 1);		
		}

		// #################### MEMBERS ####################

	private:
		node_type		_sentinel;
		node_ptr 		_root;
		pair_allocator  _pair_allocator;
		node_allocator 	_node_allocator;
		key_compare 	_comp;
		key_of_pair 	_key_of_pair;
		node_ptr 		_NULL_NODE;

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
			iterator ret(minimum(getRoot()));
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
			if (x->right != _NULL_NODE)
				return minimum(x->right);
			node_ptr y = x->parent;
			while (y != _NULL_NODE && x->isRight()) {
				x = y;
				y = y->parent;
			}
			return y;
		}

		// The predecessor is the node whose key is just before
		node_ptr predecessor(node_ptr x) const
		{
			if (x->left != _NULL_NODE)
				return maximum(x->left);
			node_ptr y = x->parent;
			while (y != _NULL_NODE && x->isLeft()) {
				x = y;
				y = y->parent;
			}
			return y;
		}

		node_ptr searchTree(key_type key) const
		{
			node_ptr ret;
			ret = searchTreeHelper(this->_root, key);
			if (ret == _NULL_NODE)
				return NULL;
			return ret;
		}

		pair_type& getPair(key_type key) const
		{
			node_ptr temp = searchTree(key);

			if (temp != NULL)
				return (temp->pair);
			else
				throw (std::out_of_range("Key doesn't exists"));
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
			while (x != _NULL_NODE && x != NULL)
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
			if (node->parent == NULL)
			{
				_root = node;
				_root->color = black;
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
			while (x != _NULL_NODE && x != NULL)
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
			if (y->right != _NULL_NODE)
				y->right->parent = x;
			y->parent = x->parent;
			if (x->parent == _NULL_NODE)
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
			getRoot()->parent = NULL;
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

		node_ptr createNullNode()
		{
			node_ptr node = _node_allocator.allocate(1);
			node->parent = NULL;
			node->right = NULL;
			node->left = NULL;
			node->color = black;
			return node;
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

		node_ptr maximum(node_ptr startSearch) const
		{
			node_ptr node = startSearch;
			if (node == _NULL_NODE)
				return _NULL_NODE;
			while (node->right != _NULL_NODE)
				node = node->right;
			return node;
		}

		node_ptr minimum(node_ptr startSearch) const
		{
			node_ptr node = startSearch;
			if (node == _NULL_NODE)
				return _NULL_NODE;
			while (node->left != _NULL_NODE)
				node = node->left;
			return node;
		}

		void eraseNode(node_ptr node)
		{
			if (node == _NULL_NODE)
				return;
			_node_allocator.destroy(node);
			_node_allocator.deallocate(node, 1);		
			node = _NULL_NODE;
		}

		void initializeNode(node_ptr node, pair_type pair)
		{
			(void)pair;
			node->parent = NULL;
			node->left = _NULL_NODE;
			node->right = _NULL_NODE;
			node->color = red;
			node->bf = 0;
		}

		node_ptr searchTreeHelper(node_ptr startSearch, const key_type& key) const
		{
			node_ptr node = startSearch;
			if (node == _NULL_NODE)
				return node;
			while (node != _NULL_NODE && !isSameKey(node, key))
			{
				if (isKeySupToNode(node, key))
					node = node->right;
				else
					node = node->left;
			}
			return node;
		}

		// v is taking u's place, but v keeps its child
		void rbtTransplant(node_ptr u, node_ptr v)
		{
			if (u->parent == NULL)
				this->_root = v;
			else if (u->isLeft())
				u->parent->left = v;
			else
				u->parent->right = v;
			v->parent = u->parent;
		}

		// a is replaced by b, b->child = a->child
		void replaceNode(node_ptr a, node_ptr b)
		{
			if (a->parent == NULL)
				this->_root = b;
			else if (a->isLeft())
				a->parent->left = b;
			else
				a->parent->right = b;
			b->parent = a->parent;
			b->right = a->right;
			b->left = a->left;
			if (b->right != _NULL_NODE)
				b->right->parent = b;
			if (b->left != _NULL_NODE)
				b->left->parent = b;
		}

		node_ptr deleteNodeHelper(node_ptr startSearch, const key_type& key)
		{
			node_ptr node = searchTreeHelper(startSearch, key);
			if (node == _NULL_NODE)
				return NULL;
			node_ptr y = node;
			node_ptr x;
			e_color originalColor = node->color;
			if (node->left == _NULL_NODE) // No children or only right child
			{
				x = node->right;
				rbtTransplant(node, node->right);
			}
			else if (node->right == _NULL_NODE) // Only left child
			{
				x = node->left;
				rbtTransplant(node, node->left);
			}
			else
			{
				y = minimum(node->right);
				x = y->right;
				originalColor = y->color;
				if (y->parent == node)
					x->parent = y;
				else 
				{
					rbtTransplant(y, x);
					y->right = node->right;
					y->right->parent = y;
				}
				rbtTransplant(node, y);
				y->left = node->left;
				y->left->parent = y;
				y->color = node->color;
			}
			eraseNode(node);
			if (x != NULL && originalColor == black)
				fixDelete(x);
			return node;
		}

		void fixDelete(node_ptr node)
		{
			node_ptr sister = NULL;
			while (node != _root && (node == NULL || node->color != red))
			{
				if (node->isLeft())
				{
					sister = node->parent->right;
					// Sister is never NULL if node is not root
					if (sister->color == red)
					{
						node->parent->color = red;
						sister->color = black;
						leftRotate(node->parent);
						sister = node->parent->right;
					}
					if ((sister->left == NULL || sister->left->color == black)
							&& (sister->right == NULL || sister->right->color == black))
					{
						sister->color = red;
						node = node->parent;
					}
					else 
					{
						if (sister->right == NULL || sister->right->color == black)
						{
							sister->left->color = black;
							sister->color = red;
							rightRotate(sister);
							sister = node->parent->right;
						}
						sister->color = node->parent->color;
						node->parent->color = black;
						sister->right->color = black;
						leftRotate(node->parent);
						node = this->_root; // Break the loop
					}
				}
				else 
				{
					sister = node->parent->left;
					// Sister is never NULL if node is not root
					if (sister->color == red)
					{
						node->parent->color = red;
						sister->color = black;
						rightRotate(node->parent);
						sister = node->parent->left;
					}
					if ((sister->left == NULL || sister->left->color == black)
							&& (sister->right == NULL || sister->right->color == black))
					{
						sister->color = red;
						node = node->parent;
					}
					else 
					{
						if (sister->left == NULL || sister->left->color == black)
						{
							sister->right->color = black;
							sister->color = red;
							leftRotate(sister);
							sister = node->parent->left;
						}
						sister->color = node->parent->color;
						node->parent->color = black;
						sister->left->color = black;
						leftRotate(node->parent);
						node = this->_root; // Break the loop
					}
				}
			}
			node->color = black;
		}

		void printHelperPerso(node_ptr node, std::string indent) const
		{
			if (node != _NULL_NODE)
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

		void printNode(node_ptr node) const
		{
			if (node == NULL)
				return;
			if (node->color == red)
				std::cout << RED;
			else
				std::cout << BLUE;
			std::cout << "(" << node->pair.first;
			std::cout << ", " << node->pair.second << ")\n" << NORMAL;
		}

		void destructorHelper(node_ptr node)
		{
			if (node != _NULL_NODE)
			{
				destructorHelper(node->left);
				destructorHelper(node->right);
				eraseNode(node);	
			}	
		}

		node_ptr copyNodeHelper(node_ptr nodeToCopy,
				const RBT<key_type, pair_type, key_of_pair, key_compare>& other)
		{
			node_ptr newNode = createNode(nodeToCopy->pair);
			newNode->color = nodeToCopy->color;
			if (nodeToCopy->right != other._NULL_NODE)
			{
				newNode->right = copyNodeHelper(nodeToCopy->right, other);
				newNode->right->parent = newNode;
			}
			if (nodeToCopy->left != other._NULL_NODE)
			{
				newNode->left = copyNodeHelper(nodeToCopy->left, other);
				newNode->left->parent = newNode;
			}
			return newNode;
		}
};
}



#endif 
