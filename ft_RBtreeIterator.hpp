#ifndef FT_RBTREEITERATOR_HPP
# define FT_RBTREEITERATOR_HPP
# include <memory>
# include "ft_iterator.hpp"
# include "ft_RBtreeNode.hpp"

namespace ft
{
	// RBtreeIterator
	template <class T>
	class tree_iterator
	{
	private :
		typedef typename ft::iterator< ft::bidirectional_iterator_tag, RBtreeNode<T> > iterator_type;

		typedef typename iterator_type::difference_type		difference_type;
		typedef typename iterator_type::iterator_category	iterator_category;
		typedef typename RBtreeNode<T>::value_type			value_type;
		typedef typename RBtreeNode<T>::node_pointer		node_pointer;
		
		typedef value_type*				pointer;
		typedef value_type&				reference;

	private :
		node_pointer _pNode;

		void _increment();
		void _decrement();

		tree_iterator() {}
	public :
		explicit tree_iterator(node_pointer pNode) : _pNode(pNode) {}
		tree_iterator(const tree_iterator & it) : _pNode(it._pNode) {}
		tree_iterator & operator=(const tree_iterator & other)
		{
			if (this != &other)
				this->_pNode = other._pNode;
			return (*this);
		}

		operator tree_iterator<const T> () const
		{
			return ( tree_iterator<const T>(this->_pNode) );
		}

		const node_pointer base() const {return _pNode;}

		reference operator*()
		{
			return (this->_pNode->_data);
		}

		pointer operator->()
		{
			return (&(this->_pNode->_data));
		}

		tree_iterator<T> & operator++()
		{
			this->_increment();
			return (*this);
		}
		tree_iterator<T> operator++(int)
		{
			tree_iterator<T> temp(*this);
			this->_increment();
			return (temp);
		}
		tree_iterator<T> & operator--()
		{
			this->_decrement();
			return (*this);
		}
		tree_iterator<T> operator--(int)
		{
			tree_iterator<T> temp(*this);
			this->_decrement();
			return (temp);
		}

		template <class Iter>
		friend bool operator==(const tree_iterator<T> & lhs, const tree_iterator<Iter> & rhs)
		{ return (lhs._pNode == rhs._pNode);}

		template <class Iter>
		friend bool operator!=(const tree_iterator<T> & lhs, const tree_iterator<Iter> & rhs)
		{ return (lhs._pNode != rhs._pNode);}
	};

	/*
		1. 오른쪽 자식이 nilnode가 아니면 (오른쪽 자식이 있으면) 오른쪽 서브트리에서 가장 작은 값을 찾는다.
		2. 현재 노드가 왼쪽 자식이라면, 부모노드의 오른쪽 서브트리는 항상 부모 노드보다 크기 때문에 부모노드로 이동한다.
		3. 현재 노드가 오른쪽 자식이라면, 부모노드의 상황에 따라 달라진다. 부모노드가 오른쪽 자식인 경우 계속 올라가고 부모노드가 왼쪽자식인 경우 멈춘다.
			계속 따라 올라가다, nilNode를 만나면 
	*/
	template<class T>
	void tree_iterator<T>::_increment()
	{
		if (_pNode->_isNilNode())
			return ;
		else if (_pNode->_pRightChild->_isNilNode() == false)
		{
			_pNode = _pNode->_pRightChild->_minimum();
		}
		else if (_pNode == _pNode->_pParent->_pLeftChild)
		{
			_pNode = _pNode->_pParent;
		}
		else
		{
			while (_pNode == _pNode->_pParent->_pRightChild)
			{
				_pNode = _pNode->_pParent;
			}
			_pNode = _pNode->_pParent;
		}
	}

	template<class T>
	void tree_iterator<T>::_decrement()
	{
		if (_pNode->_isNilNode())
			_pNode = _pNode->_pRightChild;
		else if (_pNode->_pLeftChild->_isNilNode() == false)
		{
			_pNode = _pNode->_pLeftChild->_maximum();
		}
		else if (_pNode == _pNode->_pParent->_pRightChild)
			_pNode = _pNode->_pParent;
		else
		{
			while (_pNode == _pNode->_pParent->_pLeftChild)
				_pNode = _pNode->_pParent;
			if (_pNode == _pNode->_pParent->_pParent)
				_pNode = NULL;
			_pNode = _pNode->_pParent;
		}
	}
} // namespace ft

#endif