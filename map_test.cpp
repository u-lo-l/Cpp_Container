#include <map>
#include <vector>
#include <iostream>
int main()
{
	std::map<int, std::string> testmap;

	try
	{
		// testmap.insert(std::make_pair(1, "string1"));
		// testmap.insert(std::make_pair(2, "string2"));
		// testmap.insert(std::make_pair(3, "string3"));

		std::map<int, std::string>::iterator it = testmap.begin();
		std::cout << "============================" << std::endl;
		std::cout << "addr : " << &*it << std::endl;
		std::cout << "key : " << it->first << std::endl;
		std::cout << "val : " << it->second << std::endl;

		it++;
		std::cout << "============================" << std::endl;
		std::cout << "addr : " << &*it << std::endl;
		std::cout << "key : " << it->first << std::endl;
		std::cout << "val : " << it->second << std::endl;

		// it++;
		// std::cout << "============================" << std::endl;
		// std::cout << "addr : " << &*it << std::endl;
		// std::cout << "val : " << it->first << std::endl;
		// std::cout << "val : " << it->second << std::endl;

		// it++;
		// std::cout << "============================" << std::endl;
		// std::cout << "addr : " << &*it << std::endl;
		// std::cout << "val : " << it->first << std::endl;
		// std::cout << "val : " << it->second << std::endl;

		// it = testmap.end();
		// std::cout << "============================" << std::endl;
		// std::cout << "addr : " << &*it << std::endl;
		// std::cout << "val : " << it->first << std::endl;
		// std::cout << "val : " << it->second << std::endl;

		// it++;
		// std::cout << "============================" << std::endl;
		// std::cout << "addr : " << &*it << std::endl;
		// std::cout << "val : " << it->first << std::endl;
		// std::cout << "val : " << it->second << std::end

	}
	catch (...)
	{
		std::cerr << "err" << std::endl;
	}
}