/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_evaluation_term_ExpSim.cpp                      */
/* Description:     expression similarity to the used expressions            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_EVALUATION_TERM_EXP_SIM_CPP_
#define MDL_FORM_EVALUATION_TERM_EXP_SIM_CPP_

namespace mdl {
namespace form {
namespace evaluation {
namespace term {

	/****************************
	 *		Public members
	 ****************************/

	inline
	ExpSim :: ExpSim () :
	location_ () {
	}
	inline
	ExpSim :: ExpSim
	(
		const Location& location,
		mdl :: Theory* theory
	) :
	location_ (location) {
	}
	ExpSim :: ~ ExpSim() {
	}

	// evaluation :: Term implementation
	value :: Real
	ExpSim :: eval (const HeapNode_* node) const
	{
		const math :: Expressions :: Tree_* tree = Math :: expressions()->getTree();
		const HeapNode_ :: Expression_* expression = node->getExpression();

		Memory :: stack().push();
		value :: Integer minDifference = value :: undefined :: INTEGER;
		tree->factorUnifySymmetric (expression, minDifference);
		Memory :: stack().pop();
		return (minDifference == 0) ? 1 : (1 / minDifference);
	}

using manipulator :: endLine;

	// object :: Writable implementation
	void
	ExpSim :: replicate (String& string) const
	{
		string << Indent (depth_ + 2) << Token :: expSim_;
		string << Token :: openBracket_ << Token :: closeBracket_;
	}

	// object :: Object implementation
	void
	ExpSim :: commitSuicide() {
		delete this;
	}
	Size_t
	ExpSim :: getVolume() const {
		return 0;
	}
	Size_t
	ExpSim :: getSizeOf() const {
		return sizeof (ExpSim);
	}
}
}
}
}

#endif /*MDL_FORM_EVALUATION_TERM_EXP_SIM_CPP_*/
