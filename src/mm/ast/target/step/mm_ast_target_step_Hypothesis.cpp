/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_step_Hypothesis.cpp                        */
/* Description:     mdl hypothesis proof node                                */
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
namespace step {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Hypothesis :: Hypothesis (const index :: Step index) :
	index_ (index) {
	}
	Hypothesis :: ~ Hypothesis() {
	}

	// mm :: Step implementation
	void
	Hypothesis :: incIndex (index :: Step&) const {
	}

using manipulator :: space;

	// object :: Referable implementation
	void
	Hypothesis :: writeReference (String& string) const {
		string << mdl :: Token :: hyp_ << space << index_;
	}
	void
	Hypothesis :: writeIdentificator (String&) const {
	}

	// object :: Targetive implementation
	void
	Hypothesis :: complete (mm :: target :: Block* const) const {
	}

	// object :: Writable implementation
	void
	Hypothesis :: write (String& string) const {
	}

	// object :: Object implementation
	void
	Hypothesis :: commitSuicide() {
		delete this;
	}
	Size_t
	Hypothesis :: getVolume() const {
		return 0;
	}
	Size_t
	Hypothesis :: getSizeOf() const {
		return sizeof (Hypothesis);
	}
}
}
}
}


