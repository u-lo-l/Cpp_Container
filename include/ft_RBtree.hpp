#ifndef FT_TREE_HPP
# define FT_TREE_HPP
#include <memory>
#include <exception>

#include "ft_RBtreeNode.hpp"
#include "ft_iterator.hpp"
#include "ft_less.hpp"
#include "ft_pair.hpp"

namespace ft
{
	/***************
	 *    class    *
	 ***************/
	template <	class T,
				class SelectKey,
				class Comp = ft::less<T>,
				class Alloc = std::allocator< RBtreeNode<T> > >
	class RBtree
	{
	public :
		typedef RBtreeNode<T>						node_type;
		typedef RBtreeNode<T>*						node_pointer;
	private :
		typedef Alloc								allocator_type;
		typedef Comp								key_compare;
		typedef typename allocator_type::size_type	size_type;

	private :
		allocator_type	_allocator_object;
		SelectKey		_select_key;
		node_pointer	_nilnode;
		node_pointer	_pRoot;
		key_compare		_key_compare;
		size_type		_size;

	private :
		bool	_nodeCompare(const T & v1, const T & v2) const;
		bool	_nodeEqual(node_pointer pNode, const T & val) const;
		bool	_isNilNode(node_pointer pNode) const;
		bool	_isRootNode(node_pointer pNode) const;
		bool	_isLeafNode(node_pointer pNode) const;
		void	_printTreeHelper(node_pointer pNode) const ;
		void	_deleteTreeHelper(node_pointer pNode);
		void	_copyTreeHelper(node_pointer pNode);
		// rotation
		void	_rotateLeft(node_pointer pPivotNode);
		void	_rotateRight(node_pointer pPivotNode);
		// search_helpers
		node_pointer _searchHelper(node_pointer pNode, const T & value) const;
		// insert_helpers
		ft::pair<node_pointer, bool> _BStreeInsert(node_pointer pNode, const T & value);
		node_pointer	_insertRestructor(node_pointer pPivot);
		// delete_helpers
		node_pointer _getSuccessor(node_pointer pNode) const;
		// Transplant : change targetnode and successor for delete targetnode 
		void	_transplant(node_pointer refNode, node_pointer refSuccessor);
		bool	_BStreeDelete(const T & value);
		void	_deleteRestructor(node_pointer pPivot);
	public :
		RBtree( void );
		RBtree( const RBtree & other );
		~RBtree( void );
		RBtree & operator=( const RBtree & other );

		node_pointer getNilPtr( void ) const;
		node_pointer getRootPtr( void ) const;

		node_pointer search(const T & value) const;

		ft::pair<node_pointer, bool> insertNode(const T & value);
		node_pointer insertNode(node_pointer hint, const T & value);
		bool deleteNode(const T & value);

		void clearTree( void );
		void printTree( void ) const;

		bool isEmpty( void ) const;
		size_type size() const;
		size_type max_size() const;
		node_pointer begin() const;
		node_pointer end() const;
		node_pointer lower_bound(const T & value) const;
		node_pointer upper_bound(const T & value) const;
		void swap(RBtree & other);
	};

	/***************
	 *   private   *
	 ***************/

	template < class T, class SK, class C, class A>
	bool
	RBtree<T, SK, C, A>::_nodeCompare(const T & v1, const T & v2) const
	{
		return (_key_compare(_select_key(v1), _select_key(v2)));
	}

	template < class T, class SK, class C, class A>
	bool
	RBtree<T, SK, C, A>::_nodeEqual(node_pointer pNode, const T & val ) const
	{
 		return ((!_nodeCompare(pNode->getData(), val)) && (!_nodeCompare(val, pNode->getData())));
	}

	template < class T, class SK, class C, class A>
	bool
	RBtree<T, SK, C, A>::_isNilNode( node_pointer pNode) const
	{
 		return (pNode->isNilNode());
	}
	
	template < class T, class SK, class C, class A>
	bool
	RBtree<T, SK, C, A>::_isRootNode( node_pointer pNode) const
	{
 		return (_isNilNode(pNode->_pParent));
	}

	template < class T, class SK, class C, class A>
	bool
	RBtree<T, SK, C, A>::_isLeafNode( node_pointer pNode) const
	{
 		return (_isNilNode(pNode->_pLeftChild) && _isNilNode(pNode->_pRightChild));
	}

