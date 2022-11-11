#ifndef FT_SET_HPP
# define FT_SET_HPP
# include <memory>
# include "ft_RBtree.hpp"
# include "ft_iterator.hpp"
# include "ft_RBtreeIterator.hpp"
# include "ft_pair.hpp"
# include "ft_less.hpp"
# include "ft_lexicographical_compare.hpp"
# include "ft_equal.hpp"

namespace ft
{
	/***************
	 *    class    *
	 ***************/

	template <class _Tp>
	struct _Identity
	{
		_Tp& operator()(_Tp& __x) const
		{
			return __x;
		}
		const _Tp& operator()(const _Tp& __x) const
		{
			return __x;
		}
	};

	template < class T, class Compare = ft::less<T>, class Alloc = std::allocator<T> >
	class set
	{
	public :
		typedef	T											key_type;
		typedef	T											value_type;
		typedef	Compare										key_compare;
		typedef Compare										value_compare;

		typedef	Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::difference_type	difference_type;
		typedef typename allocator_type::size_type			size_type;

	private :
		typedef ft::RBtree<value_type, _Identity<value_type>, key_compare>	_tree_type;
		typedef typename _tree_type::_tree_type								_node_pointer;

	public :
		typedef ft::tree_iterator<value_type, const value_type *, const value_type &>	iterator;
		typedef ft::tree_iterator<value_type, const value_type *, const value_type &>	const_iterator;
		typedef ft::reverse_iterator<iterator>											reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>									const_reverse_iterator;
	
	private :
		key_compare		_key_comp;
		allocator_type	_allocator_object;
		_tree_type		_rbtree;

	public :
		explicit set(const key_compare & comp = key_compare(),
					const allocator_type & alloc = allocator_type());
		template <class InputIterator>
		set (InputIterator firsit, InputIterator last,
			const key_compare & comp = key_compare(),
			const allocator_type & aloc = allocator_type());
		set (const set & other);

		~set() {}

		set & operator=(const set& other);

		iterator begin() const;
		iterator end() const ;

		reverse_iterator rbegin() const;
		reverse_iterator rend() const ;

		bool empty() const;
		size_type size() const;
		size_type max_size() const;

		ft::pair<iterator, bool> insert (const value_type & val);
		iterator insert (iterator position, const value_type & val);
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last);

		void erase(iterator position);
		size_type erase(const key_type & k);
		void erase(iterator first, iterator last);

		void swap(set & other);

		void clear();

		key_compare key_comp() const;
		value_compare value_comp() const;

		iterator find(const key_type & k) const;

		size_type count(const key_type & k) const;

		iterator lower_bound (const key_type& k) const;
		iterator upper_bound (const key_type& k) const;

		ft::pair<iterator,iterator>	equal_range (const key_type& k) const;

		allocator_type get_allocator() const;

