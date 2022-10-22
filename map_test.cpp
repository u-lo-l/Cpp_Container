#include <map>
#include <iostream>
int main()
{
	std::map<int, std::string> testmap;

	try
	{
		testmap.insert(std::make_pair(1, "string1"));
		testmap.insert(std::make_pair(2, "string2"));
		std::map<int, std::string>::iterator it = testmap.end() ;
		it--;
		std::cout << (it)->first << std::endl;
		std::cout << (it)->second << std::endl;
		std::cout << &(*it) << std::endl;
		it--;
		std::cout << (it)->first << std::endl;
		std::cout << (it)->second << std::endl;
		std::cout << &(*it) << std::endl;
		it--;
		std::cout << (it)->first << std::endl;
		std::cout << (it)->second << std::endl;
		std::cout << &(*it) << std::endl;
	}
	catch (...)
	{
		std::cerr << "err" << std::endl;
	}
}