#ifndef FT_VECTOR_ITERATOR_HPP
# define FT_VECTOR_ITERATOR_HPP
# include "ft_iterator.hpp"
# include <iostream>

namespace ft
{
	template < class T, class Alloc >
	class vector;

	template<class T>
	class vectorIterator
	{
	private:
		// template <class U, class Alloc> friend class vector;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T> iterator_type;
	public :
		typedef typename iterator_type::difference_type		difference_type;
		typedef typename iterator_type::pointer				pointer;
		typedef typename iterator_type::reference			reference;
		typedef typename iterator_type::value_type			value_type;
		typedef typename iterator_type::iterator_category	iterator_category;
	private:
		pointer _base;
	public:
		vectorIterator(pointer ptr = NULL);
		vectorIterator(const vectorIterator & other);
		vectorIterator & operator=(const vectorIterator & other);

		~vectorIterator();

		operator vectorIterator<const value_type> () const;

		const pointer & getBase() const;
		
		reference operator*() const;

		pointer operator->() const;
		
		vectorIterator & operator++();
		vectorIterator operator++(int);
		
		vectorIterator & operator--();
		vectorIterator operator--(int);
		
		vectorIterator operator+(int n) const;
		
		vectorIterator operator-(int n) const;
		template <class Iter>
		difference_type operator-(const vectorIterator<Iter> & rhs ) const;

		vectorIterator & operator+=(int n);
		
		vectorIterator & operator-=(int n);
		
		reference operator[](difference_type n);
		const reference operator[](difference_type n) const;

		template <class Iter>
		friend vectorIterator<Iter> operator+(typename vectorIterator<Iter>::difference_type n, const vectorIterator<Iter> & rhs);

		template <class Iter1, class Iter2>
		friend bool operator==(const vectorIterator<Iter1> & lhs, const vectorIterator<Iter2> & rhs);

		template <class Iter1, class Iter2>
		friend bool operator!=(const vectorIterator<Iter1> & lhs, const vectorIterator<Iter2> & rhs);

		template <class Iter1, class Iter2>
		friend bool operator>=(const vectorIterator<Iter1> & lhs, const vectorIterator<Iter2> & rhs);

		template <class Iter1, class Iter2>
		friend bool operator>(const vectorIterator<Iter1> & lhs, const vectorIterator<Iter2> & rhs);

		template <class Iter1, class Iter2>
		friend bool operator<=(const vectorIterator<Iter1> & lhs, const vectorIterator<Iter2> & rhs);

		template <class Iter1, class Iter2>
		friend bool operator<(const vectorIterator<Iter1> & lhs, const vectorIterator<Iter2> & rhs);

	}; // class vectorIterator

	template<class T>
	vectorIterator<T>::vectorIterator(pointer ptr)
	: _base(ptr) {}

	template<class T>
	vectorIterator<T>::vectorIterator(const vectorIterator<T> & other)
	: _base(other.getBase()) {}

	template<class T>
	vectorIterator<T> &
	vectorIterator<T>::operator=(const vectorIterator & other)
	{
		if (this != &other)
			this->_base = other.getBase();
		return (*this);
	}

	template<class T>
	vectorIterator<T>::~vectorIterator() {}

	template<class T>
	vectorIterator<T>::operator vectorIterator<const value_type> () const
	{
		return ( vectorIterator<const value_type>(this->_base) );
	}

	template<class T>
	const typename vectorIterator<T>::pointer &
	vectorIterator<T>::getBase() const
	{ return this->_base; }
	
	template<class T>
	typename vectorIterator<T>::reference
	vectorIterator<T>::operator*() const
	{
		return (*(this->_base));
	}

	template<class T>
	typename vectorIterator<T>::pointer
	vectorIterator<T>::operator->() const
	{
		return (this->_base);
	}

	template<class T>
	vectorIterator<T> &
	vectorIterator<T>::operator++()
	{
		++_base; return (*this);
	}

	template<class T>
	vectorIterator<T>
	vectorIterator<T>::operator++(int)
	{
		vectorIterator temp = *this;
		++_base;
		return (temp);
	}

	template<class T>
	vectorIterator<T> &
	vectorIterator<T>::operator--() { --_base; return (*this); }

	template<class T>
	vectorIterator<T>
	vectorIterator<T>::operator--(int)
	{
		vectorIterator temp = *this;
		--_base;
		return (temp);
	}
	
	template<class T>
	vectorIterator<T>
	vectorIterator<T>::operator+(int n) const
	{
		return (vectorIterator(_base + n));
	}

	template<class T>
	vectorIterator<T>
	vectorIterator<T>::operator-(int n) const
	{
		return ( *this + (-n));
	}

	template<class T>
	template <class Iter>
	typename vectorIterator<T>::difference_type
	vectorIterator<T>::operator-(const vectorIterator<Iter> & rhs ) const
	{
		return (this->_base - rhs.getBase());
	}

	template<class T>
	vectorIterator<T> &
	vectorIterator<T>::operator+=(int n)
	{
		_base += n; return (*this);
	}

	template<class T>
	vectorIterator<T> &
	vectorIterator<T>::operator-=(int n)
	{
		_base -= n; return (*this);
	}

	template<class T>
	typename vectorIterator<T>::reference
	vectorIterator<T>::operator[](difference_type n)
	{
		return (*(_base + n));
	}

	template<class T>
	const typename vectorIterator<T>::reference
	vectorIterator<T>::operator[](difference_type n) const
	{
		return (*(_base + n));
	}

	// friend functions
	template <class T>
	vectorIterator<T>
	operator+(typename vectorIterator<T>::difference_type n, const vectorIterator<T> & rhs)
	{
		return (rhs + n);
	}

	template <class Iter1, class Iter2>
	bool
	operator==(const vectorIterator<Iter1> & lhs, const vectorIterator<Iter2> & rhs)
	{
		return(lhs.getBase() == rhs.getBase());
	}

	template <class Iter1, class Iter2>
	bool
	operator!=(const vectorIterator<Iter1> & lhs, const vectorIterator<Iter2> & rhs)
	{
		return(lhs.getBase() != rhs.getBase());
	}

	template <class Iter1, class Iter2>
	bool
	operator>=(const vectorIterator<Iter1> & lhs, const vectorIterator<Iter2> & rhs)
	{
		return(lhs.getBase() >= rhs.getBase());
	}

	template <class Iter1, class Iter2>
	bool
	operator>(const vectorIterator<Iter1> & lhs, const vectorIterator<Iter2> & rhs)
	{
		return(lhs.getBase() > rhs.getBase());
	}

	template <class Iter1, class Iter2>
	bool
	operator<=(const vectorIterator<Iter1> & lhs, const vectorIterator<Iter2> & rhs)
	{
		return(lhs.getBase() <= rhs.getBase());
	}

	template <class Iter1, class Iter2>
	bool
	operator<(const vectorIterator<Iter1> & lhs, const vectorIterator<Iter2> & rhs)
	{
		return(lhs.getBase() < rhs.getBase());
	}
} // namespace ft

#endif //FT_VECTOR_ITERATOR_HPP
