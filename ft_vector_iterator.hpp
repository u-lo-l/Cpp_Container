/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_iterator.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 01:08:38 by dkim2             #+#    #+#             */
/*   Updated: 2022/11/04 16:53:55 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		vectorIterator(pointer ptr = NULL) : _base(ptr) { }
		vectorIterator(const vectorIterator & other) : _base(other.getBase()) {}
		vectorIterator & operator=(const vectorIterator & other)
		{
			if (this != &other)
				this->_base = other.getBase();
			return (*this);
		}

		~vectorIterator() {}

		operator vectorIterator<const value_type> () const
		{
			return ( vectorIterator<const value_type>(this->_base) );
		}

		const pointer & getBase() const { return this->_base; }
		
		reference operator*() const { return (*(this->_base)); }
		pointer operator->() const { return (this->_base); }
		vectorIterator & operator++() { ++_base; return (*this); }
		vectorIterator operator++(int)
		{
			vectorIterator temp = *this;
			++_base;
			return (temp);
		}
		vectorIterator & operator--() { --_base; return (*this); }
		vectorIterator operator--(int)
		{
			vectorIterator temp = *this;
			--_base;
			return (temp);
		}
		vectorIterator operator+(int n) const { return (vectorIterator(_base + n)); }
		vectorIterator operator-(int n) const { return ( *this + (-n)); }
		template <class Iter>
		difference_type operator-(const vectorIterator<Iter> & rhs ) const
		{
			return (this->_base - rhs.getBase());
		}
		vectorIterator & operator+=(int n) { _base += n; return (*this); }
		vectorIterator & operator-=(int n) { _base -= n; return (*this); }
		reference operator[](difference_type n) { return (*(_base + n)); }
		const reference operator[](difference_type n) const { return (*(_base + n)); }

		// friend functions
		friend vectorIterator operator+(difference_type n, const vectorIterator & rhs)
		{ return (rhs + n); }

		template <class Iter>
		friend bool operator==(const vectorIterator<T> & lhs, const vectorIterator<Iter> & rhs)
		{ return(lhs.getBase() == rhs.getBase()); }
		template <class Iter>
		friend bool operator!=(const vectorIterator<T> & lhs, const vectorIterator<Iter> & rhs)
		{ return(lhs.getBase() != rhs.getBase()); }
		template <class Iter>
		friend bool operator>=(const vectorIterator<T> & lhs, const vectorIterator<Iter> & rhs)
		{ return(lhs.getBase() >= rhs.getBase()); }
		template <class Iter>
		friend bool operator>(const vectorIterator<T> & lhs, const vectorIterator<Iter> & rhs)
		{ return(lhs.getBase() > rhs.getBase()); }
		template <class Iter>
		friend bool operator<=(const vectorIterator<T> & lhs, const vectorIterator<Iter> & rhs)
		{ return(lhs.getBase() <= rhs.getBase()); }
		template <class Iter>
		friend bool operator<(const vectorIterator<T> & lhs, const vectorIterator<Iter> & rhs)
		{ return(lhs.getBase() < rhs.getBase()); }
	}; // class vectorIterator
} // namespace ft

#endif //FT_VECTOR_ITERATOR_HPP
