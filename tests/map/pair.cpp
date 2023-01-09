#include "pair.hpp"

#include <map>
#include <string>
#include <iostream>

template <typename T1, typename T2>
void	print_pair(const std::string& name, const ft::pair<T1, T2>& p)
{
	std::cout << name << ": " << std::endl;
	std::cout << "first: " << p.first << std::endl;
	std::cout << "second: " << p.second << std::endl;
}

int	main(void)
{
	{
	std::string	key("key");
	std::string	value("value");

	ft::pair<std::string, std::string>			pair1;
	print_pair("pair1", pair1);

	std::cout << std::endl;

	ft::pair<std::string, std::string>			pair2(key, value);
	print_pair("pair2", pair2);

	std::cout << std::endl;

	ft::pair<std::string, std::string>			pair3(pair2);
	print_pair("pair3", pair3);

	std::cout << std::endl;

	if (pair2 == pair3)
		std::cout << "pair2 == pair3" << std::endl;
	else
		std::cout << "pair2 != pair3" << std::endl;
	
	std::cout << std::endl;
	
	ft::pair<std::string, std::string>	pair4(std::string("kex"), value);
	print_pair("pair4", pair4);

	std::cout << std::endl;

	if (pair3 == pair4)
		std::cout << "pair3 == pair4" << std::endl;
	else
		std::cout << "pair3 != pair4" << std::endl;
	
	std::cout << std::endl;

	if (pair2 < pair3)
		std::cout << "pair2 < pair3" << std::endl;
	else
		std::cout << "pair2 >= pair3" << std::endl;
	
	std::cout << std::endl;

	if (pair3 < pair4)
		std::cout << "pair3 < pair4" << std::endl;
	else
		std::cout << "pair3 >= pair4" << std::endl;
	
	std::cout << std::endl;

	pair4.first = "key";
	pair4.second = "val";
	print_pair("pair4", pair4);

	std::cout << std::endl;

	if (pair3 < pair4)
		std::cout << "pair3 < pair4" << std::endl;
	else
		std::cout << "pair3 >= pair4" << std::endl;

	std::cout << std::endl;

	pair4.first = "key";
	pair4.second = "value1";
	print_pair("pair4", pair4);

	std::cout << std::endl;

	if (pair3 < pair4)
		std::cout << "pair3 < pair4" << std::endl;
	else
		std::cout << "pair3 >= pair4" << std::endl;
	
	}		

	return (0);
}
