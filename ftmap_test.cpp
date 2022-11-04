#include <iostream>
#include "ft_map.hpp"

void print(const ft::map<int, int> & m)
{
	ft::map<int, int>::const_iterator it = m.begin();
	ft::map<int, int>::const_iterator eit = m.end();

	std::cout << "size : " << m.size() << std::endl;
	for (; it != eit ; it++)
	{
		std::cout << "key : " << it->first << std::endl;
		std::cout << "val : " << it->second << std::endl;
		std::cout << "======================" << std::endl;
	}
}

int main()
{
	ft::map<int, int> a;
	for (int i = 1 ; i < 10 ; i++)
	{
		a.insert(ft::make_pair(i,i));
		// ft::pair<ft::map<int, int>::iterator, bool> temp;
		// temp = a.insert(ft::make_pair(i,i));
		// std::cout << (temp.first)->first << ", ";
		// std::cout << (temp.first)->second << std::endl;
		// std::cout << temp.second << std::endl;
	}
	std::cout << a.max_size() << std::endl;
	print(a);
	std::cout << std::endl;
	std::cout << std::endl;
	a.erase(a.begin());
	a.erase(a.begin());
	print(a);
	std::system("leaks a.out");
}