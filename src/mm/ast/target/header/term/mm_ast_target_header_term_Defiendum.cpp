/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_header_term_Defiendum.cpp                  */
/* Description:     mdl defiendum term class                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_TARGET_HEADER_TERM_DEFIENDUM_CPP_
#define MM_AST_TARGET_HEADER_TERM_DEFIENDUM_CPP_

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
	Defiendum :: Defiendum
	(
		const mm :: Expression* const expression,
		const index :: Arity index
	) :
	Term (expression, index) {
	}
	Defiendum :: ~ Defiendum() {
	}

	// target :: Term implementation
	inline const Symbol&
	Defiendum :: getType() const {
		return Term :: getType();
	}
	inline const Symbol&
	Defiendum :: getFirstSymbol() const {
		return Term :: getFirstSymbol();
	}

	// object :: Targetive implementation
	inline void
	Defiendum :: complete (mm :: target :: Block*) const {
	}

	// object :: Writable implementation
	inline void
	Defiendum :: write (String& string) const {
		Term :: write (string);
	}

	// object :: Object implementation
	void
	Defiendum :: commitSuicide() {
		delete this;
	}
	Size_t
	Defiendum :: getVolume() const {
		return Term :: getVolume();
	}
	Size_t
	Defiendum :: getSizeOf() const {
		return sizeof (Defiendum);
	}

	/****************************
	 *		Private members
	 ****************************/

using manipulator :: space;
using manipulator :: tab;

	// target :: Term implementation
	void
	Defiendum :: writeHeader (String& string) const {
		string << tab << tab << mdl :: Token :: defiendum_ << space;
	}
	void
	Defiendum :: writeType (String& string) const
	{
		int bracketDepth = 0;
		int braceDepth = 0;
		for (index :: Literal i = firstInsideIndex(); i <= lastInsideIndex(); ++ i) {
			const Symbol& symbol = Term :: expression_->getSymbol (i);
			countDepth (symbol, bracketDepth, braceDepth);
			if ((bracketDepth == 0) && (braceDepth == 0)) {
				if (findTermType (symbol, string)) {
					break;
				}
			}
		}
	}
	void
	Defiendum :: writeBody (String& string) const
	{
		int bracketDepth = 0;
		int braceDepth = 0;
		for (index :: Literal i = firstInsideIndex(); i <= lastInsideIndex(); ++ i) {
			const Symbol& symbol = Term :: expression_->getSymbol (i);
			countDepth (symbol, bracketDepth, braceDepth);
			if (symbol == Math :: constants()->equality() ||
				symbol == Math :: constants()->equivalence()) {
				if ((bracketDepth == 0) && (braceDepth == 0)) {
					break;
				}
			}
			string << symbol;
		}
	}
}
}
}
}
}

#endif /* MM_AST_TARGET_HEADER_TERM_DEFIENDUM_CPP_ */
