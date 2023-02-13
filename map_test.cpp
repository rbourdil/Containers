#include "tests.hpp"

void	ft_map_test(void)
{
	std::ofstream	outfile("ft_map_test.txt");	

	if (!outfile)
	{
		std::cerr << "failed to create ft_map_test file" << std::endl;
		exit(EXIT_FAILURE);
	}

	// Element access
	{
		ft::map	map(
	
}
