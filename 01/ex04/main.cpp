/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 23:17:59 by daeha             #+#    #+#             */
/*   Updated: 2024/09/30 14:32:58 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mySed.hpp"

int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		std::cerr << "invalid arguments" << std::endl;
		return (1);
	}
	try
	{
		mySed	file(argv[1]);
		
		file.replace(argv[2], argv[3]);
	}
	catch (const std::ios_base::failure& e)
	{
		std::cerr << "Error : " << e.what() << std::endl;
		return (1);
	}
	return (0);
}