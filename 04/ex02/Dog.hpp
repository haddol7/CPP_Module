/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 21:08:21 by daeha             #+#    #+#             */
/*   Updated: 2024/10/03 23:21:02 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "AAnimal.hpp"
#include "Brain.hpp"

class Dog : public AAnimal
{
public:
	Dog();
	~Dog();
	Dog(const Dog& copy);
	Dog& operator=(const Dog& lhs);
	void makeSound() const;
private:
	Brain *mBrain;
};


