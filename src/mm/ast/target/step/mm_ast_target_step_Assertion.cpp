/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_step_Assertion.cpp                         */
/* Description:     mdl assertion proof step                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/lexer/mdl_lexer_Token.hpp"
#include "ast/mm_ast.hpp"

namespace mm {
namespace ast {
namespace target {
namespace step {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Assertion :: Assertion
	(
		const object :: Referable* const assertion,
		const vector :: target :: Step* const arguments,
		const Expression* const expression
	) :
	index_ (index :: undefined :: STEP),
	assertion_ (assertion),
	arguments_ (*arguments),
	expression_ (*expression) {
	}
	Assertion :: ~ Assertion() {
	}

using manipulator :: space;

	// target :: Step implementation
	void
	Assertion :: incIndex (index :: Step& index) const {
		index_ = ++ index;
	}

	// object :: Referable implementation
	void
	Assertion :: writeReference (String& string) const
	{
		string << mdl :: Token :: step_ << space;
		string << index_;
	}
	void
	Assertion :: writeIdentificator (String&) const {
	}

	// object :: Targetive implementation
	void
	Assertion :: complete (mm :: target :: Block* const) const {
	}

using manipulator :: tab;
using manipulator :: endLine;

	// object :: Writable implementation
	void
	Assertion :: write (String& string) const
	{
		writeHeader (string);
		writeArguments (string);
		writeExpression (string);
	}

	// object :: Object implementation
	void
	Assertion :: commitSuicide() {
		delete this;
	}
	Size_t
	Assertion :: getVolume() const
	{
		Size_t volume = 0;
		volume += arguments_.getVolume();
		volume += expression_.getVolume();
		return volume;
	}
	Size_t
	Assertion :: getSizeOf() const {
		return sizeof (Assertion);
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Assertion :: writeHeader (String& string) const
	{
		string << tab << tab << mdl :: Token :: step_ << space;
		if (Config :: removeProofs()) {
			string << '1' << space;
		} else {
			string << index_ << space;
		}
		string << mdl :: Token :: colon_ << space;
		expression_.writeType (string);
		string << mdl :: Token :: equality_ << space;
		if (Config :: removeProofs() || Config :: implicitSteps()) {
			string << mdl :: Token :: question_ << space;
		} else {
			assertion_->writeReference (string);
		}
	}
	void
	Assertion :: writeArguments (String& string) const
	{
		if (Config :: removeProofs() || Config :: implicitSteps()) {
			return;
		}
		string << mdl :: Token :: openBracket_;
		const index :: Arity arity = arguments_.getSize();
		for (index :: Arity i = 0; i < arity; ++ i) {
			arguments_.getValue (i)->writeReference (string);
			if (i < arity - 1) {
				string << mdl :: Token :: comma_ << space;
			}
		}
		string << mdl :: Token :: closeBracket_ << space;
	}
	void
	Assertion :: writeExpression (String& string) const
	{
		string << mdl :: Token :: turnstile_ << space;
		expression_.writeBody (string);
		string << mdl :: Token :: semicolon_ << endLine;
	}
}
}
}
}


