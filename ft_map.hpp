#ifndef FT_MAP_HPP
# define FT_MAP_HPP
# include <memory>
# include <map>
# include "ft_iterator.hpp"
# include "ft_pair.hpp"
# include "ft_less.hpp"
# include "ft_RBtreeIterator.hpp"
# include "ft_RBtree.hpp"

namespace ft
{
	template <	class Key,
				class T,
				class Compare = less<Key>,
				class Alloc = std::allocator< ft::pair<const Key, T> >
				>
	class map
	{
	public :
		// Member Types
		typedef	Key												key_type;
		typedef	T												mapped_type;
		typedef	ft::pair<key_type, mapped_type>					value_type;
		typedef	Compare											key_compare;

		class	value_compare;
		typedef	Alloc											allocator_type;
		
		typedef typename allocator_type::reference				reference;
		typedef typename allocator_type::const_reference		const_reference;
		typedef typename allocator_type::pointer				pointer;
		typedef typename allocator_type::const_pointer			const_pointer;
		typedef typename allocator_type::difference_type		difference_type;
		typedef typename allocator_type::size_type				size_type;

		typedef ft::RBTreeIterator<value_type>					iterator;
		typedef ft::RBTreeIterator<const value_type>			const_iterator;
		typedef ft::reverse_iterator<iterator>					reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

	private :

	}; //class map



	template <class Key, class T, class Compare, class Alloc>
	class map<Key, T, Compare, Alloc>::value_compare : public binary_function<T, T, bool>
	{
	/*
		두 개의 요소를 비교하여 첫 요소가 더 작은지를 판단하는 객체(함수객체)이다.
		이 comp객체는 map::value_compare의 객체로 비교함수 클래스를 생성하는 내부 클래스이다.
	*/
	private :
		friend class map;
	protected :
		Compare comp;
		value_compare (Compare C) : comp(c) {}
	public :
		bool operator() (const value_type& x, const value_type& y) const
		{
			return comp(x.first, y.first);
		}
	};
} // namespace ft

#endif