#include "tests.hpp"

void	map_test(void)
{
	std::ofstream	outfile(MAP_FILENAME);

	if (!outfile)
	{
		std::cerr << "failed to create map test file" << std::endl;
		exit(EXIT_FAILURE);
	}

	// Element access
	{
		NS::map<size_t, size_t>		map;

		// fills map with keys from 0 to 9999 (in this case)
		// and values equal to the square of the key
		fill_map(map, 10000);
			
		// at
		outfile << map.at(5) << std::endl;
		try {
			outfile << map.at(10000) << std::endl;
		} catch (std::exception& e) {
			outfile << "at threw exception" << std::endl;
		}

		outfile << std::endl;

		// operator[]
		outfile << map[5] << std::endl;
		map[5] = 5;
		outfile << map[5] << std::endl;
		try {
			outfile << map[10000] << std::endl;
		} catch (std::exception& e) {
			outfile << "operator[] threw exception" << std::endl;
		}
	}
	
	outfile << std::endl;

	// Iterators
	{
		typedef NS::map<size_t, size_t>		map_type;
		typedef map_type::iterator	iterator_type;
		typedef map_type::reverse_iterator	reverse_iterator_type;

		map_type	map;

		fill_map(map, 100);
		
		// begin, end
		for (iterator_type it = map.begin(); it != map.end(); it++)
			PRINT_NODE(outfile, it);

		outfile << std::endl;

		// rbegin, rend
		for (reverse_iterator_type it = map.rbegin(); it != map.rend(); it++)
			PRINT_NODE(outfile, it);
	}

	outfile << std::endl;

	// Capacity
	{
		NS::map<size_t, size_t>	map;

		// empty and size
		if (map.empty())
			outfile << "map is empty" << std::endl;
		outfile << map.size() << std::endl;
		fill_map(map, 100);
		if (!map.empty())
			outfile << "map is not empty" << std::endl;
		outfile << map.size() << std::endl;
	}

	outfile << std::endl;

	// Modifiers
	{
		typedef NS::map<size_t, size_t>	map_type;

		map_type	from;
		map_type	map;

		// insert
		map.insert(from.begin(), from.end());	
		print_map(outfile, map);
		map.insert(map.begin(), NS::make_pair(0, 0));
		map.insert(map.end(), NS::make_pair(1, 1));

		outfile << std::endl;

		// erase
		map.erase(map.begin());
		map.erase(35);
		map.erase(-1);
		print_map(outfile, map);

		outfile << std::endl;

		// swap
		map.swap(from);
		print_map(outfile, map);

		// clear
		map.clear();
		if (map.empty())
			outfile << "map was cleared" << std::endl;
	}

	outfile << std::endl;

	// Lookup
	{
		NS::map<size_t, size_t>	map;

		fill_map(map, 100);

		// count
		outfile << map.count(0) << std::endl;
		outfile << map.count(1000) << std::endl;

		outfile << std::endl;

		// find
		PRINT_NODE(outfile, map.find(5));
			
		// lower bound
		PRINT_NODE(outfile, map.lower_bound(5));

		// upper bound
		PRINT_NODE(outfile, map.lower_bound(5));
	}

	// Non member functions
	{
		typedef NS::map<size_t, size_t>	map_type;

		map_type	map1;
		map_type	map2;

		if (map1 == map2)
			outfile << "equal" << std::endl;
		fill_map(map1, 100);
		if (map1 != map2)
			outfile << "not equal" << std::endl;
		fill_map(map2, 200);
		if (map1 < map2)
			outfile << "map1 < map2" << std::endl;
		else
			outfile << "map1 >= map2" << std::endl;
		std::swap(map1, map2);
		print_map(outfile, map1);
		print_map(outfile, map2);
	}
}
