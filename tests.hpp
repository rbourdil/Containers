#ifndef TESTS_HPP
#define TESTS_HPP

#include "srcs/map/map.hpp"
#include "srcs/vector/vector.hpp"

#include <map>
#include <vector>
#include <iostream>
#include <fstream>

#ifdef FT
	#define NS ft
	#define FILENAME "ft_map_test.txt"
#endif
#ifdef STD
	#define NS std
	#define FILENAME "std_map_test.txt"
#endif

#define PRINT_NODE(f, x) ((f) << (x)->first << " : " << (x)->second << std::endl)

void	map_test(void);

// test helper functions

template <typename Map>
std::ofstream&	print_map(std::ofstream& f, const Map& map)
{
	typedef typename Map::const_iterator	const_iterator_type;

	if (f)
	{
		for (const_iterator_type it = map.begin(); it != map.end(); it++)
			PRINT_NODE(f, it);
	}
	return (f);
}

template <typename Map>
void	fill_map(Map& map, size_t n)
{
	for (size_t i = 0; i < n; i++)
		map.insert(NS::make_pair(i, i * i));
}

#endif
