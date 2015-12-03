/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_evaluation_term_ExpAvg.hpp                      */
/* Description:     average expression complexity                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_EVALUATION_TERM_EXP_AVG_CPP_
#define MDL_FORM_EVALUATION_TERM_EXP_AVG_CPP_

namespace mdl {
namespace form {
namespace evaluation {
namespace term {

	/****************************
	 *		Public members
	 ****************************/

	inline
	ExpAvg :: ExpAvg () :
	location_ () {
	}
	inline
	ExpAvg :: ExpAvg
	(
		const Location& location,
		mdl :: Theory* theory
	) :
	location_ (location) {
	}
	ExpAvg :: ~ ExpAvg() {
	}

	// evaluation :: Term implementation
	value :: Real
	ExpAvg :: eval (const HeapNode_*) const {
		return Math :: statistics()->get (Statistics :: EXPRESSION_COMPLEXITY).getAverage();
	}

using manipulator :: endLine;

	// object :: Writable implementation
	void
	ExpAvg :: replicate (String& string) const
	{
		string << Indent (depth_ + 2) << Token :: expAvg_;
		string << Token :: openBracket_ << Token :: closeBracket_;
	}

	// object :: Object implementation
	void
	ExpAvg :: commitSuicide() {
		delete this;
	}
	Size_t
	ExpAvg :: getVolume() const {
		return 0;
	}
	Size_t
	ExpAvg :: getSizeOf() const {
		return sizeof (ExpAvg);
	}
}
}
}
}

#endif /*MDL_FORM_EVALUATION_TERM_EXP_AVG_CPP_*/
