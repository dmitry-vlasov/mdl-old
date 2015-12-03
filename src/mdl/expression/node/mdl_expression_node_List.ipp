/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_node_List.ipp                             */
/* Description:     list expression node                                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_NODE_LIST_IPP_
#define MDL_EXPRESSION_NODE_LIST_IPP_

namespace mdl {
namespace expression {
namespace node {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	List<A> :: List (const List& node) :
	List_ (node) {
	}
	template<class A>
	inline
	List<A> :: List
	(
		const List* const node,
		const Direction direction
	) :
	List_ (node, direction) {
	}
	template<class A>
	inline
	List<A> :: List
	(
		const Symbol& symbol,
		const List* const node,
		const Direction direction
	) :
	List_ (symbol, node, direction) {
	}
	template<class A>
	inline
	List<A> :: ~ List() {
	}

	template<class A>
	template<class A_1>
	inline typename List<A> :: Node_*
	List<A> :: cloneSelf() const {
		return new Node_ (*this);
	}

	template<class A>
	inline typename List<A> :: Node_*
	List<A> :: getLeft() {
		return List_ :: getLeft (this);
	}
	template<class A>
	inline typename List<A> :: Node_*
	List<A> :: getRight() {
		return List_ :: getRight (this);
	}
	template<class A>
	inline const typename List<A> :: Node_*
	List<A> :: getLeft() const {
		return List_ :: getLeft (this);
	}
	template<class A>
	inline const typename List<A> :: Node_*
	List<A> :: getRight() const {
		return List_ :: getRight (this);
	}

	template<class A>
	inline typename List<A> :: Node_*
	List<A> :: goLeft() {
		return List_ :: goLeft (this);
	}
	template<class A>
	inline typename List<A> :: Node_*
	List<A> :: goRight() {
		return List_ :: goRight (this);
	}
	template<class A>
	inline const typename List<A> :: Node_*
	List<A> :: goLeft() const {
		return List_ :: goLeft (this);
	}
	template<class A>
	inline const typename List<A> :: Node_*
	List<A> :: goRight() const {
		return List_ :: goRight (this);
	}

	template<class A>
	void
	List<A> :: setLeft (const Node_* left) const {
		List_ :: setLeft (left);
	}
	template<class A>
	void
	List<A> :: setRight (const Node_* right) const {
		List_ :: setRight (right);
	}

	template<class A>
	inline void
	List<A> :: operator = (const Symbol& symbol) {
		List_ :: operator = (symbol);
	}

	template<class A>
	void
	List<A> :: showSymbol (String& string) const {
		List_ :: showSymbol (string);
	}
	template<class A>
	void
	List<A> :: showTerms (String& string) const {
		List_ :: showTerms (string);
	}
	template<class A>
	void
	List<A> :: showBack (String& string) const {
		List_ :: showBack (string);
	}

	// object :: Object implementation
	template<class A>
	inline void
	List<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	inline Size_t
	List<A> :: getVolume() const {
		return List_ :: getVolume();
	}
	template<class A>
	inline Size_t
	List<A> :: getSizeOf() const {
		return sizeof (List);
	}
	template<class A>
	void
	List<A> :: show (String& string) const {
		List_ :: show (string);
	}
	template<class A>
	void
	List<A> :: dump() const
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

#endif /*MDL_EXPRESSION_NODE_LIST_IPP_*/
