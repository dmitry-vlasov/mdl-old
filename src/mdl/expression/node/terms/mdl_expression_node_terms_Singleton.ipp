/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_node_terms_Singleton.ipp                  */
/* Description:     node container for terms: single term                    */
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
namespace terms {

	/****************************
	 *		Public members
	 ****************************/

	template<class T, class A, bool M>
	inline
	Singleton<T, A, M> :: Singleton() :
	node_ () {
	}
	template<class T, class A, bool M>
	inline
	Singleton<T, A, M> :: ~ Singleton() {
	}

	template<class T, class A, bool M>
	template<class P>
	inline void
	Singleton<T, A, M> :: cloneContents (P* pool) const
	{
		const Term_* term = node_.getValue();
		if (term != NULL) {
			const_cast<Node_&>(node_).getReference() = term->clone (pool);
		}
	}

	template<class T, class A, bool M>
	inline bool
	Singleton<T, A, M> :: isEmpty() const
	{
		return (node_.getValue() == NULL);
	}
	template<class T, class A, bool M>
	inline const typename Singleton<T, A, M> :: Node_*
	Singleton<T, A, M> :: getFirst() const
	{
		if (isEmpty()) {
			return NULL;
		} else {
			return &node_;
		}
	}
	template<class T, class A, bool M>
	inline const typename Singleton<T, A, M> :: Node_*
	Singleton<T, A, M> :: getLast() const
	{
		if (isEmpty()) {
			return NULL;
		} else {
			return &node_;
		}
	}
	template<class T, class A, bool M>
	inline void
	Singleton<T, A, M> :: addFirst (const Term_* const term) {
		node_.getReference() = term;
	}
	template<class T, class A, bool M>
	inline void
	Singleton<T, A, M> :: addLast (const Term_* const term) {
		node_.getReference() = term;
	}
	template<class T, class A, bool M>
	inline const typename Singleton<T, A, M> :: Term_*
	Singleton<T, A, M> :: getTerm() const {
		return node_.getValue();
	}

	template<class T, class A, bool M>
	inline void
	Singleton<T, A, M> :: operator = (const Singleton& singleton) {
		node_ = singleton.node_;
	}

	template<class T, class A, bool M>
	template<class T1, class A1, bool M1>
	inline bool
	Singleton<T, A, M> :: subset
	(
		const List<T1, A1, M1>& list,
		const Term_* term0,
		const T1* term1
	) const
	{
		if (isEmpty()) {
			return list.isEmpty();
		}
		typedef List<T1, A1, M1> List;
		typedef
			typename List :: Node_
			Node;
		typedef
			typename List :: Term_
			Term;
		const Node* node = list.getFirst();
		while (node != NULL) {
			const Term* const
				term_1 = node->getValue();
			if (*term_1 == *getTerm()) {
				return true;
			}
			if (term_1 == term1) {
				break;
			}
			node = node->getNext();
		}
		return false;
	}
	template<class T, class A, bool M>
	template<class T1, class A1, bool M1>
	inline bool
	Singleton<T, A, M> :: coinside
	(
		const Singleton<T1, A1, M1>& singleton,
		const Term_* term0,
		const T1* term1
	) const
	{
		if (isEmpty()) {
			return singleton.isEmpty();
		} else {
			bool result = true;
			//result = result && (getTerm() == term0);
			//result = result && (singleton.getTerm() == term1);
			result = result && (*singleton.getTerm() == *getTerm());
			return result;
		}
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	template<class T, class A, bool M>
	void
	Singleton<T, A, M> :: showAll (String& string) const
	{
		const Term_* term = node_.getValue();
		if (term == NULL) {
			string << tab << "NULL" << endLine;
		} else {
			term->showAll (string);
		}
		string << endLine;
	}
	template<class T, class A, bool M>
	void
	Singleton<T, A, M> :: showTypes (String& string) const
	{
		const Term_* term = node_.getValue();
		string << " : ";
		term->getType()->replicateName (string);
	}

	// object :: Object implementation
	template<class T, class A, bool M>
	inline void
	Singleton<T, A, M> :: commitSuicide() {
		delete this;
	}
	template<class T, class A, bool M>
	inline Size_t
	Singleton<T, A, M> :: getVolume() const {
		return node_.getVolume();
	}
	template<class T, class A, bool M>
	inline Size_t
	Singleton<T, A, M> :: getSizeOf() const {
		return sizeof (Singleton);
	}
	template<class T, class A, bool M>
	void
	Singleton<T, A, M> :: show (String& string) const {
		node_.show (string);
	}

	/*********************************
	 *		Public List :: Node_
	 *********************************/

	template<class T, class A, bool M>
	inline
	Singleton<T, A, M> :: Node_ :: Node_ () :
	term_ (NULL) {
	}
	template<class T, class A, bool M>
	inline
	Singleton<T, A, M> :: Node_ :: ~ Node_ ()
	{
		if (IS_MASTER) {
			if (term_ != NULL) {
				const_cast<Term_*>(term_)->commitSuicide();
				term_ = NULL;
			}
		}
	}

	template<class T, class A, bool M>
	inline const typename Singleton<T, A, M> :: Term_*
	Singleton<T, A, M> :: Node_ :: getValue() const {
		return term_;
	}
	template<class T, class A, bool M>
	inline const typename Singleton<T, A, M> :: Term_*&
	Singleton<T, A, M> :: Node_ :: getReference() {
		return term_;
	}
	template<class T, class A, bool M>
	inline const typename Singleton<T, A, M> :: Term_* const&
	Singleton<T, A, M> :: Node_ :: getReference() const {
		return term_;
	}
	template<class T, class A, bool M>
	inline const typename Singleton<T, A, M> :: Node_*
	Singleton<T, A, M> :: Node_ :: getNext() const {
		return NULL;
	}
	template<class T, class A, bool M>
	inline void
	Singleton<T, A, M> :: Node_ :: operator = (const Node_& node) {
		term_= node.term_;
	}

	// object :: Object implementation
	template<class T, class A, bool M>
	inline void
	Singleton<T, A, M> :: Node_ :: commitSuicide() {
		delete this;
	}
	template<class T, class A, bool M>
	inline Size_t
	Singleton<T, A, M> :: Node_ :: getVolume() const
	{
		Size_t volume = 0;
		if (IS_MASTER && (term_ != NULL)) {
			volume += term_->getVolume();
			volume += term_->getSizeOf();
		}
		return volume;
	}
	template<class T, class A, bool M>
	inline Size_t
	Singleton<T, A, M> :: Node_ :: getSizeOf() const {
		return sizeof (Node_);
	}
	template<class T, class A, bool M>
	void
	Singleton<T, A, M> :: Node_ :: show (String& string) const
	{
		if (term_ == NULL) {
			string << tab << "NULL" << endLine;
		} else {
			string << tab << *term_ << space;
			term_->showType (string);
			string << space << "(" << term_ << ")" << space;
			string << endLine;
		}
	}
	template<class T, class A, bool M>
	void
	Singleton<T, A, M> :: dump() const
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

	template<class T, class A, bool M>
	String&
	operator << (String& string, const Singleton<T, A, M>& list)
	{
		list.show (string);
		string << endLine;
		return string;
	}
}
}
}
}


