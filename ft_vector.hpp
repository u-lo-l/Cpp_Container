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

/*
	ft_vector.hpp contains these followings
	A. Classes
		- vector
		- vector<bool> -> not required in ft_containers
	B. Functions
		- begin()
		- end()
*/
namespace ft
{
	/*
		ft::vector class contains these followings
		generic form : template < class T, class Alloc = allocator<T> > class vector;
		A. Member Types
			- value_type
			- allocator_type
			- reference
			- const_reference
			- pointer
			- const_pointer
			- iterator
			- const_iterator
			- reverse_iterator
			- const_reverse_iterator
			- differnce_type
			- size_type
		B. Member Functions
			- (constructor)
			- (destructor)
			- operator=
		C. Iterator
			- begin()
			- end()
			- rbegin()
			- rend()
		D. Capacity
			- size()
			- max_size()
			- resize()
			- capacity()
			- empty()
			- reserve()
		E. Element access
			- operator[]
			- at()
			- front()
			- back()
		F. Modifiers
			- assign()
			- push_back()
			- pop_back()
			- insert()
			- erase()
			- swap()
			- clear()
		G. Allocator
			- get_allocator()
		H. Non-member function overloads
			- (relational operators)
			- swap()
	*/
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
		typedef ft::vectorIterator<value_type> 				iterator;
		typedef ft::vectorIterator<const value_type>		const_iterator;
		typedef typename allocator_type::size_type			size_type;
		typedef typename allocator_type::difference_type	difference_type;
		typedef ft::reverse_iterator<iterator> 				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> 		const_reverse_iterator;
	
	private :
		allocator_type	_allocator_object;
		pointer			_start;
		pointer			_end;
		size_type		_size;
		size_type		_capacity;
		size_type		_doubleCapacity( size_type new_capacity )
		{
			if (new_capacity < this->_capacity)
			{
				return (this->_capacity);
			}
			if (this->_capacity * 2 < new_capacity)
			{
				return (new_capacity);
			}
			if (this->max_size() < this->_capacity * 2)
			{
				return (this->max_size());
			}
			else
			{
				return (this->_capacity * 2);
			}
		}
	public :
		// B. Member Functions
		// default constructor
		explicit vector (const allocator_type & alloc = allocator_type())
		: _allocator_object(alloc), _start(NULL), _end(NULL), _size(0), _capacity(0)
		{
			this->_start = this->_allocator_object.allocate(1);
			this->_end = this->_start;
		}
		// fill constructor
		explicit vector (size_type n,
						const value_type & val = value_type(),
						const allocator_type & alloc = allocator_type())
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
		// range constructor
		template <class InputIterator>
		vector (typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
				InputIterator last,
				const allocator_type & alloc = allocator_type() )
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
		// copy constructor
		vector (const vector & x)
		: _allocator_object(Alloc()), _size(0), _capacity(x._capacity)
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
		~vector()
		{
			this->clear();
			if (this->_start != NULL)
				this->_allocator_object.deallocate(this->_start, this->_capacity);
		}

		vector & operator= (const vector & x)
		{
			if (this == &x)
				return (*this);
			this->assign(x.begin(), x.end());
			return (*this);
		}
		
		// iterators
		iterator begin() { return (iterator(this->_start)); }
		const_iterator begin() const { return (const_iterator(this->_start)); }
		iterator end() { return (iterator(this->_end)); }
		const_iterator end() const { return (const_iterator(this->_end)); }

		reverse_iterator rbegin() { return (reverse_iterator(this->_end)); }
		const_reverse_iterator rbegin() const { return (const_reverse_iterator(this->_end)); }
		reverse_iterator rend() { return (reverse_iterator(this->_start)); }
		const_reverse_iterator rend() const { return (const_reverse_iterator(this->_start)); }
		
		
		// Capacity
		size_type size() const
		{
			return (this->_size);
		}
		size_type max_size() const
		{
			return (this->_allocator_object.max_size());
		}
		void resize(size_type n, value_type val = value_type())
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

		size_type capacity() const
		{
			return (this->_capacity);
		}

