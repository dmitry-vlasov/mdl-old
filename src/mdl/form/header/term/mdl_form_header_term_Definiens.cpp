/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_header_term_Definiens.cpp                       */
/* Description:     definiens term class                                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_HEADER_TERM_DEFINIENS_CPP_
#define MDL_FORM_HEADER_TERM_DEFINIENS_CPP_

namespace mdl {
namespace form {
namespace header {
namespace term {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Definiens :: Definiens
	(
		const Location& location,
		index :: Arity,
		mdl :: Identificator* identificator,
		array :: Expression* expression,
		mdl :: Theory* theory
	) :
	Definition
	(
		location,
		identificator,
		expression,
		theory
	) {
	}
	Definiens :: ~ Definiens() {
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Writable interface
	void
	Definiens :: translate (String&) const {
	}
	void
	Definiens :: replicate (String& string) const
	{
		string << location_.getIndent() << Token :: definiens_ << space;
		string << Token :: colon_ << space;
		identificator_->replicate (string);
		string << space;
		string << Token :: equality_ << space;
		string << space << Token :: sharp_ << space;
		expression_->write (string);
		string << Token :: semicolon_ << endLine;
	}

	// object :: Object implementation
	void
	Definiens :: commitSuicide() {
		delete this;
	}
}
}
}
}

#endif /*MDL_FORM_HEADER_TERM_DEFINIENS_CPP_*/
