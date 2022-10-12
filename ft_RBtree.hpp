#include <memory>
#include <exception>

#include <queue>
#include "ft_RBtreeNode.hpp"

namespace ft
{
	template <class T>
	bool lessthan(const T & a, const T & b) { return (a < b); }

	template < class T >
	class RBtree
	{
	private :
		/* private members */
		typedef RBtreeNode<T> Nodetype;
		typedef RBtreeNode<T>* NodePtr;
		NodePtr _nilnode;
		NodePtr	_pRoot;
		
		/* private method */
		// utils
		bool	_isNilNode(NodePtr pNode) const {return (pNode == _nilnode);} //done
		bool	_isRootNode(NodePtr pNode) const {return (_isNilNode(pNode->_pParent));} //done
		bool	_isLeafNode(NodePtr pNode) const {return (_isNilNode(pNode->_pLeftChild) && _isNilNode(pNode->_pRightChild));} //done
		void	_inOrderHelper(NodePtr pNode);
		void	_inOrderTraversal(void) { _inOrderHelper(this->_pRoot); }
		// void	_preOrderHelper(NodePtr pNode);
		// rotation
		void	_rotateLeft(NodePtr pPivotNode); //done
		void	_rotateRight(NodePtr pPivotNode); //done
		// search_helpers
		NodePtr _searchHelper(NodePtr pNode, T key) const; //done
		// insert_helpers
		void _BStreeInsert(NodePtr pNode, T key); //done
		void _insertRestructor(NodePtr pPivot); //done
		// delete_helpers
		NodePtr _getSuccessor(NodePtr pNode) const;//done
		// Transplant : change targetnode and successor for delete targetnode 
		void _transplant(NodePtr refNode, NodePtr refSuccessor); //done
		void _BStreeDelete(NodePtr pNode, T key); //done
		void _deleteRestructor(NodePtr pPivot); //done
	public :
		//(constructor)
		RBtree( void )
		{
			_nilnode = new Nodetype(T(), NULL, NULL, NULL, BLACK);
			_pRoot = _nilnode;
		}
		RBtree( const RBtree & other )
		{
			_nilnode = new Nodetype(T(), NULL, NULL, NULL, BLACK);
			_pRoot = _nilnode;
			// ... deep copy all nodes
		}
		RBtree & operator=( const RBtree & other )
		{
			if (this == &other)
				return (*this);
			// ... clear all nodes
			// ... copy all nodes
		}
		//(destructor)
		~RBtree()
		{
			// ... clear all nodes
			delete _nilnode;
		}

		//member functions
		const NodePtr	getNilPtr( void ) const { return (_nilnode); }
		const Nodetype & getRoot( void ) const { return (*_pRoot); } 
		NodePtr search(const T & key) const { return (_searchHelper(this->_pRoot, key)); } //done
		void insertNode(T key); //done
		void deleteNode(T key);

		void printHelper(NodePtr pNode)
		{
			if (_isNilNode(pNode) == true)
				return ;
			printHelper(pNode->_pLeftChild);
			std::cout << "\t=========" << std::endl;
			std::cout << "\t" << pNode << std::endl;
			std::cout << *pNode << std::endl;
			printHelper(pNode->_pRightChild);
		}

		void printTree()
		{
			if (_isNilNode(this->_pRoot))
				std::cout << "Tree is empty" << std::endl;
			else
			{
				std::cout << "Nilptr  is " << _nilnode << std::endl;
				std::cout << "Root is " << std::endl;
				std::cout << "\t" << _pRoot << std::endl;
				std::cout << *_pRoot << std::endl;
				printHelper(_pRoot);
			}
		}

	}; // class RBtree

	template< class T >
	void RBtree<T>::_inOrderHelper(typename RBtree<T>::NodePtr pNode)
	{
		if (pNode == NULL ||_isNilNode(pNode) == true)
			return ;
		_inOrderHelper(pNode->_pLeftChild);
		std::cout << *pNode << " ";
		_inOrderHelper(pNode->_pLeftChild);
	}

	template< class T >
	typename RBtree<T>::NodePtr RBtree<T>::_searchHelper(typename RBtree<T>::NodePtr node, T key) const
	{
		if (_isNilNode(node) == true)
		{
			std::cerr << "Can not find key in the tree" << std::endl;
			throw(std::exception());
		}
		else if (node->getData() == key)
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
		// std::cout << "[rotate  Left], nodeptr : " << pPivotNode << std::endl;
		// std::cout << *pPivotNode << std::endl;
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
		std::cout << "insert : " << key << std::endl;
		if (_isNilNode(this->_pRoot) == true)
		{
			_pRoot = new RBtreeNode<T>(key, _nilnode, _nilnode, _nilnode, BLACK);
		}
		else
		{
			_BStreeInsert(this->_pRoot, key);
		}
		this->_pRoot->setColor(BLACK);
	}

