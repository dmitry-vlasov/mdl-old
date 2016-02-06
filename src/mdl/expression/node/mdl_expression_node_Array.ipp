/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_node_Array.ipp                            */
/* Description:     array expression node                                    */
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
	inline
	Array<A> :: Array() :
	Singleton_ () {
	}
	template<class A>
	inline
	Array<A> :: Array (const Array& array) :
	Singleton_ (array) {
	}
	template<class A>
	inline
	Array<A> :: ~ Array () {
	}

	template<class A>
	template<class A_1>
	inline typename Array<A> :: Node_*
	Array<A> :: cloneSelf() const {
		return new Node_ (*this);
	}

	template<class A>
	inline typename Array<A> :: const_Iterator_
	Array<A> :: getIterator() const {
		return const_Iterator_ (this);
	}
	template<class A>
	inline typename Array<A> :: Iterator_
	Array<A> :: getIterator() {
		return Iterator_ (this);
	}

	template<class A>
	inline Array<A>*
	Array<A> :: getLeft() {
		return this - 1;
	}
	template<class A>
	inline Array<A>*
	Array<A> :: getRight() {
		return this + 1;
	}
	template<class A>
	inline const Array<A>*
	Array<A> :: getLeft() const {
		return this - 1;
	}
	template<class A>
	inline const Array<A>*
	Array<A> :: getRight() const {
		return  this + 1;
	}

	template<class A>
	inline Array<A>*
	Array<A> :: goLeft() {
		return this - 1;
	}
	template<class A>
	inline Array<A>*
	Array<A> :: goRight() {
		return this + 1;
	}
	template<class A>
	inline const Array<A>*
	Array<A> :: goLeft() const {
		return this - 1;
	}
	template<class A>
	inline const Array<A>*
	Array<A> :: goRight() const {
		return this + 1;
	}

	template<class A>
	template<Direction dir>
	inline bool
	Array<A> :: isTerminal (const typename expression :: Array<Allocator_>* expression) const
	{
		if (dir == direction :: LEFT) {
			if (expression == NULL) {
				return (this - 1)->isUndefined();
			} else {
				return (expression->getBegin().getNode() == this);
			}
		}
		if (dir == direction :: RIGHT) {
			if (expression == NULL) {
				return (this + 1)->isUndefined();
			} else {
				return (expression->getEnd().getNode() == this);
			}
		}
		return true;
	}

	template<class A>
	inline void
	Array<A> :: operator = (const Symbol& symbol) {
		Singleton_ :: operator = (symbol);
	}
	template<class A>
	inline void
	Array<A> :: operator = (const Array& array) {
		Singleton_ :: operator = (array);
	}

using manipulator :: endLine;
using manipulator :: tab;

	template<class A>
	void
	Array<A> :: showSymbol (String& string) const {
		Singleton_ :: showSymbol (string);
	}
	template<class A>
	void
	Array<A> :: showTerms (String& string) const {
		Singleton_ :: showTerms (string);
	}
	template<class A>
	void
	Array<A> :: showBack (String& string) const
	{
		typedef
			typename Singleton_ :: Terms_ :: Terminal_ :: Node_
			Node_;
		const Node_* node = Singleton_ :: getTerms().getTerminal().getFirst();
		const Term_* longestTerm = NULL;
		value :: Integer maxLength = 0;
		while (node != NULL) {
			const Term_* term = node->getValue();
			const value :: Integer length = term->getLength();
			if (length > maxLength) {
				maxLength = length;
				longestTerm = term;
			}
			node = node->getNext();
		}
		string << tab;
		longestTerm->show (string);
	}

	template<class A>
	void
	Array<A> :: showKind (String& string) {
		string << "Array" << endLine;
	}

	// object :: Object implementation
	template<class A>
	inline void
	Array<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	inline Size_t
	Array<A> :: getVolume() const {
		return Singleton_ :: getVolume();
	}
	template<class A>
	inline Size_t
	Array<A> :: getSizeOf() const {
		return sizeof (Array);
	}
	template<class A>
	void
	Array<A> :: show (String& string) const {
		Singleton_ :: show (string);
	}
	template<class A>
	void
	Array<A> :: dump() const
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


