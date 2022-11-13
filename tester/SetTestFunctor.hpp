#ifndef SET_FUNCTOR
# define SET_FUNCTOR
# include <iostream>
# include <list>
# include <set>
# include <utility>
# include "../include/ft_set.hpp"
# include "../include/ft_pair.hpp"
# include "container_tester.hpp"

template<class Set, class _Tp>
class SetTestFunctor
{
private : 
	const int			_num;
	Set					_set;
	value_creator<_Tp>	_val;
	std::list<_Tp>  	_list;

	void				(SetTestFunctor::*_tester[9])(void);
	std::string			_tester_name[9];

	void _time_check(int index);
	void _print_info(const Set & v);
	void _print_info();

    void _insert();
    void _erase();
    void _swap();
    void _clear();
    void _find();
    void _count();
    void _lower_bound();
    void _upper_bound();
    void _equal_range();
public :
	SetTestFunctor()
	: _num(1000), _set(Set()), _val(value_creator<_Tp>()), _list(std::list<_Tp>())
	{
		for (int i = 0 ; i < _num ; i++)
		{
			this->_list.push_back(_val(i));
		}

		_tester[0] = & SetTestFunctor::_insert;
		_tester[1] = & SetTestFunctor::_erase;
		_tester[2] = & SetTestFunctor::_swap;
		_tester[3] = & SetTestFunctor::_clear;
		_tester[4] = & SetTestFunctor::_find;
		_tester[5] = & SetTestFunctor::_count;
		_tester[6] = & SetTestFunctor::_lower_bound;
		_tester[7] = & SetTestFunctor::_upper_bound;
		_tester[8] = & SetTestFunctor::_equal_range;

		_tester_name[0] = "\n\t[insert    tester]     ";
		_tester_name[1] = "\n\t[erase     tester]     ";
		_tester_name[2] = "\n\t[swap      tester]     ";
		_tester_name[3] = "\n\t[clear     tester]     ";
		_tester_name[4] = "\n\t[find      tester]     ";
		_tester_name[5] = "\n\t[count     tester]     ";
		_tester_name[6] = "\n\t[l_bound   tester]     ";
		_tester_name[7] = "\n\t[u_bound   tester]     ";
		_tester_name[8] = "\n\t[range     tester]     ";
	}
	~SetTestFunctor() {}
	void operator() (void)
	{
		for (int i = 0 ; i < 9 ; i++)
			this->_time_check(i);
	}
};

template<class S ,class T>
void SetTestFunctor<S, T>::_time_check(int index)
{
	clock_t start, finish;
	std::cout << _tester_name[index] << std::endl;
	start = clock();
	(this->*_tester[index])();
	finish = clock();
	// std::cout.precision(3);
	std::cout << "\t||time     : " <<std::setw(9) << std::setfill('_')  << ((double)(finish - start) / CLOCKS_PER_SEC * 1000) << "ms" << std::endl;
}

template<class S ,class T>
void SetTestFunctor<S, T>::_print_info(const S & m)
{
	std::cout << "\t||size     : " << m.size() << std::endl;
	std::cout << "\t||max_size : " << m.max_size() << std::endl;
}

template<class S ,class T>
void SetTestFunctor<S, T>::_print_info()
{
	this->_print_info(this->_set);
}

template<class S ,class T>
void SetTestFunctor<S, T>::_insert()
{
	this->_set.clear();
	std::cout << "before";
	this->_print_info();

	this->_set.insert(_list.begin(), _list.end());

	std::cout << "\nafter";
	this->_print_info();
	typename S::iterator it = this->_set.begin();
	std::cout << std::endl;

}

template<class S ,class T>
void SetTestFunctor<S, T>::_erase()
{
	std::cout << "\t<case1>" << std::endl;
	std::cout << "before";
	this->_print_info();
	for (int i = 0 ; i < _num / 5 ; i++)
		this->_set.erase(_set.begin());
	std::cout << "\nafter";
	this->_print_info();

	std::cout << "\t<case2>" << std::endl;
	std::cout << "before";
	this->_print_info();
	for (int i = 0 ; i < _num / 5 ; i++)
		this->_set.erase(--_set.end());
	std::cout << "\nafter";
	this->_print_info();

	std::cout << "\t<case3>" << std::endl;
	std::cout << "before";
	this->_print_info();
	for (int i = 0 ; i < _num / 10 ; i++)
		this->_set.erase(_set.begin());
	std::cout << "\nafter";
	this->_print_info();

	std::cout << "\t<case4>" << std::endl;
	std::cout << "before";
	this->_print_info();
	for (int i = 0 ; i < _num / 10 ; i++)
		this->_set.erase(--_set.end());
	std::cout << "\nafter";
	this->_print_info();

	std::cout << "\t<case5>" << std::endl;
	std::cout << "before";
	this->_print_info();
	this->_set.erase(_set.begin(), _set.end());
	std::cout << "\nafter";
	this->_print_info();
}
	
template<class S ,class T>
void SetTestFunctor<S, T>::_swap()
{
	S __temp_set(++_list.begin(), --_list.end());
	std::cout << "before";
	this->_print_info();
	std::cout << "temp";
	this->_print_info(__temp_set);

	this->_set.swap(__temp_set);

	std::cout << "\nafter";
	this->_print_info();
	std::cout << "temp";
	this->_print_info(__temp_set);
}

template<class S ,class T>
void SetTestFunctor<S, T>::_clear()
{
	std::cout << "before";
	this->_print_info();
	this->_set.clear();
	std::cout << "\nafter";
	this->_print_info();
}

template<class S ,class T>
void SetTestFunctor<S, T>::_find()
{
	this->_set.insert(_list.begin(), _list.end());
	typename S::iterator res = (this->_set.find(_val(_num/2)));
	if (res == _set.end())
		std::cout << "\tres : " << "end()" << std::endl;
	else
		std::cout << "\tres : " << *res << std::endl;
	res = (this->_set.find(_val(-_num)));
	if (res == _set.end())
		std::cout << "\tres : " << "end()" << std::endl;
	else
		std::cout << "\tres : " << *res << std::endl;
}

template<class S ,class T>
void SetTestFunctor<S, T>::_count()
{
	std::cout << "\tres : " << (this->_set.count(_val(_num/2))) << std::endl;
	std::cout << "\tres : " << (this->_set.count(_val(-_num))) << std::endl;
}

template<class S ,class T>
void SetTestFunctor<S, T>::_lower_bound()
{
	typename S::iterator l_bound = _set.lower_bound(_val(_num/2));
	if (l_bound == this->_set.end())
		std::cout << "\tlower bound " << "end()" << std::endl;
	else
		std::cout << "\tlower bound " << *l_bound << std::endl;
}

template<class S ,class T>
void SetTestFunctor<S, T>::_upper_bound()
{
	typename S::iterator u_bound = _set.upper_bound(_val(_num/2));
	if (u_bound == this->_set.end())
		std::cout << "\tupper bound " << "end()" << std::endl;
	else
		std::cout << "\tupper bound " << *u_bound << std::endl;
}

template<class S ,class T>
void SetTestFunctor<S, T>::_equal_range()
{
	TESTING_NAMESPACE::pair<typename S::iterator, typename S::iterator> _range;
	_range = _set.equal_range(_val(_num/2));

	if (_range.first == this->_set.end())
		std::cout << "\tlower bound " << "end()" << std::endl;
	else
		std::cout << "\tlower bound " << *_range.first << std::endl;

	if (_range.second == this->_set.end())
		std::cout << "\tupper bound " << "end()" << std::endl;
	else
		std::cout << "\tupper bound " << *_range.second << std::endl;
}

#endif
