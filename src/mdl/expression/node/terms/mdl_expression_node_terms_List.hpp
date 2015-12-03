/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_node_terms_List.hpp                       */
/* Description:     node container for terms: list                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_NODE_TERMS_LIST_HPP_
#define MDL_EXPRESSION_NODE_TERMS_LIST_HPP_

#include "mdl/types/mdl_types.hpp"

namespace mdl {
namespace expression {
namespace node {
namespace terms {

template<class T, class A, bool M = false>
class List : public Scalar<List<T, A, M>, A> {
public :
	typedef T Term_;
	typedef A Allocator_;
	enum {
		IS_MASTER = M
	};
	typedef
		typename list :: List
		<const Term_*, storage :: ByValue, Allocator_>
		List_;
	typedef
		typename List_ :: Node_
		Node_;

	List();
	~ List();

	template<class P>
	void cloneContents (P*) const;

	bool isEmpty() const;
	const Node_* getFirst() const;
	const Node_* getLast() const;

	void addFirst (const Term_* const);
	void addLast (const Term_* const);
	const Term_* getTerm() const;

	void operator = (const List&);

	template<class T1, class A1, bool M1>
	bool coinside
	(
		const List<T1, A1, M1>&,
		const Term_*, const T1*
	) const;
	template<class T1, class A1, bool M1>
	bool subset
	(
		const List<T1, A1, M1>&,
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
	List_ terms_;
};

	template<class T, class A, bool m>
	String&
	operator << (String&, const List<T, A, m>&);
}
}
}
}

#endif /*MDL_EXPRESSION_NODE_TERMS_LIST_HPP_*/
