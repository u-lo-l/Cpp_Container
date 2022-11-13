#ifndef STACK_FUNCTOR
# define STACK_FUNCTOR
# include <iostream>
# include <vector>
# include <stack>
# include <deque>
# include <list>
# include "../include/ft_stack.hpp"
# include "../include/ft_pair.hpp"
# include "container_tester.hpp"

template<class Stck, class _Tp>
class StackTestFunctor
{
private : 
	const int			_count;
	Stck				_stack;
	value_creator<_Tp>	_val;
	std::list<_Tp>		_list;

	void				(StackTestFunctor::*_tester[2])(void);
	std::string			_tester_name[2];

	void _time_check(int index);
	void _print_info(const Stck & v);
	void _print_info();

	void _push();
	void _pop();
public :
	StackTestFunctor()
	: _count(100000), _stack(Stck()), _val(value_creator<_Tp>()), _list(std::list<_Tp>())
	{
		for (int i = 0 ; i < _count ; i++)
			_list.push_back(_val(i));
		_tester[0] = &StackTestFunctor::_push;
		_tester[1] = &StackTestFunctor::_pop;

		_tester_name[0] = "\n\t[push      tester]     ";
		_tester_name[1] = "\n\t[pop       tester]     ";
	}
	~StackTestFunctor() {}
	void operator() (void)
	{
		for (int i = 0 ; i < 2 ; i++)
			this->_time_check(i);
	}
};

template<class S ,class T>
void StackTestFunctor<S, T>::_time_check(int index)
{
	clock_t start, finish;
	std::cout << _tester_name[index] << std::endl;
	start = clock();
	(this->*_tester[index])();
	finish = clock();
	// std::cout.precision(3);
	std::cout << "\t||time     : "<<std::setw(9) << std::setfill('_') << ((double)(finish - start) / CLOCKS_PER_SEC * 1000) << "ms" << std::endl;
}

template<class S ,class T>
void StackTestFunctor<S, T>::_print_info(const S & s)
{
	std::cout << "\t||size     : " << s.size() << std::endl;
}

template<class S ,class T>
void StackTestFunctor<S, T>::_print_info()
{
	this->_print_info(this->_stack);
}

template<class S ,class T>
void StackTestFunctor<S, T>::_push()
{
	std::cout << "before";
	this->_print_info();
	for (int i = 0 ; i < _count ; i++)
		this->_stack.push(_val(i));
	std::cout << "\nafter";
	this->_print_info();
}

template<class S ,class T>
void StackTestFunctor<S, T>::_pop()
{
	std::cout << "before";
	this->_print_info();
	while (this->_stack.size() > 0)
		this->_stack.pop();
	std::cout << "\nafter";
	this->_print_info();
}



#endif
