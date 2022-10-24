#ifndef FT_RBTREEITERATOR_HPP
# define FT_RBTREEITERATOR_HPP
# include <memory>
# include "ft_iterator.hpp"
# include "ft_RBtreeNode.hpp"

namespace ft
{
	template< class T >
	class treeIterator : public ft::iterator<ft::bidirectional_iterator_tag, ft::RBtreeNode<T> >
	{
	private :
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, ft::RBtreeNode<T> > iterator_type;
		typedef ft::RBtreeNode<T>	node_type;
		typedef ft::RBtreeNode<T> *	node_pointer;

	public :
		typedef typename iterator_type::difference_type		difference_type;
		typedef typename iterator_type::value_type			value_type;
		typedef typename iterator_type::pointer				pointer;
		typedef typename iterator_type::reference			reference;
		typedef typename iterator_type::iterator_category	iterator_category;
	private :
		pointer _base;
	public :
		treeIterator(pointer ptr = NULL) : _base(ptr) {}
		treeIterator(const treeIterator & other) : _base(other._base) {}
		treeIterator & opeartor=(const treeIterator & other) : _base(other.getBase())
		{
			if (this != &other)
				this->_base = other.getBase();
			return (*this);
		}
		~treeIterator();

		operator treeIterator<const T>() const
		{
			return ( treeIterator<const T>(this->_base));
		}

		const pointer & getBase() const {return this->_base;}

		reference operator*() const { return *(this->_base); }
		pointer operator->() const { return (this->_base); }
		treeIterator & operator++();
		treeIterator operator++(int);
		treeIterator & operator--()
		{
			// --_base; return (*this);
		}
		treeIterator operator--(int)
		{
			// treeIterator temp = *this;
			// --_base;
			// return (temp);
		}

		template <class Iter>
		friend bool operator==(const vectorIterator<T> & lhs, const vectorIterator<Iter> & rhs)
		{ return(lhs.getBase() == rhs.getBase()); }
		template <class Iter>
		friend bool operator!=(const vectorIterator<T> & lhs, const vectorIterator<Iter> & rhs)
		{ return(lhs.getBase() != rhs.getBase()); }
	}; // class RBtreeIterator

	/*
		++
		오른 쪽 자식이 있으면 오른쪽 서브트리에서 가장 작은 값으로 넘어간다.
		오른 쪽 자식이 없으면 부모 노드로 올라간다.
		만약 현재 노드가 부모 노드의 왼쪽 자식이라면, 부모 노드의 오른쪽 서브트리는 항상 부모노드보다 크기 때문에,
		부모 노드에서 멈춘다.
		만약 현재 노드가 부모 노드의 오른쪽 자식인 경우, 부모노드의 상태를 이용해서 판단할 수 있다.
		
	*/
	template <class T>
	treeIterator<T> & treeIterator<T>::operator++()
	{
		node_pointer * temp = NULL;

	}

	template <class T>
	treeIterator<T> & treeIterator<T>::operator++(int)
	{
		treeIterator temp = *this;

		++(*this);
		return (temp);
	}
} // namespace ft

#endif