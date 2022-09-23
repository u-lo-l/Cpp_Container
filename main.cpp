#include <iostream>
#include "ft_vector.hpp"
#include "ft_iterator.hpp"
#include "ft_vector_iterator.hpp"
#include "ft_is_integral.hpp"
#include "ft_enable_if.hpp"

#include <vector>

void vector_test();

void vector_iterator_test();

void is_integral_test();

void enable_if_test();

int main()
{
	try
	{
		vector_test();
		// vector_iterator_test();
		// is_integral_test();
		// enable_if_test();
	}
	catch ( const std::exception & e )
	{
		std::cout << std::endl;
		std::cerr << "\033[0;31m" << e.what() << "\033[0m" << std::endl;
	}
	// system("leaks test");
}

void vector_iterator_test()
{
	int * ptr1 = new int(1);
	int * ptr2 = new int(2);
	std::cout << "ptr : " << ptr1 << std::endl << "ptr2 : " << ptr2 << std::endl;
	std::cout << *ptr1 << std::endl << *ptr2 << std::endl;
	std::cout << ((ptr1 == ptr2) ? "SAME" : "NOT SAME") << std::endl;
	std::cout << "dist : " << ft::distance(ptr1, ptr2) << std::endl;
	std::cout << (ptr2 - ptr1) << std::endl;


	ft::vectorIterator<int> i1(ptr1);
	ft::vectorIterator<int> i2(ptr2);
	ft::vectorIterator<int> i3 = i1;
	std::cout << "i1 : " << i1.getBase() << std::endl;
	std::cout << "i2 : " << i2.getBase() << std::endl;
	std::cout << "i3 : " << i3.getBase() << std::endl;
	std::cout << *i1 << std::endl << *i2 << std::endl << *i3 << std::endl;
	i3 = i2 - 4;
	std::cout << "i1 : " << i1.getBase() << std::endl;
	std::cout << "i2 : " << i2.getBase() << std::endl;
	std::cout << "i3 : " << i3.getBase() << std::endl;
	std::cout << *i1 << std::endl << *i2 << std::endl << *i3 << std::endl;
	std::cout << ((i1 == i2) ? "SAME" : "NOT SAME") << std::endl;
	std::cout << "dist : " << ft::distance(i1, i2) << std::endl;
	std::cout << "dist : " << i2 - i1 << std::endl;
	std::cout << (i1.getBase() + 4) << std::endl;

	delete ptr1;
	delete ptr2;
}

void vector_test()
{
	ft::vector<int> v(4);

	v.push_back(1);
	v.push_back(1);
	v.push_back(1);
	v.push_back(1);
	// v.reserve(5);

	std::cout << "size : " << v.size() << std::endl;
	std::cout << "capacity : " << v.capacity() << std::endl;
	std::cout << "max_size : " << v.max_size() << std::endl;
	std::cout << "begin() : " << (*v.begin()) << std::endl;
	std::cout << "end() : " << (*v.end()) << std::endl;
	std::cout << "diff : " << ft::distance(v.begin(), v.end()) << std::endl;
	for (int i = 0 ; i < 10 ; i++)
		std::cout << v.at(i) << " ";
	std::cout << std::endl;

	// std::vector<int> array(4);

	// array.push_back(1);


	// std::cout << "size : " << array.size() << std::endl;
	// std::cout << "capacity : " << array.capacity() << std::endl;
	// std::cout << "max_size : " << array.max_size() << std::endl;
	// for (int i = 0 ; i < 10 ; i++)
	// 	std::cout << array[i] << " ";
	// std::cout << std::endl;
}

void is_integral_test()
{
	std::cout << std::boolalpha;
	std::cout << "\033[3m" << "For fundamental integral types" << "\033[0m" << std::endl;
	std::cout << "bool : " << ft::is_integral<bool>::value << std::endl;
	std::cout << "char : " << ft::is_integral<char>::value << std::endl;
	std::cout << "wchar_t : " << ft::is_integral<wchar_t>::value << std::endl;
	std::cout << "signed char : " << ft::is_integral<signed char>::value << std::endl;
	std::cout << "short int : " << ft::is_integral<short int>::value << std::endl;
	std::cout << "int : " << ft::is_integral<int>::value << std::endl;
	std::cout << "long int : " << ft::is_integral<long int>::value << std::endl;
	std::cout << "long long int : " << ft::is_integral<long long int>::value << std::endl;
	std::cout << "unsigned char : " << ft::is_integral<unsigned char>::value << std::endl;
	std::cout << "unsigned short int: " << ft::is_integral<unsigned short int>::value << std::endl;
	std::cout << "unsigned int : " << ft::is_integral<unsigned int>::value << std::endl;
	std::cout << "unsigned long int : " << ft::is_integral<unsigned long int>::value << std::endl;
	std::cout << "unsigned long long int : " << ft::is_integral<unsigned long long int>::value << std::endl;
	std::cout << std::endl;
	std::cout << "\033[3m" << "For non integral types" << "\033[0m" << std::endl;
	std::cout << "float : " << ft::is_integral<float>::value << std::endl;
	std::cout << "double : " << ft::is_integral<double>::value << std::endl;
	std::cout << std::noboolalpha;
}

template <class T>
typename ft::enable_if<ft::is_integral<T>::value,bool>::type
is_odd (T i) {return bool(i%2);}

// 2. the second template argument is only valid if T is an integral type:
// template < class T,
// 			class = typename ft::enable_if<ft::is_integral<T>::value>::type>
// bool is_even (T i) {return !bool(i%2);}

void enable_if_test()
{
	short int i = 1;	// code does not compile if type of i is not integral

	std::cout << std::boolalpha;
	std::cout << "i is odd: " << is_odd(i) << std::endl;
	// std::cout << "i is even: " << is_even(i) << std::endl;
}