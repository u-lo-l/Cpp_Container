#include <iostream>
#include "ft_map.hpp"

int main()
{
	ft::map<int, int> a;
	// a.insert(ft::make_pair(1,1));
	
	a.getTree().printTree();
}