#include <iostream>
#include "ft_map.hpp"

int main()
{
	ft::map<int, int> a;
	for (int i = 0 ; i < 10 ; i++)
	{
		ft::pair<ft::map<int, int>::iterator, bool> temp = a.insert(ft::make_pair(i,i));
		std::cout << *(temp.first) << std::endl;
		std::cout << temp.second << std::endl;
	}
	std::cout << a.max_size() << std::endl;
	std::system("leaks a.out");
}