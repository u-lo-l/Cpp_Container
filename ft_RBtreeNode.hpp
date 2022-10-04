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
	public :
		template<class U> friend class RBtree;
		RBtreeNode ( T data , RBtreeNode * pParent = NULL)
		: _data(data), _color(RED), _pLeftChild(NULL), _pRightChild(NULL), _pParent(pParent)
		{}
		RBtreeNode ( const RBtreeNode & other)
		: _data(other.data), _color(other.RED), _pLeftChild(other._pLeftChild), _pRightChild(other._pRightChild), _pParent(other._pParent)
		{}
		RBtreeNode operator= (const RBtreeNode & other)
		{
			if (this == &other)
				return (*this);
			return (RBtreeNode(other));
		}
		~RBtreeNode() {}

		const T & getData() const { return (this->_data); }

		enum Color getColor() const { return (_color); }

		void setColor(enum Color color) { this->_color = color; }

		bool operator== (const RBtreeNode & other) const { return (this->_data == other._data); }

		bool operator!= (const RBtreeNode & other) const { return (this->_data != other._data); }

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
} // namespace ft