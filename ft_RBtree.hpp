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
		/* private members */
		const static RBtreeNode	* _nilnode = NULL;
		RBtreeNode	*_proot;
		
		/* private method */
		// utils
		bool	_isNilNode(RBtreeNode * pNode) {return (pNode == _nilnode);}
		// rotation
		void	_rotateLeft(RBtreeNode * pPivotNode);
		void	_rotateRight(RBtreeNode * pPivotNode);
		// insert_helpers
		// delete_helpers
	public :
		//(constructor)
		RBtree( void ) :_proot(NULL) ;
		RBtree( const RBtree & other );
		RBtree & operator=( const RBtree & other );
		//(destructor)
		~RBtree();

		//member functions
		RBtreeNode * searach(const T & key);
		RBtreeNode * insertNode(T value);
		RBtreeNode * insertNode(RBtreeNode * pNode);
		void deleteNode(T value);
		void deleteNode(RBtreeNode * pNode);

		/*non_member function*/
		friend ostream & operator<<( ostream & os, const RBtree & tree );
	}; // class RBtree

} // namespace ft