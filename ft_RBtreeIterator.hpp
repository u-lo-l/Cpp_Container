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
		treeIterator & opeartor=( const vectorIterator & other) : _base(other.getBase())
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

	template <class T>
	treeIterator<T> & treeIterator<T>::operator++()
	{
		if ()
	}
} // namespace ft

#endif