/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bounds.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 12:11:11 by rmorel            #+#    #+#             */
/*   Updated: 2023/04/21 18:45:45 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

void map_bounds()
{
	std::clock_t start = std::clock();
	std::cout << "\n########## MAP BOUNDS ##########\n\n";
	{
		typedef NS::map<int, foo<int> >::value_type t_pair;	
		std::list<t_pair> lst;
		for (int i = 0; i < 10; i++)
			lst.push_back(t_pair(i, (i * 3 + 1)));

		NS::map<int, foo<int> > mp(lst.begin(), lst.end());

		for (int i = -2; i < 11; i++)
		{
			std::cout << "Lower/upper bound of " << i << " : ";
			std::cout << (mp.lower_bound(i) == mp.end() ? "end()" : printPair(mp.lower_bound(i), false));
			std::cout << " / ";
			std::cout << (mp.upper_bound(i) == mp.end() ? "end()" : printPair(mp.upper_bound(i), false));	
			std::cout << std::endl;
		}
	}
	std::clock_t end = std::clock();
	double elapsed_time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	std::cout << "Elapsed time MAP BOUNDS : " << (USING_FT == 1 ? "ft" : "std")  << " = " << elapsed_time << " seconds\n";
}
