#ifndef FT_RBTREE_HPP
# define FT_RBTREE_HPP
#include <memory>
#include <exception>

#include "ft_RBtreeNode.hpp"
#include "ft_iterator.hpp"
#include "ft_less.hpp"
namespace ft
{
	template <	class T,
				class Alloc = std::allocator< RBtreeNode<T> >,
				class Comp = ft::less<T> >
	class RBtree
	{
	private :
		/* private members */
		typedef RBtreeNode<T>	node_type;
		typedef RBtreeNode<T>*	node_pointer;
		typedef Alloc			allocator_type;
		typedef Comp			key_compare;

		allocator_type	_allocator_object;
		key_compare		_key_compare;
		node_pointer	_nilnode;
		node_pointer	_pRoot;

		/* private method */
		// utils
		bool	_isNilNode(node_pointer pNode) const {return (pNode == _nilnode);} //done
		bool	_isRootNode(node_pointer pNode) const {return (_isNilNode(pNode->_pParent));} //done
		bool	_isLeafNode(node_pointer pNode) const {return (_isNilNode(pNode->_pLeftChild) && _isNilNode(pNode->_pRightChild));} //done
		void	_printTreeHelper(node_pointer pNode) const ;
		void	_deleteTreeHelper(node_pointer pNode);
		void	_copyTreeHelper(node_pointer pNode);
		// void	_preOrderHelper(node_pointer pNode);
		// rotation
		void	_rotateLeft(node_pointer pPivotNode); //done
		void	_rotateRight(node_pointer pPivotNode); //done
		// search_helpers
		node_pointer _searchHelper(node_pointer pNode, T value) const; //done
		// insert_helpers
		void	_BStreeInsert(node_pointer pNode, T value); //done
		void	_insertRestructor(node_pointer pPivot); //done
		// delete_helpers
		node_pointer _getSuccessor(node_pointer pNode) const;//done
		// Transplant : change targetnode and successor for delete targetnode 
		void	_transplant(node_pointer refNode, node_pointer refSuccessor); //done
		void	_BStreeDelete(node_pointer pNode, T value); //done
		void	_deleteRestructor(node_pointer pPivot); //done

	public :
		//(constructor)
		RBtree( void ) : _allocator_object(allocator_type()), _key_compare(Comp())
		{
			_nilnode = _allocator_object.allocate(1);
			_allocator_object.construct(_nilnode, node_type());
			_nilnode->_pParent = _pRoot;
			_nilnode->_pRightChild = _nilnode;
			_pRoot = _nilnode;
		}
		RBtree (const RBtree & other)
		: _allocator_object(allocator_type()), _key_compare(Comp())
		{
			_nilnode = _allocator_object.allocate(1);
			_allocator_object.construct(_nilnode, node_type());
			_nilnode->_pParent = _pRoot;
			_nilnode->_pRightChild = _nilnode;
			_pRoot = _nilnode;
			_copyTreeHelper(other._pRoot);
			// this->insertNode(other._pRoot->getData());
		}
		~RBtree()
		{
			std::cout << "deleting tree" << _pRoot << std::endl;
			this->clearTree();
			_allocator_object.destroy(this->_nilnode);
			_allocator_object.deallocate(this->_nilnode, 1);
		}
		RBtree & operator=( const RBtree & other )
		{
			std::cout << "operator =" << std::endl;
			if (this == &other)
				return (*this);
			this->clearTree();
			_copyTreeHelper(other._pRoot);
			return (*this);
		}
		//member functions
		const node_pointer	getNilPtr( void ) const { return (_nilnode); }
		const node_pointer getRoot( void ) const { return (_pRoot); } 
		node_pointer search(const T & value) const { return (_searchHelper(this->_pRoot, value)); } //done
		void insertNode(T value);
		void deleteNode(T value);

		void clearTree()
		{
			_deleteTreeHelper(this->_pRoot);
		}

