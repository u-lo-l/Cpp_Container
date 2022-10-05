#include "ft_RBtree.hpp"

int main()
{
	try
	{
		ft::RBtree<int> tree = ft::RBtree<int>();

		std::cout << "step1. insert 1" << std::endl;
		tree.insertNode(1);
		{
			std::cout << "Root :" << tree.getRoot() << std::endl;
			ft::RBtreeNode<int> * node = tree.search(1);
			std::cout << *node << std::endl;
		}

		std::cout << "step2. insert 2" << std::endl;
		tree.insertNode(2);
		{
			std::cout << "Root :" << tree.getRoot() << std::endl;
			ft::RBtreeNode<int> * node = tree.search(1);
			std::cout << *node << std::endl;
			node = tree.search(2);
			std::cout << *node << std::endl;
		}


		std::cout << "step3. insert 3" << std::endl;
		tree.insertNode(3);
		{
			std::cout << "Root :" << tree.getRoot() << std::endl;
			ft::RBtreeNode<int> * node = tree.search(1);
			std::cout << *node << std::endl;
			node = tree.search(2);
			std::cout << *node << std::endl;
			node = tree.search(3);
			std::cout << *node << std::endl;
		}

		std::cout << "step3. insert 4" << std::endl;
		tree.insertNode(4);
		{
			std::cout << "Root :" << tree.getRoot() << std::endl;
			ft::RBtreeNode<int> * node = tree.search(1);
			std::cout << *node << std::endl;
			node = tree.search(2);
			std::cout << *node << std::endl;
			node = tree.search(3);
			std::cout << *node << std::endl;
			node = tree.search(4);
			std::cout << *node << std::endl;
		}
		tree.insertNode(5);
		tree.insertNode(6);
		tree.insertNode(7);
		std::cout << "step4. insert 5 6 7" << std::endl;
		{
			std::cout << "Root :" << tree.getRoot() << std::endl;
			ft::RBtreeNode<int> * node = tree.search(1);
			std::cout << *node << std::endl;
			node = tree.search(2);
			std::cout << *node << std::endl;
			node = tree.search(3);
			std::cout << *node << std::endl;
			node = tree.search(4);
			std::cout << *node << std::endl;
			node = tree.search(5);
			std::cout << *node << std::endl;
			node = tree.search(6);
			std::cout << *node << std::endl;
			node = tree.search(7);
			std::cout << *node << std::endl;
		}

		tree.deleteNode(6);
		ft::RBtreeNode<int> * node = tree.search(6);
		std::cout << node << std::endl;

		std::cout << "after delete" << std::endl;
		{
			std::cout << "Root :" << tree.getRoot() << std::endl;
			ft::RBtreeNode<int> * node = tree.search(1);
			std::cout << *node << std::endl;
			node = tree.search(2);
			std::cout << *node << std::endl;
			node = tree.search(3);
			std::cout << *node << std::endl;
			node = tree.search(4);
			std::cout << *node << std::endl;
			node = tree.search(5);
			std::cout << *node << std::endl;
			// node = tree.search(6);
			// std::cout << *node << std::endl;
			node = tree.search(7);
			std::cout << *node << std::endl;
		}
	}
	catch (const std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}
}
