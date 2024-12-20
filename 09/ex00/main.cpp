#include <iostream>
#include <fstream>
#include "BitcoinExchange.hpp"

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << "./btc input.txt" << std::endl;
		return (1);
	}
	std::ifstream file(argv[1]);
	if (file.fail() || file.bad())
	{
		std::cout << "Error: could not open " << argv[1] << std::endl;
		return (1);
	}
	std::string		line;
	BitcoinExchange database;
	try
	{
		database.ReadDataBase("data.csv");
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << '\n';
		file.close();
		return (1);
	}
	
	getline(file, line);
	if (line != "date | value")
	{
		std::cout << "Error: header must be \"date | value\"" << std::endl;
		file.close();
		return (1);
	}
	while (true)
	{
		getline(file, line);
		if (file.eof() || file.fail() || file.bad())
		{
			break ;
		}
		database.DisplayPrice(line);
	}
	
	file.close();
	return (0);
}
