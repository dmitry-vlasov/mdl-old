/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_header_term_Term.cpp                       */
/* Description:     abstract mdl term class                                  */
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
namespace term {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Term :: Term
	(
		const mm :: Expression* const expression,
		const index :: Arity index
	) :
	Line (expression, index) {
	}
	Term :: ~ Term() {
	}

	// target :: Term implementation
	const Symbol&
	Term :: getType() const {
		return expression_->getType();
	}
	const Symbol&
	Term :: getFirstSymbol() const {
		return expression_->getSymbol (1);
	}

	// object :: Targetive implementation
	void
	Term :: complete (mm :: target :: Block* const block) const
	{
		const Symbol&
			typeSymbol = expression_->getType();
		const mm :: target :: Type* const
			type = block->getType (typeSymbol);
		if (type == NULL) {
			new ast :: target :: Type (typeSymbol, block);
		}
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	// object :: Writable implementation
	void
	Term :: write (String& string) const
	{
		writeHeader (string);
		string << mdl :: Token :: colon_ << space;
		writeType (string);
		string << mdl :: Token :: equality_ << space;
		string << mdl :: Token :: sharp_ << space;
		writeBody (string);
		string << mdl :: Token :: semicolon_ << endLine;
	}

	// object :: Object implementation
	Size_t
	Term :: getVolume() const {
		return Line :: getVolume();
	}
	Size_t
	Term :: getSizeOf() const {
		return sizeof (Term);
	}
}
}
}
}
}


