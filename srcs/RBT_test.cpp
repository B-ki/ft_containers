/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT_test.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:44:12 by rmorel            #+#    #+#             */
/*   Updated: 2023/03/21 18:42:24 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <climits>
#include <linux/limits.h>
#include <vector>
#include "binary_heap.hpp"
#include "AVL.hpp"
#include "binary_search_tree.hpp"
#include "map.hpp"

#ifndef NS
# define NS std
#endif

void RBT_test(void)
{
	{
		std::cout << "\n########## BINARY HEAP ##########\n\n";
		BinaryHeap tree;
		tree.insert(1);
		tree.insert(10);
		tree.insert(9);
		tree.insert(2);
		tree.insert(8);
		tree.insert(3);
		tree.insert(7);
		tree.insert(4);
		tree.insert(6);
		tree.insert(5);
		tree.printHeap();
	}
	{
		std::cout << "\n########## BST ##########\n\n";
		BST bst;
		bst.createSampleTree1();
		bst.prettyPrint();
	}
	{
		std::cout << "\n########## AVL ##########\n\n";
		AVL avl;
		avl.insert(50);
		avl.prettyPrint();
		std::cout << "\n -------------------- \n\n";
		avl.insert(40);
		avl.prettyPrint();
		std::cout << "\n -------------------- \n\n";
		avl.insert(30);
		avl.prettyPrint();
		std::cout << "\n -------------------- \n\n";
		avl.insert(20);
		avl.prettyPrint();
		std::cout << "\n -------------------- \n\n";
		avl.insert(60);
		avl.prettyPrint();
		std::cout << "\n -------------------- \n\n";
		avl.insert(55);
		avl.prettyPrint();
		std::cout << "\n -------------------- \n\n";
		avl.insert(45);
		avl.prettyPrint();
		std::cout << "\n -------------------- \n\n";
		avl.insert(35);
		avl.prettyPrint();
		std::cout << "\n -------------------- \n\n";
		avl.insert(25);
		avl.prettyPrint();
		std::cout << "\n -------------------- \n\n";
		avl.insert(52);
		avl.prettyPrint();
		std::cout << "\n -------------------- \n\n";
		avl.insert(100);
		avl.prettyPrint();
		std::cout << "\n -------------------- \n\n";
	}
	{
		std::cout << "\n########## AVL2 ##########\n\n";
		AVL avl;
		avl.insert(50);
		avl.insert(30);
		avl.insert(70);
		avl.insert(65);
		avl.prettyPrint();
		std::cout << "\n -------------------- \n\n";
		avl.insert(68);
		avl.prettyPrint();
		std::cout << "\n -------------------- \n\n";
	}
	{
		std::cout << "\n########## RBT ##########\n\n";
		ft::map<int, std::string> mapOfString;

		mapOfString.insert(
		
	}
	return;
}
