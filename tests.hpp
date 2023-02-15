#ifndef TESTS_HPP
#define TESTS_HPP

#include "srcs/map/map.hpp"
#include "srcs/vector/vector.hpp"
#include "srcs/stack/stack.hpp"

#include <map>
#include <vector>
#include <stack>
#include <iostream>
#include <fstream>

#ifdef FT
	#define NS ft
	#define MAP_FILENAME "ft_map_test.txt"
	#define VEC_FILENAME "ft_vec_test.txt"
	#define STACK_FILENAME "ft_stack_test.txt"
#endif
#ifdef STD
	#define NS std
	#define MAP_FILENAME "std_map_test.txt"
	#define VEC_FILENAME "std_vec_test.txt"
	#define STACK_FILENAME "std_stack_test.txt"
#endif

#define PRINT_NODE(f, x) ((f) << (x)->first << " : " << (x)->second << std::endl)

void	map_test(void);
void	vec_test(void);
void	stack_test(void);

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

template <typename Vec>
std::ofstream&	print_vec(std::ofstream& f, const Vec& vec)
{
	typedef typename Vec::const_iterator	const_iterator_type;

	if (f)
	{
		for (const_iterator_type it = vec.begin(); it != vec.end(); it++)
			f << *it << std::endl;
	}
	return (f);
}

template <typename Vec>
void	fill_vec(Vec& vec, size_t n)
{
	for (size_t i = 0; i < n; i++)
		vec.push_back(i * i);
}

#endif
