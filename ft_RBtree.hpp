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
		const static RBtreeNode	* _nilnode = NULL;
		RBtreeNode	*_proot;
		bool	_isNilNode(RBtreeNode * pNode) {return (pNode == _nilnode);}
		void	_rotateLeft(RBtreeNode * pPivotNode);
		void	_rotateRight(RBtreeNode * pPivotNode);
	public :
		//(constructor)
		//(destructor)

		//member functions
		RBtreeNode * insertNode(T value);
		RBtreeNode * insertNode(RBtreeNode * pNode);
		void deleteNode(T value);
		void deleteNode(RBtreeNode * pNode);
	};

} // namespace ft