		template < class K, class C, class A>
		friend bool operator==(const ft::set<K, C, A> & lhs, const ft::set<K, C, A> & rhs);
		template < class K, class C, class A>
		friend bool operator!=(const ft::set<K, C, A> & lhs, const ft::set<K, C, A> & rhs);
		template < class K, class C, class A>
		friend bool operator<(const ft::set<K, C, A> & lhs, const ft::set<K, C, A> & rhs);
		template < class K, class C, class A>
		friend bool operator<=(const ft::set<K, C, A> & lhs, const ft::set<K, C, A> & rhs);
		template < class K, class C, class A>
		friend bool operator>(const ft::set<K, C, A> & lhs, const ft::set<K, C, A> & rhs);
		template < class K, class C, class A>
		friend bool operator>=(const ft::set<K, C, A> & lhs, const ft::set<K, C, A> & rhs);
		template < class K, class C, class A>
		friend void swap(const ft::set<K, C, A> & x, const ft::set<K, C, A> & y);
	}; // class set

	/***************
	 *   public    *
	 ***************/
	
	template<class K, class C, class A>
	set<K, C, A>::set(const key_compare & comp, const allocator_type & alloc)
	: _key_comp(comp), _allocator_object(alloc), _rbtree()
	{}

	template<class K, class C, class A>
	template <class InputIterator>
	set<K, C, A>::set(InputIterator first, InputIterator last,
	 					const key_compare & comp, const allocator_type & alloc)
	: _key_comp(comp), _allocator_object(alloc), _rbtree()
	{
		for (InputIterator it = first; it != last ; it++)
			this->_rbtree.insertNode(*it);
	}

	template<class K, class C, class A>
	set<K, C, A>::set(const set & other)
	: _key_comp(other._key_comp), _allocator_object(other._allocator_object), _rbtree(other._rbtree)
	{}

	template<class K, class C, class A>
	set<K, C, A> &
	set<K, C, A>::operator=(const set & other)
	{
		if (this != &other)
		{
			this->_allocator_object = other._allocator_object;
			this->_key_comp = other._key_comp;
			this->_rbtree = other._rbtree;
		}
		return (*this);
	}

	template<class K, class C, class A>
	typename set<K, C, A>::iterator
	set<K, C, A>::begin() const
	{
		return (iterator(this->_rbtree.getRootPtr()->_minimum()));
	}

	template<class K, class C, class A>
	typename set<K, C, A>::iterator
	set<K, C, A>::end() const
	{
		return (iterator(this->_rbtree.getNilPtr()));
	}

	template<class K, class C, class A>
	typename set<K, C, A>::reverse_iterator
	set<K, C, A>::rbegin() const
	{
		return (reverse_iterator(this->_rbtree.getNilPtr()));
	}

	template<class K, class C, class A>
	typename set<K, C, A>::reverse_iterator
	set<K, C, A>::rend() const
	{
		return (reverse_iterator(this->_rbtree.getRootPtr()->_minimum()));
	}

	template<class K, class C, class A>
	bool
	set<K, C, A>::empty() const
	{
		return (this->_rbtree.isEmpty());
	}

	template<class K, class C, class A>
	typename set<K, C, A>::size_type
	set<K, C, A>::size() const
	{
		return (this->_rbtree.size());
	}
	
	template<class K, class C, class A>
	typename set<K, C, A>::size_type
	set<K, C, A>::max_size() const
	{
		return (this->_rbtree.max_size());
	}

	template<class K, class C, class A>
	ft::pair<typename set<K, C, A>::iterator, bool>
	set<K, C, A>::insert (const value_type & val)
	{
		ft::pair<_node_pointer, bool> res = _rbtree.insertNode(val);
		return (ft::make_pair(iterator(res.first), res.second));
	}

	template<class K, class C, class A>
	typename set<K, C, A>::iterator
	set<K, C, A>::insert (iterator position, const value_type & val)
	{
		return (iterator(_rbtree.insertNode(position.base(), val)));
	}
	
	template<class K, class C, class A>
	template <class InputIterator>
	void
	set<K, C, A>::insert(InputIterator first, InputIterator last)
	{
		while (first != last)
			this->insert(*first++);
	}

	template<class K, class C, class A>
	void
	set<K, C, A>::erase(iterator position)
	{
		this->_rbtree.deleteNode(*position);
	}
	
	template<class K, class C, class A>
	typename set<K, C, A>::size_type
	set<K, C, A>::erase(const key_type & k)
	{
		if (this->_rbtree.deleteNode(k) == true)
			return (1);
		return (0);
	}
	
	template<class K, class C, class A>
	void
	set<K, C, A>::erase(iterator first, iterator last)
	{
		while (first != last)
			this->erase(first++);
	}

	template<class K, class C, class A>
	void
	set<K, C, A>::swap(set & other)
	{
		if (this == &other)
			return ;
		this->_rbtree.swap(other._rbtree);
	}

	template<class K, class C, class A>
	void
	set<K, C, A>::clear()
	{
		this->_rbtree.clearTree();
	}

	template<class K, class C, class A>
	typename set<K, C, A>::key_compare
	set<K, C, A>::key_comp() const
	{
		return (this->_key_comp);
	}
	
	template<class K, class C, class A>
	typename set<K, C, A>::value_compare
	set<K, C, A>::value_comp() const
	{
		return (value_compare(key_compare()));
	}

	template<class K, class C, class A>
	typename set<K, C, A>::iterator
	set<K, C, A>::find(const key_type & k) const
	{
		return (iterator(this->_rbtree.search(k)));
	}
	
	template<class K, class C, class A>
	typename set<K, C, A>::size_type
	set<K, C, A>::count(const key_type & k) const
	{
		_node_pointer search_result;

		search_result = _rbtree.search(k);
		if (const_iterator(search_result) == this->end())
			return (0);
		return (1);
	}

	template<class K, class C, class A>
	typename set<K, C, A>::iterator
	set<K, C, A>::lower_bound (const key_type& k) const
	{
		iterator it = this->begin();
		for ( ; it != this->end() ; it++)
		{
			if (_key_comp(*it, k) == false)
				break ;
		}
		return (it);
	}
	
	template<class K, class C, class A>
	typename set<K, C, A>::iterator
	set<K, C, A>::upper_bound (const key_type& k) const
	{
		iterator it = this->begin();
		for ( ; it != this->end() ; it++)
		{
			if (_key_comp(k, *it) == true)
				break ;
		}
		return (it);
	}
	
	template<class K, class C, class A>
	ft::pair<typename set<K, C, A>::iterator, typename set<K, C, A>::iterator>
	set<K, C, A>::equal_range (const key_type& k) const
	{
		return (ft::make_pair(lower_bound(k), upper_bound(k)));
	}

	template<class K, class C, class A>
	typename set<K, C, A>::allocator_type
	set<K, C, A>::get_allocator() const
	{
		return (this->_allocator_object);
	}
	
	/***************
	 *   friend    *
	 ***************/

	template < class K, class C, class A>
	bool operator==(const ft::set<K, C, A> & lhs, const ft::set<K, C, A> & rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}
		
	template < class K, class C, class A>
	bool operator!=(const ft::set<K, C, A> & lhs, const ft::set<K, C, A> & rhs)
	{
		return ( !(lhs == rhs) );
	}
		
	template < class K, class C, class A>
	bool operator<(const ft::set<K, C, A> & lhs, const ft::set<K, C, A> & rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
		
	template < class K, class C, class A>
	bool operator<=(const ft::set<K, C, A> & lhs, const ft::set<K, C, A> & rhs)
	{
		return ( !(rhs < lhs) );
	}
		
	template < class K, class C, class A>
	bool operator>(const ft::set<K, C, A> & lhs, const ft::set<K, C, A> & rhs)
	{
		return ( rhs < lhs );
	}
		
	template < class K, class C, class A>
	bool operator>=(const ft::set<K, C, A> & lhs, const ft::set<K, C, A> & rhs)
	{
		return ( !(lhs < rhs) );
	}
		
	template < class K, class C, class A>
	void swap(const ft::set<K, C, A> & x, const ft::set<K, C, A> & y)
	{
		x.swap(y);
	}
} // namespace ft
#endif
