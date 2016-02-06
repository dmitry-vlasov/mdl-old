/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_header_Disjoined.cpp                       */
/* Description:     mdl disjoined variables restriction                      */
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
	Disjoined :: Disjoined (const vector :: Literal* const variables) :
	variables_ (variables) {
	}
	Disjoined :: ~ Disjoined() {
	}

	// target :: Disjointed implementation
	bool
	Disjoined :: isEmpty() const {
		return (variables_->getSize() < 2);
	}

	// object :: Targetive implementation
	void
	Disjoined :: complete (mm :: target :: Block* const) const {
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	// object :: Writable implementation
	void
	Disjoined :: write (String& string) const
	{
		const index :: Arity arity = variables_->getSize();
		for (index :: Arity i = 0; i < arity; i++) {
			const value :: Literal variable = variables_->getValue (i);
			string << Table :: literals()->get (variable);
			if (i < arity - 1) {
				string << space;
			}
		}
	}

	// object :: Object implementation
	void
	Disjoined :: commitSuicide() {
		delete this;
	}
	Size_t
	Disjoined :: getVolume() const {
		return 0;
	}
	Size_t
	Disjoined :: getSizeOf() const {
		return sizeof (Disjoined);
	}
}
}
}
}


