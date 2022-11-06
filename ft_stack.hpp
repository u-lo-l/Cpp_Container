#ifndef FT_STACK_HPP
# define FT_STACK_HPP
# include "ft_vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
	public :
		typedef Container	container_type;
		typedef	T			value_type;
		typedef size_t		size_type;
	private :
		container_type _cont;
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

	template <class T, class C>
	stack<T, C>::stack(const container_type & c)
	: _cont(c)
	{}

	template <class T, class C>
	bool
	stack<T, C>::empty() const
	{
		return (this->_cont.empty());
	}


	template <class T, class C>
	typename stack<T,C>::size_type
	stack<T, C>::size() const
	{
		return (this->_cont.size());
	}

	template <class T, class C>
	typename stack<T,C>::value_type &
	stack<T, C>::top()
	{
		return (this->_cont.back());
	}

	template <class T, class C>
	const typename stack<T,C>::value_type &
	stack<T, C>::top() const
	{
		return (this->_cont.back());
	}

	template <class T, class C>
	void
	stack<T, C>::push( const value_type & val)
	{
		this->_cont.push_back(val);
	}

	template <class T, class C>
	void
	stack<T, C>::pop()
	{
		this->_cont.pop_back();
	}

	template <class T, class C>
	bool operator== (const stack<T,C>& lhs, const stack<T,C>& rhs)
	{
		return (lhs._cont == rhs._cont);
	}
 
	template <class T, class C>
	bool operator!= (const stack<T,C>& lhs, const stack<T,C>& rhs)
	{
		return (lhs._cont != rhs._cont);
	}

	template <class T, class C>
	bool operator< (const stack<T,C>& lhs, const stack<T,C>& rhs)
	{
		return (lhs._cont < rhs._cont);
	}

	template <class T, class C>
	bool operator<= (const stack<T,C>& lhs, const stack<T,C>& rhs)
	{
		return (lhs._cont <= rhs._cont);
	}

	template <class T, class C>
	bool operator> (const stack<T,C>& lhs, const stack<T,C>& rhs)
	{
		return (lhs._cont > rhs._cont);
	}

	template <class T, class C>
	bool operator>= (const stack<T,C>& lhs, const stack<T,C>& rhs)
	{
		return (lhs._cont >= rhs._cont);
	}
} // namespace ft
#endif
