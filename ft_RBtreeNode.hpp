#ifndef FT_RBTREENODE_HPP
# define FT_RBTREENODE_HPP
# include <iostream>

namespace ft
{
	enum Color {RED = 0, BLACK = 1};

	template < class T >
	class RBtreeNode
	{
	private:
		typedef	T				value_type;
		typedef	RBtreeNode<T>	node_type;
		typedef	RBtreeNode<T> *	node_pointer;

		template<class U, class Alloc, class Comp>
		friend class RBtree;
		template<class U>
		friend class tree_iterator;

		bool			_isnil;
		enum Color		_color;
		value_type		_data;
		node_pointer	_pLeftChild;
		node_pointer	_pRightChild;
		node_pointer	_pParent;
		RBtreeNode()
		: _isnil(true), _color(ft::BLACK), _pLeftChild(NULL), _pRightChild(NULL), _pParent(NULL)
		{}

		RBtreeNode<T> & operator= (const RBtreeNode<T> & other)
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

		bool _isNilNode() const
		{
			if (_isnil == true)
				return (true);
			return (false);
		}

		enum Color getColor() const { return (_color); }
		
		void setColor(enum Color color) { this->_color = color; }
		
		bool operator== (const RBtreeNode & other) const { return (this->_data == other._data); }

		bool operator!= (const RBtreeNode & other) const { return (this->_data != other._data); }


	public :
		
		const T & getData() const { return (this->_data); }

		node_pointer _maximum()
		{
			node_pointer pResult = this;
			if (pResult->_isNilNode() == true)
				return (pResult);
			while (pResult->_pRightChild->_isNilNode() == false)
				pResult = pResult->_pRightChild;
			return (pResult);
		}	
		node_pointer _minimum()
		{
			node_pointer pResult = this;
			if (pResult->_isNilNode() == true)
				return (pResult);
			while (pResult->_pLeftChild->_isNilNode() == false)
				pResult = pResult->_pLeftChild;
			return (pResult);
		}
		
		RBtreeNode ( 
			T data , 
			RBtreeNode * pleft = NULL,
			RBtreeNode * pright = NULL,
			RBtreeNode * pparent = NULL,
			Color color = RED)
		: 	_isnil(false),
			_color(color),
			_data(data),
			_pLeftChild(pleft),
			_pRightChild(pright),
			_pParent(pparent)
		{}
		RBtreeNode ( const RBtreeNode & other )
		:	_isnil(other._isnil),
			_color(other._color),
			_data(other._data),
			_pLeftChild(other._pLeftChild),
			_pRightChild(other._pRightChild),
			_pParent(other._pParent)
		{}
		~RBtreeNode() {}

		friend std::ostream & operator<< ( std::ostream & os, const RBtreeNode & node)
		{
			if (node.getColor() == RED)
				os << "\033[1;107;91m";
			else
				os << "\033[1;107;30m";
			if (node._isNilNode() == true)
				os << "\t 'nil_node'" << std::endl;
			os << "\t data   : " << node.getData().first << "\033[0m" << std::endl;
			os << "\t parent : " << (node._pParent) << std::endl;
			os << "\t left   : " << (node._pLeftChild) << std::endl;
			os << "\t right  : " << (node._pRightChild) << std::endl;
			return (os);
		}
	}; // class RBtreeNode

	template <class T>
	Color getColor(typename ft::RBtreeNode<T>::node_type * pNode)
	{
		if(!pNode)
			return (ft::BLACK);
		return (pNode->getColor());
	}

	template <class T>
	void swap( ft::RBtreeNode<T> & node1, ft::RBtreeNode<T> & node2)
	{
		ft::RBtreeNode<T> temp = node1;
		node1 = node2;
		node2 = temp;
	}

	template <class T>
	void swap( ft::RBtreeNode<T> * pnode1, ft::RBtreeNode<T> * pnode2)
	{
		ft::RBtreeNode<T> * temp = pnode1;
		pnode1 = pnode2;
		pnode2 = temp;
	}
} // namespace ft
#endif