	template< class T >
	void RBtree<T>::_BStreeInsert( typename RBtree<T>::NodePtr pNode, T key )
	{
		if (key == pNode->getData())
			throw std::exception();
		if (key < pNode->getData())
		{
			if (_isNilNode(pNode->_pLeftChild) == true)
			{
				pNode->_pLeftChild = new RBtreeNode<T>(key, _nilnode, _nilnode, pNode);
				_insertRestructor(pNode->_pLeftChild);
			}
			else
				_BStreeInsert(pNode->_pLeftChild, key);
		}
		else
		{
			if (_isNilNode(pNode->_pRightChild) == true)
			{
				pNode->_pRightChild = new RBtreeNode<T>(key, _nilnode, _nilnode, pNode);
				_insertRestructor(pNode->_pRightChild);
			}
			else
				_BStreeInsert(pNode->_pRightChild, key);
		}
	}

	template< class T >
	void RBtree<T>::_insertRestructor( typename RBtree<T>::NodePtr KeyNode )
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
		NodePtr K = KeyNode;
		NodePtr P = K->_pParent;
		if (P->getColor() == BLACK)
			return ;
		NodePtr	G = P->_pParent;
		NodePtr U;
		while (K->getColor() == RED && P->getColor() == RED)
		{
			if (P == G->_pRightChild)
			{
				U = G->_pLeftChild;
				if (!_isNilNode(U) && U->getColor() == RED) // 3.1
				{
					P->setColor(BLACK);
					U->setColor(BLACK);
					G->setColor(RED);
					K = G; // update target Node for next iteration
				}
				else
				{
					if (K == P->_pLeftChild)
					{
						_rotateRight(P); // 3.2.2 K becomes P's Parent
					}
					G->setColor(RED);
					P->setColor(BLACK);
					_rotateLeft(G);	// 3.2.1
					K = P; // update target Node for next iteration
				}
			}
			else
			{
				U = G->_pRightChild;
				if (!_isNilNode(U) && U->getColor() == RED) // 3.1
				{
					P->setColor(BLACK);
					U->setColor(BLACK);
					G->setColor(RED);
					K = G;
				}
				else
				{
					if (K == P->_pRightChild)
					{
						_rotateLeft(P); // 3.2.4 K becomes P's Parent
					}
					G->setColor(RED);
					P->setColor(BLACK);
					_rotateRight(G);	// 3.2.3
					K = P; // update target Node for next iteration
				}
			}
			P = K->_pParent;
			G = P->_pParent;
		}
		std::cout << std::endl;
	}

	template< class T >
	typename RBtree<T>::NodePtr	RBtree<T>::_getSuccessor( typename RBtree<T>::NodePtr pNode ) const
	{
		NodePtr successor;

		if (_isNilNode(pNode->_pLeftChild) == true) // pNode is leafnode or just have rightchild
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

	// 트리에서 특정 노드를 빼내고, 트리는 이진트리 규칙을 유지하는 기능이다.
	template< class T >
	void RBtree<T>::_transplant(typename RBtree<T>::NodePtr pNode, typename RBtree<T>::NodePtr pSuccessor)
	{
		if (_isRootNode(pNode) == true)
			this->_pRoot = pSuccessor;
		else if (pNode == pNode->_pParent->_pLeftChild)
			pNode->_pParent->_pLeftChild = pSuccessor;
		else
			pNode->_pParent->_pRightChild = pSuccessor;
		if (_isNilNode(pSuccessor) == false)
			pSuccessor->_pParent = pNode->_pParent;
	}

	template< class T >
	void RBtree<T>::_BStreeDelete( typename RBtree<T>::NodePtr pNode , T key )
	{
		NodePtr pTargetNode = RBtree<T>::_nilnode;
		NodePtr K = pNode;
		// 1. find node to delete
		while (!_isNilNode(K))
		{
			if (K->getData() == key) 
			{
				pTargetNode = K;
				break;
			}
			if (K->getData() <= key)
				K = K->_pRightChild;
			else
				K = K->_pLeftChild;
		}
		// pTargetNode = this->search(key);
		// 2. exception
		if (_isNilNode(pTargetNode))
		{
			std::cerr << "Can not find key in the tree" << std::endl;
			throw (std::exception());
		}
		Color deleting_color;
		NodePtr occupyingNode;
		if (_isLeafNode(pTargetNode) == true) // no child
		{
			occupyingNode = this->_nilnode;
			deleting_color = pTargetNode->getColor();
			_transplant(pTargetNode, occupyingNode);
		}
		else if (_isNilNode(pTargetNode->_pLeftChild) == true) // just rightchild
		{
			occupyingNode = pTargetNode->_pRightChild;
			deleting_color = pTargetNode->getColor();
			_transplant(pTargetNode, occupyingNode);
		}
		else if (_isNilNode(pTargetNode->_pRightChild) == true) // just leftchild
		{
			occupyingNode = pTargetNode->_pLeftChild;
			deleting_color = pTargetNode->getColor();
			_transplant(pTargetNode, occupyingNode);
		}
		else // both child
		{
			NodePtr successorNode = this->_getSuccessor(pTargetNode);
			deleting_color = successorNode->getColor();
			occupyingNode = successorNode->_pRightChild;

			if (pTargetNode == successorNode->_pParent)
			{
				occupyingNode->_pParent = successorNode; // actually do nothing
			}
			else
			{
				_transplant(successorNode, occupyingNode);
				successorNode->_pRightChild = pTargetNode->_pRightChild;
				successorNode->_pRightChild->_pParent = successorNode;
			}
			_transplant(pTargetNode, successorNode);
			successorNode->_pLeftChild = pTargetNode->_pLeftChild;
			successorNode->_pLeftChild->_pParent = successorNode;
			successorNode->_color = pTargetNode->getColor();
		}
		delete pTargetNode;
		if (deleting_color == ft::BLACK)
			_deleteRestructor(occupyingNode);
	}


	/*
		Nephew node : child nodes of Sibling Node
		-> LN : left child of Sibling
		-> RN : right child of Sibling
	*/
	template <class T>
	void RBtree<T>::_deleteRestructor(typename RBtree<T>::NodePtr pNode)
	{
		NodePtr N = pNode;
		NodePtr P; // parentNode
		NodePtr S; // siblingNode
		NodePtr LN; // left nephew
		NodePtr RN; // right nephew
		while (N->getColor() == ft::BLACK && !_isRootNode(N) && !_isNilNode(N))
		{
			P = N->_pParent;
			if (N == P->_pLeftChild)
			{
				S = P->_pRightChild;
				// case 3.1
				if (S->getColor() == ft::RED)
				{
					P->setColor(ft::RED);
					S->setColor(ft::BLACK);
					_rotateLeft(P);
					S = N->_pParent->_pRightChild;
				}
				LN = S->_pLeftChild;
				RN = S->_pRightChild;
				// case 3.2
				if (S->getColor() == ft::BLACK && RN->getColor() == ft::BLACK)
				{
					S->setColor(ft::RED);
					N = N->_pParent;
				}
				else {
					// case 3.3
					if (RN->getColor() == ft::BLACK)
					{
						LN->setColor(ft::BLACK);
						S->setColor(ft::RED);
						_rotateRight(S);
						S = N->_pParent->_pRightChild;
					} 
					// case 3.4
					S->setColor(P->getColor());
					P->setColor(ft::BLACK);
					RN->setColor(ft::BLACK);
					_rotateLeft(P);
					N = _pRoot;
				}
			}
			else
			{
				S = P->_pLeftChild;
				// case 3.1
				if (S->getColor() == ft::RED)
				{
					P->setColor(ft::RED);
					S->setColor(ft::BLACK);
					_rotateRight(P);
					S = N->_pParent->_pLeftChild;
				}
				LN = S->_pLeftChild;
				RN = S->_pRightChild;
				// case 3.2
				if (S->getColor() == ft::BLACK && LN->getColor() == ft::BLACK)
				{
					S->setColor(ft::RED);
					N = N->_pParent;
				}
				else {
					// case 3.3
					if (LN->getColor() == ft::BLACK)
					{
						RN->setColor(ft::BLACK);
						S->setColor(ft::RED);
						_rotateLeft(S);
						S = N->_pParent->_pLeftChild;
					} 
					// case 3.4
					S->setColor(P->getColor());
					P->setColor(ft::BLACK);
					LN->setColor(ft::BLACK);
					_rotateRight(P);
					N = _pRoot;
				}
			}
		}
	}

	template <class T>
	void RBtree<T>::deleteNode(T key)
	{
		_BStreeDelete(this->_pRoot, key);
		this->_pRoot->setColor(ft::BLACK);
	}

} // namespace ft
