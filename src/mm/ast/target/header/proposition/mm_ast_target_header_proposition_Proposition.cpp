/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_header_proposition_Proposition.cpp         */
/* Description:     mdl general proposition class                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_TARGET_HEADER_PROPOSITION_PROPOSITION_CPP_
#define MM_AST_TARGET_HEADER_PROPOSITION_PROPOSITION_CPP_

#include "mdl/lexer/mdl_lexer_Token.hpp"
#include "auxiliary/mm_auxiliary.hpp"
#include "ast/mm_ast.hpp"

namespace mm {
namespace ast {
namespace target {
namespace header {
namespace proposition {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Proposition :: Proposition
	(
		const mm :: Expression* const expression,
		const index :: Arity index
	) :
	Line (expression, index) {
	}
	Proposition :: ~ Proposition() {
	}

	// object :: Referable implementation
	void
	Proposition :: writeReference (String& string) const {
		string << mdl :: Token :: prop_ << space << index_ << space;
	}

	// object :: Targetive implementation
	void
	Proposition :: complete (mm :: target :: Block* const) const {
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	// object :: Writable implementation
	void
	Proposition :: write (String& string) const
	{
		string << tab << tab << mdl :: Token :: prop_ << space;
		if (index_ != index :: undefined :: ARITY) {
			string << index_ << space;
		}
		string << mdl :: Token :: colon_ << space;
		expression_->writeType (string);
		string << mdl :: Token :: equality_ << space;
		string << mdl :: Token :: turnstile_ << space;
		writeBody (string);
		string << mdl :: Token :: semicolon_ << endLine;
	}

	// object :: Object implementation
	Size_t
	Proposition :: getVolume() const {
		return Line :: getVolume();
	}
	Size_t
	Proposition :: getSizeOf() const {
		return sizeof (Proposition);
	}
}
}
}
}
}

#endif /* MM_AST_TARGET_HEADER_PROPOSITION_PROPOSITION_CPP_ */
