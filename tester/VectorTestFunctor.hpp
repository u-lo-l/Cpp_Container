#ifndef VECTOR_FUNCTOR
# define VECTOR_FUNCTOR
# include <iostream>
# include <vector>
# include "../include/ft_vector.hpp"
# include "../include/ft_pair.hpp"
# include "container_tester.hpp"

template<class Vec, class _Tp>
class VectorTestFunctor
{
private : 
	const int			_count;;
	Vec					_vector;
	value_creator<_Tp>	_val;
	std::list<_Tp>		_list;

	void				(VectorTestFunctor::*_tester[7])(void);
	std::string			_tester_name[7];

	void _time_check(int index);
	void _print_info(const Vec & v);
	void _print_info();

	void _push_back();
	void _pop_back();
	void _assign();
	void _insert();
	void _erase();
	void _swap();
	void _clear();
public :
	VectorTestFunctor()
	: _count(100000), _vector(Vec()), _val(value_creator<_Tp>()), _list(std::list<_Tp>())
	{
		for (int i = 0 ; i < _count ; i++)
			_list.push_back(_val(i));
		_tester[0] = &VectorTestFunctor::_push_back;
		_tester[1] = &VectorTestFunctor::_pop_back;
		_tester[2] = &VectorTestFunctor::_assign;
		_tester[3] = &VectorTestFunctor::_insert;
		_tester[4] = &VectorTestFunctor::_erase;
		_tester[5] = &VectorTestFunctor::_swap;
		_tester[6] = &VectorTestFunctor::_clear;

		_tester_name[0] = "\n\t[push_back tester]     ";
		_tester_name[1] = "\n\t[pop_back  tester]     ";
		_tester_name[2] = "\n\t[assign    tester]     ";
		_tester_name[3] = "\n\t[insert    tester]     ";
		_tester_name[4] = "\n\t[erase     tester]     ";
		_tester_name[5] = "\n\t[swap      tester]     ";
		_tester_name[6] = "\n\t[clear     tester]     ";
	}
	~VectorTestFunctor() {}
	void operator() (void)
	{
		for (int i = 0 ;i < 7 ; i++)
			this->_time_check(i);
	}
};

template<class V ,class T>
void VectorTestFunctor<V, T>::_time_check(int index)
{
	clock_t start, finish;
	std::cout << _tester_name[index] << std::endl;
	start = clock();
	(this->*_tester[index])();
	finish = clock();
	// std::cout.precision(3);
	std::cout << "\t||time     : "<<std::setw(9) << std::setfill('_') << ((double)(finish - start) / CLOCKS_PER_SEC * 1000) << "ms" << std::endl;
}

template<class V ,class T>
void VectorTestFunctor<V, T>::_print_info(const V & v)
{
	std::cout << "\t||size     : " << v.size() << std::endl;
	std::cout << "\t||capacity : " << v.capacity() << std::endl;
	std::cout << "\t||max_size : " << v.max_size() << std::endl;
}

template<class V ,class T>
void VectorTestFunctor<V, T>::_print_info()
{
	this->_print_info(this->_vector);
}

template<class V ,class T>
void VectorTestFunctor<V, T>::_push_back()
{
	this->_vector.clear();
	std::cout << "before";
	this->_print_info();
	for (int i = 0 ; i < _count ; i++)
		this->_vector.push_back(_val(i));
	std::cout << "\nafter";
	this->_print_info();
}

template<class V ,class T>
void VectorTestFunctor<V, T>::_pop_back()
{
	std::cout << "before";
	this->_print_info();
	while (this->_vector.size() > 0)
		this->_vector.pop_back();
	std::cout << "\nafter";
	this->_print_info();
}

template<class V ,class T>
void VectorTestFunctor<V, T>::_assign()
{
	this->_vector.clear();
	std::cout << "\t<case1>"<< std::endl;
	std::cout << "before";
	this->_print_info();
	this->_vector.assign(_list.begin(), _list.end());
	std::cout << "\nafter";
	this->_print_info();
	
	std::cout << "\t<case2>" << std::endl;
	this->_vector.clear();
	std::cout << "before";
	this->_print_info();
	this->_vector.assign(4242, _val(2));
	std::cout << "\nafter";
	this->_print_info();
}

template<class V ,class T>
void VectorTestFunctor<V, T>::_insert()
{
	this->_vector.clear();
	std::cout << "\t<case1>"<< std::endl;
	std::cout << "before";
	this->_print_info();
	this->_vector.insert(_vector.end(), 2424, _val(1000));
	std::cout << "\nafter";
	this->_print_info();

	std::cout << "\t<case2>" << std::endl;
	std::cout << "before";
	this->_print_info();
	this->_vector.insert(_vector.begin() + 1000 , _list.begin(), _list.end());
	std::cout << "\nafter";
	this->_print_info();
}

template<class V ,class T>
void VectorTestFunctor<V, T>::_erase()
{
	std::cout << "before";
	this->_print_info();
	this->_vector.erase(_vector.begin(), _vector.end());
	std::cout << "\nafter";
	this->_print_info();
}

template<class V ,class T>
void VectorTestFunctor<V, T>::_swap()
{
	V __temp_vector(_list.begin(), _list.end());
	std::cout << "before";
	this->_print_info();
	std::cout << "temp";
	this->_print_info(__temp_vector);

	this->_vector.swap(__temp_vector);
	std::cout << "\nafter";
	this->_print_info();
	std::cout << "temp";
	this->_print_info(__temp_vector);
}

template<class V ,class T>
void VectorTestFunctor<V, T>::_clear()
{
	std::cout << "before";
	this->_print_info();
	this->_vector.clear();
	std::cout << "\nafter";
	this->_print_info();
}

#endif
