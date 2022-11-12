#include "../container_tester.hpp"
#include <vector>
#include "../../include/ft_vector.hpp"

void iterator_basic_test(int);
void const_iterator_basic_test(int);
void iterator_arrow_test(int);
void const_iterator_arrow_test(int);
void both_iterator_relational_ops(int);

int main(void)
{
	iterator_basic_test();
	const_iterator_basic_test();
	iterator_arrow_test();
	const_iterator_arrow_test();
	both_iterator_relational_ops();
	return (0);
}

void iterator_basic_test(int print_content = true)
{
	const int SIZE = 10;
	value_creator<TYPE> val_creator;

	TESTING_NAMESPACE::vector<TYPE> vct(SIZE);
	TESTING_NAMESPACE::vector<TYPE>::iterator		it = vct.begin();
	TESTING_NAMESPACE::vector<TYPE>::const_iterator	ite = vct.begin();

	for (int i = 0 ; i < SIZE ; i++)
		it[i] = val_creator(i * (SIZE - i));
	printContainer("operator []", vct, print_content);

	if (print_content) std::cout << "operator +" << std::endl;

	it = it + (SIZE / 2);
	if (print_content)
		std::cout << "it + " << (SIZE / 2) << " : " << *it << std::endl;

	it = it - (SIZE / 2);
	if (print_content)
		std::cout << "it - " << (SIZE / 2) << " : " << *it << std::endl;
	
	it += (SIZE / 2);
	if (print_content)
		std::cout << "it += " << (SIZE / 2) << " : " << *it << std::endl;
	
	it -= (SIZE / 2);
	if (print_content)
		std::cout << "it -= " << (SIZE / 2) << " : " << *it << std::endl;
	
	it = 1 + it;
	if (print_content)
		std::cout << "1 + val : " << *it << std::endl;
}

void const_iterator_basic_test(int print_content = true)
{
	const int SIZE = 10;
	value_creator<TYPE> val_creator;

	TESTING_NAMESPACE::vector<TYPE> vct(SIZE);
	TESTING_NAMESPACE::vector<TYPE>::iterator		it = vct.begin();
	TESTING_NAMESPACE::vector<TYPE>::const_iterator	c_it;
	
	for (int i = 0 ; i < SIZE ; i++)
		it[i] = val_creator(i * (SIZE - i));
	printContainer("operator []", vct, print_content);

	c_it = (it += (SIZE / 2));
	if (print_content)
		std::cout << "cit : it += " << (SIZE / 2) << " : " << *c_it << std::endl;
	
	c_it = (it -= (SIZE / 2));
	if (print_content)
		std::cout << "cit : it -= " << (SIZE / 2) << " : " << *c_it << std::endl;
}

void iterator_arrow_test(int print_content = true)
{
	const int SIZE = 10;
	value_creator<TYPE> val_creator;

	TESTING_NAMESPACE::vector<TYPE> vct(SIZE);
	TESTING_NAMESPACE::vector<TYPE>::iterator		it = vct.begin();
	TESTING_NAMESPACE::vector<TYPE>::const_iterator	 ite = vct.begin();

	for (int i = 0 ; i < SIZE ; i++)
		it[i] = val_creator(i * (SIZE - i));
	
}
