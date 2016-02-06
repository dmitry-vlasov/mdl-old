/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_node_terms_Singleton.hpp                  */
/* Description:     node container for terms: single term                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/types/mdl_types.hpp"

namespace mdl {
namespace expression {
namespace node {
namespace terms {

template<class T, class A, bool M = false>
class Singleton : public Scalar<Singleton<T, A, M>, A> {
public :
	typedef T Term_;
	typedef A Allocator_;
	enum {
		IS_MASTER = M
	};

	class Node_ : public Scalar<Node_, Allocator_> {
	public :
		Node_();
		~ Node_();

		const Term_* getValue() const;
		const Term_*& getReference();
		const Term_* const& getReference() const;
		const Node_* getNext() const;
		void operator = (const Node_&);

		// object :: Object interface
		void commitSuicide();
		Size_t getVolume() const;
		Size_t getSizeOf() const;
		void show (String&) const;

	private :
		const Term_* term_;
	};

	Singleton();
	~ Singleton();

	template<class P>
	void cloneContents (P*) const;

	bool isEmpty() const;
	const Node_* getFirst() const;
	const Node_* getLast() const;

	void addFirst (const Term_* const);
	void addLast (const Term_* const);
	const Term_* getTerm() const;

	void operator = (const Singleton&);

	template<class T1, class A1, bool M1>
	bool subset
	(
		const List<T1, A1, M1>&,
		const Term_*, const T1*
	) const;
	template<class T1, class A1, bool M1>
	bool coinside
	(
		const Singleton<T1, A1, M1>&,
		const Term_*, const T1*
	) const;

	void showAll (String&) const;
	void showTypes (String&) const;

	// object :: Object interface
	void commitSuicide();
	Size_t getVolume() const;
	Size_t getSizeOf() const;
	void show (String&) const;
	void dump() const;

private :
	Node_ node_;
};

	template<class T, class A, bool M>
	String&
	operator << (String&, const List<T, A, M>&);
}
}
}
}


