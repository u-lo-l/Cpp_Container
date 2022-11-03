#include <iostream>
// #include "std_map.hpp"
#include <map>

int main()
{
	std::map<int, int> a;
	for (int i = 0 ; i < 10 ; i++)
	{
		std::pair<std::map<int, int>::iterator, bool> temp = a.insert(std::make_pair(i,i));
		std::cout << (temp.first)->first << ", ";
		std::cout << (temp.first)->second << std::endl;
		std::cout << temp.second << std::endl;
	}
}