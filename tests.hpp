#ifndef TESTS_HPP
#define TESTS_HPP

#include "srcs/map/map.hpp"
#include "srcs/vector/vector.hpp"

#include <map>
#include <vector>
#include <iostream>
#include <fstream>

void	ft_map_test(void);

// test helper functions

template <typename Map>
void	print_map(std::ostream& f, const Map& map)
{
	typedef typename Map::iterator	iterator_type;

	if (f)
	{
		for (iterator_type it = map.begin(); it != map.end(); it++)
			ostream << it->first << ":" << it->second << std::endl;
	}
	return (f);
}

#endif
