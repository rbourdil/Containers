#include <algorithm>

#include "type_traits.hpp"
#include "iterator/iterator_adaptors.hpp"
#include "iterator/iterator_primitives.hpp"
#include "iterator/iterators.hpp"
#include "includes/stl_vector.h"

int	main(void)
{
	{
	typedef ft::rand_access_iterator<const int*, std::vector<int> >	_const_iter;
	typedef ft::rand_access_iterator<int*, std::vector<int> >	_iter;

	int	src[5] = { 0, 1, 2, 3, 4 };
	_iter		a(src);
	_const_iter	b = a;
	_iter		c;

	c = a;

	// test postfix increment operator and dereference operator
	for (int i = 0; i < 5; i++)
		std::cout << "arr[" << i << "] = " << *b++ << std::endl;

	std::cout << std::endl;

	// simultaneous decrement increment
	for (int i = 0; i < 5; i++)
	{
		std::cout << "arr[" << i << "] = " << *c << std::endl;
		*c++ = *--b;
	}
	std::cout << std::endl;

	// verify previous test was successful
	for (int i = 0; i < 5; i++)
		std::cout << "arr[" << i << "] = " << *--c << std::endl;

	std::cout << std::endl;

	// test prefix increment operator
	std::cout << "arr[1] = " << *++c << std::endl;
	}
	std::cout << std::endl;
	{
	typedef std::vector<int>::iterator	iter;
	typedef std::vector<int>::const_iterator	const_iter;

	std::vector<int>			vec1;
	std::vector<int>			vec2;

	vec1.push_back(0);
	vec1.push_back(1);
	vec1.push_back(2);
	vec1.push_back(3);
	vec1.push_back(4);

	vec2.push_back(3);
	vec2.push_back(4);
	vec2.push_back(5);
	vec2.push_back(6);
	vec2.push_back(7);

	iter		i;
	const_iter	ci;

	// check that the defined iterator is comptatible with begin and end functions
	for (i = vec1.begin(); i != vec1.end(); i++)
		std::cout << *i << std::endl;
	
	std::cout << std::endl;
	
	ci = vec2.begin();
	// check the + operator
	std::cout << *(ci + 2) << std::endl;
	// equivalent test using [] operator
	std::cout << ci[2] << std::endl;
	ci += 2;
	// equivalent test using += operator
	std::cout << *ci << std::endl;
	// test -= operator
	ci -= 2;
	std::cout << *ci << std::endl;

	std::cout << std::endl;

	i = vec2.begin(); // now ci == i

	// check == operator
	if (ci == i)
		std::cout << "ci == i" << std::endl;
	else
		std::cout << "ci != i" << std::endl;
	
	// check <= operator
	if (ci <= i)
		std::cout << "ci <= i" << std::endl;
	else
		std::cout << "ci > i" << std::endl;
	
	// check >= operator
	if (ci >= i)
		std::cout << "ci >= i" << std::endl;
	else
		std::cout << "ci < i" << std::endl;

	i++; // now ci != i

	// check != operator
	if (ci != i)
		std::cout << "ci != i" << std::endl;
	else
		std::cout << "ci == i" << std::endl;
	
	// check < operator
	if (ci < i)
		std::cout << "ci < i" << std::endl;
	else
		std::cout << "ci >= i" << std::endl;
	
	// check > operator
	if (ci > i)
		std::cout << "ci > i" << std::endl;
	else
		std::cout << "ci <= i" << std::endl;
	}
	std::cout << std::endl;
	{
	typedef std::vector<std::vector<int> >::iterator	iter;

	std::vector<std::vector<int> >	vec1;
	std::vector<int>				vec2;

	vec2.push_back(3);
	vec2.push_back(4);
	vec2.push_back(5);
	vec2.push_back(6);
	vec2.push_back(7);

	vec1.push_back(vec2);

	iter	i = vec1.begin();

	// check -> operator
	std::cout << *i->begin() << std::endl;
	}	
	return (0);
}
