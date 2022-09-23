#include <iostream>
#include <vector>

#include "ft_vector.hpp"

using std::string;

void ft_vector_test();
void std_vector_test();

void print_intvector_info(const string & name, const ft::vector<int> & v)
{
	std::cout << name << std::endl;
	std::cout << "size : " << v.size() << " capacity : " << v.capacity() << std::endl;
	std::cout << "elements : ";
	for (int i = 0 ; i < v.size() ; i++)
		std::cout << "  " << v.at(i);
	std::cout << std::endl;
}

void print_intvector_info(const string & name, const std::vector<int> & v)
{
	std::cout << name << std::endl;
	std::cout << "size : " << v.size() << " capacity : " << v.capacity() << std::endl;
	std::cout << "elements : ";
	for (int i = 0 ; i < v.size() ; i++)
		std::cout << "  " << v.at(i);
	std::cout << std::endl;
}

int main()
{
	std::cout << "\033[1;35m";
	std::cout << "FT_VECTOR CASE";
	std::cout << "\033[0m" << std::endl;
	ft_vector_test();
	std::cout << "\033[1;35m";
	std::cout << "STD_VECTOR CASE";
	std::cout << "\033[0m" << std::endl;
	std_vector_test();
}

void ft_vector_test()
{
	using ft::vector;
	// (constructors)
	//	---> default
	vector<int> myvector1;
	print_intvector_info("myvector1", myvector1);
	//	---> fill
	vector<int> myvector2(4U, 5);
	print_intvector_info("myvector2", myvector2);
	//	---> range
	int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	vector<int> myvector3( &(arr[0]), &(arr[9]));
	print_intvector_info("myvector3", myvector3);
	//	---> copy
	vector<int> myvector4(myvector1);
	print_intvector_info("myvector4", myvector4);
	// operator=
	myvector2 = myvector1;
	print_intvector_info("myvector2", myvector2);
	// begin
	//	---> non const
	std::cout << "begin() " << &*(myvector3.begin()) << std::endl;
	std::cout << "value of begin() " << *(myvector3.begin()) << std::endl;
	//	---> const
	// end
	//	---> non const
	std::cout << "end() " << &*(myvector3.end()) << std::endl;
	std::cout << "value of just before end() " << *(myvector3.end() - 1) << std::endl;
	//	---> const
	// rbegin
	//	---> non const
	std::cout << "rbegin() " << *(myvector3.rbegin()) << std::endl;
	std::cout << "value of right after rbegin() " << *(myvector3.rbegin()) << std::endl;
	//	---> const
	// rend
	//	---> non const
	std::cout << "rend() " << *(myvector3.rend()) << std::endl;
	std::cout << "value of rend() " << *(myvector3.rend()) << std::endl;
	// std::cout << std::boolalpha;
	// std::cout << (myvector1.begin() == myvector1.rend()) << std::endl;
	// std::cout << std::noboolalpha;
	//	---> const
	// size
	std::cout << "myvector3 size : " << myvector3.size() << std::endl;
	// max_size
	std::cout << "myvector3 max_size : " << myvector3.max_size() << std::endl;
	// capcity
	std::cout << "myvector3 capatcity : " << myvector3.capacity() << std::endl;
	// resize
	std::cout << "resize myvector3 to 3" << std::endl;
	myvector3.resize(3);
	print_intvector_info("myvector3", myvector3);
	std::cout << "resize myvector3 to 15" << std::endl;
	myvector3.resize(15);
	print_intvector_info("myvector3", myvector3);
	// empty
	std::cout << std::boolalpha;
	std::cout << "myvector1 is empty ? : " << myvector1.empty() << std::endl;
	std::cout << "myvector3 is empty ? : " << myvector3.empty() << std::endl;
	std::cout << std::noboolalpha;
	// reserve
	std::cout << "myvector3 reserve test" << std::endl;
	try
	{
		print_intvector_info("myvector3", myvector3);
		std::cout << "case 1 : less than current capacity" << std::endl;
		myvector3.reserve(8);
		print_intvector_info("myvector3", myvector3);
		std::cout << "case 2 : greater than current capacity" << std::endl;
		myvector3.reserve(30);
		print_intvector_info("myvector3", myvector3);
		std::cout << "case 3 : greater than max_size" << std::endl;
		myvector3.reserve(myvector3.max_size() + 1);
		print_intvector_info("myvector3", myvector3);
	}
	catch(const std::exception& e)
	{
		std::cerr << "\033[3;31m";
		std::cerr << e.what() << std::endl;
		print_intvector_info("myvector3", myvector3);
		std::cerr << "\033[0m" << std::endl;
	}
	// operator[]
	std::cout << "[] for ";
	print_intvector_info("myvector3", myvector3);
	for (int i = 0 ; i <= myvector3.capacity() ; i++)
		std::cout << myvector3[i] << " ";
	std::cout << std::endl;
	// at
	std::cout << "at for ";
	print_intvector_info("myvector3", myvector3);
	try 
	{
		for (int i = 0 ; i <= myvector3.capacity() ; i++)
			std::cout << myvector3[i] << " ";
		std::cout << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "\033[3;31m";
		std::cerr << e.what();
		std::cerr << "\033[0m" << std::endl;
	}
	// front
	std::cout << "myvector3 front : " << myvector3.front() << std::endl; 
	// back
	std::cout << "myvector3 back : " << myvector3.back() << std::endl; 
	// assign
	std::cout << "myvector3 assign" << std::endl;
	//	---> range
	std::cout << "range" << std::endl;
	int myints[] = {1776,7,4};
	myvector3.assign (myints,myints+3);
	print_intvector_info("myvector3", myvector3);
	//	---> fill
	std::cout << "fill" << std::endl;
	myvector3.assign(7U, 100);
	print_intvector_info("myvector3", myvector3);
	// push_back
	myvector3.push_back(200);
	// pop_back
	myvector3.pop_back();
	// insert
	//	---> single element
	vector<int>::iterator it = myvector3.begin();
	it = myvector3.insert(it, 300);
	print_intvector_info("myvector3", myvector3);
	//	---> fill
	myvector3.insert(it, 2, 123);
	print_intvector_info("myvector3", myvector3);
	//	---> range
	it += 3;
	myvector3.insert(it, myints, myints + 3);
	print_intvector_info("myvector3", myvector3);
	// erase : invalid position or range causes Undefined Behavior
	// ---> position
	myvector3.erase(it);
	print_intvector_info("myvector3", myvector3);
	// ---> range
	myvector3.erase(it, it + 5);
	print_intvector_info("myvector3", myvector3);
	// swap
	std::cout << "swap (member function)" << std::endl;
	print_intvector_info("myvector2", myvector2);
	print_intvector_info("myvector3", myvector3);
	myvector3.swap(myvector2);
	print_intvector_info("myvector2", myvector2);
	print_intvector_info("myvector3", myvector3);
	// clear
	std::cout << "clear myvector2" << std::endl;
	myvector2.clear();
	print_intvector_info("myvector2", myvector2);
	// get_allocator
	// (relational operators)
	// swap
	std::cout << "swap (non member function)" << std::endl;
	myvector1.assign(myints, myints+3);
	print_intvector_info("myvector1", myvector1);
	print_intvector_info("myvector2", myvector2);
	swap(myvector1, myvector2);
	print_intvector_info("myvector1", myvector1);
	print_intvector_info("myvector2", myvector2);
	// (destructor)
}

