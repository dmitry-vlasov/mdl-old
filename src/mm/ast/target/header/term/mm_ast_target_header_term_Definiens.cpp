/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_header_term_Definiens.cpp                  */
/* Description:     mdl definiens term class                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_TARGET_HEADER_TERM_DEFINIENS_CPP_
#define MM_AST_TARGET_HEADER_TERM_DEFINIENS_CPP_

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
	Definiens :: Definiens
	(
		const mm :: Expression* const expression,
		const index :: Arity index
	) :
	Term (expression, index) {
	}
	Definiens :: ~ Definiens() {
	}

	// target :: Term implementation
	inline const Symbol&
	Definiens :: getType() const {
		return Term :: getType();
	}
	inline const Symbol&
	Definiens :: getFirstSymbol() const {
		return Term :: getFirstSymbol();
	}

	// object :: Targetive implementation
	inline void
	Definiens :: complete (mm :: target :: Block*) const {
	}

	// object :: Writable implementation
	inline void
	Definiens :: write (String& string) const {
		Term :: write (string);
	}

	// object :: Object implementation
	void
	Definiens :: commitSuicide() {
		delete this;
	}
	Size_t
	Definiens :: getVolume() const {
		return Term :: getVolume();
	}
	Size_t
	Definiens :: getSizeOf() const {
		return sizeof (Definiens);
	}

	/****************************
	 *		Private members
	 ****************************/

using manipulator :: space;
using manipulator :: tab;

	// target :: Term implementation
	void
	Definiens :: writeHeader (String& string) const {
		string << tab << tab << mdl :: Token :: definiens_ << space;
	}
	void
	Definiens :: writeType (String& string) const
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
	Definiens :: writeBody (String& string) const
	{
		bool start = false;
		int bracketDepth = 0;
		int braceDepth = 0;
		for (index :: Literal i = firstInsideIndex(); i <= lastInsideIndex(); ++ i) {
			const Symbol& symbol = Term :: expression_->getSymbol (i);
			countDepth (symbol, bracketDepth, braceDepth);
			if (start) {
				string << symbol;
			}
			if (symbol == Math :: constants()->equality() ||
				symbol == Math :: constants()->equivalence()) {
				if ((bracketDepth == 0) && (braceDepth == 0)) {
					start = true;
				}
			}
		}
	}
}
}
}
}
}

#endif /* MM_AST_TARGET_HEADER_TERM_DEFINIENS_CPP_ */
