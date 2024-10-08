/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mySed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:31:25 by daeha             #+#    #+#             */
/*   Updated: 2024/10/06 00:55:34 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mySed.hpp"

mySed::mySed(const std::string& filename)
{
	std::string replaceString = filename + ".replace";
	const char * cFileName = filename.c_str();
	const char * cFileNameReplace = replaceString.c_str();
	
	fin.open(cFileName);
	fout.open(cFileNameReplace);
	if (!fout.is_open() || !fin.is_open())
		throw (std::ios_base::failure("file open failure"));
}

mySed::~mySed()
{
	fin.close();
	fout.close();
}

void mySed::replace(const std::string& target, const std::string& replace)
{
	std::string line;
	size_t		pos;
	
	while (!fin.eof())
	{
		std::getline(fin, line);
		if (!fin.eof() && (fin.fail() || fin.bad()))
		{
			throw (std::ios_base::failure("fin getline error"));
		}
		pos = line.find(target);
		while (pos != std::string::npos)
		{
			line = line.substr(0, pos) + replace + line.substr(pos + target.length());
			pos = line.find(target, pos + replace.length());
		}
		fout << line << std::endl;
		if (fout.fail() || fout.bad())
		{
			throw (std::ios_base::failure("fout error"));
		}
	}
}
