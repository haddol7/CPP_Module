/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 21:08:08 by daeha             #+#    #+#             */
/*   Updated: 2024/10/03 22:06:27 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat()
	: Animal("Cat")
{
	std::cout << "Constructor : Cat - " << getType() << std::endl;
}

Cat::~Cat()
{
	std::cout << "Destructor : Cat" << std::endl;
	//std::cout << getType() << std::endl;
}

Cat::Cat(const Cat& copy)
	: Animal(copy.getType())
{
	std::cout << "Copy Constructor : Cat " << getType() << std::endl;
}

Cat& Cat::operator=(const Cat& lhs)
{
	if (this != &lhs)
	{
		SetType(lhs.getType());
	}
	return (*this);
}

void Cat::makeSound() const
{
	std::cout << getType() << " - meow meow" << std::endl;
}