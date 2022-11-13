#ifndef FT_PAIR_HPP
# define FT_PAIR_HPP

# include <iostream>
namespace ft
{
	/***************
	 *    class    *
	 ***************/
	template <class T1, class T2>
	struct pair
	{
		//member type
		typedef T1 first_type;
		typedef T2 second_type;
		//member vairable
		T1 first;
		T2 second;
		//member function
		pair()
		: first(first_type()), second(second_type()) {}
		
		template<class U, class V>
		pair(const pair<U, V> & pr)
		: first(pr.first), second(pr.second) {}
		
		pair(const  first_type & a, const second_type & b)
		: first(a), second(b) {}

		//non-member function
		friend bool operator== (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
		{ return lhs.first==rhs.first && lhs.second==rhs.second; }

		friend bool operator!= (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
		{ return !(lhs==rhs); }

		friend bool operator<  (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
		{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

		friend bool operator<= (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
		{ return !(rhs<lhs); }

		friend bool operator>  (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
		{ return rhs<lhs; }

		friend bool operator>= (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
		{ return !(lhs<rhs); }
	};

	template <class K, class V>
	std::ostream & operator<< (std::ostream & os, const ft::pair<K, V> & p)
	{
		os << "<" << p.first << ", " << p.second << ">";
		return (os);
	}
	/***************
	 *  non-member *
	 ***************/
	template <class T1,class T2>
	pair<T1,T2> make_pair (T1 x, T2 y)
	{
		return ( pair<T1,T2>(x, y) );
	}
}
#endif
