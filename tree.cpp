#include "ft_RBtree.hpp"

int main()
{
	try
	{
		ft::RBtree<int> tree = ft::RBtree<int>();
		std::cout << "init done" << std::endl;
		std::cout << "nil ptr : " << tree.getNilPtr() << std::endl;
		std::cout << "nil color : " << tree.getNilPtr()->getColor() << std::endl;
		std::cout << "Root :" << tree.getRoot() << std::endl;
		ft::RBtreeNode<int> * node = tree.search(1);
		tree.insertNode(1);
		node = tree.search(1);
		std::cout << "Root :" << tree.getRoot() << std::endl;
		std::cout << *node << "\t" << node << std::endl;
		tree.insertNode(2);
		tree.insertNode(3);
		node = tree.search(3);
		std::cout << "Root :" << tree.getRoot() << std::endl;
		std::cout << *node << "\t" << node << std::endl;
		std::exit(1);
		tree.insertNode(4);
		tree.insertNode(5);
		tree.insertNode(6);
		tree.insertNode(7);
		std::cout << "step1. insert" << std::endl;
		{
			std::cout << "Root :" << tree.getRoot() << std::endl;
			ft::RBtreeNode<int> * node = tree.search(1);
			std::cout << *node << "\t" << node << std::endl;
			node = tree.search(2);
			std::cout << *node << "\t" << node << std::endl;
			node = tree.search(3);
			std::cout << *node << "\t" << node << std::endl;
			node = tree.search(4);
			std::cout << *node << "\t" << node << std::endl;
			node = tree.search(5);
			std::cout << *node << "\t" << node << std::endl;
			node = tree.search(6);
			std::cout << *node << "\t" << node << std::endl;
			node = tree.search(7);
			std::cout << *node << "\t" << node << std::endl;
		}

		// tree.deleteNode(6);
		// ft::RBtreeNode<int> * node = tree.search(6);
		// std::cout << node << std::endl;

		// std::cout << "after delete" << std::endl;
		// {
		// 	std::cout << "Root :" << tree.getRoot() << std::endl;
		// 	ft::RBtreeNode<int> * node = tree.search(1);
		// 	std::cout << *node << "\t" << node << std::endl;
		// 	node = tree.search(2);
		// 	std::cout << *node << "\t" << node << std::endl;
		// 	node = tree.search(3);
		// 	std::cout << *node << "\t" << node << std::endl;
		// 	node = tree.search(4);
		// 	std::cout << *node << "\t" << node << std::endl;
		// 	node = tree.search(7);
		// 	std::cout << *node << "\t" << node << std::endl;
		// 	node = tree.search(5);
		// 	std::cout << *node << "\t" << node << std::endl;
		// 	// node = tree.search(6);
		// 	// std::cout << *node << "\t" << node << std::endl;
		// }
	}
	catch (const std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}
}