		void printTree() const
		{
			if (_isNilNode(this->_pRoot))
				std::cout << "Tree is empty" << std::endl;
			else
			{
				std::cout << "Nilptr  is " << _nilnode << std::endl;
				std::cout << *_nilnode << std::endl;
				std::cout << "Root is " << std::endl;
				std::cout << "\t" << _pRoot << std::endl;
				std::cout << *_pRoot << std::endl;
				_printTreeHelper(_pRoot);
			}
		}
	}; // class RBtree

	template<class T, class Alloc, class Comp>
	void RBtree<T, Alloc, Comp>::_printTreeHelper(typename RBtree<T, Alloc, Comp>::node_pointer pNode) const
	{
		if (pNode == NULL || pNode->_isNilNode() == true)
			return ;
		_printTreeHelper(pNode->_pLeftChild);
		std::cout << "ptr  " << pNode << std::endl;
		std::cout << "data " << *pNode << " ";
		_printTreeHelper(pNode->_pRightChild);
	}

	template<class T, class Alloc, class Comp>
	void RBtree<T, Alloc, Comp>::_deleteTreeHelper(node_pointer pNode)
	{
		if (pNode->_isNilNode() == true)
			return ;
		_deleteTreeHelper(pNode->_pLeftChild);
		_deleteTreeHelper(pNode->_pRightChild);
		this->_allocator_object.destroy(pNode);
		this->_allocator_object.deallocate(pNode, 1);
	}

	template<class T, class Alloc, class Comp>
	void RBtree<T, Alloc, Comp>::_copyTreeHelper(typename RBtree<T, Alloc, Comp>::node_pointer pNode)
	{
		if (pNode == NULL || pNode->_isNilNode() == true)
			return ;
		_copyTreeHelper(pNode->_pLeftChild);
		this->insertNode(pNode->getData());
		_copyTreeHelper(pNode->_pRightChild);
	}

	template<class T, class Alloc, class Comp>
	typename RBtree<T, Alloc, Comp>::node_pointer RBtree<T, Alloc, Comp>::_searchHelper(typename RBtree<T, Alloc, Comp>::node_pointer node, T value) const
	{
		if (_isNilNode(node) == true)
		{
			std::cerr << "Can not find value in the tree" << std::endl;
			throw(std::exception());
		}
		else if (node->getData() == value)
			return (node);
		if (_key_compare(value, node->getData()))
			return (_searchHelper(node->_pLeftChild, value));
		return (_searchHelper(node->_pRightChild, value));
	}

