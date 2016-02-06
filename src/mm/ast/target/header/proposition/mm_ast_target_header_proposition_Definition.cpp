/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_header_proposition_Definition.cpp          */
/* Description:     mdl definition proposition                               */
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
namespace proposition {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Definition :: Definition
	(
		const mm :: Expression* const expression,
		const index :: Arity index
	) :
	Proposition (expression, index) {
	}
	Definition :: ~ Definition() {
	}

	// object :: Referable implementation
	inline void
	Definition :: writeReference (String& string) const {
		Proposition :: writeReference (string);
	}

	// object :: Targetive implementation
	inline void
	Definition :: complete (mm :: target :: Block* const block) const {
		Proposition :: complete (block);
	}

	// object :: Writable implementation
	inline void
	Definition :: write (String& string) const {
		Proposition :: write (string);
	}

	// object :: Object implementation
	void
	Definition :: commitSuicide() {
		delete this;
	}
	Size_t
	Definition :: getVolume() const {
		return Proposition :: getVolume();
	}
	Size_t
	Definition :: getSizeOf() const {
		return sizeof (Proposition);
	}

	/****************************
	 *		Private members
	 ****************************/

using manipulator :: space;
using manipulator :: tab;

	// target :: Proposition implementation
	void
	Definition :: writeBody (String& string) const
	{
		if (expressionInBrackets()) {
			string << Proposition :: expression_->getSymbol (1);
		}
		string << mdl :: Token :: defiendum_ << space;

		int bracketDepth = 0;
		int braceDepth = 0;
		for (index :: Literal i = firstInsideIndex(); i <= lastInsideIndex(); ++ i) {
			const Symbol& symbol = Proposition :: expression_->getSymbol (i);
			countDepth (symbol, bracketDepth, braceDepth);
			if (symbol == Math :: constants()->equality() ||
				symbol == Math :: constants()->equivalence()) {
				if ((bracketDepth == 0) && (braceDepth == 0)) {
					string << symbol;
					break;
				}
			}
		}
		string << mdl :: Token :: definiens_ << space;
		if (expressionInBrackets()) {
			const index :: Literal
				size = Proposition :: expression_->getSize();
			string << Proposition :: expression_->getSymbol (size - 1);
		}
	}
}
}
}
}
}


