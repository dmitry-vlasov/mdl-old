/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_evaluation_term_ExpCplx.cpp                     */
/* Description:     expression complexity evaluation function                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_EVALUATION_TERM_EXP_CPLX_CPP_
#define MDL_FORM_EVALUATION_TERM_EXP_CPLX_CPP_

namespace mdl {
namespace form {
namespace evaluation {
namespace term {

	/****************************
	 *		Public members
	 ****************************/

	inline
	ExpCplx :: ExpCplx () :
	location_ () {
	}
	inline
	ExpCplx :: ExpCplx
	(
		const Location& location,
		mdl :: Theory* theory
	) :
	location_ (location) {
	}
	ExpCplx :: ~ ExpCplx() {
	}

	// evaluation :: Term implementation
	value :: Real
	ExpCplx :: eval (const HeapNode_* node) const
	{
		const value :: Real expComplexity = node->getExpComplexity();
		const value :: Real normalizedExpComplexity =
			Math :: statistics()->get (Statistics :: EXPRESSION_COMPLEXITY).normalize (expComplexity);
		return normalizedExpComplexity;
	}

using manipulator :: endLine;

	// object :: Writable implementation
	void
	ExpCplx :: replicate (String& string) const
	{
		string << Indent (depth_ + 2) << Token :: expCplx_;
		string << Token :: openBracket_ << Token :: closeBracket_;
	}

	// object :: Object implementation
	void
	ExpCplx :: commitSuicide() {
		delete this;
	}
	Size_t
	ExpCplx :: getVolume() const {
		return 0;
	}
	Size_t
	ExpCplx :: getSizeOf() const {
		return sizeof (ExpCplx);
	}
}
}
}
}

#endif /*MDL_FORM_EVALUATION_TERM_EXP_CPLX_CPP_*/
