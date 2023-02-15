#!/bin/bash

# create the output test files and clean
make --silent && ./ft_containers && make --silent fclean
make --silent std=1 && ./std_containers && make --silent std=1 fclean

# check whether std and ft test files are identical

diff ft_map_test.txt std_map_test.txt
if [ $? -eq 0 ]
then
	echo "map: OK"
else
	echo "map: fail"
fi

diff ft_vec_test.txt std_vec_test.txt
if [ $? -eq 0 ]
then
	echo "vector: OK"
else
	echo "vector: fail"
fi

diff ft_stack_test.txt std_stack_test.txt
if [ $? -eq 0 ]
then
	echo "stack: OK"
else
	echo "stack: fail"
fi

rm -f ft_vec_test.txt std_vec_test.txt
rm -f ft_map_test.txt std_map_test.txt
rm -f ft_stack_test.txt std_stack_test.txt
