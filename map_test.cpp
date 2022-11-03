#include <map>
#include <vector>
#include <iostream>
int main()
{
	std::map<int, std::string> testmap;

	try
	{
		std::pair<std::map<int, std::string>::iterator, bool> p;
		p = testmap.insert(std::make_pair(1, "string1"));
		std::cout << &(*(p.first)) << " | " << p.second << std::endl;
		p = testmap.insert(std::make_pair(2, "string2"));
		std::cout << &(*(p.first)) << " | " << p.second << std::endl;
		p = testmap.insert(std::make_pair(3, "string3"));
		std::cout << &(*(p.first)) << " | " << p.second << std::endl;
		p = testmap.insert(std::make_pair(3, "string3"));
		std::cout << &(*(p.first)) << " | " << p.second << std::endl;

		// std::map<int, std::string>::iterator it = testmap.begin();
		// std::cout << "============================" << std::endl;
		// std::cout << "addr : " << &*it << std::endl;
		// std::cout << "key : " << it->first << std::endl;
		// std::cout << "val : " << it->second << std::endl;

		// it++;
		// std::cout << "============================" << std::endl;
		// std::cout << "addr : " << &*it << std::endl;
		// std::cout << "key : " << it->first << std::endl;
		// std::cout << "val : " << it->second << std::endl;

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