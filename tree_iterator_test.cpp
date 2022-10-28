#include <iostream>
#include "ft_RBtreeNode.hpp"
#include "ft_RBtree.hpp"
#include "ft_pair.hpp"
#include "ft_RBtreeIterator.hpp"

int main()
{
	ft::RBtree< ft::pair<int, std::string> > T;

	for (int i = 1 ; i <= 1 ; i++)
		T.insertNode( ft::make_pair(i, "str"));

	ft::RBtreeNode< ft::pair<int, std::string> > * N = T.getRoot();
	N = N->_minimum();

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "start" << N << std::endl;

	ft::tree_iterator< ft::pair<int, std::string> > it(N);
	std::cout << "============================" << std::endl;
	std::cout << "addr : " << &*it << std::endl;
	std::cout << "key : " << it->first << std::endl;
	std::cout << "val : " << it->second << std::endl;

	// it++;
	// std::cout << "============================" << std::endl;
	// std::cout << "addr : " << &*it << std::endl;
	// std::cout << "key : " << it->first << std::endl;
	// std::cout << "val : " << it->second << std::endl;

	char c;
	while (true)
	{
		std::cout << "input : ";
		std::cin >> c;
		if (c == '+')
			++it;
		else if (c == '-')
			it--;
		else if (c == '0')
			T.printTree();
		else
		{
			std::cout << c << std::endl;
			break;
		}
		// T.printTree();
	}	

}