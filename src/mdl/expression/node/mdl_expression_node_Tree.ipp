/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_node_Tree.ipp                             */
/* Description:     tree (2-dimensional) expression node                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_NODE_TREE_IPP_
#define MDL_EXPRESSION_NODE_TREE_IPP_

namespace mdl {
namespace expression {
namespace node {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	Tree<A> :: Tree
	(
		const Tree* const node,
		const Direction direction
	) :
	Tree_ (node, direction) {
	}
	template<class A>
	Tree<A> :: Tree
	(
		const Symbol& symbol,
		const Tree* const node,
		const Direction direction
	) :
	Tree_ (symbol, node, direction) {
	}
	template<class A>
	Tree<A> :: ~ Tree() {
	}

	template<class A>
	inline typename Tree<A> :: Node_*
	Tree<A> :: getLeft() {
		return Tree_ :: getLeft (this);
	}
	template<class A>
	inline typename Tree<A> :: Node_*
	Tree<A> :: getRight() {
		return Tree_ :: getRight (this);
	}
	template<class A>
	inline typename Tree<A> :: Node_*
	Tree<A> :: getUp() {
		return Tree_ :: getUp (this);
	}
	template<class A>
	inline typename Tree<A> :: Node_*
	Tree<A> :: getDown() {
		return Tree_ :: getDown (this);
	}
	template<class A>
	inline const typename Tree<A> :: Node_*
	Tree<A> :: getLeft() const {
		return Tree_ :: getLeft (this);
	}
	template<class A>
	inline const typename Tree<A> :: Node_*
	Tree<A> :: getRight() const {
		return Tree_ :: getRight (this);
	}
	template<class A>
	inline const typename Tree<A> :: Node_*
	Tree<A> :: getUp() const {
		return Tree_ :: getUp ();
	}
	template<class A>
	inline const typename Tree<A> :: Node_*
	Tree<A> :: getDown() const {
		return Tree_ :: getDown ();
	}

	template<class A>
	inline typename Tree<A> :: Node_*
	Tree<A> :: goLeft() {
		return Tree_ :: goLeft (this);
	}
	template<class A>
	inline typename Tree<A> :: Node_*
	Tree<A> :: goRight() {
		return Tree_ :: goRight (this);
	}
	template<class A>
	inline typename Tree<A> :: Node_*
	Tree<A> :: goUp() {
		return Tree_ :: goUp (this);
	}
	template<class A>
	inline typename Tree<A> :: Node_*
	Tree<A> :: goDown() {
		return Tree_ :: goDown (this);
	}
	template<class A>
	inline const typename Tree<A> :: Node_*
	Tree<A> :: goLeft() const {
		return Tree_ :: goLeft (this);
	}
	template<class A>
	inline const typename Tree<A> :: Node_*
	Tree<A> :: goRight() const {
		return Tree_ :: goRight (this);
	}
	template<class A>
	inline const typename Tree<A> :: Node_*
	Tree<A> :: goUp() const {
		return Tree_ :: goUp ();
	}
	template<class A>
	inline const typename Tree<A> :: Node_*
	Tree<A> :: goDown() const {
		return Tree_ :: goDown ();
	}

	template<class A>
	inline void
	Tree<A> :: operator = (const Symbol& symbol) {
		Tree_ :: operator = (symbol);
	}

	template<class A>
	template<Direction>
	inline bool
	Tree<A> :: isTerminal () const {
		return Tree_ :: template isTerminal<Direction>();
	}

	template<class A>
	void
	Tree<A> :: showSymbol (String& string) const {
		Tree_ :: showSymbol (string);
	}
	template<class A>
	void
	Tree<A> :: showTerms (String&string) const {
		Tree_ :: showTerm (string);
	}
	template<class A>
	void
	Tree<A> :: showTree (String& string) const {
		Tree_ :: showTree (string);
	}
	template<class A>
	void
	Tree<A> :: showBack (String& string) const {
		Tree_ :: showBack (string);
	}

	// object :: Object implementation
	template<class A>
	inline void
	Tree<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	inline Size_t
	Tree<A> :: getVolume() const {
		return Tree_ :: getVolume();
	}
	template<class A>
	inline Size_t
	Tree<A> :: getSizeOf() const {
		return sizeof (Tree);
	}
	template<class A>
	void
	Tree<A> :: show (String& string) const {
		Tree_ :: show (string);
	}
	template<class A>
	void
	Tree<A> :: dump() const
	{
		enum {
			INITIAL_STRING_CAPACITY = 64
		};
		String string (INITIAL_STRING_CAPACITY);
		show (string);
		std :: cout << string;
	}
}
}
}

#endif /*MDL_EXPRESSION_NODE_TREE_IPP_*/
