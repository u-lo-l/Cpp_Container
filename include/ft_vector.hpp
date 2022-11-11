#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP
# include <iostream>
# include <memory> // for allocator
# include <exception>
# include "ft_vector_iterator.hpp"
# include "ft_enable_if.hpp"
# include "ft_is_integral.hpp"
# include "ft_lexicographical_compare.hpp"
# include "ft_equal.hpp"

namespace ft
{
	/***************
	 *    class    *
	 ***************/

	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
	public :
		// A. Member Type
		typedef T											value_type;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;

		typedef ft::vectorIterator<value_type *> 			iterator;
		typedef ft::vectorIterator<const value_type *>		const_iterator;
		typedef ft::reverse_iterator<iterator> 				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> 		const_reverse_iterator;

		typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
		typedef typename allocator_type::size_type						size_type;
	
	private :
		allocator_type	_allocator_object;
		pointer			_start;
		pointer			_end;
		size_type		_size;
		size_type		_capacity;
		
		size_type		_doubleCapacity( size_type new_capacity );

	public :
		explicit vector (const allocator_type & alloc = allocator_type());

		explicit vector (size_type n,
						const value_type & val = value_type(),
						const allocator_type & alloc = allocator_type());

		template <class InputIterator>
		vector (typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
				InputIterator last,
				const allocator_type & alloc = allocator_type() );

		vector (const vector & x);

		~vector();

		vector & operator= (const vector & x);
		
		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;

		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		reverse_iterator rend();
		const_reverse_iterator rend() const;
		
		size_type size() const;
		
		size_type max_size() const;
		
		void resize(size_type n, value_type val = value_type());

		size_type capacity() const;

		bool empty() const;

		void reserve(size_type new_capacity);
		
		reference 		operator[](size_type n);
		const_reference operator[](size_type n) const;
		reference 		at(size_type n);
		const_reference	at(size_type n) const;
		reference		front();
		const_reference	front() const;
		reference		back();
		const_reference back() const;

		template <class InputIterator>
		void
		assign
		(
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
			InputIterator last
		);
		void assign(size_type n, const value_type & val);
		
		void push_back(const value_type & val);
		void pop_back();
		

		iterator insert(iterator position, const value_type & val);
		void insert(iterator position, size_type n, const value_type & val);
		
