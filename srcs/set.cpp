/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:59:53 by rmorel            #+#    #+#             */
/*   Updated: 2023/04/21 19:09:56 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

void set_test()
{
	std::clock_t start = std::clock();
	{
		std::cout << "\n########## SET INSERTION ##########\n\n";
		std::list<int> lst;

		for (int i = 0; i < 1000; i++)
			lst.push_back(i * 24 - 13 * i + i);

		NS::set<int> s(lst.begin(), lst.end());
		NS::set<int>::iterator it = s.begin(), ite = s.end();
		NS::set<int>::reverse_iterator rit(it), rite = s.rend();

		std::cout << (it == rit.base()) << std::endl;
		std::cout << (it == (rit--).base()) << std::endl;

		std::cout << "it : " << *it << ", and rit.base() : "
			<< *rit;

		rit = s.rbegin();
		std::cout << "Reverse iteration : ";
		while (rit != rite)
			std::cout << " | " << *rit++;
		std::cout << " | " << std::endl;
		std::cout << "Normal iteration : ";
		while (it != ite)
			std::cout << " | " << *it++;
		std::cout << " | " << std::endl;
	}
	std::clock_t end = std::clock();
	double elapsed_time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	std::cout << "Elapsed time SET INSERT : " << NAME << " = " << elapsed_time << " seconds\n";
	start = std::clock();
	{
		std::cout << "\n########## SET ERASE ##########\n\n";
		std::list<int> lst;

		for (int i = 0; i < 1000; i++)
			lst.push_back(i * 24 - 13 * i + i);

		NS::set<int> s(lst.begin(), lst.end());
		for(std::list<int>::iterator it = lst.begin(); it != lst.end(); it++)
			s.erase(*it);
	}
	end = std::clock();
	elapsed_time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	std::cout << "Elapsed time SET ERASE : " << NAME << " = " << elapsed_time << " seconds\n";
}
