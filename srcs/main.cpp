/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 15:44:36 by rmorel            #+#    #+#             */
/*   Updated: 2023/03/28 21:46:39 by rmorel           ###   ########.fr       */
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

	return 0;
}

