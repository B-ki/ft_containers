/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT_test.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:44:12 by rmorel            #+#    #+#             */
/*   Updated: 2023/04/20 14:17:27 by rmorel           ###   ########.fr       */
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

#ifndef NS
# define NS std
#endif

# define _pair NS::pair

template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}

template <typename T_MAP>
void	printSize(T_MAP const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	std::cout << "max_size: " << mp.max_size() << std::endl;
	if (print_content)
	{
		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

template <typename U, typename V>
void	printReverse(NS::map<U, V> &mp)
{
	typename NS::map<U, V>::iterator it = mp.end(), ite = mp.begin();

	std::cout << "printReverse:" << std::endl;
	while (it != ite) {
		it--;
		std::cout << "-> " << printPair(it, false) << std::endl;
	}
	std::cout << "_______________________________________________" << std::endl;
}

template <typename T>
T	inc(T it, int n)
{
	while (n-- > 0)
		++it;
	return (it);
}

template <typename T>
T	dec(T it, int n)
{
	while (n-- > 0)
		--it;
	return (it);
}

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
		std::cout << "\n########## RBT PRINT (ONLY FT) ##########\n\n";
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
		std::cout << "Value at key=999 : " << mapOfString[999] << std::endl;
		mapOfString.printRBT();
		ft::map<int, std::string> mapCopy(mapOfString);
		mapCopy.find(5);
		std::cout << "Erase 5\n";
		mapCopy.erase(5);
		mapCopy.printRBT();
		std::cout << "Erase 6\n";
		mapCopy.erase(6);
		mapCopy.printRBT();
		mapCopy.erase(0);
		mapCopy.printRBT();
		mapCopy.erase(3);
		mapCopy.printRBT();
		mapCopy.erase(4);
		mapCopy.printRBT();
		mapCopy.erase(1);
		mapCopy.printRBT();
		mapCopy.erase(2);
		mapCopy.printRBT();
		mapCopy.erase(7);
		mapCopy.printRBT();
		mapCopy.erase(999);
		mapCopy.printRBT();
		mapCopy.erase(9);
		mapCopy.printRBT();
	}
	{
		std::cout << "\n########## RBT INSERT, ERASE, SIZE ##########\n\n";
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
		mapOfString.insert(pair2);
		mapOfString.insert(pair3);
		mapOfString.insert(pair4);
		mapOfString.insert(pair5);
		mapOfString.insert(pair6);
		mapOfString.insert(pair7);
		std::cout << (mapOfString.insert(pair8)).second << std::endl;
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
		NS::map<int, std::string> mapCopy(mapOfString);
		mapCopy.find(5);
		mapCopy.erase(5);
		mapCopy.erase(10);
		mapCopy.erase(6);
		mapCopy.erase(0);
		mapCopy.erase(3);
		mapCopy.erase(4);
		mapCopy.erase(1);
		mapCopy.erase(2);
		mapCopy.erase(7);
		mapCopy.erase(999);
		mapCopy.erase(9);
	}
	{
		std::cout << "\n########## RBT ITERATORS 0 ##########\n\n";
		NS::map<int, std::string> c;
		NS::map<int, std::string>::iterator i = c.begin();
		NS::map<int, std::string>::iterator j = c.begin();
		(void)i;
		(void)j;
		NS::pair<int, std::string> p1 = NS::make_pair(0, "a");
		c.insert(p1);
		i++;
		j--;
		std::cout << i->second << std::endl;
		std::cout << j->second << std::endl;
	}
	{
		std::cout << "\n########## RBT ITERATORS 1 ##########\n\n";

		#define T1 char
		#define T2 int
		typedef _pair<const T1, T2> T3;
		std::list<T3> lst;
		unsigned int lst_size = 5;
		for (unsigned int i = 0; i < lst_size; ++i)
			lst.push_back(T3('a' + i, (i + 1) * 7));

		NS::map<T1, T2> mp(lst.begin(), lst.end());
		NS::map<T1, T2>::iterator it_ = mp.begin();
		NS::map<T1, T2>::reverse_iterator it(it_), ite;
		printSize(mp);

		std::cout << (it_ == it.base()) << std::endl;
		std::cout << (it_ == dec(it, 3).base()) << std::endl;

		printPair(it.base());
		printPair(inc(it.base(), 1));

		std::cout << "TEST OFFSET" << std::endl;
		--it;
		printPair(it);
		printPair(it.base());

		it = mp.rbegin(); ite = mp.rend();
		while (it != ite)
			std::cout << "[rev] " << printPair(it++, false) << std::endl;

	}
	{
		std::cout << "\n########## RBT ITERATORS 2 ##########\n\n";
		NS::map<int, std::string> c;
		NS::pair<int, std::string> p1 = NS::make_pair(0, "a");
		c.insert(p1);
		NS::pair<int, std::string> p2 = NS::make_pair(1, "b");
		std::cout << (c.insert(p2)).second << std::endl;;
		NS::pair<int, std::string> p3 = NS::make_pair(2, "c");
		c.insert(p3);
		NS::map<int, std::string>::iterator i = c.begin();
		std::cout << i->second << std::endl;
		i++;
		std::cout << i->second << std::endl;
		i++;
		std::cout << i->second << std::endl;	
		i++;
		c.erase(2);
		i--;
		std::cout << i->second << std::endl;	
		i--;
		std::cout << i->second << std::endl;	
		c.erase(1);
		std::cout << i->second << std::endl;	
		c.insert(p2);
		NS::map<int, std::string>::iterator j = ++i;
		std::cout << i->second << std::endl;
		std::cout << j->second << std::endl;
		c.insert(p2);
		std::cout << c.size() << std::endl;
		c.insert(p3);
		//c.printRBT();
		NS::map<int, std::string>::reverse_iterator k = c.rbegin();
		std::cout << k->second << std::endl;
		k++;
		std::cout << k->second << std::endl;
		k++;
		std::cout << k->second << std::endl;
		
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
		std::cout << "\n########## RBT INSERT POS ##########\n\n";
		NS::map<int, std::string> c;
		NS::pair<int, std::string> p0 = NS::make_pair(0, "a");
		NS::pair<int, std::string> p1 = NS::make_pair(1, "b");
		NS::pair<int, std::string> p2 = NS::make_pair(2, "c");
		NS::pair<int, std::string> p3 = NS::make_pair(3, "d");
		NS::pair<int, std::string> p3bis = NS::make_pair(3, "dddd");
		NS::pair<int, std::string> p4 = NS::make_pair(4, "e");
		NS::pair<int, std::string> p5 = NS::make_pair(5, "f");
		c.insert(p0);
		std::cout << (c.insert(p1)).second << std::endl;;
		c.insert(p2);
		NS::map<int, std::string>::iterator i = c.begin();
		i++;
		i++; // Pointe sur p2
		c.insert(i, p3);
		c.insert(i, p3bis);
		std::cout << "Size is : " << c.size() << std::endl;
		//c.printRBT();
		c.insert(c.begin(), p4);
		//c.printRBT();
		c.insert(c.end()--, p5);
		//c.printRBT();
	}
	{
	}
	return;
}

