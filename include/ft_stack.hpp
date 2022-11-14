#ifndef FT_STACK_HPP
# define FT_STACK_HPP
# include "ft_vector.hpp"

namespace ft
{
	/***************
	 *    class    *
	 ***************/

	template <class T, class Container = ft::vector<T> >
	class stack
	{
	public :
		typedef Container	container_type;
		typedef	T			value_type;
		typedef size_t		size_type;
	/* protected member object */
	protected :
		container_type c;
	public :
		explicit stack ( const container_type & ctnr = container_type() );
		
		bool empty() const;
		
		size_type size() const;
		
		value_type & top();
		const value_type & top() const;

		void push( const value_type & val );

		void pop();

		template<class U, class D>
		friend bool operator==( const ft::stack<U, D> & lhs, const ft::stack<U, D> & rhs);
		template<class U, class D>
		friend bool operator!=( const ft::stack<U, D> & lhs, const ft::stack<U, D> & rhs);
		template<class U, class D>
		friend bool operator< ( const ft::stack<U, D> & lhs, const ft::stack<U, D> & rhs);
		template<class U, class D>
		friend bool operator<=( const ft::stack<U, D> & lhs, const ft::stack<U, D> & rhs);
		template<class U, class D>
		friend bool operator> ( const ft::stack<U, D> & lhs, const ft::stack<U, D> & rhs);
		template<class U, class D>
		friend bool operator>=( const ft::stack<U, D> & lhs, const ft::stack<U, D> & rhs);
	};

	/***************
	 *   public    *
	 ***************/
	
	template <class T, class C>
	stack<T, C>::stack(const container_type & contiainer)
	: c(contiainer)
	{}

	template <class T, class C>
	bool
	stack<T, C>::empty() const
	{
		return (this->c.empty());
	}


	template <class T, class C>
	typename stack<T,C>::size_type
	stack<T, C>::size() const
	{
		return (this->c.size());
	}

	template <class T, class C>
	typename stack<T,C>::value_type &
	stack<T, C>::top()
	{
		return (this->c.back());
	}

	template <class T, class C>
	const typename stack<T,C>::value_type &
	stack<T, C>::top() const
	{
		return (this->c.back());
	}

	template <class T, class C>
	void
	stack<T, C>::push( const value_type & val)
	{
		this->c.push_back(val);
	}

	template <class T, class C>
	void
	stack<T, C>::pop()
	{
		this->c.pop_back();
	}

	/***************
	 *   friend    *
	 ***************/

	template <class T, class C>
	bool operator== (const stack<T,C>& lhs, const stack<T,C>& rhs)
	{
		return (lhs.c == rhs.c);
	}
 
	template <class T, class C>
	bool operator!= (const stack<T,C>& lhs, const stack<T,C>& rhs)
	{
		return (lhs.c != rhs.c);
	}

	template <class T, class C>
	bool operator< (const stack<T,C>& lhs, const stack<T,C>& rhs)
	{
		return (lhs.c < rhs.c);
	}

	template <class T, class C>
	bool operator<= (const stack<T,C>& lhs, const stack<T,C>& rhs)
	{
		return (lhs.c <= rhs.c);
	}

	template <class T, class C>
	bool operator> (const stack<T,C>& lhs, const stack<T,C>& rhs)
	{
		return (lhs.c > rhs.c);
	}

	template <class T, class C>
	bool operator>= (const stack<T,C>& lhs, const stack<T,C>& rhs)
	{
		return (lhs.c >= rhs.c);
	}
} // namespace ft
#endif
