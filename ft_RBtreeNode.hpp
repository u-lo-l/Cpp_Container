#ifndef FT_RBTREENODE_HPP
# define FT_RBTREENODE_HPP
# include <iostream>

namespace ft
{
	enum Color {RED = 0, BLACK = 1};

	/***************
	 *    class    *
	 ***************/

	template < class T >
	class RBtreeNode
	{
	private:
		typedef	T				value_type;
		typedef	RBtreeNode<T>	node_type;
		typedef	RBtreeNode<T> *	node_pointer;

		template<class U, class SK, class Alloc, class Comp>
		friend class RBtree;
		template<class U, class Ptr, class Ref>
		friend class tree_iterator;

		node_pointer	_pLeftChild;
		node_pointer	_pRightChild;
		node_pointer	_pParent;

		value_type		_data;
		enum Color		_color;
		bool			_isnil;

		RBtreeNode();

		RBtreeNode<T> & operator= (const RBtreeNode<T> & other);

		enum Color getColor() const;
		
		void setColor(enum Color color);
		
		bool operator== (const RBtreeNode & other) const;

		bool operator!= (const RBtreeNode & other) const;

		T & getData();

		bool isNilNode() const;
		
	public :
	
		RBtreeNode
		( 
			T data , 
			RBtreeNode * pleft = NULL,
			RBtreeNode * pright = NULL,
			RBtreeNode * pparent = NULL,
			Color color = RED
		);

		RBtreeNode ( const RBtreeNode & other );
		
		~RBtreeNode();

		node_pointer _maximum();

		node_pointer _minimum();

		template<class U>
		friend std::ostream & operator<< ( std::ostream & os, const RBtreeNode<U> & node);
	}; // class RBtreeNode

	/***************
	 *   private   *
	 ***************/

	template <class T>
	RBtreeNode<T>::RBtreeNode()
	: _pLeftChild(NULL), _pRightChild(NULL), _pParent(NULL), _color(ft::BLACK), _isnil(true)
	{}

	template <class T>
	RBtreeNode<T> & 
	RBtreeNode<T>::operator= (const RBtreeNode<T> & other)
	{
		if (this == &other)
			return (*this);
		this->_data = other._data;
		this->_color = other._color;
		this->_pLeftChild = other._pLeftChild;
		this->_pRightChild = other._pRightChild;
		this->_pParent = other._pParent;
		return (*this);
	}

	template <class T>
	enum Color 
	RBtreeNode<T>::getColor() const
	{
		return (_color);
	}
	
	template <class T>
	void 
	RBtreeNode<T>::setColor(enum Color color)
	{
		this->_color = color;
	}
	
	template <class T>
	bool 
	RBtreeNode<T>::operator== (const RBtreeNode & other) const
	{
		return (this->_data == other._data);
	}

	template <class T>
	bool 
	RBtreeNode<T>::operator!= (const RBtreeNode & other) const 
	{
		return (this->_data != other._data);
	}

	template <class T>
	T &
	RBtreeNode<T>::getData()
	{
		return (this->_data);
	}

	template <class T>
	bool
	RBtreeNode<T>::isNilNode() const
	{
		if (_isnil == true)
			return (true);
		return (false);
	}

	/***************
	 *   public    *
	 ***************/

	template <class T>
	RBtreeNode<T>::RBtreeNode
	( 
		T data , 
		RBtreeNode * pleft,
		RBtreeNode * pright,
		RBtreeNode * pparent,
		Color color
	)
	:	_pLeftChild(pleft),
		_pRightChild(pright),
		_pParent(pparent),
		_data(data),
		_color(color),
		_isnil(false)
	{}

	template <class T>
	RBtreeNode<T>::RBtreeNode ( const RBtreeNode & other )
	:	_pLeftChild(other._pLeftChild),
		_pRightChild(other._pRightChild),
		_pParent(other._pParent),
		_data(other._data),
		_color(other._color),
		_isnil(other._isnil)
	{}

	template <class T>
	RBtreeNode<T>::~RBtreeNode()
	{}
	
	template <class T>
	typename RBtreeNode<T>::node_pointer
	RBtreeNode<T>::_maximum()
	{
		node_pointer pResult = this;
		if (pResult->isNilNode() == true)
			return (pResult);
		while (pResult->_pRightChild->isNilNode() == false)
			pResult = pResult->_pRightChild;
		return (pResult);
	}	

	template <class T>
	typename RBtreeNode<T>::node_pointer
	RBtreeNode<T>::_minimum()
	{
		node_pointer pResult = this;
		if (pResult->isNilNode() == true)
			return (pResult);
		while (pResult->_pLeftChild->isNilNode() == false)
			pResult = pResult->_pLeftChild;
		return (pResult);
	}

	/***************
	 *   friend    *
	 ***************/

	template <class T>
	std::ostream & operator<< ( std::ostream & os , const RBtreeNode<T> & node)
	{
		if (node.getColor() == RED)
			os << "\033[1;107;91m";
		else
			os << "\033[1;107;30m";
		if (node.isNilNode() == true)
			os << "\t 'nil_node'" << std::endl;
		os << "\t data   : " << node._data << "\033[0m" << std::endl;
		os << "\033[0m" << "\t parent : " << (node._pParent) << std::endl;
		os << "\t left   : " << (node._pLeftChild) << std::endl;
		os << "\t right  : " << (node._pRightChild) << std::endl;
		return (os);
	}

} // namespace ft
#endif
