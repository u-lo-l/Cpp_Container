#ifndef FT_MAP_HPP
# define FT_MAP_HPP
# include <memory>
# include <map>
# include "ft_pair.hpp"

namespace ft
{
	// template <class T>
	// bool less(const T & a, const T & b) { return (a < b); }

	template <	class Key,
				class T,
				class Compare = less<Key>,
				class Alloc = std::allocator< ft::pair<const Key, T> >
				>
	class map
	{

	}; //class map

} // namespace ft

#endif