#ifndef ITERATOR_TESTER_HPP
# define ITERATOR_TESTER_HPP
# include "container_tester.hpp"


template<class Cont>
void iterator_basic_test(int print_content = true)
{
	const int SIZE = 10;
	value_creator<TYPE> val_creator;

	Cont cont(SIZE);
	Cont::iterator			it = cont.begin();
	Cont::const_iterator	ite = cont.begin();

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

template<class Cont>
void const_iterator_basic_test(int print_content = true)
{
	const int SIZE = 10;
	value_creator<TYPE> val_creator;

	Cont cont(SIZE);
	Cont::iterator			it = cont.begin();
	Cont::const_iterator	c_it;
	
	for (int i = 0 ; i < SIZE ; i++)
		it[i] = val_creator(i * (SIZE - i));
	printContainer("operator []", vct, print_content);

	c_it = *(it += (SIZE / 2));
	if (print_content)
		std::cout << "cit : it += " << (SIZE / 2) << " : " << *c_it << std::endl;
	
	c_it = *(it -= (SIZE / 2));
	if (print_content)
		std::cout << "cit : it -= " << (SIZE / 2) << " : " << *c_it << std::endl;
}

template<class Cont>
void iterator_arrow_test(int print_content = true)
{
	const int SIZE = 10;
	value_creator<TYPE> val_creator;

	Cont cont(SIZE);
	Cont::iterator			it = cont.begin();
	Cont::const_iterator	ite = cont.begin();

	for (int i = 0 ; i < SIZE ; i++)
		it[i] = val_creator(i * (SIZE - i));
	
}



#endif

