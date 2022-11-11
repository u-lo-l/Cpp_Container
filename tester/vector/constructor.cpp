#include "../container_tester.hpp"
#include <vector>
#include "../../include/ft_vector.hpp"

int main()
{
	value_creator<TYPE> val_creator;

	TESTING_NAMESPACE::vector<TYPE> v_default;
	printContainer("default constructor", v_default);

	TESTING_NAMESPACE::vector<TYPE> v_fill(5, val_creator(42));
	printContainer("fill constructor", v_fill);

	TESTING_NAMESPACE::vector<TYPE>::iterator it, ite;
	it = v_fill.begin();
	ite = v_fill.end();

	for (int i = 0; it != ite; ++it)
		*it = val_creator(++i * 5);
	it = v_fill.begin();
	TESTING_NAMESPACE::vector<TYPE> vct_range(it, --(--ite));
	printContainer("range constructor", v_fill);

	for (int i = 0; it != ite; ++it)
		*it = val_creator(++i * 7);
	it = v_fill.begin();
	TESTING_NAMESPACE::vector<TYPE> vct_copy(v_fill);
	vct_copy.push_back(val_creator(42));
	vct_copy.push_back(val_creator(21));
	printContainer("copy constructor", vct_copy);

	return (0);
}

