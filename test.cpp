#include <vector>
#include <iterator>
#include <list>
#include <map>
#include <iostream>

int main()
{
	std::vector<int> v(3, 4);
	v[1] = 5;
	v[2] = 6;
	for (int i = 0 ; i < v.size(); i++)
		std::cout << v.at(i) << std::endl;
	std::vector<int>::iterator it = v.rbegin();
	std::cout << *it << std::endl;
}