		bool empty() const
		{
			return (static_cast<bool>(!this->_size));
		}
		/*
			reserve()
			request a change in capacity
			if n > this->_capacity : reallocate it's storage capacity to n
		*/
		void reserve(size_type new_capacity)
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
		reference operator[](size_type n)
		{
			return (*(this->_start + n));
		}
		const_reference operator[](size_type n) const
		{
			return (*(this->_start + n));
		}
		reference at(size_type n)
		{
			if (n >= this->_size)
				throw std::out_of_range("ft::vector : at() Out of range");
			return (*(this->_start + n));
		}
		const_reference at(size_type n) const
		{
			if (n >= this->_size)
				throw std::out_of_range("ft::vector : const at() Out of range");
			return (*(this->_start + n));
		}
		reference front()
		{
			return (*(this->_start));
		}
		const_reference front() const
		{
			return (*(this->_start));
		}
		reference back()
		{
			return (*(this->_end - 1));
		}
		const_reference back() const
		{
			return (*(this->_end - 1));
		}

		// Modifiers
		/*
			assign : Assigns new contents to the vector, replacing its cuurent contents and modifying its size
			 ☆ This causes an automatic reallocation of the storage if the size of new vector surpassess the current capacity.
		*/
		template <class InputIterator>
		void
		assign
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
		void assign(size_type n, const value_type & val)
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
		
		void push_back(const value_type & val)
		{
			if ( this->_size == this->_capacity )
				this->reserve(_doubleCapacity(this->_capacity + 1));
			this->_allocator_object.construct(this->_end, val);
			this->_end++;
			this->_size++;
			// this->insert(this->end(), val);
		}
		
		void pop_back()
		{
			if ( this->_size == 0)
				return ;
			this->_allocator_object.destroy(--this->_end);
			this->_size--;
		}
		

		iterator insert(iterator position, const value_type & val)
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

		void insert(iterator position, size_type n, const value_type & val)
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
		
		// 현재 insert의 문제 : 새로운 데이터 공간을 만드는 도중에 실패가 발생하면 망한다.
		template <class InputIterator>
		void
		insert
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
		
		iterator erase(iterator position)
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
		iterator erase(iterator first, iterator last)
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
		
		void swap(vector & x)
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
		void clear()
		{
			if (this->_start != this->_end)
			while (this->_start != this->_end)
				this->_allocator_object.destroy(--this->_end);
			this->_size = 0;
		}

		// Allocator
		allocator_type get_allocator() const
		{
			return (this->_allocator_object());
		}

		// C. Non-member Functions

		friend bool operator==(const ft::vector<T, Alloc> & lhs, const ft::vector<T, Alloc> & rhs)
		{
			if (lhs.size() != rhs.size())
				return (false);
			return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		}
		friend bool operator!=(const ft::vector<T, Alloc> & lhs, const ft::vector<T, Alloc> & rhs)
		{
			return ( !(lhs == rhs) );
		}
		friend bool operator<(const ft::vector<T, Alloc> & lhs, const ft::vector<T, Alloc> & rhs)
		{
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}
		friend bool operator<=(const ft::vector<T, Alloc> & lhs, const ft::vector<T, Alloc> & rhs)
		{
			// return ( !(rhs < lhs) );
			bool res = ( ( lhs < rhs ) || ( lhs == rhs ) );
			return res;
		}
		friend bool operator>(const ft::vector<T, Alloc> & lhs, const ft::vector<T, Alloc> & rhs)
		{
			return ( rhs < lhs );
		}
		friend bool operator>=(const ft::vector<T, Alloc> & lhs, const ft::vector<T, Alloc> & rhs)
		{
			// return ( !(lhs < rhs) );
			bool res = ( ( lhs > rhs ) || ( lhs == rhs ) );
			return res;
		}
		friend void swap(const ft::vector<T, Alloc> & x, const ft::vector<T, Alloc> & y)
		{
			x.swap(y);
		}
	}; // class vector

} // namespace_ft

#endif // FT_VECTOR_HPP
