/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_evaluation_term_ExpEq.cpp                       */
/* Description:     expression strong similarity to the used expressions     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace form {
namespace evaluation {
namespace term {

	/****************************
	 *		Public members
	 ****************************/

	inline
	ExpEq :: ExpEq () :
	location_ () {
	}
	inline
	ExpEq :: ExpEq
	(
		const Location& location,
		mdl :: Theory* theory
	) :
	location_ (location) {
	}
	ExpEq :: ~ ExpEq() {
	}

	// evaluation :: Term implementation
	value :: Real
	ExpEq :: eval (const HeapNode_* node) const
	{
		const math :: Expressions :: Tree_* tree = Math :: expressions()->getTree();
		const HeapNode_ :: Expression_* expression = node->getExpression();

		typedef
			math :: Expressions :: Tree_ :: Equify_
			<
				HeapNode_ :: Expression_,
				unify :: policy :: SYMMETRIC
			> :: Result_
			Result;

		Memory :: stack().push();
		Result result = tree->equifySymmetric (expression);
		Memory :: stack().pop();
		return result.isEmpty() ? 0 : 1;
	}

using manipulator :: endLine;

	// object :: Writable implementation
	void
	ExpEq :: replicate (String& string) const
	{
		string << Indent (depth_ + 2) << Token :: expEq_;
		string << Token :: openBracket_ << Token :: closeBracket_;
	}

	// object :: Object implementation
	void
	ExpEq :: commitSuicide() {
		delete this;
	}
	Size_t
	ExpEq :: getVolume() const {
		return 0;
	}
	Size_t
	ExpEq :: getSizeOf() const {
		return sizeof (ExpEq);
	}
}
}
}
}


