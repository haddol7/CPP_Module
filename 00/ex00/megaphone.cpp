/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 14:11:11 by daeha             #+#    #+#             */
/*   Updated: 2024/09/29 12:39:15 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int main(int argc, char *argv[])
{		
	if (argc == 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
	for (int i = 1; i < argc; i++)
	{
		for (int ch = 0; ch < std::strlen(argv[i]); ch++)
		{
			std::cout << static_cast<char>(toupper(argv[i][ch]));
		}
	}
	std::cout << std::endl;
	return (0);
}