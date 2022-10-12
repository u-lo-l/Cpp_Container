#include "ft_RBtree.hpp"

int main()
{
	try
	{
		ft::RBtree<int> tree;
		while (1)
		{
			std::cout << "enter number. positive to insert, negative to remove : ";
			int i;
			std::cin >> i;
			if (i == 0)
			{
				tree.printTree();
			}
			else if (i < 0)
			{
				std::cout << "delete : " << -i << std::endl;
				tree.deleteNode(-i);
			}
			else
			{
				std::cout << "add : " << i << std::endl;
				tree.insertNode(i);
			}
			std::cin.clear();
		}
	}
	catch (const std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}
}
