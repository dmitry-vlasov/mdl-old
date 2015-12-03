/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_header_term_Rule.cpp                       */
/* Description:     mdl rule term class                                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_TARGET_HEADER_TERM_RULE_CPP_
#define MM_AST_TARGET_HEADER_TERM_RULE_CPP_

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
	Rule :: Rule
	(
		const mm :: Expression* const expression,
		const index :: Arity index
	) :
	Term (expression, index) {
	}
	Rule :: ~ Rule() {
	}

	// target :: Term implementation
	inline const Symbol&
	Rule :: getType() const {
		return Term :: getType();
	}
	inline const Symbol&
	Rule :: getFirstSymbol() const {
		return Term :: getFirstSymbol();
	}

	// object :: Targetive implementation
	inline void
	Rule :: complete (mm :: target :: Block* const block) const {
		Term :: complete (block);
	}

	// object :: Writable implementation
	inline void
	Rule :: write (String& string) const {
		Term :: write (string);
	}

	// object :: Object implementation
	void
	Rule :: commitSuicide() {
		delete this;
	}
	Size_t
	Rule :: getVolume() const {
		return Term :: getVolume();
	}
	Size_t
	Rule :: getSizeOf() const {
		return sizeof (Rule);
	}

	/****************************
	 *		Private members
	 ****************************/

using manipulator :: space;
using manipulator :: tab;

	// target :: Term implementation
	void
	Rule :: writeHeader (String& string) const {
		string << tab << tab << mdl :: Token :: term_ << space;
	}
	void
	Rule :: writeType (String& string) const {
		expression_->writeType (string);
	}
	void
	Rule :: writeBody (String& string) const {
		Term :: expression_->writeBody (string);
	}
}
}
}
}
}

#endif /* MM_AST_TARGET_HEADER_TERM_RULE_CPP_ */
