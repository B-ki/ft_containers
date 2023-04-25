/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_insert_erase.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:08:05 by rmorel            #+#    #+#             */
/*   Updated: 2023/04/25 18:06:23 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

void map_insert_erase()
{
	std::clock_t start = std::clock();
	{
		std::cout << "\n########## MAP PRINT (ONLY FT) ##########\n\n";
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
		mapOfString.insert(pair2);
		mapOfString.insert(pair3);
		mapOfString.insert(pair4);
		mapOfString.insert(pair5);
		mapOfString.insert(pair6);
		mapOfString.insert(pair7);
		mapOfString.insert(pair8);
		std::cout << "Value at key=4 : " << mapOfString[4] << std::endl;
		std::cout << "Value at key=9 : " << mapOfString[9] << std::endl;
		std::cout << "Value at key=999 : " << mapOfString[999] << std::endl;
		ft::map<int, std::string> mapCopy(mapOfString);
		mapCopy.find(5);
		std::cout << "Erase 5\n";
		mapCopy.erase(5);
		std::cout << "Erase 6\n";
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
		std::cout << "\n########## MAP INSERT, ERASE, SIZE ##########\n\n";
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
		std::cout << "\n########## MAP INSERT POS ##########\n\n";
		NS::map<int, foo<int> > c;
		foo<int> a(1);
		foo<int> b(2);
		foo<int> f(3);
		foo<int> d(4);
		foo<int> e(5);
		NS::pair<int, foo<int> > p0 = NS::make_pair(0, a);
		NS::pair<int, foo<int> > p1 = NS::make_pair(1, b);
		NS::pair<int, foo<int> > p2 = NS::make_pair(2, f);
		NS::pair<int, foo<int> > p3 = NS::make_pair(3, d);
		NS::pair<int, foo<int> > p3bis = NS::make_pair(3, d);
		NS::pair<int, foo<int> > p4 = NS::make_pair(4, e);
		NS::pair<int, foo<int> > p5 = NS::make_pair(5, a);
		c.insert(p0);
		std::cout << (c.insert(p1)).second << std::endl;;
		c.insert(p2);
		NS::map<int, foo<int> >::iterator i = c.begin();
		i++;
		i++; // Pointe sur p2
		c.insert(i, p3);
		c.insert(i, p3bis);
		std::cout << "Size is : " << c.size() << std::endl;
		c.insert(c.begin(), p4);
		c.insert(c.end()--, p5);
	}
	std::clock_t end = std::clock();
	double elapsed_time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	std::cout << "Elapsed time MAP INSERT ERASE : " << NAME << " = " << elapsed_time << " seconds\n";
	{
		NS::RBT<int, int> tree;
		std::cout << "\n######### random mode #########\n\n";
		int RANDOM_TEST_SIZE = 10000;
		ft::vector<int> numbers(RANDOM_TEST_SIZE);
		std::srand(std::time(0));
		for (int i = 0; i < RANDOM_TEST_SIZE; i++)
		{
			int number = std::rand() % 13337;
			numbers.push_back(number);
			tree.insert(number);
			//tree.printTree();
		}

		while (numbers.size())
		{
			ft::vector<int>::iterator randIt = numbers.begin();
			std::advance(randIt, std::rand() % numbers.size());
			tree.erase(*randIt);
			numbers.erase(randIt);
		}
		tree.prettyPrint();
		//tree.printTree();

	}
}
