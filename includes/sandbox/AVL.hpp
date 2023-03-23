/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVL.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:49:51 by rmorel            #+#    #+#             */
/*   Updated: 2023/03/22 10:37:37 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AVL_HPP
#define AVL_HPP 

#include <iostream>
#include "binary_search_tree.hpp"

typedef Node* NodePtr;

class AVL {
	private:
		NodePtr root;

		void initializeNode(NodePtr node, int key) {
			node->data = key;
			node->parent = NULL;
			node->left = NULL;
			node->right = NULL;
			node->bf = 0;
		}

		// Affiche les donnees depuis la node en question
		void preOrderHelper(NodePtr node) {
			if (node != NULL) {
				std::cout << node->data << " ";
				preOrderHelper(node->left);
				preOrderHelper(node->right);
			}
		}

		// Affiche les donnes depuis la node la plus a gauche, jusqu'a la node,
		// puis le subtree a droite
		void inOrderHelper(NodePtr node) {
			if (node != NULL) {
				inOrderHelper(node->left);
				std::cout << node->data << " ";
				inOrderHelper(node->right);
			}
		}

		// Affiche les donnes lignes par lignes
		void postOrderHelper(NodePtr node) {
			if (node != NULL) {
				postOrderHelper(node->left);
				postOrderHelper(node->right);
				std::cout << node->data << " ";
			}
		}

		NodePtr searchTreeHelper(NodePtr node, int key) {
			if (node == NULL || key == node->data) {
				return node;
			}
			if (key < node->data) {
				return searchTreeHelper(node->left, key);
			}
			return searchTreeHelper(node->right, key);
		}

		NodePtr deleteNodeHelper(NodePtr node, int key) {
			if (node == NULL) 
				return node;
			else if (key < node->data)
				node->left = deleteNodeHelper(node->left, key);
			else if (key > node->data)
				node->right = deleteNodeHelper(node->right, key);
			else {
				//The key has been found, now we have to delete it

				//Case 1 : The node to delete is a leaf Node
				if (node->left == NULL && node->right == NULL) {
					delete node;
					node = NULL;
				}

				//Case 2 : The node has only one child
				else if (node->left == NULL) {
					NodePtr temp = node;
					node = node->left;
					delete temp;
				}

				else if (node->right == NULL) {
					NodePtr temp = node;
					node = node->right;
					delete temp;
				}

				//Case 3 : The node has 2 children
				else {
					NodePtr temp = minimum(node->right);
					node->data = temp->data;
					node->right = deleteNodeHelper(node->right, temp->data);
				}
			}
			// Update balance logic
			updateBalance(node);
			return node;
		}


		void printHelper(NodePtr root, std::string indent, bool last) {
			// print the tree structure on the screen
			if (root != NULL) {
				std::cout << indent;
				if (last) {
					std::cout << "R----";
					indent += "     ";
				} else {
					std::cout << "L----";
					indent += "|    ";
				}
				std::cout << root->data << "( BF = "<<root->bf<<")" << std::endl;
				printHelper(root->left, indent, false);
				printHelper(root->right, indent, true);
			}
		}

		void printHelperPerso(NodePtr node, std::string indent) {
			if (node != NULL) {
				indent += "            ";
				printHelperPerso(node->right, indent);
				std::cout << indent << node->data << "(bf=" << node->bf << ")\n";
				printHelperPerso(node->left, indent);
			}	
		}

		void destructorHelper(NodePtr node) {
			if (node != NULL) {
				destructorHelper(node->left);
				destructorHelper(node->right);
				delete node;
			}	
		}

	public: 
		AVL() {
			root = NULL;
		}

		~AVL() {
			destructorHelper(this->root);
		}

		void preOrder() {
			preOrderHelper(this->root);
		}

		void inOrder() {
			inOrderHelper(this->root);
		}

		void postOrder() {
			postOrderHelper(this->root);
		}

		NodePtr searchTree(int key) {
			return searchTreeHelper(this->root, key);
		}

		NodePtr minimum(NodePtr node) {
			while (node->left) {
				minimum(node->left);
			}
			return node;
		}

		NodePtr maximum(NodePtr node) {
			while (node->right) {
				maximum(node->right);
			}
			return node;
		}

		NodePtr successor(NodePtr x) {
			if (x->right != NULL)
				return minimum(x->right);
			NodePtr y = x->parent;
			while (y != NULL && x == y->right) {
				x = y;
				y = y->parent;
			}
			return y;
		}

		NodePtr predecessor(NodePtr x) {
			if (x->left != NULL)
				maximum(x->left);
			NodePtr y = x->parent;
			while (y != NULL && x == y->left) {
				x = y;
				y = y->parent;
			}
			return y;
		}

		void insert(int key) {
			NodePtr node = new Node;
			node->parent = NULL;
			node->left = NULL;
			node->right = NULL;
			node->data = key;
			node->bf = 0;
			NodePtr y = NULL;
			NodePtr x = this->root;
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

		NodePtr getRoot() { return this->root; }

		NodePtr deleteNode(int data) {
			return deleteNodeHelper(this->root, data);
		}

		void prettyPrint() {
			printHelperPerso(this->root, "");
		}

		void leftRotate(NodePtr x) {
			std::cout << "leftRotate node " << x->data << std::endl;
			NodePtr y = x->right;
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


		void rightRotate(NodePtr x) {
			std::cout << "rightRotate node " << x->data << std::endl;
			NodePtr y = x->left;
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

	void updateBalance(NodePtr node) {
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

		void rebalance(NodePtr node) {
			if (node->bf > 0) {
				if (node->right->bf < 0) {
					rightRotate(node->right);
					leftRotate(node);
				}
				else
					leftRotate(node);
			}
			else if (node->bf < 0) {
				if (node->left->bf > 0) {
					leftRotate(node->left);
					rightRotate(node);
				}
				else
					rightRotate(node);
			}
		}

		void createSampleTree1() {
			NodePtr node50 = new Node;
			initializeNode(node50, 50);
			NodePtr node30 = new Node;
			initializeNode(node30, 30);
			NodePtr node70 = new Node;
			initializeNode(node70, 70);

			node30->parent = node50;
			node70->parent = node50;
			node50->left = node30;
			node50->right = node70;

			NodePtr node23 = new Node;
			initializeNode(node23, 23);
			NodePtr node35 = new Node;
			initializeNode(node35, 35);

			node23->parent = node30;
			node35->parent = node30;
			node30->left = node23;
			node30->right = node35;

			NodePtr node11 = new Node;
			initializeNode(node11, 11);
			NodePtr node25 = new Node;
			initializeNode(node25, 25);

			node11->parent = node23;
			node25->parent = node23;
			node23->left = node11;
			node23->right = node25;

			NodePtr node31 = new Node;
			initializeNode(node31, 31);
			NodePtr node42 = new Node;
			initializeNode(node42, 42);

			node31->parent = node35;
			node42->parent = node35;
			node35->left = node31;
			node35->right = node42;

			NodePtr node80 = new Node;
			initializeNode(node80, 80);

			node80->parent = node70;
			node70->right = node80;

			NodePtr node73 = new Node;
			initializeNode(node73, 73);
			NodePtr node85 = new Node;
			initializeNode(node85, 85);

			node73->parent = node80;
			node85->parent = node80;
			node80->left = node73;
			node80->right = node85;

			this->root = node50;
		}

};

#endif 