void std_vector_test()
{
	using std::vector;
	// (constructors)
	//	---> default
	vector<int> myvector1;
	print_intvector_info("myvector1", myvector1);
	//	---> fill
	vector<int> myvector2(4U, 5);
	print_intvector_info("myvector2", myvector2);
	//	---> range
	int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	vector<int> myvector3( &(arr[0]), &(arr[9]));
	print_intvector_info("myvector3", myvector3);
	//	---> copy
	vector<int> myvector4(myvector1);
	print_intvector_info("myvector4", myvector4);
	// operator=
	myvector2 = myvector1;
	print_intvector_info("myvector2", myvector2);
	// begin
	//	---> non const
	std::cout << "begin() " << &*(myvector3.begin()) << std::endl;
	std::cout << "value of begin() " << *(myvector3.begin()) << std::endl;
	//	---> const
	// end
	//	---> non const
	std::cout << "end() " << &*(myvector3.end()) << std::endl;
	std::cout << "value of just before end() " << *(myvector3.end() - 1) << std::endl;
	//	---> const
	// rbegin
	//	---> non const
	std::cout << "rbegin() " << &*(myvector3.rbegin()) << std::endl;
	std::cout << "value of right after rbegin() " << *(myvector3.rbegin()) << std::endl;
	//	---> const
	// rend
	//	---> non const
	std::cout << "rend() " << &*(myvector3.rend()) << std::endl;
	std::cout << "value of rend() " << *(myvector3.rend()) << std::endl;

	//	---> const
	// size
	std::cout << "myvector3 size : " << myvector3.size() << std::endl;
	// max_size
	std::cout << "myvector3 max_size : " << myvector3.max_size() << std::endl;
	// capcity
	std::cout << "myvector3 capatcity : " << myvector3.capacity() << std::endl;
	// resize
	std::cout << "resize myvector3 to 3" << std::endl;
	myvector3.resize(3);
	print_intvector_info("myvector3", myvector3);
	std::cout << "resize myvector3 to 15" << std::endl;
	myvector3.resize(15);
	print_intvector_info("myvector3", myvector3);
	// empty
	std::cout << std::boolalpha;
	std::cout << "myvector1 is empty ? : " << myvector1.empty() << std::endl;
	std::cout << "myvector3 is empty ? : " << myvector3.empty() << std::endl;
	std::cout << std::noboolalpha;
	// reserve
	std::cout << "myvector3 reserve test" << std::endl;
	try
	{
		print_intvector_info("myvector3", myvector3);
		std::cout << "case 1 : less than current capacity" << std::endl;
		myvector3.reserve(8);
		print_intvector_info("myvector3", myvector3);
		std::cout << "case 2 : greater than current capacity" << std::endl;
		myvector3.reserve(30);
		print_intvector_info("myvector3", myvector3);
		std::cout << "case 3 : greater than max_size" << std::endl;
		myvector3.reserve(myvector3.max_size() + 1);
		print_intvector_info("myvector3", myvector3);
	}
	catch(const std::exception& e)
	{
		std::cerr << "\033[3;31m";
		std::cerr << e.what() << std::endl;
		print_intvector_info("myvector3", myvector3);
		std::cerr << "\033[0m" << std::endl;
	}
	// operator[]
	std::cout << "[] for ";
	print_intvector_info("myvector3", myvector3);
	for (int i = 0 ; i <= myvector3.capacity() ; i++)
		std::cout << myvector3[i] << " ";
	std::cout << std::endl;
	// at
	std::cout << "at for ";
	print_intvector_info("myvector3", myvector3);
	try 
	{
		for (int i = 0 ; i <= myvector3.capacity() ; i++)
			std::cout << myvector3[i] << " ";
		std::cout << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "\033[3;31m";
		std::cerr << e.what();
		std::cerr << "\033[0m" << std::endl;
	}
	// front
	std::cout << "myvector3 front : " << myvector3.front() << std::endl; 
	// back
	std::cout << "myvector3 back : " << myvector3.back() << std::endl; 
	// assign
	std::cout << "myvector3 assign" << std::endl;
	//	---> range
	std::cout << "range" << std::endl;
	int myints[] = {1776,7,4};
	myvector3.assign (myints,myints+3);
	print_intvector_info("myvector3", myvector3);
	//	---> fill
	std::cout << "fill" << std::endl;
	myvector3.assign(7U, 100);
	print_intvector_info("myvector3", myvector3);
	// push_back
	myvector3.push_back(200);
	// pop_back
	myvector3.pop_back();
	// insert
	//	---> single element
	vector<int>::iterator it = myvector3.begin();
	it = myvector3.insert(it, 300);
	print_intvector_info("myvector3", myvector3);
	//	---> fill
	myvector3.insert(it, 2, 123);
	print_intvector_info("myvector3", myvector3);
	//	---> range
	it += 3;
	myvector3.insert(it, myints, myints + 3);
	print_intvector_info("myvector3", myvector3);
	// erase : invalid position or range causes Undefined Behavior
	// ---> position
	myvector3.erase(it);
	print_intvector_info("myvector3", myvector3);
	// ---> range
	myvector3.erase(it, it + 5);
	print_intvector_info("myvector3", myvector3);
	// swap
	std::cout << "swap (member function)" << std::endl;
	print_intvector_info("myvector2", myvector2);
	print_intvector_info("myvector3", myvector3);
	myvector3.swap(myvector2);
	print_intvector_info("myvector2", myvector2);
	print_intvector_info("myvector3", myvector3);
	// clear
	std::cout << "clear myvector2" << std::endl;
	myvector2.clear();
	print_intvector_info("myvector2", myvector2);
	// get_allocator
	// (relational operators)
	// swap
	std::cout << "swap (non member function)" << std::endl;
	myvector1.assign(myints, myints+3);
	print_intvector_info("myvector1", myvector1);
	print_intvector_info("myvector2", myvector2);
	swap(myvector1, myvector2);
	print_intvector_info("myvector1", myvector1);
	print_intvector_info("myvector2", myvector2);
	// (destructor)
}
