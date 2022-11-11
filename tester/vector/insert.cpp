#include "../container_tester.hpp"
#include <vector>
#include "../../include/ft_vector.hpp"

int main(void)
{
	value_creator<TYPE> val_creator;

	/* insert1 */
	
	TESTING_NAMESPACE::vector<TYPE> vct(10);
	TESTING_NAMESPACE::vector<TYPE> vct2;
	TESTING_NAMESPACE::vector<TYPE> vct3;

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = val_creator((vct.size() - i) * 3);
	printContainer("vct1_init", vct);

	vct2.insert(vct2.end(), val_creator(42));
	vct2.insert(vct2.begin(), 2, val_creator(21));
	printContainer("vct2_insert1", vct2);

	vct2.insert(vct2.end() - 2, val_creator(42));
	printContainer("vct2_insert2", vct2);

	vct2.insert(vct2.end(), 2, val_creator(84));
	printContainer("vct2_insert3", vct2);

	vct2.resize(4);
	printContainer("vct2_resize", vct2);

	vct2.insert(vct2.begin() + 2, vct.begin(), vct.end());
	vct.clear();
	printContainer("vct2_insert", vct2);

	printContainer("vct1_clear", vct);

	for (int i = 0; i < 5; ++i)
		vct3.insert(vct3.end(), val_creator(i));
	vct3.insert(vct3.begin() + 1, 2, val_creator(111));
	printContainer("1", vct3);

	/* insert2 */

	vct.reserve(5);
 	vct2.reserve(0);
	printContainer("vct1_reserve", vct);
	printContainer("vct2_reserve", vct2);
	const int cut = 3;

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = val_creator((vct.size() - i) * 7);
	printContainer("2", vct);

	vct2.insert(vct2.begin(), vct.begin(), vct.begin() + cut);
	printContainer("3", vct2);
	vct2.insert(vct2.begin(), vct.begin() + cut, vct.end());
	printContainer("4", vct2);
	vct2.insert(vct2.end(), vct.begin(), vct.begin() + cut);
	printContainer("5", vct2);

	std::cout << "insert return:" << std::endl;

	std::cout << *vct2.insert(vct2.end(), val_creator(42)) << std::endl;
	std::cout << *vct2.insert(vct2.begin() + 5, val_creator(84)) << std::endl;
	std::cout << "----------------------------------------" << std::endl;

	printContainer("6", vct2);
	
	return (0);
}
