/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 17:16:32 by daeha             #+#    #+#             */
/*   Updated: 2024/10/10 22:22:27 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"

AMateria::AMateria()
	: type("")
{
}

AMateria::AMateria(const AMateria& copy)
	: type(copy.getType())
{
}

AMateria::AMateria(const std::string& type)
	: type(type)
{
}

AMateria::~AMateria()
{
}

AMateria& AMateria::operator=(const AMateria& rhs)
{
	if (this != &rhs)
	{
		type = rhs.getType();
	}
	return (*this);
}

const std::string& AMateria::getType() const
{
	return (type);	
}

void AMateria::use(ICharacter& target)
{
	std::cout << target.getName() << ": It's Undefined Materia" << std::endl;
}
