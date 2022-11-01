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
		typedef	Key											key_type;
		typedef	T											mapped_type;
		typedef	ft::pair<key_type, mapped_type>				value_type;
		typedef	Compare										key_compare;

		typedef	Alloc										allocator_type;
		
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::difference_type	difference_type;
		typedef typename allocator_type::size_type			size_type;

	private :
		class value_compare;
		typedef ft::RBtree<value_type, allocator_type, value_compare>	_tree_type;
		typedef ft::RBtreeNode<value_type>								_node_type;

	public :
		typedef ft::tree_iterator<value_type>			iterator;
		typedef ft::tree_iterator<const value_type>		const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	private :
		key_compare		_compare_functor;
		allocator_type	_allocator_object;
		_tree_type		_rbtree;
		size_type		_size;
	public :
		explicit map(const key_compare & comp = key_compare(),
					const allocator_type & alloc = allocator_type());
		template <class InputIterator>
		map (InputIterator firsit, InputIterator last,
			const key_compare * comp = key_compare(),
			const allocator_type & aloc = allocator_type());
		map (const map & other);

		~map() {}

		map & operator=(const map& other);

		iterator 		begin();
		iterator 		end();
		const_iterator	begin() const;
		const_iterator	end() const;

		reverse_iterator		rbegin();
		reverse_iterator		rend();
		const_reverse_iterator	rbegin() const;
		const_reverse_iterator	rend() const;

		bool empty() const;
		size_type size() const;
		size_type max_size() const; // ???

		mapped_type & operator[] (const key_type & k);

		ft::pair<iterator, bool> insert (const value_type & val);
		iterator insert (iterator position, const value_type & val);
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last);

		void erase(iterator position);
		size_type erase(const key_type & k);
		void erase(iterator first, iterator last);

		void swap(map & other);

		void clear();

		key_compare		key_comp() const;
		value_compare	value_comp() const;

		iterator 		find(const key_type & k);
		const_iterator	find(const key_type & k) const;

		size_type count(const key_type & k) const;

		iterator		lower_bound (const key_type& k);
		const_iterator	lower_bound (const key_type& k) const;

		iterator		upper_bound (const key_type& k);
		const_iterator	upper_bound (const key_type& k) const;

		ft::pair<const_iterator,const_iterator>	equal_range (const key_type& k) const;
		ft::pair<iterator,iterator>				equal_range (const key_type& k);

		allocator_type get_allocator() const;
	}; //class map

	/*
		두 개의 요소를 비교하여 첫 요소가 더 작은지를 판단하는 객체(함수객체)이다.
		이 comp객체는 map::value_compare의 객체로 비교함수 클래스를 생성하는 내부 클래스이다.
	*/
	template <class Key, class T, class Compare, class Alloc>
	class map<Key, T, Compare, Alloc>::value_compare : public binary_function<T, T, bool>
	{
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
	}; // class map::value_compare

	template<class Key, class T, class Compare, class Alloc>
	map<Key, T, Compare, Alloc>::map(const key_compare & comp, const allocator_type & alloc)
	: _compare_functor(comp), _allocator_object(alloc), _rbtree()
	{}

	template<class Key, class T, class Compare, class Alloc>
	template <class InputIterator>
	map<Key, T, Compare, Alloc>::map(InputIterator firsit, InputIterator last,
	 								const key_compare * comp = key_compare(),
	 								const allocator_type & aloc = allocator_type())
	: _compare_functor(comp), _allocator_object(alloc), _rbtree()
	{
		for (InputIterator it = first; it != last ; i++)
			this->_rbtree.insertNode(*it);
	}

	template<class Key, class T, class Compare, class Alloc>
	map<Key, T, Compare, Alloc>::map(const map & other)
	: _compare_functor(other.comp), _allocator_object(other.alloc), _rbtree(other._rbtree)
	{}

	template<class Key, class T, class Compare, class Alloc>
	map<Key, T, Compare, Alloc> &
	map<Key, T, Compare, Alloc>::operator=(const map & other)
	{
		if (this != other)
			this->_rbtree = other._rbtree;
		return *this;
	}

	template<class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator
	map<Key, T, Compare, Alloc>::begin()
	{
		return (iterator(this->_rbtree->getRoot->_minimum()));
	}

	template<class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator
	map<Key, T, Compare, Alloc>::end()
	{
		return (iterator(this->_rbtree->getNilPtr()));
	}

	template<class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_iterator
	map<Key, T, Compare, Alloc>::begin() const
	{
		return (const_iterator(this->_rbtree->getRoot->_minimum()));
	}

	template<class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_iterator
	map<Key, T, Compare, Alloc>::end() const
	{
		return (const_iterator(this->_rbtree->getNilPtr()));
	}

	template<class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::reverse_iterator
	map<Key, T, Compare, Alloc>::rbegin()
	{
		return (reverse_iterator(this->_rbtree->getNilPtr()));
	}

	template<class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::reverse_iterator
	map<Key, T, Compare, Alloc>::rend()
	{
		return (reverse_iterator(this->_rbtree->getRoot->_minimum()));
	}

	template<class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_reverse_iterator
	map<Key, T, Compare, Alloc>::rbegin() const
	{
		return (const_reverse_iterator(this->_rbtree->getNilPtr()));
	}

	template<class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_reverse_iterator
	map<Key, T, Compare, Alloc>::rend() const
	{
		return (const_reverse_iterator(this->_rbtree->getRoot->_minimum()));
	}

	template<class Key, class T, class Compare, class Alloc>
	bool
	map<Key, T, Compare, Alloc>::empty() const
	{
		
	}

	template<class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::size_type
	map<Key, T, Compare, Alloc>::size() const
	{

	}
	
	template<class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::size_type
	map<Key, T, Compare, Alloc>::max_size() const
	{

	}

	template<class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::mapped_type &
	map<Key, T, Compare, Alloc>::operator[] (const key_type & k)
	{

	}

	template<class Key, class T, class Compare, class Alloc>
	ft::pair<typename map<Key, T, Compare, Alloc>::iterator, bool>
	map<Key, T, Compare, Alloc>::insert (const value_type & val)
	{

	}

	template<class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator
	map<Key, T, Compare, Alloc>::insert (iterator position, const value_type & val)
	{

	}
	
	template<class Key, class T, class Compare, class Alloc>
	template <class InputIterator>
	void
	map<Key, T, Compare, Alloc>::insert(InputIterator first, InputIterator last)
	{

	}

	template<class Key, class T, class Compare, class Alloc>
	void
	map<Key, T, Compare, Alloc>::erase(iterator position)
	{

	}
	
	template<class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::size_type
	map<Key, T, Compare, Alloc>::erase(const key_type & k)
	{

	}
	
	template<class Key, class T, class Compare, class Alloc>
	void
	map<Key, T, Compare, Alloc>::erase(iterator first, iterator last)
	{

	}

	template<class Key, class T, class Compare, class Alloc>
	void
	map<Key, T, Compare, Alloc>::swap(map & other)
	{

	}

	template<class Key, class T, class Compare, class Alloc>
	void
	map<Key, T, Compare, Alloc>::clear()
	{

	}

	template<class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::key_compare
	map<Key, T, Compare, Alloc>::key_comp() const
	{

	}
	
	template<class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::value_compare
	map<Key, T, Compare, Alloc>::value_comp() const
	{

	}

	template<class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator
	map<Key, T, Compare, Alloc>::find(const key_type & k)
	{

	}
	
	template<class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_iterator
	map<Key, T, Compare, Alloc>::find(const key_type & k) const
	{

	}

	template<class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::size_type
	map<Key, T, Compare, Alloc>::count(const key_type & k) const
	{

	}

	template<class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator
	map<Key, T, Compare, Alloc>::lower_bound (const key_type& k)
	{

	}
	
	template<class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_iterator
	map<Key, T, Compare, Alloc>::lower_bound (const key_type& k) const
	{

	}

	template<class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator
	map<Key, T, Compare, Alloc>::upper_bound (const key_type& k)
	{

	}
	
	template<class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_iterator
	map<Key, T, Compare, Alloc>::upper_bound (const key_type& k) const
	{

	}

	template<class Key, class T, class Compare, class Alloc>
	ft::pair<typename map<Key, T, Compare, Alloc>::const_iterator, typename map<Key, T, Compare, Alloc>::const_iterator>
	map<Key, T, Compare, Alloc>::equal_range (const key_type& k) const
	{

	}
	
	template<class Key, class T, class Compare, class Alloc>
	ft::pair<typename map<Key, T, Compare, Alloc>::iterator, typename map<Key, T, Compare, Alloc>::iterator>
	map<Key, T, Compare, Alloc>::equal_range (const key_type& k)
	{

	}

	template<class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::allocator_type
	map<Key, T, Compare, Alloc>::get_allocator() const
	{

	}
} // namespace ft

#endif