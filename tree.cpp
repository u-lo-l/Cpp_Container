#include "ft_RBtree.hpp"

int main()
{
	ft::RBtree<int> tree;
	try
	{
		while (1)
		{
			std::cout << "enter number. positive to insert, negative to remove : ";
			int i;
			std::cin >> i;
			if (i == 0)
			{
				// std::cout << "copy" << std::endl;
				// ft::RBtree<int> tree2(tree);
				// tree.insertNode(10);
				tree.printTree();
				// tree2 = tree;
				// tree2.printTree();
				// break;
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
	// std::system("leaks a.out");
}
