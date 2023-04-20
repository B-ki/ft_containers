/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 15:44:36 by rmorel            #+#    #+#             */
/*   Updated: 2023/04/20 17:52:32 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NS
# define NS std
#endif

#include "tests.hpp"
#include "RBT.hpp"

int main()
{
	vector_stack_test();
	RBT_test();
	mli_bounds();
	mli_empty();
	mli_erase();
	std::cout << "MLI ERASE DONE\n";
	mli_erase2();
	std::cout << "MLI ERASE2 DONE\n";
	mli_find();
	std::cout << "MLI FIND DONE\n";

	return 0;
}

