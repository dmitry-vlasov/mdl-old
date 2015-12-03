/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_header_proposition_Statement.cpp           */
/* Description:     mdl statement proposition                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_TARGET_HEADER_PROPOSITION_STATEMENT_CPP_
#define MM_AST_TARGET_HEADER_PROPOSITION_STATEMENT_CPP_

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
	Statement :: Statement
	(
		const mm :: Expression* const expression,
		const index :: Arity index
	) :
	Proposition (expression, index) {
	}
	Statement :: ~ Statement() {
	}

	// object :: Referable implementation
	inline void
	Statement :: writeReference (String& string) const {
		Proposition :: writeReference (string);
	}

	// object :: Targetive implementation
	inline void
	Statement :: complete (mm :: target :: Block* const block) const {
		Proposition :: complete (block);
	}

	// object :: Writable implementation
	inline void
	Statement :: write (String& string) const {
		Proposition :: write (string);
	}

	// object :: Object implementation
	void
	Statement :: commitSuicide() {
		delete this;
	}
	Size_t
	Statement :: getVolume() const {
		return Proposition :: getVolume();
	}
	Size_t
	Statement :: getSizeOf() const {
		return sizeof (Statement);
	}

	/****************************
	 *		Private members
	 ****************************/

using manipulator :: space;
using manipulator :: tab;

	// target :: Proposition implementation
	void
	Statement :: writeBody (String& string) const {
		Proposition :: expression_->writeBody (string);
	}
}
}
}
}
}

#endif /* MM_AST_TARGET_HEADER_PROPOSITION_STATEMENT_CPP_ */
