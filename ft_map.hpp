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
				class Alloc = std::allocator< ft::pair<const Key, T> > >
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
		typedef ft::RBtreeNode<value_type> *							_node_pointer;

	public :
		typedef ft::tree_iterator<value_type>			iterator;
		typedef ft::tree_iterator<const value_type>		const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	private :
		key_compare		_compare_functor;
		allocator_type	_allocator_object;
		_tree_type		_rbtree;
	public :
		explicit map(const key_compare & comp = key_compare(),
					const allocator_type & alloc = allocator_type());
		template <class InputIterator>
		map (InputIterator firsit, InputIterator last,
			const key_compare & comp = key_compare(),
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

		size_type		count(const key_type & k) const;

		iterator		lower_bound (const key_type& k);
		const_iterator	lower_bound (const key_type& k) const;

		iterator		upper_bound (const key_type& k);
		const_iterator	upper_bound (const key_type& k) const;

		ft::pair<iterator,iterator>				equal_range (const key_type& k);
		ft::pair<const_iterator,const_iterator>	equal_range (const key_type& k) const;

		allocator_type get_allocator() const;
	}; //class map

	/*
		두 개의 요소를 비교하여 첫 요소가 더 작은지를 판단하는 객체(함수객체)이다.
		이 comp객체는 map::value_compare의 객체로 비교함수 클래스를 생성하는 내부 클래스이다.
	*/
	template <class K, class T, class C, class A>
	class map<K, T, C, A>::value_compare : public binary_function<T, T, bool>
	{
	private :
		friend class map;
		typedef C	key_compare;
	protected :
		key_compare comp;
		value_compare (C C) : comp(c) {}
	public :
		bool operator() (const value_type& x, const value_type& y) const
		{
			return comp(x.first, y.first);
		}
	}; // class map::value_compare

	template<class K, class T, class C, class A>
	map<K, T, C, A>::map(const key_compare & comp, const allocator_type & alloc)
	: _compare_functor(comp), _allocator_object(alloc), _rbtree()
	{}

	template<class K, class T, class C, class A>
	template <class InputIterator>
	map<K, T, C, A>::map(InputIterator firsit, InputIterator last,
	 					const key_compare & comp = key_compare(),
	 					const allocator_type & aloc = allocator_type())
	: _compare_functor(comp), _allocator_object(alloc), _rbtree()
	{
		for (InputIterator it = first; it != last ; i++)
			this->_rbtree.insertNode(*it);
	}

	template<class K, class T, class C, class A>
	map<K, T, C, A>::map(const map & other)
	: _compare_functor(other.comp), _allocator_object(other.alloc), _rbtree(other._rbtree)
	{}

	template<class K, class T, class C, class A>
	map<K, T, C, A> &
	map<K, T, C, A>::operator=(const map & other)
	{
		if (this != other)
		{
			this->_allocator_object = other._allocator_object;
			this->_compare_functor = other._compare_functor;
			this->_rbtree = other._rbtree;
			this->_size = other._size;
		}
		return (*this);
	}

	template<class K, class T, class C, class A>
	typename map<K, T, C, A>::iterator
	map<K, T, C, A>::begin()
	{
		return (iterator(this->_rbtree->getRoot->_minimum()));
	}

	template<class K, class T, class C, class A>
	typename map<K, T, C, A>::iterator
	map<K, T, C, A>::end()
	{
		return (iterator(this->_rbtree->getNilPtr()));
	}

	template<class K, class T, class C, class A>
	typename map<K, T, C, A>::const_iterator
	map<K, T, C, A>::begin() const
	{
		return (const_iterator(this->_rbtree->getRoot->_minimum()));
	}

	template<class K, class T, class C, class A>
	typename map<K, T, C, A>::const_iterator
	map<K, T, C, A>::end() const
	{
		return (const_iterator(this->_rbtree->getNilPtr()));
	}

	template<class K, class T, class C, class A>
	typename map<K, T, C, A>::reverse_iterator
	map<K, T, C, A>::rbegin()
	{
		return (reverse_iterator(this->_rbtree->getNilPtr()));
	}

	template<class K, class T, class C, class A>
	typename map<K, T, C, A>::reverse_iterator
	map<K, T, C, A>::rend()
	{
		return (reverse_iterator(this->_rbtree->getRoot->_minimum()));
	}

	template<class K, class T, class C, class A>
	typename map<K, T, C, A>::const_reverse_iterator
	map<K, T, C, A>::rbegin() const
	{
		return (const_reverse_iterator(this->_rbtree->getNilPtr()));
	}

	template<class K, class T, class C, class A>
	typename map<K, T, C, A>::const_reverse_iterator
	map<K, T, C, A>::rend() const
	{
		return (const_reverse_iterator(this->_rbtree->getRoot->_minimum()));
	}

	template<class K, class T, class C, class A>
	bool
	map<K, T, C, A>::empty() const
	{
		return (this->_rbtree->isEmpty());
	}

	template<class K, class T, class C, class A>
	typename map<K, T, C, A>::size_type
	map<K, T, C, A>::size() const
	{

	}
	
	template<class K, class T, class C, class A>
	typename map<K, T, C, A>::size_type
	map<K, T, C, A>::max_size() const
	{

	}

	template<class K, class T, class C, class A>
	typename map<K, T, C, A>::mapped_type &
	map<K, T, C, A>::operator[] (const key_type & k)
	{
		return ((*((this->insert(make_pair(k,mapped_type()))).first)).second);
	}

	// TODO : RBtree의 insert 를 pointer 를 반환하도록 수정.
	template<class K, class T, class C, class A>
	ft::pair<typename map<K, T, C, A>::iterator, bool>
	map<K, T, C, A>::insert (const value_type & val)
	{
		_node_pointer temp = this->_rbtree.search(val);
		bool res = false;
		ft::pair<iterator, bool> ret;
		if (!temp)
		{
			res = true
			temp = this->_rbtree.insertNode(val);
			this->_size++:
		}
		ret = ft::make_pair(iterator(temp), res);
		return (ret);
	}

	template<class K, class T, class C, class A>
	typename map<K, T, C, A>::iterator
	map<K, T, C, A>::insert (iterator position, const value_type & val)
	{
		// hint를 어떻게 사용해야 하지??
	}
	
	template<class K, class T, class C, class A>
	template <class InputIterator>
	void
	map<K, T, C, A>::insert(InputIterator first, InputIterator last)
	{
		while (first != last)
			this->insert(*first++);
	}

	template<class K, class T, class C, class A>
	void
	map<K, T, C, A>::erase(iterator position)
	{
		node_
		this->_rbtree.deleteNode(*position);
		if()

	}
	
	template<class K, class T, class C, class A>
	typename map<K, T, C, A>::size_type
	map<K, T, C, A>::erase(const key_type & k)
	{
		t
	}
	
	template<class K, class T, class C, class A>
	void
	map<K, T, C, A>::erase(iterator first, iterator last)
	{

	}

	template<class K, class T, class C, class A>
	void
	map<K, T, C, A>::swap(map & other)
	{

	}

	template<class K, class T, class C, class A>
	void
	map<K, T, C, A>::clear()
	{
		this->_rbtree->clearTree();
	}

	template<class K, class T, class C, class A>
	typename map<K, T, C, A>::key_compare
	map<K, T, C, A>::key_comp() const
	{
		return (this->key_comp);
	}
	
	template<class K, class T, class C, class A>
	typename map<K, T, C, A>::value_compare
	map<K, T, C, A>::value_comp() const
	{
		return (this->value_comp);
	}

	template<class K, class T, class C, class A>
	typename map<K, T, C, A>::iterator
	map<K, T, C, A>::find(const key_type & k)
	{
		return (iterator(this->_rbtree->search(ft::make_pair(k, mapped_type()))));
	}
	
	template<class K, class T, class C, class A>
	typename map<K, T, C, A>::const_iterator
	map<K, T, C, A>::find(const key_type & k) const
	{
		return (const_iterator(this->_rbtree->search(ft::make_pair(k, mapped_type()))));
	}

	template<class K, class T, class C, class A>
	typename map<K, T, C, A>::size_type
	map<K, T, C, A>::count(const key_type & k) const
	{

	}

	template<class K, class T, class C, class A>
	typename map<K, T, C, A>::iterator
	map<K, T, C, A>::lower_bound (const key_type& k)
	{

	}
	
	template<class K, class T, class C, class A>
	typename map<K, T, C, A>::const_iterator
	map<K, T, C, A>::lower_bound (const key_type& k) const
	{

	}

	template<class K, class T, class C, class A>
	typename map<K, T, C, A>::iterator
	map<K, T, C, A>::upper_bound (const key_type& k)
	{

	}
	
	template<class K, class T, class C, class A>
	typename map<K, T, C, A>::const_iterator
	map<K, T, C, A>::upper_bound (const key_type& k) const
	{

	}

	template<class K, class T, class C, class A>
	ft::pair<typename map<K, T, C, A>::const_iterator, typename map<K, T, C, A>::const_iterator>
	map<K, T, C, A>::equal_range (const key_type& k) const
	{

	}
	
	template<class K, class T, class C, class A>
	ft::pair<typename map<K, T, C, A>::iterator, typename map<K, T, C, A>::iterator>
	map<K, T, C, A>::equal_range (const key_type& k)
	{

	}

	template<class K, class T, class C, class A>
	typename map<K, T, C, A>::allocator_type
	map<K, T, C, A>::get_allocator() const
	{
		return (this->_allocator_object);
	}
} // namespace ft

#endif