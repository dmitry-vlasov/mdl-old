/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_build_Builder.hpp                         */
/* Description:     expression building routines                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_BUILD_BUILDER_HPP_
#define MDL_EXPRESSION_BUILD_BUILDER_HPP_

#include "mdl/types/mdl_types.hpp"
#include "mdl/expression/mdl_expression.dpp"
#include "mdl/expression/mdl_expression_Symbol.hpp"

#include "mdl/expression/build/mdl_expression_build_Node_ADD_DATA.hpp"
#include "mdl/expression/build/mdl_expression_build_Node_NO_DATA.hpp"
#include "mdl/expression/build/mdl_expression_build_Switch_BACK.hpp"
#include "mdl/expression/build/mdl_expression_build_Switch_FORTH.hpp"

namespace mdl {
namespace expression {
namespace build {

template
<
	class E,
	class T,
	class V = typename mdl :: type :: Empty
>
class Builder {
public :
	typedef E Expression_; // target
	typedef T Term_2_;     // source
	typedef V Value_;      // value
	typedef
		typename Expression_ :: Allocator_
		Allocator_;
	typedef
		typename Expression_ :: Term_
		Term_1_;
	typedef
		typename Term_1_ :: Iterator_
		Iterator_1_;
	typedef
		typename Term_2_ :: const_Iterator_
		Iterator_2_;
	typedef
		typename Term_1_ :: Node_
		Node_1_;
	typedef
		typename Term_2_ :: Node_
		Node_2_;

	enum {
		NODE_POLICY =
			(mdl :: type :: Type<Value_> :: is_empty) ?
			NO_DATA : ADD_DATA
	};
	enum {
		DIRECTION_POLICY =
			(Node_2_ :: IS_ITERABLE_FORTH) ?
			FORTH : BACK,
		DIRECTION_FORTH =
			(Node_2_ :: IS_ITERABLE_FORTH) ?
			true : false,
	};
	typedef
		typename Node_1_ :: Terms_
		Terms_1_;
	typedef
		typename mdl :: type :: template Selector
		<
			DIRECTION_FORTH,
			typename Node_2_ :: Terms_ :: Initial_,
			typename Node_2_ :: Terms_ :: Terminal_
		> :: Result_
		Terms_2_;
	typedef
		Switch<Builder, DIRECTION_POLICY>
		Switch_;
	typedef
		Node<Builder, NODE_POLICY>
		Node_;

	Builder
	(
		const Term_2_* source,
		Value_ value = Undefined<Value_> :: getValue()
	);

	Term_1_*
	build (Expression_* target = NULL);

private :
	Term_1_*
	addNode
	(
		Expression_* const target,
		const Iterator_1_ targetBegin,   Iterator_1_& targetEnd,
		const Iterator_2_ sourceBegin,   Iterator_2_& sourceEnd,
		const Terms_2_& sourceTerms,
		const bool initial,
		const int depth = 0
	);
	void
	buildTerms
	(
		Iterator_1_  targetBegin,
		Iterator_1_& targetEnd,
		Iterator_2_& sourceEnd,
		Term_1_*& targetTerm,
		const Term_2_*& sourceTerm,
		const Terms_2_& sourceTerms,
		const int depth
	);

	const Term_2_* source_;
	const Iterator_2_ absoluteBegin_;
	const Iterator_2_ absoluteEnd_;
	Value_ value_;
};

}
}
}

#endif /*MDL_EXPRESSION_BUILD_BUILDER_HPP_*/
