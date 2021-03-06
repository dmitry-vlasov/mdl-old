/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_notation_Abbreviation.cpp                 */
/* Description:     abbreviation in notation                                 */
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
namespace proof {
namespace notation {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Abbreviation :: Abbreviation
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
	Abbreviation :: ~ Abbreviation() {
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Writable interface
	void
	Abbreviation :: replicate (String& string) const
	{
		string << location_.getIndent() << Token :: abbreviation_ << space;
		string << Token :: colon_ << space;
		identificator_->replicate (string);
		string << Token :: sharp_ << space;
		expression_->write (string);
		string << Token :: semicolon_ << endLine;
	}

	// object :: Object implementation
	void
	Abbreviation :: commitSuicide() {
		delete this;
	}
}
}
}
}


