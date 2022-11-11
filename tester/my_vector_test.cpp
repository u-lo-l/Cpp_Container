#include "./container_tester.hpp"
#include "../include/ft_vector.hpp"
#include <vector>
#include <iostream>

void creator_test();

void test_basic();
void test_assign();
void test_iterators();
void test_sizes();
void test_reserve();

int main()
{
	value_creator<TYPE> val_creator;

	std::cout << "################ Test Vector ################" << std::endl;
	test_basic();
	test_assign();
	test_iterators();
	test_sizes();
	test_reserve();

	return (0);
}

void creator_test()
{
	value_creator<int>								int_creator;
	value_creator<float>							float_creator;
	value_creator<std::string>						string_creator;
	value_creator<std::pair<float, int> > 			pair_creator;
	value_creator<Foo<float> >						foo_creator;


	for (unsigned int i = 0; i < 20 ; i++)
		std::cout << int_creator(i) << std::endl;
	std::cout << "============================================" << std::endl;

	for (int i = 0; i < 20 ; i++)
		std::cout << float_creator(i) << std::endl;
	std::cout << "============================================" << std::endl;

	for (int i = 0; i < 20 ; i++)
		std::cout << string_creator(i) << std::endl;
	std::cout << "============================================" << std::endl;

	for (int i = 0; i < 20 ; i++)
		std::cout << foo_creator(i) << std::endl;
	std::cout << "============================================" << std::endl;

	for (int i = 0; i < 20 ; i++)
		std::cout << pair_creator(i) << std::endl;
	std::cout << "============================================" << std::endl;
}

void test_basic()
{
	std::cout << "===== default | fill | range | copy constructor " << std::endl;
	TESTING_NAMESPACE::vector<TYPE> v_default;
	TESTING_NAMESPACE::vector<TYPE> v_fill(5, 42);
	TESTING_NAMESPACE::vector<TYPE> v_range(v_fill.begin(), --(v_fill.end()));
	TESTING_NAMESPACE::vector<TYPE> v_copy(v_range);
	std::cout << "\n################################################" << std::endl;
}

void test_assign()
{
	std::cout << "===== assign() | operator= " << std::endl;
	TESTING_NAMESPACE::vector<TYPE> v_fill(5, 42);
	TESTING_NAMESPACE::vector<TYPE> v_assign(4, 21);
	printContainer(v_assign);
	v_assign = v_fill;
	printContainer(v_assign);
	std::cout << "\n################################################" << std::endl;
}

void test_iterators()
{

}
void test_sizes()
{

}
void test_reserve()
{

}

void test_relational_ops()
{
	std::cout << "===== relational operators =====" << std::endl;
	TESTING_NAMESPACE::vector<TYPE> v_lhs(5);
	TESTING_NAMESPACE::vector<TYPE> v_rhs;
	for (unsigned int i = 0; i < v_lhs.size(); ++i)
		v_lhs[i] = (i * 3) + 2;

	v_rhs.insert(v_rhs.begin(), v_lhs.begin(), v_lhs.end());
	printContainer(v_lhs);
	printContainer(v_rhs);

	std::cout << "same vector..." << std::endl;
	std::cout << "operator==: " << ( (v_lhs == v_rhs) ? "OK" : "KO") << std::endl;
	std::cout << "operator!=: " << (!(v_lhs != v_rhs) ? "OK" : "KO") << std::endl;
	std::cout << "operator<:  " << (!(v_lhs < v_rhs)  ? "OK" : "KO") << std::endl;
	std::cout << "operator<=: " << ( (v_lhs <= v_rhs) ? "OK" : "KO") << std::endl;
	std::cout << "operator>:  " << (!(v_lhs > v_rhs)  ? "OK" : "KO") << std::endl;
	std::cout << "operator>=: " << ( (v_lhs >= v_rhs) ? "OK" : "KO") << std::endl;
	std::cout << std::endl;

	std::cout << "different vector..." << std::endl;
	std::cout << "vector_lhs > vector_rhs" << std::endl;
	v_rhs.erase(v_rhs.begin());
	std::cout << "operator==: " << (!(v_lhs == v_rhs) ? "OK" : "KO") << std::endl;
	std::cout << "operator!=: " << ( (v_lhs != v_rhs) ? "OK" : "KO") << std::endl;
	std::cout << "operator<:  " << ( (v_lhs < v_rhs)  ? "OK" : "KO") << std::endl;
	std::cout << "operator<=: " << ( (v_lhs <= v_rhs) ? "OK" : "KO") << std::endl;
	std::cout << "operator>:  " << (!(v_lhs > v_rhs)  ? "OK" : "KO") << std::endl;
	std::cout << "operator>=: " << (!(v_lhs >= v_rhs) ? "OK" : "KO") << std::endl;
	std::cout << "\n################################################" << std::endl;
}