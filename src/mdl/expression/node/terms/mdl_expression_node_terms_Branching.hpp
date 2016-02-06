/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_node_terms_Branching.hpp                  */
/* Description:     node container for terms: branching node                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/types/mdl_types.hpp"
#include "mdl/expression/node/terms/mdl_expression_node_terms_List.hpp"
#include "mdl/expression/node/terms/mdl_expression_node_terms_Singleton.hpp"

namespace mdl {
namespace expression {
namespace node {
namespace terms {

template<class T, class A>
class Branching : public Scalar<Branching<T, A>, A> {
public :
	typedef T Term_;
	typedef A Allocator_;
	typedef List<Term_, Allocator_, true> Initial_;
	typedef List<Term_, Allocator_> Terminal_;

	Branching();
	~ Branching();

	template<class P>
	void cloneContents (P*) const;

	bool isEmpty() const;

	Initial_& initial();
	Terminal_& terminal();
	const Initial_& getInitial() const;
	const Terminal_& getTerminal() const;

	void operator = (const Branching&);

	template<class T1, class A1>
	bool coinside
	(
		const Branching<T1, A1>&,
		const Term_*, const T1*
	) const;
	template<class T1, class A1>
	bool coinside
	(
		const Linear<T1, A1>&,
		const Term_*, const T1*
	) const;

	void showAll (String&) const;
	void showTypes (String&, bool initial) const;

	// object :: Object interface
	void commitSuicide();
	Size_t getVolume() const;
	Size_t getSizeOf() const;
	void show (String&) const;
	void dump() const;

private :
	Initial_ initial_;
	Terminal_ terminal_;
};

	template<class T, class A>
	String&
	operator << (String&, const Branching<T, A>&);
}
}
}
}


