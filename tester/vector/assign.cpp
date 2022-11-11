#include "../container_tester.hpp"
#include <vector>
#include "../../include/ft_vector.hpp"

int main(void)
{
	value_creator<TYPE> val_creator;

	TESTING_NAMESPACE::vector<TYPE> vct(7);
	TESTING_NAMESPACE::vector<TYPE> vct_two(4);
	TESTING_NAMESPACE::vector<TYPE> vct_three;
	TESTING_NAMESPACE::vector<TYPE> vct_four;

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = val_creator((vct.size() - i) * 3);
	for (unsigned long int i = 0; i < vct_two.size(); ++i)
		vct_two[i] = val_creator((vct_two.size() - i) * 5);
	printContainer("<bef> vct1", vct);
	printContainer("<bef> vct2", vct_two);
	printContainer("<bef> vct3", vct_three);
	printContainer("<bef> vct4", vct_four);

	vct_three.assign(vct.begin(), vct.end());
	vct.assign(vct_two.begin(), vct_two.end());
	vct_two.assign(2, val_creator(42));
	vct_four.assign(4, val_creator(21));

	printContainer("<aft> vct1", vct);
	printContainer("<aft> vct2", vct_two);
	printContainer("<aft> vct3", vct_three);
	printContainer("<aft> vct4", vct_four);

	vct.assign(5, val_creator(53));
	vct_two.assign(vct_three.begin(), vct_three.begin() + 3);

	std::cout << "### assign() on enough capacity and low size: ###" << std::endl;
	printContainer("vec1", vct);
	printContainer("vec2", vct_two);

	return (0);
}
