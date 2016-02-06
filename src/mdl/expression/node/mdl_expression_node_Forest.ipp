/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_node_Forest.ipp                           */
/* Description:     forest (monotonous tree set) expression node             */
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

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	Forest<A> :: Forest
	(
		const Forest* const node,
		const Direction direction
	) :
	Forest_ (node, direction) {
	}
	template<class A>
	Forest<A> :: Forest
	(
		const Symbol& symbol,
		const index :: Step level,
		const Forest* const node,
		const Direction direction
	) :
	Forest_ (symbol, level, node, direction) {
	}
	template<class A>
	Forest<A> :: ~ Forest() {
	}

	template<class A>
	inline typename Forest<A> :: Node_*
	Forest<A> :: getLeft () {
		return Forest_ :: getLeft (this);
	}
	template<class A>
	inline typename Forest<A> :: Node_*
	Forest<A> :: getRight () {
		return Forest_ :: getRight (this);
	}
	template<class A>
	inline typename Forest<A> :: Node_*
	Forest<A> :: getUp () {
		return Forest_ :: getUp (this);
	}
	template<class A>
	inline typename Forest<A> :: Node_*
	Forest<A> :: getDown () {
		return Forest_ :: getDown (this);
	}
	template<class A>
	inline const typename Forest<A> :: Node_*
	Forest<A> :: getLeft() const {
		return Forest_ :: getLeft (this);
	}
	template<class A>
	inline const typename Forest<A> :: Node_*
	Forest<A> :: getRight() const {
		return Forest_ :: getRight (this);
	}
	template<class A>
	inline const typename Forest<A> :: Node_*
	Forest<A> :: getUp() const {
		return Forest_ :: getUp ();
	}
	template<class A>
	inline const typename Forest<A> :: Node_*
	Forest<A> :: getDown() const {
		return Forest_ :: getDown ();
	}

	template<class A>
	inline typename Forest<A> :: Node_*
	Forest<A> :: goLeft () {
		return Forest_ :: goLeft (this);
	}
	template<class A>
	inline typename Forest<A> :: Node_*
	Forest<A> :: goRight () {
		return Forest_ :: goRight (this);
	}
	template<class A>
	inline typename Forest<A> :: Node_*
	Forest<A> :: goUp () {
		return Forest_ :: goUp (this);
	}
	template<class A>
	inline typename Forest<A> :: Node_*
	Forest<A> :: goDown () {
		return Forest_ :: goDown (this);
	}
	template<class A>
	inline const typename Forest<A> :: Node_*
	Forest<A> :: goLeft() const {
		return Forest_ :: goLeft (this);
	}
	template<class A>
	inline const typename Forest<A> :: Node_*
	Forest<A> :: goRight() const {
		return Forest_ :: goRight (this);
	}
	template<class A>
	inline const typename Forest<A> :: Node_*
	Forest<A> :: goUp() const {
		return Forest_ :: goUp ();
	}
	template<class A>
	inline const typename Forest<A> :: Node_*
	Forest<A> :: goDown() const {
		return Forest_ :: goDown ();
	}

	template<class A>
	inline void
	Forest<A> :: operator = (const Symbol& symbol) {
		Forest_ :: operator = (symbol);
	}

	template<class A>
	void
	Forest<A> :: showSymbol (String& string) const {
		Forest_ :: showSymbol (string);
	}
	template<class A>
	void
	Forest<A> :: showTerms (String&string) const {
		Forest_ :: showTerm (string);
	}
	template<class A>
	void
	Forest<A> :: showTree (String& string) const {
		Forest_ :: showTree (string);
	}
	template<class A>
	void
	Forest<A> :: showBack (String& string) const {
		Forest_ :: showBack (string);
	}

	// object :: Object implementation
	template<class A>
	inline void
	Forest<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	inline Size_t
	Forest<A> :: getVolume() const {
		return Forest_ :: getVolume();
	}
	template<class A>
	inline Size_t
	Forest<A> :: getSizeOf() const {
		return sizeof (Forest);
	}
	template<class A>
	void
	Forest<A> :: show (String& string) const {
		Forest_ :: show (string);
	}
	template<class A>
	void
	Forest<A> :: dump() const
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


