/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_header_statement_Hypothesis.cpp                 */
/* Description:     hypothesis statement class                               */
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
	Hypothesis :: Hypothesis
	(
		const Location& location,
		index :: Arity index,
		mdl :: Identificator* identificator,
		array :: Expression* expression,
		mdl :: Theory* theory
	) :
	form :: header :: statement :: Statement
	(
		location,
		index,
		identificator,
		expression,
		theory
	) {
	}
	Hypothesis :: ~ Hypothesis() {
	}

	// object :: Buildable implementation
	void
	Hypothesis :: build()
	{
		Statement :: build();
		Statement :: proofNode_ =
			new form :: proof :: node :: Hypothesis
			(
				Statement :: assertion_,
				Statement :: index_,
				Statement :: expression_
			);
	}

using manipulator :: space;
using manipulator :: tab;
using manipulator :: endLine;
using manipulator :: underline;

	// object :: Writable implementation
	void
	Hypothesis :: translate (String& string) const
	{
		string << tab;
		string << :: smm :: Token :: prefix_e_ << index_;
		string << space;
		string << :: smm :: Token :: essential_ << space;
		expression_->write (string);
		string << :: smm :: Token :: end_ << endLine;
	}
	void
	Hypothesis :: replicate (String& string) const
	{
		const Indent indent = location_.getIndent();
		string << indent << Token :: hyp_ << space;
		if (assertion_->getHypArity() > 1) {
			string << (index_ + 1) << space;
		}
		string << Token :: colon_ << space;
		identificator_->replicate (string);
		string << space << Token :: equality_ << space;
		string << Token :: turnstile_ << space;
		expression_->write (string, indent);
		string << Token :: semicolon_ << endLine;
	}

	// object :: Object implementation
	void
	Hypothesis :: commitSuicide() {
		delete this;
	}
	Size_t
	Hypothesis :: getVolume() const {
		return Statement :: getVolume();
	}
	Size_t
	Hypothesis :: getSizeOf() const {
		return sizeof (Hypothesis);
	}
}
}
}
}


