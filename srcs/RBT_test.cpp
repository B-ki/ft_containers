/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT_test.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:44:12 by rmorel            #+#    #+#             */
/*   Updated: 2023/04/23 14:25:28 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <climits>
#include <linux/limits.h>
#include <vector>
#include "binary_heap.hpp"
#include <list>
#include "AVL.hpp"
#include "binary_search_tree.hpp"
#include "pair.hpp"
#include "map.hpp"
#include <map>
#include <cstdlib>
#include <time.h>
#include "tests.hpp"

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
		std::cout << "\n########## RBT BALANCE ##########\n\n";
		ft::RBT<int> tree;
		srand( (unsigned)time(NULL) );
		
		std::cout << "1000 insertion\n";
		for(int i = 0; i < 1000; i++)
		{
			tree.insert(i);
			tree.checkRbt();
		}
		std::cout << "100 deletion\n";
		for (int i = 0; i < 100; i+= 10)
		{
			int t = i + rand() % 10;
			std::cout << "Deleting : " << t << ", in tree of size :" << tree.size() << ", result :";
			tree.erase(t);
			tree.checkRbt();
		}
	}
	{
		std::cout << "\n########## RBT PRINT ##########\n\n";
		ft::map<int, std::string> mapOfString;
		ft::pair<int, std::string> pair1 = ft::make_pair(0, "ab");
		ft::pair<int, std::string> pair2 = ft::make_pair(1, "cd");
		ft::pair<int, std::string> pair3 = ft::make_pair(2, "ef");
		ft::pair<int, std::string> pair4 = ft::make_pair(3, "gh");
		ft::pair<int, std::string> pair5 = ft::make_pair(4, "ij");
		ft::pair<int, std::string> pair6 = ft::make_pair(5, "kl");
		ft::pair<int, std::string> pair7 = ft::make_pair(6, "mn");
		ft::pair<int, std::string> pair8 = ft::make_pair(7, "op");
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
		mapOfString.insert(pair8);
		mapOfString.printRBT();
		std::cout << "Value at key=4 : " << mapOfString[4] << std::endl;
		std::cout << "Value at key=9 : " << mapOfString[9] << std::endl;
		mapOfString.printRBT();
		std::cout << "Value at key=10 : " << mapOfString[10] << std::endl;
		mapOfString.printRBT();
		mapOfString.erase(6);
		mapOfString.printRBT();
		mapOfString.erase(0);
		mapOfString.printRBT();
		mapOfString.erase(3);
		mapOfString.printRBT();
		mapOfString.erase(4);
		mapOfString.printRBT();
		mapOfString.erase(1);
		mapOfString.printRBT();
		mapOfString.erase(2);
		mapOfString.printRBT();
		mapOfString.erase(7);
		mapOfString.printRBT();
		mapOfString.erase(10);
		mapOfString.printRBT();
		mapOfString.erase(9);
		mapOfString.printRBT();
	}
	return;
}

