#include <ostream>


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
		friend template<class U> class RBtree;
		RBtreeNode ( T data , RBtreeNode * pParent = NULL)
		: _data(data), _color(RED), _pleftChild(NULL), _pRightChild(NULL), _pParent(pParent)
		{}
		RBtreeNode ( const RBtreeNode & other)
		: _data(other.data), _color(other.RED), _pleftChild(other._pleftChild), _pRightChild(other._pRightChild), _pParent(other._pParent)
		{}
		RBtreeNode & operatpor= (const RBtreeNode & other)
		{
			if (this == &other)
				return (*this);
			return (RBtreeNode(other));
		}
		~RBtreeNode() {};

		const T & getData() const { return (this->_data); }

		enum Color getColor() const { return (_color); }

		void setColor(enum Color color) { this->_color = color; }

		bool operator== (const RBtreeNode & other) const { return (this->_data == other._data); }

		bool operator!= (const RBtreeNode & other) const { return (this->_data != other._data); }

		friend ostream & operator<< ( ostream & os, const RBtreeNode & node)
		{
			if (node.getColor() == RED)
				os << "\033[1;107;91m"
			else
				os << "\033[1;107;30m"
			os << node.data << "\033[0m";
			return (os);
		}
	};
}