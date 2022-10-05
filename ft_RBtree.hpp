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
		bool	_isNilNode(NodePtr pNode) {return (pNode == _nilnode);} //done
		bool	_isRootNode(NodePtr pNode) {return (pNode->_pParent == NULL);} //done
		bool	_isLeafNode(NodePtr pNode) {return (_isNilNode(pNode->_pLeftChild) && _isNilNode(pNode->_pRightChild));} //done
		void	_inOrderHelper(NodePtr pNode);
		void	_inOrderTraversal(void) { _inOrderHelper(this->_pRoot); }
		// void	_preOrderHelper(NodePtr pNode);
		// rotation
		void	_rotateLeft(NodePtr pPivotNode); //done
		void	_rotateRight(NodePtr pPivotNode); //done
		// search_helpers
		NodePtr _searchHelper(NodePtr pNode, T key); //done
		// insert_helpers
		void _BStreeInsert(NodePtr pNode, T key); //done
		void _insertRestructor(NodePtr pPivot); //done
		// delete_helpers
		NodePtr _getSuccessor(NodePtr pNode); //done
		// Transplant : change targetnode and successor for delete targetnode 
		void _transplant(NodePtr pNode, NodePtr pSuccessor); //done
		void _BStreeDelete(NodePtr pNode, T key);
		void _deleteRestructor(NodePtr pPivot);
	public :
		//(constructor)
		RBtree( void ) :_pRoot(NULL), _nilnode(NULL) {}
		RBtree( const RBtree & other );
		RBtree & operator=( const RBtree & other );
		//(destructor)
		~RBtree() {};

		//member functions
		const Nodetype & getRoot( void ) { return (*_pRoot); } const 
		NodePtr search(const T & key) { return (_searchHelper(this->_pRoot, key)); } //done
		void insertNode(T key); //done
		void deleteNode(T key);

		/*non_member function*/
		template<class U>
		friend std::ostream & operator<<( std::ostream & os, const RBtree<U> & tree );
	}; // class RBtree

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
		if (this->_pRoot == NULL)
		{
			std::cout << "[insert 0] : " << key << std::endl;
			_pRoot = new RBtreeNode<T>(key);
		}
		else
		{
			std::cout << "[insert] : " << key << std::endl;
			_BStreeInsert(this->_pRoot, key);
		}
		this->_pRoot->setColor(BLACK);
	}

	template< class T >
	void RBtree<T>::_BStreeInsert( typename RBtree<T>::NodePtr pNode, T key )
	{
		if (key == pNode->getData())
			throw std::exception();
		else if (key < pNode->getData())
		{
			std::cout << "[insert]	go left" << std::endl;
			if (this->_isNilNode(pNode->_pLeftChild) == true)
			{
				std::cout << "[insert]	make new node at left" << std::endl;
				pNode->_pLeftChild = new RBtreeNode<T>(key, pNode);
				_insertRestructor(pNode->_pLeftChild);
			}
			else
				_BStreeInsert(pNode->_pLeftChild, key);
		}
		else
		{
			std::cout << "[insert]	go right" << std::endl;
			if (this->_isNilNode(pNode->_pRightChild) == true)
			{
				std::cout << "[insert]	make new node at right" << std::endl;
				pNode->_pRightChild = new RBtreeNode<T>(key, pNode);
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
		if (_isNilNode(P) || P->getColor() == BLACK)
			return ;
		NodePtr	G = P->_pParent;
		NodePtr U;
		std::cout << "[insert]	Restruct : ";
		while (P->getColor() == RED)
		{
			if (P == G->_pRightChild)
			{
				U = G->_pLeftChild;
				if (!_isNilNode(U) && U->getColor() == RED) // 3.1
				{
					std::cout << "R case 3.1 ";
					P->setColor(BLACK);
					U->setColor(BLACK);
					G->setColor(RED);
					K = G; // update target Node for next iteration
				}
				else
				{
					if (K == P->_pLeftChild)
					{
						std::cout << "R case 3.2.2 ";
						_rotateRight(P); // 3.2.2 K becomes P's Parent
					}
					std::cout << "R case 3.2.1 ";
					_rotateLeft(G);	// 3.2.1
					G->setColor(RED);
					P->setColor(BLACK);
					K = P; // update target Node for next iteration
				}
			}
			else
			{
				U = G->_pRightChild;
				if (!_isNilNode(U) && U->getColor() == RED) // 3.1
				{
					std::cout << "L case 3.1 ";
					P->setColor(BLACK);
					U->setColor(BLACK);
					G->setColor(RED);
					K = G;
				}
				else
				{
					if (K == P->_pRightChild)
					{
						std::cout << "L case 3.2.4 ";
						_rotateLeft(P); // 3.2.4 K becomes P's Parent
					}
					std::cout << "L case 3.2.3 ";
					_rotateRight(G);	// 3.2.3
					G->setColor(RED);
					P->setColor(BLACK);
					K = P; // update target Node for next iteration
				}
			}
		}
		std::cout << std::endl;
	}

	template< class T >
	typename RBtree<T>::NodePtr	RBtree<T>::_getSuccessor( typename RBtree<T>::NodePtr pNode )
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

	template< class T >
	void RBtree<T>::_transplant(typename RBtree<T>::NodePtr pNode, typename RBtree<T>::NodePtr pSuccessor)
	{
		std::cout << "[TRANSPLANT]";
		std::cout << pNode << " and " << pSuccessor << std::endl;
		std::cout << "pNode : " << *pNode << std::endl;
		std::cout << "pSuccessor : " << *pSuccessor << std::endl;
		// if (_isRootNode(pNode) == true)
		// 	this->_pRoot = pSuccessor;
		// else if (pNode == pNode->_pParent->_pLeftChild)
		// 	pNode->_pParent->_pLeftChild = pSuccessor;
		// else
		// 	pNode->_pParent->_pRightChild = pSuccessor;
		// pSuccessor->_pParent = pNode->_pParent;
		// ft::swap(*pNode, *pSuccessor);
		pNode->swap((*pSuccessor));
		(*pNode)._data = 8;
		std::cout << "[TRANSPLANT RESULT]";
		std::cout << pNode << " and " << pSuccessor << std::endl;
		std::cout << "pNode : " << *pNode << std::endl;
		std::cout << "pSuccessor : " << *pSuccessor << std::endl;
		std::exit(1);
	}

	/*
		process : firstly follow the ordinary BST deletion.
		이진 탐색트리에서의 삭제는 
	*/
	template< class T >
	void RBtree<T>::_BStreeDelete( typename RBtree<T>::NodePtr pNode , T key )
	{
		std::cout << "[bsDELETE]" << std::endl;
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
		// 전달 받은 키에 해당하는 노드가 없는 경우
		if (_isNilNode(targetNode))
		{
			std::cerr << "Can not find key in the tree" << std::endl;
			throw (std::exception());
		}
		// 삭제할 노드가 leafnode가 아닌 경우, 이 노드와 successor노드와 교체해준다. successor는 항상 leaf이다.
		// 그럼 삭제할 노드가 leafnode로 변경된다.
		ft::Color target_color = targetNode->getColor();
		if (_isLeafNode(targetNode) == false)
		{
			NodePtr successor = _getSuccessor(targetNode);
			std::cout << "[Before Transplamt] " << std::endl;
			std::cout << "\t  target  : " << targetNode << std::endl;
			std::cout << "\tsuccessor : " << successor << std::endl;
			_transplant(targetNode, successor);
			std::cout << "[After  Transplant] " << std::endl;
			std::cout << "\t  target  : " << targetNode << std::endl;
			std::cout << "\tsuccessor : " << successor << std::endl;
			targetNode = successor;
		}
		// 여기서 본격적인 삭제가 수행되는 부분이다.
		// 삭제할 노드가 루트노드인 경우, 예외처리 해준다.
		// 삭제할 노드가 루트노드이면, 그냥 노드를 삭제하고 this->_pRoot를 Null로 초기화 해주고 끝낸다.
		if (_isRootNode(targetNode) == true)
		{
			delete targetNode;
			this->_pRoot = NULL;
			return ;
		}
		// 삭제할 노드가 루트노드가 아닌 경우이다. 현재 targetNode는 항상 LeafNode이다.
		else
		{
			if (targetNode == targetNode->_pParent->_pLeftChild)
				targetNode->_pParent->_pLeftChild = this->_nilnode;
			else
				targetNode->_pParent->_pRightChild = this->_nilnode;
			delete targetNode;
			// _deleteRestructor();
		}
	}

	template <class T>
	void RBtree<T>::_deleteRestructor(typename RBtree<T>::NodePtr pPivot)
	{
		
	}

	template <class T>
	void RBtree<T>::deleteNode(T key)
	{
		_BStreeDelete(this->_pRoot, key);
	}

} // namespace ft


	