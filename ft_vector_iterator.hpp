/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_iterator.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 01:08:38 by dkim2             #+#    #+#             */
/*   Updated: 2022/09/24 09:33:50 by dkim2            ###   ########.fr       */
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
	class vectorIterator : public ft::iterator<ft::random_access_iterator_tag, T>
	{
	private:
		template <class U, class Alloc>
		friend class vector;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T> iterator_type;
	public :
		typedef typename iterator_type::difference_type		difference_type;
		typedef typename iterator_type::value_type			value_type;
		typedef typename iterator_type::pointer				pointer;
		typedef typename iterator_type::reference			reference;
		typedef typename iterator_type::iterator_category	iterator_category;
	private:
		pointer _base;
	public:
		// constructors and destructor
		vectorIterator(pointer ptr = NULL) : _base(ptr) { }
		vectorIterator(const vectorIterator & other) : _base(other.getBase()) {}
		vectorIterator & operator=(const vectorIterator & other)
		{
			if (this != &other)
				this->_base = other.getBase();
			return (*this);
		}

		~vectorIterator() {}

		operator vectorIterator<const T> () const
		{
			return ( vectorIterator<const T>(this->_base));
		}

		// getter
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
		difference_type operator-(const vectorIterator & rhs ) const
		{
			return (this->_base - rhs.getBase());
		}
		vectorIterator & operator+=(int n) { _base += n; return (*this); }
		vectorIterator & operator-=(int n) { _base -= n; return (*this); }
		reference operator[](difference_type n) { return (*(_base + n)); }
		const reference operator[](difference_type n) const { return (*(_base + n)); }

		friend vectorIterator<T> operator+(difference_type n, const vectorIterator<T> & rhs)
		{ return (rhs + n); }
		// 비교 연산자들을 friend함수로 만들어 놨지만, 그냥 멤버함수로 오버로딩 해도 될 것 같다.
		friend bool operator==(const vectorIterator<T> & lhs, const vectorIterator<T> & rhs)
		{ return(lhs.getBase() == rhs.getBase()); }
		friend bool operator!=(const vectorIterator<T> & lhs, const vectorIterator<T> & rhs)
		{ return(lhs.getBase() != rhs.getBase()); }
		friend bool operator>=(const vectorIterator<T> & lhs, const vectorIterator<T> & rhs)
		{ return(lhs.getBase() >= rhs.getBase()); }
		friend bool operator>(const vectorIterator<T> & lhs, const vectorIterator<T> & rhs)
		{ return(lhs.getBase() > rhs.getBase()); }
		friend bool operator<=(const vectorIterator<T> & lhs, const vectorIterator<T> & rhs)
		{ return(lhs.getBase() <= rhs.getBase()); }
		friend bool operator<(const vectorIterator<T> & lhs, const vectorIterator<T> & rhs)
		{ return(lhs.getBase() < rhs.getBase()); }
	}; // class vectorIterator
} // namespace ft

#endif //FT_VECTOR_ITERATOR_HPP
