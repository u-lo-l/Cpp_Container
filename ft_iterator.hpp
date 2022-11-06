#ifndef FT_ITERATOR_HPP
# define FT_ITERATOR_HPP
# include <cstddef> // for ptrdiff_t

/*
	ft_iterator.hpp contains these followings
	A. Classes
		1. iterator class
		2. iteraits_traits class and it's specialization
		3. predefined iterators	-> only reverse_iterator is required.
			- reverse_iterator
		4. iterator tags	-> not required in ft_containers but interator_traits class needs these.
			- input_iterator_tag
			- output_iterator_tag
			- forward_iterator_tag
			- bidirectional_iterator_tag
			- random_access_iterator_tag
	B. Functions
		5. iterator operations	->	not required in ft_containers
			- advance()
			- distance()
		6. iterator generator	->	not required in ft_containers
			- back_inserter()
			- front_inserter()
			- inserter()
	Refernce : https://cplusplus.com/reference/iterator/
*/
namespace ft
{
	// 4. iterator_tags
	struct input_iterator_tag{};
	struct output_iterator_tag{};
	struct forward_iterator_tag : public input_iterator_tag{};
	struct bidirectional_iterator_tag : public forward_iterator_tag{};
	struct random_access_iterator_tag : public bidirectional_iterator_tag{};
	
	// 1. Iterator Class
	template <typename Category, 
				typename T,
				typename Distance = ptrdiff_t,
				typename Pointer = T*,
				typename Reference = T&>
	struct iterator
	{
		typedef	T			value_type;
		typedef	Distance	difference_type;
		typedef	Pointer		pointer;
		typedef	Reference	reference;
		typedef	Category	iterator_category;
	};

