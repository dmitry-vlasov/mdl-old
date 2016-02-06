/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_header_Hypothesis.cpp                      */
/* Description:     mdl hypothesis                                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/lexer/mdl_lexer_Token.hpp"
#include "auxiliary/mm_auxiliary.hpp"
#include "ast/mm_ast.hpp"

namespace mm {
namespace ast {
namespace target {
namespace header {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Hypothesis :: Hypothesis
	(
		const mm :: Expression* const expression,
		const index :: Arity index
	) :
	Line (expression, index) {
	}
	Hypothesis :: ~ Hypothesis() {
	}

	// object :: Referable implementation
	void
	Hypothesis :: writeReference (String& string) const {
		string << mdl :: Token :: hyp_ << space << index_ << space;
	}

	// object :: Targetive implementation
	void
	Hypothesis :: complete (mm :: target :: Block* const) const {
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	// object :: Writable implementation
	void
	Hypothesis :: write (String& string) const
	{
		string << tab << tab << mdl :: Token :: hyp_ << space;
		if (index_ != index :: undefined :: ARITY) {
			string << index_ << space;
		}
		string << mdl :: Token :: colon_ << space;
		expression_->writeType (string);
		string << mdl :: Token :: equality_ << space;
		string << mdl :: Token :: turnstile_ << space;
		expression_->writeBody (string);
		string << mdl :: Token :: semicolon_ << endLine;
	}

	// object :: Object implementation
	void
	Hypothesis :: commitSuicide() {
		delete this;
	}
	Size_t
	Hypothesis :: getVolume() const {
		return Line :: getVolume();
	}
	Size_t
	Hypothesis :: getSizeOf() const {
		return sizeof (Hypothesis);
	}
}
}
}
}


