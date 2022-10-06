#include <memory>
#include <exception>

#include <vector>
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
		void _transplant(NodePtr refNode, NodePtr refSuccessor);
		void _BStreeDelete(NodePtr pNode, T key);
		void _deleteRestructor(NodePtr pPivot);
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

		/*non_member function*/
		template<class U>
		friend std::ostream & operator<<( std::ostream & os, const RBtree<U> & tree );
	}; // class RBtree

	// template <class T>
	// typename RBtree<T>::Nodetype NULLNODE = RBtree<T>(T(), NULL, BLACK);

	// template< class T >
	// void RBtree<T>::_preOrderHelper(typename RBtree<T>::NodePtr pNode)
	// {
	// 	if (pNode == NULL ||_isNilNode(pNode) == true)
	// 		return ;
	// 	std::cout << *pNode << " ";
	// 	_inOrderHelper(pNode->_pLeftChild);
	// 	_inOrderHelper(pNode->_pLeftChild);
	// }

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
		// std::cout << "[rotate  Left], Done : " << std::endl;
	}

	template< class T >
	void RBtree<T>::_rotateRight( typename RBtree<T>::NodePtr pPivotNode )
	{
		// std::cout << "[rotate Right], nodeptr : " << pPivotNode << std::endl;
		// std::cout << *pPivotNode << std::endl;
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
		// std::cout << "[rotate Right], Done : " << std::endl;
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
			std::cout << "smal" << std::endl;
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
			std::cout << "big" << std::endl;
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
					std::cout << "case 3.1 : P is r" << std::endl;
					P->setColor(BLACK);
					U->setColor(BLACK);
					G->setColor(RED);
					K = G; // update target Node for next iteration
				}
				else
				{
					if (K == P->_pLeftChild)
					{
						std::cout << "case 3.2.2" << std::endl;
						_rotateRight(P); // 3.2.2 K becomes P's Parent
					}
					std::cout << "case 3.2.1" << std::endl;
					std::cout << "[ha...debug]" << std::endl;
					std::cout << "\t G :" << G << ", " << *G << std::endl;
					std::cout << "\t P :" << P << ", " << *P << std::endl;
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
					std::cout << "case 3.1 : P is l" << std::endl;
					P->setColor(BLACK);
					U->setColor(BLACK);
					G->setColor(RED);
					K = G;
				}
				else
				{
					if (K == P->_pRightChild)
					{
						std::cout << "case 3.2.4" << std::endl;
						_rotateLeft(P); // 3.2.4 K becomes P's Parent
					}
					std::cout << "case 3.2.3" << std::endl;
					G->setColor(RED);
					P->setColor(BLACK);
					_rotateRight(G);	// 3.2.3
					K = P; // update target Node for next iteration
				}
			}
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

	/*
		process : firstly follow the ordinary BST deletion.
		
		1. find node to delete (= x)
		2. if there is no matching node, throw exception or do nothing
		3. delete node by 3 cases
			3.1 : node has no left child 
				==> transplant(x, x->right)
			3.2 : node has only left child
				==> transplant(x, x->left)
			3.3 : node has both left and right child
				find successor or decessor node (substitute node : y) -> y = x->successor()
				z = y->right
				3.3.1 : y == x->rightchild (x->rightchild has no leftchild) (사실상 예외처리)
					==> transplant(x, y),
					==> y->left = x->left
				3.3.2 : x->rightchild has left subtree (일반적인 케이스)
					==> y->left = x->left
					==> y->right = x->right
					==> y->parent = x->parent
					==> if x is rootnode
					==> 	rootnode = y
					==> elif x is leftchild
					==> 	x->parent->left = y
					==> else
					==> 	x->parent->right = y;
	*/
	template< class T >
	void RBtree<T>::_BStreeDelete( typename RBtree<T>::NodePtr pNode , T key )
	{
		std::cout << "[bsDELETE]" << std::endl;
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
		// 2. exception
		if (_isNilNode(pTargetNode))
		{
			std::cerr << "Can not find key in the tree" << std::endl;
			throw (std::exception());
		}
		// 3.
		Color nodecolor = pTargetNode->getColor();
		NodePtr pSuccessor = this->_getSuccessor(pTargetNode);
		if (_isLeafNode(pTargetNode) == true) // 3.1
			this->_transplant(pTargetNode, pSuccessor);
		else if (_isNilNode(pTargetNode->_pRightChild) == true) // 3.2
			this->_transplant(pTargetNode, pSuccessor);
		else if (_isNilNode(pTargetNode->_pRightChild->_pLeftChild) == true) // 3.3.1
		{
			this->_transplant(pTargetNode,pSuccessor);
			pTargetNode->_pRightChild->_pLeftChild = pTargetNode->_pLeftChild;
		}
		else // 3.3.2
		{
			this->_transplant(pSuccessor, pSuccessor->_pRightChild);
			pSuccessor->_pLeftChild = pTargetNode->_pLeftChild;
			pSuccessor->_pRightChild = pTargetNode->_pRightChild;
			pSuccessor->_pParent = pTargetNode->_pParent;
			if ( _isRootNode(pTargetNode) == true )
				this->_pRoot = pSuccessor;
			else if ( pTargetNode->_pParent->_pLeftChild  == pTargetNode )
				pTargetNode->_pParent->_pLeftChild = pSuccessor;
			else
				pTargetNode->_pParent->_pRightChild = pSuccessor;
		}
		delete pTargetNode;
		if (nodecolor == ft::Color::BLACK)
			_deleteRestructor(pSuccessor);
	}

	template <class T>
	void RBtree<T>::_deleteRestructor(typename RBtree<T>::NodePtr pNode)
	{
		if (pNode->getColor() == ft::Color::RED)
		{
			pNode->setColor(ft::Color::BLACK);	
			return ;
		}
		else
		{
			
		}
	}

	template <class T>
	void RBtree<T>::deleteNode(T key)
	{
		_BStreeDelete(this->_pRoot, key);
	}

} // namespace ft


	