/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_header_statement_Axiomatic.cpp                  */
/* Description:     axiomatic statement class                                */
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
namespace header {
namespace statement {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Axiomatic :: Axiomatic
	(
		const Location& location,
		index :: Arity index,
		mdl :: Identificator* identificator,
		array :: Expression* expression,
		mdl :: Theory* theory
	) :
	header :: statement :: Proposition
	(
		location,
		index,
		identificator,
		expression,
		theory
	) {
	}
	Axiomatic :: ~ Axiomatic() {
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Writable implementation
	void
	Axiomatic :: translate (String& string) const
	{
		string << tab;
		assertion_->translateName (string, Statement :: index_);
		string << space;
		string << :: smm :: Token :: axiomatic_ << space;
		Proposition :: translate (string);
		string << :: smm :: Token :: end_ << endLine;
	}
	void
	Axiomatic :: replicate (String& string) const {
		Proposition :: replicate (string);
	}

	// object :: Object implementation
	void
	Axiomatic :: commitSuicide() {
		delete this;
	}
	Size_t
	Axiomatic :: getVolume() const {
		return Proposition :: getVolume();
	}
	Size_t
	Axiomatic :: getSizeOf() const {
		return sizeof (Axiomatic);
	}
}
}
}
}



