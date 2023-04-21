/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:03:28 by rmorel            #+#    #+#             */
/*   Updated: 2023/04/21 19:00:31 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

void map_iterator(void)
{
	std::clock_t start = std::clock();
	{
		std::cout << "\n########## MAP ITERATORS 0 ##########\n\n";
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
		std::cout << "\n########## MAP ITERATORS 1 ##########\n\n";
		typedef NS::pair<const char, int> t_pair;
		std::list<t_pair> lst;

		for (int i = 0; i < 10; i++)
			lst.push_back(t_pair('a' + i, i * 5 + 2));

		NS::map<const char, int> map(lst.begin(), lst.end());
		NS::map<const char, int>::iterator it = map.begin(), ite = map.end();
		NS::map<const char, int>::reverse_iterator rit(it), rite = map.rend();

		std::cout << (it == rit.base()) << std::endl;
		std::cout << (it == (rit--).base()) << std::endl;

		std::cout << "it : " << printPair(it, false) << ", and rit.base() : "
			<< printPair(rit.base());

		rit = map.rbegin();
		std::cout << "Reverse iteration : ";
		while (rit != rite)
			std::cout << " | " << printPair(rit++);
		std::cout << " | " << std::endl;
		std::cout << "Normal iteration : ";
		while (it != ite)
			std::cout << " | " << printPair(it++);
		std::cout << " | " << std::endl;
	}
	{
		std::cout << "\n########## MAP ITERATORS 2 ##########\n\n";
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
		//c.printMAP();
		NS::map<int, std::string>::reverse_iterator k = c.rbegin();
		std::cout << k->second << std::endl;
		k++;
		std::cout << k->second << std::endl;
		k++;
		std::cout << k->second << std::endl;
		
	}
	std::clock_t end = std::clock();
	double elapsed_time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	std::cout << "Elapsed time MAP ITERATORS : " << NAME << " = " << elapsed_time << " seconds\n";
}