	// 2. Iterator traits class and it's specialization
	template<typename Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	// T* specialization
	template<typename T>
	struct iterator_traits<T*>
	{
		typedef ptrdiff_t					difference_type;
		typedef T							value_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	// const T* specialization : removed since C++20
	template<typename T>
	struct iterator_traits<const T*>
	{
		typedef ptrdiff_t					difference_type;
		typedef T							value_type;
		typedef const T*					pointer;
		typedef const T&					reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	/*
		3. reverse_iterator
			This class reverses the direction in which a bidirectional or randomaccess
			iterator iterates throngh a range.
	*/
	template <typename Iterator>
	class reverse_iterator : public iterator<typename iterator_traits<Iterator>::iterator_category,
											typename iterator_traits<Iterator>::value_type,
											typename iterator_traits<Iterator>::difference_type,
											typename iterator_traits<Iterator>::pointer,
											typename iterator_traits<Iterator>::reference>
	{
	public :
		// Member Types
		typedef Iterator												iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename iterator_traits<Iterator>::value_type			value_type;
		typedef typename iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename iterator_traits<Iterator>::reference			reference;
		typedef typename iterator_traits<Iterator>::pointer				pointer;
	protected :
		iterator_type current;
	public :
		// Member functions
		reverse_iterator()
		: current()
		{}
		explicit reverse_iterator(iterator_type it)
		: current(it)
		{}
		template <class Iter>
		reverse_iterator (const reverse_iterator<Iter> & rev_it)
		: current(rev_it.base())
		{}
		/*
			base :
				Returns a copy of the 'base iterator'.
				The 'base iterator' is an iterator of the same type as the one used to 
				construct the reverse_iterator.
		*/
		iterator_type base() const
		{
			return (this->current);
		}

		// operator reverse_iterator<const Iterator> () const
		// {
		// 	return (reverse_iterator<const Iterator>(this->current));
		// }

		/* 
			operator* :
				returns a reference to the pointed by iterator.
				decreases a copy of its base_iterator and returns the dereferencing it.
			반환 타입이 value_type인 경우, 외부에서 &*(vector.rbegin())과 같은 것이 컴파일 안된다.
			error msg: cannot take the address of an rvalue of type....
		*/
		reference operator*() const
		{
			iterator_type temp = this->current;
			temp--;
			return (*temp);
		}
		/*
			operator+ :
				Returns a 'reverse_iterator' pointing to the element located n positions away from the element the iterator currently points to.
				Applies the operator-() on the base_iterator and returns a reverse_iterator constructed with resulting iterator value.
		*/
		reverse_iterator operator+ (difference_type n) const
		{
			return (reverse_iterator(this->current - n));
		}

		reverse_iterator operator++ ()
		{
			// this->current -= 1;
			this->current--;
			return (*this);
		}

		reverse_iterator operator++ (int)
		{
			reverse_iterator temp = *this;
			++(*this);
			return (temp);
		}

		reverse_iterator operator+= (difference_type n)
		{
			this->current -= n;
			return (*this);
		}

		reverse_iterator operator- (difference_type n) const
		{
			return (reverse_iterator(this->current + n));
		}

		reverse_iterator operator-- ()
		{
			// this->current += 1;
			this->current++;
			return (*this);
		}

		reverse_iterator operator-- (int)
		{
			reverse_iterator temp = *this;
			--(*this);
			return (temp);
		}

		reverse_iterator operator-= (difference_type n)
		{
			this->current += n;
			return (*this);
		}

		pointer operator-> () const
		{
			return (&(operator*()));
		}
		/*
			operator[]
				Internally, the function accesses the proper element of its base iterator, returning the same as: base()[-n-1].
		*/
		reference operator[] (difference_type n) const
		{
			return (base()[-n - 1]);
		}

		// non-member function
		template <class Iter1, class Iter2>
		friend bool operator== (const reverse_iterator<Iter1> & lhs, const reverse_iterator<Iter2> & rhs)
		{ return (lhs.base() == rhs.base()); }

		template <class Iter1, class Iter2>
		friend bool operator!= (const reverse_iterator<Iter1> & lhs, const reverse_iterator<Iter2> & rhs)
		{ return (lhs.base() != rhs.base()); }

		template <class Iter1, class Iter2>
		friend bool operator<  (const reverse_iterator<Iter1> & lhs, const reverse_iterator<Iter2> & rhs)
		{ return (lhs.base() > rhs.base()); }

		template <class Iter1, class Iter2>
		friend bool operator<= (const reverse_iterator<Iter1> & lhs, const reverse_iterator<Iter2> & rhs)
		{ return (lhs.base() >= rhs.base()); }
    
		template <class Iter1, class Iter2>
		friend bool operator>  (const reverse_iterator<Iter1> & lhs, const reverse_iterator<Iter2> & rhs)
		{ return (lhs.base() < rhs.base()); }

		template <class Iter1, class Iter2>
		friend bool operator>= (const reverse_iterator<Iter1> & lhs, const reverse_iterator<Iter2> & rhs)
		{ return (lhs.base() <= rhs.base()); }

		template<class Iter>
		friend reverse_iterator operator+ ( difference_type n,	const reverse_iterator<Iter>& rev_it)
		{ return (rev_it + n); }

		template <class Iter1, class Iter2>
		friend difference_type operator- ( const reverse_iterator<Iter1> & lhs, const reverse_iterator<Iter2> & rhs)
		{ return (rhs.base() - lhs.base()); }
	};
	
	// // 5. Iterator operations
	template <class InputIterator, class Distance>
	void advance (InputIterator& it, Distance n)
	{
		for (int i = 0 ; i < n ; i++)
			it++;
	}

	template<class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
	distance (InputIterator first, InputIterator last)
	{
		if (first == last)
			return (0);
		typename ft::iterator_traits<InputIterator>::difference_type n = 0 ;
		InputIterator temp = first;
		while (temp != last)
		{
			temp++;
			n++;
		}
		return (n);
	}
}

#endif // FT_ITERATOR_HPP