	template<class T, class Alloc, class Comp>
	void RBtree<T, Alloc, Comp>::_rotateLeft( typename RBtree<T, Alloc, Comp>::node_pointer pPivotNode )
	{
		/*
			1. move y's left_tree to x's right
			2. change y's left_tree's root's parent to x (if root is no NULL)
			3. set y's parent to x's one
			4. change parent's child
			5. set x to y's left child
			6. set x's parent to y
		*/
		// std::cout << "[rotate  Left], node_pointer : " << pPivotNode << std::endl;
		// std::cout << *pPivotNode << std::endl;
		node_pointer 	x = pPivotNode;
		node_pointer	y = x->_pRightChild;
		
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

	template<class T, class Alloc, class Comp>
	void RBtree<T, Alloc, Comp>::_rotateRight( typename RBtree<T, Alloc, Comp>::node_pointer pPivotNode )
	{
		node_pointer x = pPivotNode;
		node_pointer y = x->_pLeftChild;

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

	template<class T, class Alloc, class Comp>
	void RBtree<T, Alloc, Comp>::insertNode(T data)
	{
		if (_isNilNode(this->_pRoot) == true)
		{
			_pRoot = this->_allocator_object.allocate(1);
			this->_allocator_object.construct(_pRoot, node_type(data, _nilnode, _nilnode, _nilnode, BLACK));
		}
		else
		{
			_BStreeInsert(this->_pRoot, data);
		}
		this->_pRoot->setColor(BLACK);
		this->_nilnode->_pRightChild = this->_pRoot->_maximum();
		this->_nilnode->_pLeftChild = NULL;
		this->_nilnode->_pParent = this->_pRoot;
	}

	template<class T, class Alloc, class Comp>
	void RBtree<T, Alloc, Comp>::_BStreeInsert( typename RBtree<T, Alloc, Comp>::node_pointer pNode, T data )
	{
		if (data == pNode->getData())
			throw std::exception();
		if (this->_key_compare(data, pNode->getData()))
		{
			if (_isNilNode(pNode->_pLeftChild) == true)
			{
				pNode->_pLeftChild = this->_allocator_object.allocate(1);
				this->_allocator_object.construct(pNode->_pLeftChild, node_type(data, _nilnode, _nilnode, pNode));
				_insertRestructor(pNode->_pLeftChild);
			}
			else
				_BStreeInsert(pNode->_pLeftChild, data);
		}
		else
		{
			if (_isNilNode(pNode->_pRightChild) == true)
			{
				pNode->_pRightChild = this->_allocator_object.allocate(1);
				this->_allocator_object.construct(pNode->_pRightChild, node_type(data, _nilnode, _nilnode, pNode));
				_insertRestructor(pNode->_pRightChild);
			}
			else
				_BStreeInsert(pNode->_pRightChild, data);
		}
	}

	template<class T, class Alloc, class Comp>
	void RBtree<T, Alloc, Comp>::_insertRestructor( typename RBtree<T, Alloc, Comp>::node_pointer KeyNode )
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
		node_pointer	K = KeyNode;
		node_pointer	P = K->_pParent;
		if (P->getColor() == BLACK)
			return ;
		node_pointer	G = P->_pParent;
		node_pointer	U;
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
	}

	template<class T, class Alloc, class Comp>
	typename RBtree<T, Alloc, Comp>::node_pointer	RBtree<T, Alloc, Comp>::_getSuccessor( typename RBtree<T, Alloc, Comp>::node_pointer pNode ) const
	{
		node_pointer successor;

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
	template<class T, class Alloc, class Comp>
	void RBtree<T, Alloc, Comp>::_transplant(typename RBtree<T, Alloc, Comp>::node_pointer pNode, typename RBtree<T, Alloc, Comp>::node_pointer pSuccessor)
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

	template<class T, class Alloc, class Comp>
	void RBtree<T, Alloc, Comp>::_BStreeDelete( typename RBtree<T, Alloc, Comp>::node_pointer pNode , T value )
	{
		node_pointer pTargetNode = RBtree<T, Alloc, Comp>::_nilnode;
		node_pointer K = pNode;
		// 1. find node to delete
		while (!_isNilNode(K))
		{
			if (value == K->getData()) 
			{
				pTargetNode = K;
				break;
			}
			if (_key_compare(value, K->getData()))
				K = K->_pRightChild;
			else
				K = K->_pLeftChild;
		}
		// pTargetNode = this->search(value);
		// 2. exception
		if (_isNilNode(pTargetNode))
		{
			std::cerr << "Can not find value in the tree" << std::endl;
			throw (std::exception());
		}
		Color deleting_color;
		node_pointer occupyingNode;
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
			node_pointer successorNode = this->_getSuccessor(pTargetNode);
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
	template<class T, class Alloc, class Comp>
	void RBtree<T, Alloc, Comp>::_deleteRestructor(typename RBtree<T, Alloc, Comp>::node_pointer pNode)
	{
		node_pointer N = pNode;
		node_pointer P; // parentNode
		node_pointer S; // siblingNode
		node_pointer LN; // left nephew
		node_pointer RN; // right nephew
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

	template<class T, class Alloc, class Comp>
	void RBtree<T, Alloc, Comp>::deleteNode(T value)
	{
		_BStreeDelete(this->_pRoot, value);
		this->_pRoot->setColor(ft::BLACK);
		this->_nilnode->_pRightChild = this->_pRoot->_maximum();
		this->_nilnode->_pLeftChild = NULL;
		this->_nilnode->_pParent = this->_pRoot;
	}

} // namespace ft
#endif