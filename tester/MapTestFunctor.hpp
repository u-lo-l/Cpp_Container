#ifndef MAP_FUNCTOR
# define MAP_FUNCTOR
# include <iostream>
# include <vector>
# include <stack>
# include <deque>
# include <list>
# include <utility>
# include "../include/ft_map.hpp"
# include "../include/ft_pair.hpp"
# include "container_tester.hpp"

template<class Map, class _Tp>
class MapTestFunctor
{
private : 
	typedef TESTING_NAMESPACE::pair<_Tp, int> _pair_type;
	// typename Map::value_type _pair_type;
	const int				_num;
	Map						_map;
	value_creator<_Tp>		_val;
	std::list<_pair_type>	_list;

	void				(MapTestFunctor::*_tester[9])(void);
	std::string			_tester_name[9];

	void _time_check(int index);
	void _print_info(const Map & v);
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
	MapTestFunctor()
	: _num(10000), _map(Map()), _val(value_creator<_Tp>()), _list(std::list<_pair_type>())
	{
		for (int i = 0 ; i < _num ; i++)
		{
			_pair_type __data = TESTING_NAMESPACE::make_pair(_val(i), i);
			this->_list.push_back(__data);
		}

		_tester[0] = & MapTestFunctor::_insert;
		_tester[1] = & MapTestFunctor::_erase;
		_tester[2] = & MapTestFunctor::_swap;
		_tester[3] = & MapTestFunctor::_clear;
		_tester[4] = & MapTestFunctor::_find;
		_tester[5] = & MapTestFunctor::_count;
		_tester[6] = & MapTestFunctor::_lower_bound;
		_tester[7] = & MapTestFunctor::_upper_bound;
		_tester[8] = & MapTestFunctor::_equal_range;

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
	~MapTestFunctor() {}
	void operator() (void)
	{
		for (int i = 0 ; i < 9 ; i++)
			this->_time_check(i);
	}
};

template<class M ,class T>
void MapTestFunctor<M, T>::_time_check(int index)
{
	clock_t start, finish;
	std::cout << _tester_name[index] << std::endl;
	start = clock();
	(this->*_tester[index])();
	finish = clock();
	std::cout << "\t||time     : " <<std::setw(8) << std::setfill('_') <<(double)(finish - start) << "ms" << std::endl;
}

template<class M ,class T>
void MapTestFunctor<M, T>::_print_info(const M & m)
{
	std::cout << "\t||size     : " << m.size() << std::endl;
	std::cout << "\t||max_size : " << m.max_size() << std::endl;
}

template<class M ,class T>
void MapTestFunctor<M, T>::_print_info()
{
	this->_print_info(this->_map);
}

template<class M ,class T>
void MapTestFunctor<M, T>::_insert()
{
	this->_map.clear();
	std::cout << "before";
	this->_print_info();

	this->_map.insert(_list.begin(), _list.end());

	std::cout << "\nafter";
	this->_print_info();
	typename M::iterator it = this->_map.begin();
	std::cout << std::endl;
}

template<class M ,class T>
void MapTestFunctor<M, T>::_erase()
{
	// std::cout << "\t<case1>" << std::endl;
	// std::cout << "before";
	// this->_print_info();
	// for (int i = 0 ; i < 500 ; i++)
	// 	this->_map.erase(_map.begin());
	// std::cout << "\nafter";
	// this->_print_info();

	std::cout << "\t<case2>" << std::endl;
	std::cout << "before";
	this->_print_info();
	this->_map.erase(_map.begin(), _map.end());
	std::cout << "\nafter";
	this->_print_info();
}

template<class M ,class T>
void MapTestFunctor<M, T>::_swap()
{
	M __temp_map(++_list.begin(), --_list.end());
	std::cout << "before";
	this->_print_info();
	std::cout << "temp";
	this->_print_info(__temp_map);

	this->_map.swap(__temp_map);

	std::cout << "\nafter";
	this->_print_info();
	std::cout << "temp";
	this->_print_info(__temp_map);
}

template<class M ,class T>
void MapTestFunctor<M, T>::_clear()
{
	std::cout << "before";
	this->_print_info();
	this->_map.clear();
	std::cout << "\nafter";
	this->_print_info();
}

template<class M ,class T>
void MapTestFunctor<M, T>::_find()
{
	this->_map.insert(_list.begin(), _list.end());
	std::cout << "\tres : " << *(this->_map.find(_val(_num/2))) << std::endl;
	std::cout << "\tres : " << *(this->_map.find(_val(-_num))) << std::endl;
}

template<class M ,class T>
void MapTestFunctor<M, T>::_count()
{
	std::cout << "\tres : " << (this->_map.count(_val(_num/2))) << std::endl;
	std::cout << "\tres : " << (this->_map.count(_val(-_num))) << std::endl;
}

template<class M ,class T>
void MapTestFunctor<M, T>::_lower_bound()
{
	typename M::iterator l_bound = _map.lower_bound(_val(_num/2));
	std::cout << "\tlower bound" << *l_bound << std::endl;
}

template<class M ,class T>
void MapTestFunctor<M, T>::_upper_bound()
{
	typename M::iterator u_bound = _map.upper_bound(_val(_num/2));
	std::cout << "\tupper bound" << *u_bound << std::endl;
}

template<class M ,class T>
void MapTestFunctor<M, T>::_equal_range()
{
	TESTING_NAMESPACE::pair<typename M::iterator, typename M::iterator> _range;
	_range = _map.equal_range(_val(_num/2));
	std::cout << "\tlower bound" << *_range.first << std::endl;
	std::cout << "\tupper bound" << *_range.second << std::endl;
}

#endif
