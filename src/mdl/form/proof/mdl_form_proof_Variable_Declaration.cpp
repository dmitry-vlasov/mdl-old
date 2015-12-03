/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_Variable.cpp                              */
/* Description:     variable declaration in proof                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_PROOF_VARIABLE_DECLARATION_CPP_
#define MDL_FORM_PROOF_VARIABLE_DECLARATION_CPP_

namespace mdl {
namespace form {
namespace proof {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Variable :: Declaration :: Declaration
	(
		const Location& location,
		value :: Literal literal,
		mdl :: Identificator* identificator,
		mdl :: Theory* theory
	) :
	header :: Variable
	(
		location,
		literal,
		identificator,
		theory
	) {
	}
	Variable :: Declaration :: ~ Declaration() {
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;
using manipulator :: underline;

	// mdl :: header :: Variable implementation
	void
	Variable :: Declaration :: translateReference (String& string) const {
		string << smm :: Token :: prefix_i_ << index_;
	}

	// object :: Object implementation
	void
	Variable :: Declaration :: commitSuicide() {
		delete this;
	}
}
}
}

#endif /*MDL_FORM_PROOF_VARIABLE_DECLARATION_CPP_*/
