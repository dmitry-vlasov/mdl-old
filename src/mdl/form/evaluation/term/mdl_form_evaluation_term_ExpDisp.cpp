/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_evaluation_term_ExpDisp.cpp                     */
/* Description:     expression complexity dispersion                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_EVALUATION_TERM_EXP_DISP_CPP_
#define MDL_FORM_EVALUATION_TERM_EXP_DISP_CPP_

namespace mdl {
namespace form {
namespace evaluation {
namespace term {

	/****************************
	 *		Public members
	 ****************************/

	inline
	ExpDisp :: ExpDisp () :
	location_ () {
	}
	inline
	ExpDisp :: ExpDisp
	(
		const Location& location,
		mdl :: Theory* theory
	) :
	location_ (location) {
	}
	ExpDisp :: ~ ExpDisp() {
	}

	// evaluation :: Term implementation
	value :: Real
	ExpDisp :: eval (const HeapNode_*) const {
		return Math :: statistics()->get (Statistics :: EXPRESSION_COMPLEXITY).getDispersion();
	}

using manipulator :: endLine;

	// object :: Writable implementation
	void
	ExpDisp :: replicate (String& string) const
	{
		string << Indent (depth_ + 2) << Token :: expDisp_;
		string << Token :: openBracket_ << Token :: closeBracket_;
	}

	// object :: Object implementation
	void
	ExpDisp :: commitSuicide() {
		delete this;
	}
	Size_t
	ExpDisp :: getVolume() const {
		return 0;
	}
	Size_t
	ExpDisp :: getSizeOf() const {
		return sizeof (ExpDisp);
	}
}
}
}
}

#endif /*MDL_FORM_EVALUATION_TERM_EXP_DISP_CPP_*/
