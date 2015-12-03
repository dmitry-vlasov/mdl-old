/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_header_term_Defiendum.cpp                       */
/* Description:     defiendum term class                                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_HEADER_TERM_DEFIENDUM_CPP_
#define MDL_FORM_HEADER_TERM_DEFIENDUM_CPP_

namespace mdl {
namespace form {
namespace header {
namespace term {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Defiendum :: Defiendum
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
	Defiendum :: ~ Defiendum() {
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Buildable implementation
	void
	Defiendum :: build()
	{
		Definition :: build();
		mdl :: Term*
			term = Math :: defiendums()->unifiesWith (this);
		if (term != NULL) {
			Error* error = new Error (location_, Error :: SEMANTIC);
			error->message() << "defiendum term " << *expression_ << space;
			error->message() << "unifies with the previously written defiendum term ";
			error->message() << *term << endLine;
			throw error;
		}
		Math :: defiendums()->add (this);
	}

	// object :: Writable interface
	void
	Defiendum :: translate (String&) const {
	}
	void
	Defiendum :: replicate (String& string) const
	{
		string << location_.getIndent() << Token :: defiendum_ << space;
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
	Defiendum :: commitSuicide() {
		delete this;
	}
}
}
}
}

#endif /*MDL_FORM_HEADER_TERM_DEFIENDUM_HPP_*/
