/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT_test.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:44:12 by rmorel            #+#    #+#             */
/*   Updated: 2023/03/30 17:21:16 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <climits>
#include <linux/limits.h>
#include <vector>
#include "binary_heap.hpp"
#include "AVL.hpp"
#include "binary_search_tree.hpp"
#include "pair.hpp"
#include "map.hpp"
#include <map>

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
		NS::map<int, std::string> mapOfString;
		NS::pair<int, std::string> pair1 = NS::make_pair(0, "ab");
		NS::pair<int, std::string> pair2 = NS::make_pair(1, "cd");
		NS::pair<int, std::string> pair3 = NS::make_pair(2, "ef");
		NS::pair<int, std::string> pair4 = NS::make_pair(3, "gh");
		NS::pair<int, std::string> pair5 = NS::make_pair(4, "ij");
		NS::pair<int, std::string> pair6 = NS::make_pair(5, "kl");
		NS::pair<int, std::string> pair7 = NS::make_pair(6, "mn");
		NS::pair<int, std::string> pair8 = NS::make_pair(7, "op");
		mapOfString.insert(pair1);
		mapOfString.printRBT();
		mapOfString.insert(pair2);
		mapOfString.printRBT();
		mapOfString.insert(pair3);
		mapOfString.printRBT();
		mapOfString.insert(pair4);
		mapOfString.printRBT();
		mapOfString.insert(pair5);
		mapOfString.printRBT();
		mapOfString.insert(pair6);
		mapOfString.printRBT();
		mapOfString.insert(pair7);
		mapOfString.printRBT();
		std::cout << (mapOfString.insert(pair8)).second << std::endl;
		mapOfString.printRBT();
		std::cout << mapOfString.size() << std::endl;
		std::cout << mapOfString.max_size() << std::endl;
		std::cout << "Value at key=5 : \n" << mapOfString.at(5) << std::endl;
		try {
		std::cout << "Value at key=8 : " << mapOfString.at(8) << std::endl;
		} catch (...) {
			std::cout << "Key 8 doesn't exists\n";
		}
		std::cout << "Value at key=4 : " << mapOfString[4] << std::endl;
		std::cout << "Value at key=9 : " << mapOfString[9] << std::endl;
		std::cout << "Value at key=9 : " << mapOfString[999] << std::endl;
		mapOfString.printRBT();
		NS::map<int, std::string> mapCopy(mapOfString);
		mapCopy.printRBT();
		mapCopy.find(5);
		mapCopy.erase(5);
		mapCopy.printRBT();
		//mapCopy.erase(10);
	}
	return;
}