	template < class T, class SK, class C, class A>
	void
	RBtree<T, SK, C, A>::_printTreeHelper(node_pointer pNode) const
	{
		if (pNode == NULL || _isNilNode(pNode) == true)
			return ;
		_printTreeHelper(pNode->_pLeftChild);
		std::cout << "ptr  " << pNode << std::endl;
		std::cout << "data " << *pNode << " ";
		_printTreeHelper(pNode->_pRightChild);
	}

	template < class T, class SK, class C, class A>
	void
	RBtree<T, SK, C, A>::_deleteTreeHelper(node_pointer pNode)
	{
		if (pNode->isNilNode() == true)
			return ;
		_deleteTreeHelper(pNode->_pLeftChild);
		_deleteTreeHelper(pNode->_pRightChild);
		this->_allocator_object.destroy(pNode);
		this->_allocator_object.deallocate(pNode, 1);
		this->_size--;
	}

	template < class T, class SK, class C, class A>
	void
	RBtree<T, SK, C, A>::_copyTreeHelper(node_pointer pNode)
	{
		if (pNode == NULL || _isNilNode(pNode) == true)
			return ;
		_copyTreeHelper(pNode->_pLeftChild);
		this->insertNode(pNode->getData());
		_copyTreeHelper(pNode->_pRightChild);
	}

	/*
		TODO : key를 이용하여 삭제하는 경우 make_pair(k, 0)으로 찾는다.
		여기서 pair의 ==는 비교에 적절하지 않다. key로 바교하는 부분이 필요한데....
		== 대신 비교 두번
	*/
	template < class T, class SK, class C, class A>
	typename RBtree<T, SK, C, A>::node_pointer
	RBtree<T, SK, C, A>::_searchHelper(node_pointer node, const T & value) const
	{
		if (_isNilNode(node) == true)
			return (node);
		else if (this->_nodeEqual(node, value))
			return (node);
		if (_nodeCompare(value, node->getData()))
			return (_searchHelper(node->_pLeftChild, value));
		return (_searchHelper(node->_pRightChild, value));
	}

	template < class T, class SK, class C, class A>
	void
	RBtree<T, SK, C, A>::_rotateLeft( node_pointer pPivotNode )
	{
		/*
			1. move y's left_tree to x's right
			2. change y's left_tree's root's parent to x (if root is no NULL)
			3. set y's parent to x's one
			4. change parent's child
			5. set x to y's left child
			6. set x's parent to y
		*/
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

	template < class T, class SK, class C, class A>
	void
	RBtree<T, SK, C, A>::_rotateRight( node_pointer pPivotNode )
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

	template < class T, class SK, class C, class A>
	ft::pair<typename RBtree<T, SK, C, A>::node_pointer, bool>
	RBtree<T, SK, C, A>::_BStreeInsert( node_pointer pNode, const T & value )
	{
		if (this->_nodeEqual(pNode, value))
			return (ft::make_pair(pNode, false));
		if (this->_nodeCompare(value, pNode->_data))
		{
			if (_isNilNode(pNode->_pLeftChild) == true)
			{
				pNode->_pLeftChild = this->_allocator_object.allocate(1);
				this->_allocator_object.construct(pNode->_pLeftChild, node_type(value, _nilnode, _nilnode, pNode));
				this->_size++;
				node_pointer res =  _insertRestructor(pNode->_pLeftChild);
				return (ft::make_pair(res, true));
			}
			else
				return (_BStreeInsert(pNode->_pLeftChild, value));
		}
		else
		{
			if (_isNilNode(pNode->_pRightChild) == true)
			{
				pNode->_pRightChild = this->_allocator_object.allocate(1);
				this->_allocator_object.construct(pNode->_pRightChild, node_type(value, _nilnode, _nilnode, pNode));
				this->_size++;
				node_pointer res = _insertRestructor(pNode->_pRightChild);
				return (ft::make_pair(res, true));
			}
			else
				return (_BStreeInsert(pNode->_pRightChild, value));
		}
	}

	template < class T, class SK, class C, class A>
	typename RBtree<T, SK, C, A>::node_pointer
	RBtree<T, SK, C, A>::_insertRestructor( node_pointer KeyNode )
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
			return (KeyNode);
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
		return (KeyNode);
	}

	template < class T, class SK, class C, class A>
	typename RBtree<T, SK, C, A>::node_pointer
	RBtree<T, SK, C, A>::_getSuccessor( node_pointer pNode ) const
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
	template < class T, class SK, class C, class A>
	void
	RBtree<T, SK, C, A>::_transplant(node_pointer pNode, typename RBtree<T, SK, C, A>::node_pointer pSuccessor)
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

