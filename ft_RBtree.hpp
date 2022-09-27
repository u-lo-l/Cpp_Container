#include <memory>
#include <exception>

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
		bool	_isLeafNode(NodePrt pNode) {return (_isNilNode(pNode->_pLeftChild) && _isNilNode(pNode->_pRightChild));}
		// rotation
		void	_rotateLeft(NodePtr pPivotNode);
		void	_rotateRight(NodePtr pPivotNode);
		// search_helpers
		NodePtr _searchHelper(NodePtr pNode, T key);
		// insert_helpers
		void _BStreeInsert(NodePtr pNode, T key);
		void _insertRestructor(NodePtr pPivot);
		// delete_helpers
		NodePtr _getSuccessor(NodePtr pNode);
		void _transplant(NodePtr pNode, NodePtr pSuccessor); // change targetnode and successor for delete targetnode
		void _BStreeDelete(NodePtr pNode, T key);
		void _deleteRestructor(NodePtr pPivot);
	public :
		//(constructor)
		RBtree( void ) :_pRoot(NULL) {}
		RBtree( const RBtree & other );
		RBtree & operator=( const RBtree & other );
		//(destructor)
		~RBtree();

		//member functions
		NodePtr searach(const T & key) { return (_searchHelper(this->_pRoot, key)); }
		void insertNode(T key);
		void deleteNode(T key);

		/*non_member function*/
		friend ostream & operator<<( ostream & os, const RBtree & tree );
	}; // class RBtree

	template< class T >
	typename RBtree<T>::NodePtr RBtree<T>::_searchHelper(typename RBtree<T>::NodePtr node, T key)
	{
		if (_isNilNode(node) || node->getData() == key)
			return (node);
		if (key < node->getData())
			return (_searchHelper(node->_pLeftChild, key));
		return (_searchHelper(node->_pRightChild, key));
	}

	template< class T >
	void RBtree<T>::_rotateLeft( typename RBtree<T>::NodePtr pPivotNode )
	{
		/*
			1. move y's left_tree to x's right
			2. change y's left_tree's root's parent to x (if root is no NULL)
			3. set y's parent to x's one
			4. change parent's child
			5. set x to y's left child
			6. set x's parent to y
		*/
		NodePtr x = pPivotNode;
		NodePtr	y = x->_pRightChild;
		
		x->_pRightChild = y->_pLeftChild;
		
		if (_isNilNode(y->_pLeftChild) == false)
			y->_pLeftChild->_pParent = x;
		
		y->_pParent = x->_pParent;
		
		if (_isRootNode(x) == true)
			this->_pRoot = y;
		else if (x == x->_pParent->_pLeftChild)
			x->_pParent->_pLeftChild = y;
		else 
			x->_pParent->_pRightChild = y;
		
		y->_pLeftChild = x;
		
		x->_pParent = y;
	}

	template< class T >
	void RBtree<T>::_rotateRight( typename RBtree<T>::NodePtr pPivotNode )
	{
		NodePtr x = pPivotNode;
		NodePtr y = x->_pLeftChild;

		x->_pLeftChild = y->_pRightChild;
		if (_isNilNode(y->_pRightChild) == false)
			y->_pRightChild->_pParent = x;
		y->_pParent = x->_pParent;
		if (_isRootNode(x) == true)
			this->_pRoot = y;
		else if (x == x->_pParent->_pLeftChild)
			x->_pParent->_pLeftChild = y;
		else 
			x->_pParent->_pRightChild = y;
		y->_pRightChild = x;
		x->_pParent = y;
	}

	template< class T >
	void RBtree<T>::insertNode(T key)
	{
		if (this->_pRoot == NULL)
			_pRoot = new RBtreeNode<T>(key);
		else
			_BStreeInsert(this->_pRoot, key);
		this->_pRoot->setColor(BLACK);
	}

	template< class T >
	void RBtree<T>::_BStreeInsert( typename RBtree<T>::NodePtr pNode, T key )
	{
		if (key == pNode.getData())
			throw std::exception();
		else if (key < pNode.getData())
		{
			if (this->_isNilNode(pNode->_pLeftChild) == true)
			{
				pNode->_pLeftChild = new RBtreeNode<T>(key, pNode);
				_insertRestructor(pNode->_pLeftChild);
			}
			else
				_BStreeInsert(pNode->_pLeftChild, key);
		}
		else
		{
			if (this->_isNilNode(pNode->_pRightChild) == true)
			{
				pNode->_pRightChild = new RBtreeNode<T>(key, pNode);
				_insertRestructor(pNode->_pRightChild);
			}
			else
				_BStreeInsert(pNode->_pRightChild, key);
		}
	}

	template< class T >
	void RBtree<T>::_insertRestructor( typename RBtree<T>::NodePtr pKeyNode )
	{
		/*
		 *  K : target_node. P : parent_node. U : uncle_node.(sibling of P) G : grand_parenent_node. S : sibling
		 *	1. tree is empty
		 *	2. K's parent( = P ) is black (this case doesnt violate rbtree properties)
		 *	3. (!) P is red_node
		 *		3.1 : U is red (U : Uncle node)
		 *		3.2 : U is black or nilNode
		 *			3.2.1: P is rightchild of G and K is right child of P => leftRotate->recolor
		 *			3.2.2: P is rightchild of G and K is left child of P => rightRotate-> case 3.2.1
		 *			3.2.3: P is leftchild of G and K is left child of P => mirror of case 3.2.1 : RightRotate->recolor
		 *			3.2.4: P is leftchild of G and K is left child of P => mirror of case 3.2.2 : leftRotate -> 3.2.3
		*/
		NodePtr K = pKeyNode;
		NodePtr P = K->_pParent;
		if (_isNilNode(P) || P->getColor() == BLACK)
			return ;
		NodePtr	G = P->_pParent;
		NodePtr U;
		while (P->getColor() == RED)
		{
			if (P == G->_pRightChild)
			{
				U = G->_pRightChild;
				if (U->getColor() == RED) // 3.1
				{
					P->setColor(BLACK);
					U->setColor(BLACK);
					G->setColor(RED);
					K = G; // update target Node for next iteration
				}
				else
				{
					if (K = P->_pRightChild)
						_rotateLeft(P); // 3.2.2 K becomes P's Parent
					_rotateRight(G)	// 3.2.1
					G->setColor(RED);
					P->setColor(BLACK);
					K = P; // update target Node for next iteration
				}
			}
			else
			{
				U = G->_pLeftChild;
				if (U->getColor() == RED) // 3.1
				{
					P->setColor(BLACK);
					U->setColor(BLACK);
					G->setColor(RED);
					K = G;
				}
				else
				{
					if (K = P->_pLeftChild)
						_rotateRight(P); // 3.2.4 K becomes P's Parent
					_rotateLeft(G)	// 3.2.3
					G->setColor(RED);
					P->setColor(BLACK);
					K = P; // update target Node for next iteration
				}
			}
		}
	}

	template< class T >
	typename RBtree<T>::NodePtr	RBtree<T>::_getSuccessor( typename RBtree<T>::NodePtr pNode )
	{
		NodePtr successor;

		if (_isNilNode(pNode->_pleftChild) == true) // pNode is leafnode or just have rightchild
			successor = pNode->_pRightChild;
		else if (_isNilNode(pNode->_pRightChild) == true) // pNode just have leftChild
			successor = pNode->_pLeftChild;
		else										// pNode both have left and right child;
		{
			successor = pNode->_pRightChild;
			while (_isNilNode(successor->_pLeftChild) == false)
				successor = successor->_pLeftChild;
		}
		return (successor);
	}

	template< class T >
	void RBtree<T>::_BStreeDelete( typename RBtree<T>::NodePtr pNode , T key )
	{
		NodePtr targetNode = RBtree<T>::_nilnode;
		NodePtr K = pNode;
		while (!_isNilNode(K))
		{
			if (K->getData() == key) 
			{
				targetNode = K;
				break;
			}
			if (K->getData() <= key)
				K = K->_pRightChild;
			else
				K = K->_pLeftChild;
		}
		if (_isNilNode(targetNode))
		{
			std::cerr<<"Couldn't find key in the tree"<<std::endl;
			throw (std::exception());
		}
		if (_isLeafNode(targetNode) == false)
		{
			NodePtr successor = _getSuccessor(targetNode)->getData();
			_transplant(targetNode, successor);
			targetNode = successor;
		}
		if (_isRootNode(targetNode) == true)
		{
			delete taregetNode;
			this->_pRoot = NULL;
		}
	}

	template< class T >
	void RBtree<T>::_transplant(typename RBtree<T>::NodePtr pNode, typename RBtree<T>::NodePtr pSuccessor)
	{
		if (_isRootNode(pNode) == true)
			this->_pRoot = pSuccessor;
		else if (pNode == pNode->_pParent->_pleftChild)
			pNode->_pParent->_pleftChild = pSuccessor;
		else
			pNode->_pParent->_pRightChild = pSuccessor;
		pSuccessor->_pLeftChild = pNode->_pLeftChild;
		pSuccessor->_pRightChild = pNode->_pRightChild;
		pSuccessor->_pParent = pNode->_pParent;
	}
} // namespace ft


	