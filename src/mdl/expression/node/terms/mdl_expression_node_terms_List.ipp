/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_node_terms_List.ipp                       */
/* Description:     node container for terms: list                           */
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
	List<T, A, M> :: List() :
	terms_ () {
	}
	template<class T, class A, bool M>
	List<T, A, M> :: ~ List()
	{
		if (IS_MASTER) {
			const Node_* node = terms_.getFirst();
			while (node != NULL) {
				Term_* term = const_cast<Term_*>(node->getValue());
				term->commitSuicide();
				node = node->getNext();
			}
		}
	}

	template<class T, class A, bool M>
	template<class P>
	inline void
	List<T, A, M> :: cloneContents (P* pool) const
	{
		const Node_*
			node = terms_.getFirst();
		while (node != NULL) {
			const Term_* term = node->getValue();
			const_cast<Node_*>(node)->getReference() = term->clone (pool);
			node = node->getNext();
		}
	}

	template<class T, class A, bool M>
	inline bool
	List<T, A, M> :: isEmpty() const {
		return terms_.isEmpty();
	}
	template<class T, class A, bool M>
	inline const typename List<T, A, M> :: Node_*
	List<T, A, M> :: getFirst() const {
		return terms_.getFirst();
	}
	template<class T, class A, bool M>
	inline const typename List<T, A, M> :: Node_*
	List<T, A, M> :: getLast() const {
		return terms_.getLast();
	}
	template<class T, class A, bool M>
	inline void
	List<T, A, M> :: addFirst (const Term_* const term) {
		terms_.addFirst (term);
	}
	template<class T, class A, bool M>
	inline void
	List<T, A, M> :: addLast (const Term_* const term) {
		terms_.addLast (term);
	}
	template<class T, class A, bool M>
	inline const typename List<T, A, M> :: Term_*
	List<T, A, M> :: getTerm() const
	{
		const Node_* const
			node = terms_.getFirst();
		if (node == NULL) {
			return NULL;
		} else {
			return node->getValue();
		}
	}

	template<class T, class A, bool M>
	inline void
	List<T, A, M> :: operator = (const List& list)
	{
		const Node_* node = list.getFirst();
		while (node != NULL) {
			terms_.addLast (node->getValue());
			node = node->getNext();
		}
	}

	template<class T, class A, bool M>
	template<class T1, class A1, bool M1>
	inline bool
	List<T, A, M> :: coinside
	(
		const List<T1, A1, M1>& list,
		const Term_* term0,
		const T1* term1
	) const
	{
		typedef
			List<T, A, M>
			List_0;
		typedef Node_ Node_0;
		typedef Term_ Term_0;
		typedef
			List<T1, A1, M1>
			List_1;
		typedef
			typename List_1 :: Node_
			Node_1;
		typedef
			typename List_1 :: Term_
			Term_1;
		const Node_0* node0 = getFirst();
		const Node_1* node1 = list.getFirst();
		while ((node0 != NULL) && (node1 != NULL)) {
			const Term_0* const
				term_0 = node0->getValue();
			const Term_1* const
				term_1 = node1->getValue();
			if (*term_0 != *term_1) {
				return false;
			}
			if (term_0 == term0) {
				return (term_1 == term1);
			}
			if (term_1 == term1) {
				return (term_0 == term0);
			}
			node0 = node0->getNext();
			node1 = node1->getNext();
		}
		return ((node0 == NULL) && (node1 == NULL));
	}
	template<class T, class A, bool M>
	template<class T1, class A1, bool M1>
	inline bool
	List<T, A, M> :: subset
	(
		const List<T1, A1, M1>& list,
		const Term_* term0,
		const T1* term1
	) const
	{
		typedef
			List<T, A, M>
			List_0;
		typedef Node_ Node_0;
		typedef Term_ Term_0;
		typedef
			List<T1, A1, M1>
			List_1;
		typedef
			typename List_1 :: Node_
			Node_1;
		typedef
			typename List_1 :: Term_
			Term_1;
		const Node_0* node0 = getFirst();
		while (node0 != NULL) {
			const Term_0* const
				term_0 = node0->getValue();
			bool isElement = false;

			const Node_1*
				node1 = list.getFirst();
			while (node1 != NULL) {
				const Term_1* const
					term_1 = node1->getValue();
				if (*term_0 == *term_1) {
					isElement = true;
					break;
				}
				if (term_1 == term1) {
					break;
				}
				node1 = node1->getNext();
			}

			if (!isElement) {
				return false;
			}
			if (term_0 == term0) {
				break;
			}
			node0 = node0->getNext();
		}
		return true;
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	template<class T, class A, bool M>
	void
	List<T, A, M> :: showAll (String& string) const
	{
		const Node_*
			node = terms_.getFirst();
		while (node != NULL) {
			const Term_* term = node->getValue();
			term->showAll (string);
			string << "(" << term << ")" << endLine;
			string << endLine;
			node = node->getNext();
		}
	}
	template<class T, class A, bool M>
	void
	List<T, A, M> :: showTypes (String& string) const
	{
		const Node_*
			node = terms_.getFirst();
		while (node != NULL) {
			const Term_* term = node->getValue();
			string << " : ";
			term->getType()->replicateName (string);
			node = node->getNext();
		}
	}

	// object :: Object implementation
	template<class T, class A, bool M>
	inline void
	List<T, A, M> :: commitSuicide() {
		delete this;
	}
	template<class T, class A, bool M>
	inline Size_t
	List<T, A, M> :: getVolume() const
	{
		Size_t volume = 0;
		volume += terms_.getVolume();
		if (IS_MASTER) {
			const Node_*
				node = terms_.getFirst();
			while (node != NULL) {
				const Term_* const
					term = node->getValue();
				volume += term->getVolume();
				volume += term->getSizeOf();
				node = node->getNext();
			}
		}
		return volume;
	}
	template<class T, class A, bool M>
	inline Size_t
	List<T, A, M> :: getSizeOf() const {
		return sizeof (List);
	}
	template<class T, class A, bool M>
	void
	List<T, A, M> :: show (String& string) const
	{
		Mode globalMode (string);
		Mode localMode;
		localMode.setValue (Mode :: SHOW_TERMS, false);
		string << localMode;
		const Node_*
			node = terms_.getFirst();
		while (node != NULL) {
			const Term_* term = node->getValue();
			string << tab << *term << space;
			term->showType (string);
			string << space << "(" << term << ")" << space;
			string << endLine;
			node = node->getNext();
		}
		string << globalMode;
	}
	template<class T, class A, bool M>
	void
	List<T, A, M> :: dump() const
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
	operator << (String& string, const List<T, A, M>& list)
	{
		list.show (string);
		string << endLine;
		return string;
	}
}
}
}
}


