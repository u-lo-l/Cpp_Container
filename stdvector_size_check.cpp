#include <vector>
#include <iostream>
#include "ft_vector.hpp"

void printSize( const ft::vector<int> & v)
{
	std::cout << "size : " << v.size() << std::endl << "capacity : " << v.capacity() << std::endl;
	for (int i = 0 ; i < v.size() ; i++)
		std::cout << v.at(i) << " ";
	std::cout << std::endl;
	std::cout << std::endl;
}

int		main(void)
{
	ft::vector<int> vct(10);
	ft::vector<int> vct2;
	ft::vector<int> vct3;

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i) * 3;
	printSize(vct);

	vct2.insert(vct2.end(), 42);
	vct2.insert(vct2.begin(), 2, 21);
	printSize(vct2);

	vct2.insert(vct2.end() - 2, 42);
	printSize(vct2);

	vct2.insert(vct2.end(), 2, 84);
	printSize(vct2);

	vct2.resize(4);
	printSize(vct2);

	vct2.insert(vct2.begin() + 2, vct.begin(), vct.end());
	vct.clear();
	printSize(vct2);

	printSize(vct);

	for (int i = 0; i < 5; ++i)
		vct3.insert(vct3.end(), i);
	vct3.insert(vct3.begin() + 1, 2, 111);
	printSize(vct3);

	return (0);
}