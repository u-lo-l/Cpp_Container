#include <memory>

#include "ft_RBtreeNode.hpp"
namespace ft
{
	template <class T>
	bool lessthan(const T & a, const T & b) { return (a < b); }

	template < class T >
	class RBtree
	{
	private :
		typedef RBtreeNode * NodePtr;
		/* private members */
		const static NodePtr _nilnode = NULL;
		NodePtr	_pRoot;
		
		/* private method */
		// utils
		bool	_isNilNode(NodePtr pNode) {return (pNode == _nilnode);}
		bool	_isRootNode(NodePrt pNode) {return (pNode->_pParent == NULL);}
		// rotation
		void	_rotateLeft(NodePtr pPivotNode)
		{
			NodePrt x = pPivotNode;
			NodePtr	y = x->_pRightChild;
			// 1. move y's left_tree to x's right
			x->_pRightChild = y->_pleftChild;
			// 2. change y's left_tree's root's parent to x (if root is no NULL)
			if (_isNilNode(y->_pleftChild) == false)
				y->_pleftChild->_pParent = x;
			// 3. set y's parent to x's one
			y->parent = x->parent;
			// 4. change parent's child
			if (_isRootNode(x) == true)
				this->_pRoot = y;
			else if (x == x->_pParent->_pleftChild)
				x->_pParent->_pleftChild = y;
			else 
				x->_pParent->_pRightChild = y;
			// 5. set x to y's left child
			y->_pleftChild = x;
			// 6. set x's parent to y
			x->_pParent = y;
		}
		void	_rotateRight(NodePtr pPivotNode)
		{
			NodePrt x = pPivotNode;
			NodePrt y = x->_pleftChild;
		}
		// search_helpers
		NodePtr _searchHelper(NodePtr node, T key)
		{
			if (_isNilNode(node) || node->getData() == key)
				return (node);
			if (key < node->getData())
				return (_searchHelper(node->_pleftChild, key));
			return (_searchHelper(node->_pRightChild, key));
		}
		// insert_helpers
		// delete_helpers
	public :
		//(constructor)
		RBtree( void ) :_pRoot(NULL) {}
		RBtree( const RBtree & other );
		RBtree & operator=( const RBtree & other );
		//(destructor)
		~RBtree();

		//member functions
		NodePtr searach(const T & key)
		{
			return (_searchHelper(this->_pRoot, key));
		}
		NodePtr insertNode(T value);
		NodePtr insertNode(NodePtr pNode);
		void deleteNode(T value);
		void deleteNode(NodePtr pNode);

		/*non_member function*/
		friend ostream & operator<<( ostream & os, const RBtree & tree );
	}; // class RBtree

} // namespace ft