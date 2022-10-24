#include <iostream>


/*
	
*/
namespace ft
{
	enum Color {RED = 0, BLACK = 1};

	template < class T >
	class RBtreeNode
	{
	private:
		typedef	T					value_type;
		typedef	struct RBtreeNode	node_type;
		enum Color					_color;
		T							_data;
		RBtreeNode	*_pLeftChild;
		RBtreeNode	*_pRightChild;
		RBtreeNode	*_pParent;
		RBtreeNode()
		: _color(ft::BLACK), _pLeftChild(NULL), _pRightChild(NULL), _pParent(NULL)
		{}
		template<class U, class Alloc> friend class RBtree;
		RBtreeNode ( 
			T data , 
			RBtreeNode * pleft = NULL,
			RBtreeNode * pright = NULL,
			RBtreeNode * pparent = NULL,
			Color color = RED)
		: _data(data), _color(color), _pLeftChild(pleft), _pRightChild(pright), _pParent(pparent)
		{}
		RBtreeNode ( const RBtreeNode & other)
		: _data(other._data), _color(other._color), _pLeftChild(other._pLeftChild), _pRightChild(other._pRightChild), _pParent(other._pParent)
		{}
		RBtreeNode & operator= (const RBtreeNode & other)
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

		bool _isNilNode()
		{
			if (this->_color == ft::BLACK && this->_pLeftChild == NULL \
				&& this->_pRightChild == NULL && this->_pParent == NULL)
				return (true);
			return (false);
		}
		
		const T & getData() const { return (this->_data); }

		enum Color getColor() const { return (_color); }

		void setColor(enum Color color) { this->_color = color; }

		bool operator== (const RBtreeNode & other) const { return (this->_data == other._data); }

		bool operator!= (const RBtreeNode & other) const { return (this->_data != other._data); }

	public :
			~RBtreeNode() {}
		friend std::ostream & operator<< ( std::ostream & os, const RBtreeNode & node)
		{
			if (node.getColor() == RED)
				os << "\033[1;107;91m";
			else
				os << "\033[1;107;30m";
			os << "\t data   : " << node.getData() << "\033[0m" << std::endl;
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
