/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:36:55 by daeha             #+#    #+#             */
/*   Updated: 2024/10/06 01:20:32 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

class Fixed
{
public:
	Fixed();
	Fixed(const Fixed& copy);
	Fixed& operator=(const Fixed &rhs);
	~Fixed();
	int getRawBits(void) const;
	void setRawBits(int const raw);

private:
	static const int mBits;
	int	mValue;
};