	template < class T, class SK, class C, class A>
	bool
	RBtree<T, SK, C, A>::_BStreeDelete( const T & value )
	{
		node_pointer pTargetNode = RBtree<T, SK, C, A>::_nilnode;
		// 1. find node to delete
		pTargetNode = this->search(value);
		// 2. exception
		if (_isNilNode(pTargetNode))
		{
			return (false);
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
		this->_size--;
		if (deleting_color == ft::BLACK)
			_deleteRestructor(occupyingNode);
		delete pTargetNode;
		return (true);
	}

	/*
		Nephew node : child nodes of Sibling Node
		-> LN : left child of Sibling
		-> RN : right child of Sibling
	*/
	template < class T, class SK, class C, class A>
	void
	RBtree<T, SK, C, A>::_deleteRestructor(node_pointer pNode)
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
	
	/***************
	 *   public    *
	 ***************/

	template < class T, class SK, class C, class A>
	RBtree<T, SK, C, A>::RBtree( void )
	: _allocator_object(A()),
	_select_key(SK()),
	_key_compare(C()),
	_size(0)
	{
		_nilnode = _allocator_object.allocate(1);
		_allocator_object.construct(_nilnode, node_type());
		_nilnode->_pParent = _pRoot;
		_nilnode->_pRightChild = _nilnode;
		_pRoot = _nilnode;
	}

	template < class T, class SK, class C, class A>
	RBtree<T, SK, C, A>::RBtree (const RBtree & other)
	: _allocator_object(A()),
	_select_key(SK()),
	_key_compare(C()),
	_size(0)
	{
		_nilnode = _allocator_object.allocate(1);
		_allocator_object.construct(_nilnode, node_type());
		_nilnode->_pParent = _pRoot;
		_nilnode->_pRightChild = _nilnode;
		_pRoot = _nilnode;
		_copyTreeHelper(other._pRoot);
	}

	template < class T, class SK, class C, class A>
	RBtree<T, SK, C, A>::~RBtree()
	{
		this->clearTree();
		_allocator_object.destroy(this->_nilnode);
		_allocator_object.deallocate(this->_nilnode, 1);
	}

	template < class T, class SK, class C, class A>
	RBtree<T, SK, C, A> & 
	RBtree<T, SK, C, A>::operator=( const RBtree & other )
	{
		if (this == &other)
			return (*this);
		this->_allocator_object = other._allocator_object;
		this->_key_compare = other._key_compare;
		this->clearTree();
		_copyTreeHelper(other._pRoot);
		return (*this);
	}

	template < class T, class SK, class C, class A>
	typename RBtree<T, SK, C, A>::node_pointer
	RBtree<T, SK, C, A>::getNilPtr() const
	{
		return (this->_nilnode);
	}

	template < class T, class SK, class C, class A>
	typename RBtree<T, SK, C, A>::node_pointer
	RBtree<T, SK, C, A>::getRootPtr() const
	{
		return (this->_pRoot);
	}

	template < class T, class SK, class C, class A>
	typename RBtree<T, SK, C, A>::node_pointer
	RBtree<T, SK, C, A>::search( const T & value ) const
	{
		return (_searchHelper(this->_pRoot, value));
	}

	template < class T, class SK, class C, class A>
	ft::pair<typename RBtree<T, SK, C, A>::node_pointer, bool>
	RBtree<T, SK, C, A>::insertNode(const T & value)
	{
		ft::pair<node_pointer, bool> res;
		if (_isNilNode(this->_pRoot) == true)
		{
			_pRoot = this->_allocator_object.allocate(1);
			this->_allocator_object.construct(_pRoot, node_type(value, _nilnode, _nilnode, _nilnode, BLACK));
			this->_size++;
			res = ft::make_pair(this->_pRoot, true);
		}
		else
		{
			res = _BStreeInsert(this->_pRoot, value);
		}
		this->_pRoot->setColor(BLACK);
		this->_nilnode->_pRightChild = this->_pRoot->_maximum();
		this->_nilnode->_pLeftChild = NULL;
		this->_nilnode->_pParent = this->_pRoot;
		return (res);
	}


	template < class T, class SK, class C, class A>
	typename RBtree<T, SK, C, A>::node_pointer
	RBtree<T, SK, C, A>::insertNode(node_pointer hint, const T & value)
	{
		(void)hint;
		return ((this->insertNode(value)).first);
	}
	
	template < class T, class SK, class C, class A>
	bool
	RBtree<T, SK, C, A>::deleteNode(const T & value)
	{
		if (_BStreeDelete(value) == false)
			return (false);
		this->_pRoot->setColor(ft::BLACK);
		this->_nilnode->_pRightChild = this->_pRoot->_maximum();
		this->_nilnode->_pLeftChild = NULL;
		this->_nilnode->_pParent = this->_pRoot;
		return (true);
	}

	template < class T, class SK, class C, class A>
	void
	RBtree<T, SK, C, A>::clearTree()
	{
		_deleteTreeHelper(this->_pRoot);
		_pRoot = _nilnode;
	}

	template < class T, class SK, class C, class A>
	void
	RBtree<T, SK, C, A>::printTree() const
	{
		if (_isNilNode(this->_pRoot))
			std::cout << "Tree is empty" << std::endl;
		else
		{
			std::cout << "Tree size : " << this->_size << std::endl;
			std::cout << "Nilptr  is " << _nilnode << std::endl;
			std::cout << *_nilnode << std::endl;
			std::cout << "Root is " << std::endl;
			std::cout << "\t" << _pRoot << std::endl;
			std::cout << *_pRoot << std::endl;
			_printTreeHelper(_pRoot);
		}
	}

	template < class T, class SK, class C, class A>
	bool
	RBtree<T, SK, C, A>::isEmpty( void ) const
	{
		return (_isNilNode(this->_pRoot));
	}

	template < class T, class SK, class C, class A>
	typename RBtree<T, SK, C, A>::size_type
	RBtree<T, SK, C, A>::size() const
	{
		return (this->_size);
	}

	template < class T, class SK, class C, class A>
	typename RBtree<T, SK, C, A>::size_type
	RBtree<T, SK, C, A>::max_size() const
	{
		return (this->_allocator_object.max_size());
	}
	
	template < class T, class SK, class C, class A>
	typename RBtree<T, SK, C, A>::node_pointer
	RBtree<T, SK, C, A>::begin() const
	{
		return (this->_pRoot->_minimum());
	}
	
	template < class T, class SK, class C, class A>
	typename RBtree<T, SK, C, A>::node_pointer
	RBtree<T, SK, C, A>::end() const
	{
		return (this->_nilnode);
	}

	template < class T, class SK, class C, class A>
	typename RBtree<T, SK, C, A>::node_pointer
	RBtree<T, SK, C, A>::lower_bound(const T & val) const
	{
		node_pointer begin = this->_pRoot->_minimum();
		node_pointer target = begin;
		node_pointer pNode = this->_pRoot;
		while (pNode->isNilNode() == false)
		{
			if (this->_nodeCompare(val, pNode->getData()) == true) // val < node->data -> go left
			{
				pNode = pNode->_pLeftChild;
			}
			else if (this->_nodeCompare(pNode->getData(), val) == true) // val > node->data -> go right
			{
				if (pNode == this->_nilnode->_pRightChild)
					return (this->_nilnode);
				target = pNode;
				pNode = pNode->_pRightChild;
			}
			else // val == node->data;
				return (pNode);
		}
		return (target);
	}
	
	template < class T, class SK, class C, class A>
	typename RBtree<T, SK, C, A>::node_pointer
	RBtree<T, SK, C, A>::upper_bound(const T & val) const
	{
		node_pointer target = this->_nilnode->_pRightChild;
		node_pointer pNode = this->_pRoot;
		while (pNode->isNilNode() == false)
		{
			if (this->_nodeCompare(val, pNode->getData()) == false) // val >= node->data -> go->right
			{
				if (pNode == this->_nilnode->_pRightChild)
					return (this->_nilnode);
				pNode = pNode->_pRightChild;
			}
			else
			{
				target = pNode;
				pNode = pNode->_pLeftChild;
			}
		}
		return (target);
	}

	template < class T, class SK, class C, class A>
	void
	RBtree<T, SK, C, A>::swap(RBtree & other)
	{
		{
			node_pointer temp_node_ptr;

			temp_node_ptr = other._nilnode;
			other._nilnode = this->_nilnode;
			this->_nilnode = temp_node_ptr;

			temp_node_ptr = other._pRoot;
			other._pRoot = this->_pRoot;
			this->_pRoot = temp_node_ptr;
		}
		{
			size_type temp = other._size;
			other._size = this->_size;
			this->_size = temp;
		}
	}
}

#endif