		template <class InputIterator>
		void
		insert
		(
			iterator position,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
			InputIterator last
		);
		
		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);
		
		void swap(vector & x);
		
		void clear();

		allocator_type get_allocator() const;

		template<class U, class B>
		friend bool operator==(const ft::vector<U, B> & lhs, const ft::vector<U, B> & rhs);
		template<class U, class B>
		friend bool operator!=(const ft::vector<U, B> & lhs, const ft::vector<U, B> & rhs);
		template<class U, class B>
		friend bool operator<(const ft::vector<U, B> & lhs, const ft::vector<U, B> & rhs);
		template<class U, class B>
		friend bool operator<=(const ft::vector<U, B> & lhs, const ft::vector<U, B> & rhs);
		template<class U, class B>
		friend bool operator>(const ft::vector<U, B> & lhs, const ft::vector<U, B> & rhs);
		template<class U, class B>
		friend bool operator>=(const ft::vector<U, B> & lhs, const ft::vector<U, B> & rhs);
		template<class U, class B>
		friend void swap(ft::vector<U, B> & x, ft::vector<U, B> & y);
	}; // class vector

	/***************
	 *   private   *
	 ***************/

	template <class T, class A>
	typename vector<T, A>::size_type
	vector<T, A>::_doubleCapacity( size_type new_capacity )
	{
		if (new_capacity < this->_capacity)
			return (this->_capacity);
		if (this->_capacity * 2 < new_capacity)
			return (new_capacity);
		if (this->max_size() < this->_capacity * 2)
			return (this->max_size());
		else
			return (this->_capacity * 2);
	}

	/***************
	 *   public    *
	 ***************/

	template <class T, class A>
	vector<T, A>::vector (const allocator_type & alloc)
	: _allocator_object(alloc), _start(NULL), _end(NULL), _size(0), _capacity(0)
	{
		this->_start = this->_allocator_object.allocate(1);
		this->_end = this->_start;
	}

	template <class T, class A>
	vector<T, A>::vector (size_type n,
			const value_type & val,
			const allocator_type & alloc)
	: _allocator_object(alloc), _size(0), _capacity(n)
	{
		this->_start = this->_allocator_object.allocate(n);
		this->_end = this->_start;
		while (this->_size < this->_capacity)
		{
			this->_allocator_object.construct((this->_end)++, val);
			this->_size++;
		}
	}

	template <class T, class A>
	template <class InputIterator>
	vector<T, A>::vector
	(
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
		InputIterator last,
		const allocator_type & alloc
	)
	: _allocator_object(alloc), _size(0)
	{
		this->_capacity = static_cast<size_type>(ft::distance(first, last));
		this->_start = this->_allocator_object.allocate(this->_capacity);
		this->_end = this->_start;
		while (this->_size < this->_capacity)
		{
			this->_allocator_object.construct(this->_end++, *(first++));
			this->_size++;
		}
	}

	template <class T, class A>
	vector<T, A>::vector (const vector & x)
	: _allocator_object(x.get_allocator()), _size(0), _capacity(x._capacity)
	{
		this->_start = this->_allocator_object.allocate(this->_capacity);
		this->_end = this->_start;
		iterator	it = x._start;
		while (this->_size < x._size)
		{
			this->_allocator_object.construct((this->_end)++, *(it++));
			this->_size++;
		}
	}

	// destructor
	template <class T, class A>
	vector<T, A>::~vector()
	{
		this->clear();
		if (this->_start != NULL)
			this->_allocator_object.deallocate(this->_start, this->_capacity);
	}

	template <class T, class A>
	vector<T,A> &
	vector<T, A>::operator= (const vector & x)
	{
		if (this == &x)
			return (*this);
		this->assign(x.begin(), x.end());
		return (*this);
	}
	
	// iterators
	template <class T, class A>
	typename vector<T,A>::iterator
	vector<T,A>::begin()
	{
		return (iterator(this->_start));
	}

	template <class T, class A>
	typename vector<T,A>::const_iterator
	vector<T,A>::begin() const
	{
		return (const_iterator(this->_start));
	}

	template <class T, class A>
	typename vector<T,A>::iterator
	vector<T,A>::end()
	{
		return (iterator(this->_end));
	}

	template <class T, class A>
	typename vector<T,A>::const_iterator
	vector<T,A>::end() const
	{
		return (const_iterator(this->_end));
	}

	template <class T, class A>
	typename vector<T,A>::reverse_iterator
	vector<T,A>::rbegin()
	{
		return (reverse_iterator(this->_end));
	}

	template <class T, class A>
	typename vector<T,A>::const_reverse_iterator
	vector<T,A>::rbegin() const
	{
		return (const_reverse_iterator(this->_end));
	}

	template <class T, class A>
	typename vector<T,A>::reverse_iterator
	vector<T,A>::rend()
	{
		return (reverse_iterator(this->_start));
	}

	template <class T, class A>
	typename vector<T,A>::const_reverse_iterator
	vector<T,A>::rend() const
	{
		return (const_reverse_iterator(this->_start));
	}
	
	// Capacity
	template <class T, class A>
	typename vector<T, A>::size_type
	vector<T, A>::size() const
	{
		return (this->_size);
	}

	template <class T, class A>
	typename vector<T, A>::size_type
	vector<T, A>::max_size() const
	{
		return (this->_allocator_object.max_size());
	}

	template <class T, class A>
	void
	vector<T, A>::resize(size_type n, value_type val)
	{
		/*
			if n < this->_size : remove elements beyond n-th
			if n > this->_size : 
			if n > this->_capacity : reallocation
		*/
		if (n == this->_size)
		{
			return ;
		}
		if (n > this->_capacity)
		{
			this->reserve(_doubleCapacity(n));
		}
		pointer new_end =  this->_start + n;
		if (n < this->_size)
		{
			while ( new_end != this->_end)
				this->_allocator_object.destroy(--this->_end);
		}
		else
		{
			while ( new_end != this->_end )
				this->_allocator_object.construct(this->_end++, val);
		}
		this->_size = n;
	}

	template <class T, class A>
	typename vector<T, A>::size_type
	vector<T, A>::capacity() const
	{
		return (this->_capacity);
	}

	template <class T, class A>
	bool
	vector<T, A>::empty() const
	{
		return (static_cast<bool>(!this->_size));
	}
	/*
		reserve()
		request a change in capacity
		if n > this->_capacity : reallocate it's storage capacity to n
	*/
	template <class T, class A>
	void
	vector<T, A>::reserve(size_type new_capacity)
	{
		if (new_capacity > this->max_size())
			throw(std::length_error("[ERROR] ft::vector::reserve() : length error"));
		if (new_capacity <= this->_capacity)
			return ;
		pointer		prev_start = this->_start;
		pointer		prev_end = this->_end;
		size_type	prev_capacity = this->_capacity;

		this->_start = this->_allocator_object.allocate(new_capacity);
		this->_end = this->_start;
		this->_capacity = new_capacity;
		pointer p = prev_start; 
		while ( p != prev_end )
		{
			this->_allocator_object.construct(this->_end++, *p);
			this->_allocator_object.destroy(p++);
		}
		this->_allocator_object.deallocate(prev_start, prev_capacity);
	}
	
	// Element access
	template <class T, class A>
	typename vector<T, A>::reference
	vector<T, A>::operator[](size_type n)
	{
		return (*(this->_start + n));
	}

	template <class T, class A>
	typename vector<T, A>::const_reference
	vector<T, A>::operator[](size_type n) const
	{
		return (*(this->_start + n));
	}

	template <class T, class A>
	typename vector<T, A>::reference
	vector<T, A>::at(size_type n)
	{
		if (n >= this->_size)
			throw std::out_of_range("ft::vector : at() Out of range");
		return (*(this->_start + n));
	}
	
	template <class T, class A>
	typename vector<T, A>::const_reference
	vector<T, A>::at(size_type n) const
	{
		if (n >= this->_size)
			throw std::out_of_range("ft::vector : const at() Out of range");
		return (*(this->_start + n));
	}
	
	template <class T, class A>
	typename vector<T, A>::reference
	vector<T, A>::front()
	{
		return (*(this->_start));
	}
	
	template <class T, class A>
	typename vector<T, A>::const_reference
	vector<T, A>::front() const
	{
		return (*(this->_start));
	}
	
	template <class T, class A>
	typename vector<T, A>::reference
	vector<T, A>::back()
	{
		return (*(this->_end - 1));
	}
	
	template <class T, class A>
	typename vector<T, A>::const_reference
	vector<T, A>::back() const
	{
		return (*(this->_end - 1));
	}

	// Modifiers
	/*
		assign : Assigns new contents to the vector, replacing its cuurent contents and modifying its size
			☆ This causes an automatic reallocation of the storage if the size of new vector surpassess the current capacity.
	*/
	template <class T, class A>
	template <class InputIterator>
	void
	vector<T, A>::assign
	(
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
		InputIterator last
	)
	{
		this->clear();
		size_type new_size = static_cast<size_type>(ft::distance(first, last));
		if (new_size > this->_capacity)
		{
			this->_allocator_object.deallocate(this->_start, this->_size);
			this->_capacity = new_size;
			this->_start = this->_allocator_object.allocate(new_size);
		}
		this->_end = this->_start;
		for ( _size = 0 ; _size < new_size ; _size++)
			this->_allocator_object.construct(this->_end++, *(first++));
	}

	template <class T, class A>
	void
	vector<T, A>::assign(size_type n, const value_type & val)
	{
		this->clear();
		if (n > this->_capacity)
		{
			this->_allocator_object.deallocate(this->_start, this->_size);
			this->_capacity = n;
			this->_start = this->_allocator_object.allocate(this->_capacity);
		}
		this->_end = this->_start;
		for (this->_size = 0; _size < n ; _size++, _end++)
			this->_allocator_object.construct(this->_end, val);
	}
	
	template <class T, class A>
	void
	vector<T, A>::push_back(const value_type & val)
	{
		if ( this->_size == this->_capacity )
			this->reserve(_doubleCapacity(this->_capacity + 1));
		this->_allocator_object.construct(this->_end, val);
		this->_end++;
		this->_size++;
		// this->insert(this->end(), val);
	}
	
	template <class T, class A>
	void
	vector<T, A>::pop_back()
	{
		if ( this->_size == 0)
			return ;
		this->_allocator_object.destroy(--this->_end);
		this->_size--;
	}
	

	template <class T, class A>
	typename vector<T, A>::iterator
	vector<T, A>::insert(iterator position, const value_type & val)
	{
		difference_type	offset = ft::distance(this->begin(), position);
		if ( this->_size + 1 > this->_capacity )
			this->reserve(_doubleCapacity(this->_size + 1));

		pointer target_ptr = this->_end;
		position = this->begin() + offset;

		while (target_ptr > &(*position))
		{
			this->_allocator_object.construct(target_ptr, *(target_ptr - 1));
			this->_allocator_object.destroy(--target_ptr);
		}

		this->_allocator_object.construct(target_ptr, val);
		this->_end++;
		this->_size += 1;
		return (position);
	}

	template <class T, class A>
	void
	vector<T, A>::insert(iterator position, size_type n, const value_type & val)
	{
		const difference_type offset = ft::distance(this->begin(), position);
		
		if ( this->_size + n > this->_capacity )
			this->reserve(_doubleCapacity(this->_size + n));
		pointer construct_ptr = this->_end + n;
		pointer destroy_ptr = this->_end;
		position = this->begin() + offset;
		while ( destroy_ptr > &(*position) )
		{
			this->_allocator_object.construct(--construct_ptr, *(--destroy_ptr));
			this->_allocator_object.destroy(destroy_ptr);
		}
		while ( construct_ptr > &(*position) )
		{
			this->_allocator_object.construct(--construct_ptr, val);
		}
		this->_size += n;
		this->_end += n;
	}
	
	template <class T, class A>
	template <class InputIterator>
	void
	vector<T, A>::insert
	(
		iterator position,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
		InputIterator last
	)
	{
		const difference_type offset = ft::distance(this->begin(), position);
		const difference_type n = ft::distance(first, last);
		if ( this->_size + n > this->_capacity )
			this->reserve(_doubleCapacity(this->_size + n));
		pointer construct_ptr = this->_end + n;
		pointer destroy_ptr = this->_end;
		position = this->begin() + offset;
		while ( destroy_ptr != &*position )
		{
			this->_allocator_object.construct(--construct_ptr, *(--destroy_ptr));
			this->_allocator_object.destroy(destroy_ptr);
		}
		while ( construct_ptr != &*position )
			this->_allocator_object.construct(--construct_ptr, *(--last));
		this->_size += n;
		this->_end += n;
	}
	
	template <class T, class A>
	typename vector<T, A>::iterator
	vector<T, A>::erase(iterator position)
	{
		pointer target_ptr = &(*position);

		this->_allocator_object.destroy(target_ptr);
		while (target_ptr != this->_end)
		{
			this->_allocator_object.construct(target_ptr, *(target_ptr + 1));
			this->_allocator_object.destroy(++target_ptr);
		}
		this->_end--;
		this->_size--;
		return (position);
	}
	
	template <class T, class A>
	typename vector<T, A>::iterator
	vector<T, A>::erase(iterator first, iterator last)
	{
		pointer first_ptr = &(*first);
		pointer last_ptr = &(*last);
		const difference_type range = last_ptr - first_ptr;

		while (first_ptr != last_ptr)
			this->_allocator_object.destroy(first_ptr++);
		first_ptr = &(*first);
		while (last_ptr != this->_end)
			this->_allocator_object.construct(first_ptr++, *(last_ptr++));
		this->_size -= range;
		this->_end -= range;
		return (first);
	}
	
	template <class T, class A>
	void
	vector<T, A>::swap(vector & x)
	{
		if (*this == x)
			return ;
		
		allocator_type alloc_temp = x._allocator_object;
		pointer	start_temp = x._start;
		pointer end_temp = x._end;
		size_type size_temp = x._size;
		size_type capacity_temp = x._capacity;

		x._allocator_object = this->_allocator_object;
		x._start = this->_start;
		x._end = this->_end;
		x._size = this->_size;
		x._capacity = this->_capacity;

		this->_allocator_object = alloc_temp;
		this->_start = start_temp;
		this->_end = end_temp;
		this->_size = size_temp;
		this->_capacity = capacity_temp;
	}
	
	/*
		removes all elements from vector. leaving the container with size of 0
		☆ reallocation is NOT guarenteed
	*/
	template <class T, class A>
	void
	vector<T, A>::clear()
	{
		if (this->_start != this->_end)
		while (this->_start != this->_end)
			this->_allocator_object.destroy(--this->_end);
		this->_size = 0;
	}

	// Allocator
	template <class T, class A>
	typename vector<T, A>::allocator_type
	vector<T, A>::get_allocator() const
	{
		return (this->_allocator_object);
	}

	/***************
	 *   friend    *
	 ***************/

	template<class T, class A>
	bool operator==(const ft::vector<T, A> & lhs, const ft::vector<T, A> & rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}
	
	template<class T, class A>
	bool operator!=(const ft::vector<T, A> & lhs, const ft::vector<T, A> & rhs)
	{
		return ( !(lhs == rhs) );
	}
	
	template<class T, class A>
	bool operator<(const ft::vector<T, A> & lhs, const ft::vector<T, A> & rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	
	template<class T, class A>
	bool operator<=(const ft::vector<T, A> & lhs, const ft::vector<T, A> & rhs)
	{
		return ( !(rhs < lhs) );
	}
	
	template<class T, class A>
	bool operator>(const ft::vector<T, A> & lhs, const ft::vector<T, A> & rhs)
	{
		return ( rhs < lhs );
	}
	
	template<class T, class A>
	bool operator>=(const ft::vector<T, A> & lhs, const ft::vector<T, A> & rhs)
	{
		return ( !(lhs < rhs) );
	}
	
	template<class T, class A>
	void swap(ft::vector<T, A> & x, ft::vector<T, A> & y)
	{
		x.swap(y);
	}
} // namespace_ft

#endif // FT_VECTOR_HPP
