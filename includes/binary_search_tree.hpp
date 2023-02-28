/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_search_tree.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:49:51 by rmorel            #+#    #+#             */
/*   Updated: 2023/02/28 19:07:21 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP 

#include <iostream>

struct Node {
	int data;
	Node *parent;
	Node *left;
	Node *right;
};

typedef Node* NodePtr;

class BST {
	private:
		NodePtr root;

		void initializeNode(NodePtr node, int key) {
			node->data = key;
			node->parent = NULL;
			node->left = NULL;
			node->right = NULL;
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
			return node;
		}

		void printHelper(NodePtr root, std::string indent, bool last) {
			// print the tree structure on the screen
			if (root != NULL) {
					if (last) {
						std::cout<<"└────";
						indent += "     ";
					} else {
						std::cout<<"├────";
						indent += "|    ";
					}
					std::cout << indent;
					std::cout << root->data << std::endl;
				printHelper(root->right, indent, true);
				printHelper(root->left, indent, false);
			}
		}

		void printHelperPerso(NodePtr node, std::string indent) {
			if (node != NULL) {
				std::cout << indent << node->data << std::endl;
				indent += "      ";
				printHelperPerso(node->right, indent);
				printHelperPerso(node->left, indent);
			}	
		}

	public: 
		BST() {
			root = NULL;
		}

		~BST() {
			destructorHelper(this->root);
		}

		void destructorHelper(NodePtr node) {
			if (node != NULL) {
				destructorHelper(node->left);
				destructorHelper(node->right);
				delete node;
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
		}

		NodePtr getRoot() { return this->root; }

		NodePtr deleteNode(int data) {
			return deleteNodeHelper(this->root, data);
		}

		void prettyPrint() {
			printHelperPerso(this->root, "");
			//printHelper(this->root, "", true);
		}
};

#endif 
