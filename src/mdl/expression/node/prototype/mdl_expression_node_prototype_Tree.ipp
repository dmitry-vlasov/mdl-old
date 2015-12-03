/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_node_prototype_Tree.ipp                   */
/* Description:     represents a tree node (2-dimensional)                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_NODE_PROTOTYPE_TREE_IPP_
#define MDL_EXPRESSION_NODE_PROTOTYPE_TREE_IPP_

namespace mdl {
namespace expression {
namespace node {
namespace prototype {

	/****************************
	 *		Public members
	 ****************************/

	template<class T, class N, template<class, class> class S, class A>
	inline
	Tree<T, N, S, A> :: Tree
	(
		const Node_* const node,
		const Direction dir
	) :
	List_ (node, dir),
	up_ (dir == direction :: DOWN ? const_cast<Node_*>(node) : NULL),
	down_ (dir == direction :: UP ? const_cast<Node_*>(node) : NULL) {
	}
	template<class T, class N, template<class, class> class S, class A>
	inline
	Tree<T, N, S, A> :: Tree
	(
		const Symbol& symbol,
		const Node_* const node,
		const Direction dir
	) :
	List_ (symbol, node, dir),
	up_ (dir == direction :: DOWN ? const_cast<Node_*>(node) : NULL),
	down_ (dir == direction :: UP ? const_cast<Node_*>(node) : NULL) {
	}
	template<class T, class N, template<class, class> class S, class A>
	inline
	Tree<T, N, S, A> :: ~ Tree() {
	}

	template<class T, class N, template<class, class> class S, class A>
	inline void
	Tree<T, N, S, A> :: deleteNodes() const
	{
		List_ :: deleteNodes();
		if (up_ != NULL) {
			up_->deleteNodes();
			delete up_;
			up_ = NULL;
		}
	}

	template<class T, class N, template<class, class> class S, class A>
	inline typename Tree<T, N, S, A> :: const_Iterator_
	Tree<T, N, S, A> :: getIterator() const {
		return const_Iterator_ (this);
	}
	template<class T, class N, template<class, class> class S, class A>
	inline typename Tree<T, N, S, A> :: Iterator_
	Tree<T, N, S, A> :: getIterator() {
		return Iterator_ (this);
	}

	template<class T, class N, template<class, class> class S, class A>
	inline typename Tree<T, N, S, A> :: Node_*
	Tree<T, N, S, A> :: getLeft (Node_* node) {
		return List_ :: getLeft (node);
	}
	template<class T, class N, template<class, class> class S, class A>
	inline typename Tree<T, N, S, A> :: Node_*
	Tree<T, N, S, A> :: getRight (Node_* node) {
		return  List_ :: getRight (node);
	}
	template<class T, class N, template<class, class> class S, class A>
	inline typename Tree<T, N, S, A> :: Node_*
	Tree<T, N, S, A> :: getUp() {
		return up_;
	}
	template<class T, class N, template<class, class> class S, class A>
	inline typename Tree<T, N, S, A> :: Node_*
	Tree<T, N, S, A> :: getDown() {
		return  down_;
	}
	template<class T, class N, template<class, class> class S, class A>
	inline const typename Tree<T, N, S, A> :: Node_*
	Tree<T, N, S, A> :: getLeft (const Node_* node) const {
		return List_ :: getLeft (node);
	}
	template<class T, class N, template<class, class> class S, class A>
	inline const typename Tree<T, N, S, A> :: Node_*
	Tree<T, N, S, A> :: getRight (const Node_* node) const {
		return List_ :: getRight (node);
	}
	template<class T, class N, template<class, class> class S, class A>
	inline const typename Tree<T, N, S, A> :: Node_*
	Tree<T, N, S, A> :: getUp() const {
		return up_;
	}
	template<class T, class N, template<class, class> class S, class A>
	inline const typename Tree<T, N, S, A> :: Node_*
	Tree<T, N, S, A> :: getDown() const {
		return down_;
	}
	template<class T, class N, template<class, class> class S, class A>
	inline const typename Tree<T, N, S, A> :: Node_*
	Tree<T, N, S, A> :: goLeft (const Node_* node) const {
		return List_ :: goLeft (node);
	}
	template<class T, class N, template<class, class> class S, class A>
	inline const typename Tree<T, N, S, A> :: Node_*
	Tree<T, N, S, A> :: goRight (const Node_* node) const {
		return List_ :: goRight (node);
	}
	template<class T, class N, template<class, class> class S, class A>
	inline const typename Tree<T, N, S, A> :: Node_*
	Tree<T, N, S, A> :: goUp() const {
		return up_;
	}
	template<class T, class N, template<class, class> class S, class A>
	inline const typename Tree<T, N, S, A> :: Node_*
	Tree<T, N, S, A> :: goDown() const {
		return down_;
	}

	template<class T, class N, template<class, class> class S, class A>
	inline void
	Tree<T, N, S, A> :: operator = (const Symbol& symbol) {
		List_ :: operator = (symbol);
	}

	template<class T, class N, template<class, class> class S, class A>
	template<Direction dir>
	inline bool
	Tree<T, N, S, A> :: isTerminal() const
	{
		switch (dir) {
		case direction :: UP : {
			return (up_ == NULL);
		}
		case direction :: DOWN : {
			return (down_ == NULL);
		}
		default :
			return List_ :: template isTerminal<dir>();
		}
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	template<class T, class N, template<class, class> class S, class A>
	void
	Tree<T, N, S, A> :: showSymbol (String& string) const {
		List_ :: showSymbol (string);
	}
	template<class T, class N, template<class, class> class S, class A>
	void
	Tree<T, N, S, A> :: showTerms (String& string) const {
		List_ :: showTerms (string);
	}
	template<class T, class N, template<class, class> class S, class A>
	void
	Tree<T, N, S, A> :: showTree (String& string) const
	{
		if (List_ :: right_ == NULL) {
			showBack (string);
			string << endLine;
		} else {
			List_ :: right_->showTree (string);
		}
		if (up_ != NULL) {
			up_->showTree (string);
		}
	}
	template<class T, class N, template<class, class> class S, class A>
	void
	Tree<T, N, S, A> :: showBack (String& string) const {
		List_ :: showBack (string);
	}
	template<class T, class N, template<class, class> class S, class A>
	void
	Tree<T, N, S, A> :: showKind (String& string) {
		string << "Tree" << endLine;
	}

	// object :: Object implementation
	template<class T, class N, template<class, class> class S, class A>
	inline void
	Tree<T, N, S, A> :: commitSuicide() {
		delete this;
	}
	template<class T, class N, template<class, class> class S, class A>
	inline Size_t
	Tree<T, N, S, A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += List_ :: getVolume();
		volume += List_ :: getAggregateVolume (List_ :: right_);
		volume += List_ :: getAggregateVolume (up_);
		return volume;
	}
	template<class T, class N, template<class, class> class S, class A>
	inline Size_t
	Tree<T, N, S, A> :: getSizeOf() const {
		return sizeof (Tree);
	}
	template<class T, class N, template<class, class> class S, class A>
	void
	Tree<T, N, S, A> :: show (String& string) const {
		List_ :: show (string);
	}
	template<class T, class N, template<class, class> class S, class A>
	void
	Tree<T, N, S, A> :: dump() const
	{
		enum {
			INITIAL_STRING_CAPACITY = 64
		};
		String string (INITIAL_STRING_CAPACITY);
		show (string);
		std :: cout << string;
	}

	/****************************
	 *		Protected members
	 ****************************/

	template<class T, class N, template<class, class> class S, class A>
	inline typename Tree<T, N, S, A> :: Node_*
	Tree<T, N, S, A> :: goLeft (Node_* right) {
		return List_ :: goLeft (right);
	}
	template<class T, class N, template<class, class> class S, class A>
	inline typename Tree<T, N, S, A> :: Node_*
	Tree<T, N, S, A> :: goRight (Node_* left) {
		return List_ :: goRight (left);
	}
	template<class T, class N, template<class, class> class S, class A>
	inline typename Tree<T, N, S, A> :: Node_*
	Tree<T, N, S, A> :: goUp (Node_* down)
	{
		if (up_ == NULL) {
			up_ = new Node_ (down, direction :: UP);
			up_->left_ = List_ :: left_;
		}
		return up_;
	}
	template<class T, class N, template<class, class> class S, class A>
	inline typename Tree<T, N, S, A> :: Node_*
	Tree<T, N, S, A> :: goDown (Node_* up)
	{
		if (down_ == NULL) {
			down_ = new Node_ (up, direction :: DOWN);
			up_->left_ = List_ :: left_;
		}
		return down_;
	}

	/******************************
	 *		Overloaded operators
	 ******************************/

	template<class T, class N, template<class, class> class S, class A>
	String&
	operator << (String& string, const Tree<T, N, S, A>& tree)
	{
		tree.showTree (string);
		return string;
	}
}
}
}
}

#endif /*MDL_EXPRESSION_NODE_PROTOTYPE_TREE_IPP_*/
