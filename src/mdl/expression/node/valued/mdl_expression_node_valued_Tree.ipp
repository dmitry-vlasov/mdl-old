/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_node_valued_Tree.ipp                      */
/* Description:     value containing tree node                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace expression {
namespace node {
namespace valued {

	/****************************
	 *		Public members
	 ****************************/

	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	Tree<V, H, S, A> :: Tree
	(
		const Tree* const node,
		const Direction direction,
		const Value_ value
	) :
	Tree_ (node, direction),
	data_ (value) {
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	Tree<V, H, S, A> :: Tree
	(
		const Symbol& symbol,
		const Tree* const node,
		const Direction direction,
		const Value_ value
	) :
	Tree_ (symbol, node, direction),
	data_ (value) {
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	Tree<V, H, S, A> :: ~ Tree() {
	}

	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline typename Tree<V, H, S, A> :: Data_&
	Tree<V, H, S, A> :: getData() {
		return data_;
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline const typename Tree<V, H, S, A> :: Data_&
	Tree<V, H, S, A> :: getData() const {
		return data_;
	}

	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline typename Tree<V, H, S, A> :: Node_*
	Tree<V, H, S, A> :: getLeft() {
		return Tree_ :: getLeft (this);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline typename Tree<V, H, S, A> :: Node_*
	Tree<V, H, S, A> :: getRight() {
		return Tree_ :: getRight (this);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline typename Tree<V, H, S, A> :: Node_*
	Tree<V, H, S, A> :: getUp () {
		return Tree_ :: getUp ();
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline typename Tree<V, H, S, A> :: Node_*
	Tree<V, H, S, A> :: getDown () {
		return Tree_ :: getDown ();
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline const typename Tree<V, H, S, A> :: Node_*
	Tree<V, H, S, A> :: getLeft() const {
		return Tree_ :: getLeft (this);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline const typename Tree<V, H, S, A> :: Node_*
	Tree<V, H, S, A> :: getRight() const {
		return Tree_ :: getRight (this);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline const typename Tree<V, H, S, A> :: Node_*
	Tree<V, H, S, A> :: getUp () const {
		return Tree_ :: getUp ();
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline const typename Tree<V, H, S, A> :: Node_*
	Tree<V, H, S, A> :: getDown () const {
		return Tree_ :: getDown ();
	}

	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline typename Tree<V, H, S, A> :: Node_*
	Tree<V, H, S, A> :: goLeft () {
		return Tree_ :: goLeft (this);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline typename Tree<V, H, S, A> :: Node_*
	Tree<V, H, S, A> :: goRight () {
		return Tree_ :: goRight (this);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline typename Tree<V, H, S, A> :: Node_*
	Tree<V, H, S, A> :: goUp () {
		return Tree_ :: goUp (this);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline typename Tree<V, H, S, A> :: Node_*
	Tree<V, H, S, A> :: goDown () {
		return Tree_ :: goDown (this);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline const typename Tree<V, H, S, A> :: Node_*
	Tree<V, H, S, A> :: goLeft() const
	{
		const Node_* result = Tree_ :: goLeft (this);
		if (Tree_ :: isLambda()) {
			const_cast<Node_*>(result)->data_.copy (data_);
		}
		return result;
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline const typename Tree<V, H, S, A> :: Node_*
	Tree<V, H, S, A> :: goRight() const
	{
		const Node_* result = Tree_ :: goRight (this);
		if (Tree_ :: isLambda()) {
			const_cast<Node_*>(result)->data_.copy (data_);
		}
		return result;
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline const typename Tree<V, H, S, A> :: Node_*
	Tree<V, H, S, A> :: goUp () const {
		return Tree_ :: goUp ();
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline const typename Tree<V, H, S, A> :: Node_*
	Tree<V, H, S, A> :: goDown () const {
		return Tree_ :: goDown ();
	}

	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline void
	Tree<V, H, S, A> :: operator = (const Symbol& symbol) {
		Tree_ :: operator = (symbol);
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	void
	Tree<V, H, S, A> :: showSymbol (String& string) const {
		Tree_ :: showSymbol (string);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	void
	Tree<V, H, S, A> :: showTerms (String& string) const {
		Tree_ :: showTerms (string);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	void
	Tree<V, H, S, A> :: showTree (String& string) const
	{
		if (Tree_ :: right_ == NULL) {
			showBack (string);
			string << tab <<" data:" << tab;
			string << data_;
			string << endLine;
		} else {
			Tree_ :: right_->showTree (string);
		}
		if (Tree_ :: up_ != NULL) {
			Tree_ :: up_->showTree (string);
		}
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	void
	Tree<V, H, S, A> :: showBack (String& string) const {
		Tree_ :: showBack (string);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	void
	Tree<V, H, S, A> :: showKind (String& string) {
		string << "Tree (valued)" << endLine;
	}

	// object :: Object implementation
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	inline void
	Tree<V, H, S, A> :: commitSuicide() {
		delete this;
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	Size_t
	Tree<V, H, S, A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += Tree_ :: getVolume();
		volume += data_.getVolume();
		return volume;
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	Size_t
	Tree<V, H, S, A> :: getSizeOf() const {
		return sizeof (Tree);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	void
	Tree<V, H, S, A> :: show (String& string) const {
		Tree_ :: show (string);
	}
	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	void
	Tree<V, H, S, A> :: dump() const
	{
		enum {
			INITIAL_STRING_CAPACITY = 64
		};
		String string (INITIAL_STRING_CAPACITY);
		show (string);
		std :: cout << string;
	}

	/******************************
	 *		Overloaded operators
	 ******************************/

	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	String&
	operator << (String& string, const Tree<V, H, S, A>& tree)
	{
		tree.showTree (string);
		return string;
	}
}
}
}
}


