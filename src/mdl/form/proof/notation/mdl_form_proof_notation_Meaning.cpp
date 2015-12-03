/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_notation_Meaning.cpp                      */
/* Description:     meaning in notation                                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_PROOF_NOTATION_MEANING_CPP_
#define MDL_FORM_PROOF_NOTATION_MEANING_CPP_

namespace mdl {
namespace form {
namespace proof {
namespace notation {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Meaning :: Meaning
	(
		const Location& location,
		index :: Arity,
		mdl :: Identificator* identificator,
		array :: Expression* expression,
		mdl :: Theory* theory
	) :
	Term
	(
		location,
		identificator,
		expression,
		theory
	) {
	}
	Meaning :: ~ Meaning() {
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Writable interface
	void
	Meaning :: replicate (String& string) const
	{
		string << location_.getIndent() << Token :: meaning_ << space;
		string << Token :: colon_ << space;
		identificator_->replicate (string);
		string << Token :: sharp_ << space;
		expression_->write (string);
		string << Token :: semicolon_ << endLine;
	}

	// object :: Object implementation
	void
	Meaning :: commitSuicide() {
		delete this;
	}
}
}
}
}

#endif /*MDL_FORM_PROOF_NOTATION_MEANING_CPP_*/
