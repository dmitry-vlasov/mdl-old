/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_step_Qed.cpp                               */
/* Description:     mdl q.e.d. proof node                                    */
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
	Qed :: Qed (const index :: Step index) :
	index_ (index) {
	}
	Qed :: ~ Qed() {
	}

	// target :: Step implementation
	void
	Qed :: incIndex (index :: Step&) const {
	}

	// object :: Referable implementation
	void
	Qed :: writeReference (String&) const {
	}
	void
	Qed :: writeIdentificator (String&) const {
	}

	// object :: Targetive implementation
	void
	Qed :: complete (mm :: target :: Block* const) const {
	}

using manipulator :: space;
using manipulator :: tab;
using manipulator :: endLine;

	// object :: Writable implementation
	void
	Qed :: write (String& string) const
	{
		string << tab << tab << mdl :: Token :: qed_ << space;
		string << mdl :: Token :: prop_ /*<< space << '1'*/ << space;
		string << mdl :: Token :: equality_ << space;
		string << mdl :: Token :: step_ << space;
		if (Config :: removeProofs()) {
			string << '1' << space;
		} else {
			string << index_ << space;
		}
		string << mdl :: Token :: semicolon_ << endLine;
	}

	// object :: Object implementation
	void
	Qed :: commitSuicide() {
		delete this;
	}
	Size_t
	Qed :: getVolume() const {
		return 0;
	}
	Size_t
	Qed :: getSizeOf() const {
		return sizeof (Qed);
	}
}
}
}
}


