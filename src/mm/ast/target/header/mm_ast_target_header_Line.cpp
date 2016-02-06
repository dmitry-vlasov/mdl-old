/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_header_Line.cpp                            */
/* Description:     mdl header line general class                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "math/mm_math.hpp"
#include "ast/target/header/mm_ast_target_header_Line.hpp"

namespace mm {
namespace ast {
namespace target {
namespace header {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Line :: Line
	(
		const mm :: Expression* const expression,
		const index :: Arity index
	) :
	expression_ (expression),
	index_ (index) {
	}
	Line :: ~ Line() {
	}

	// object :: Object interface
	Size_t
	Line :: getVolume() const {
		return 0;
	}
	Size_t
	Line :: getSizeOf() const {
		return sizeof (Line);
	}

	/****************************
	 *		Protected members
	 ****************************/

	index :: Literal
	Line :: firstInsideIndex() const
	{
		if (expressionInBrackets()) {
			return 2;
		} else {
			return 1;
		}
	}
	index :: Literal
	Line :: lastInsideIndex() const
	{
		if (expressionInBrackets()) {
			return expression_->getSize() - 2;
		} else {
			return expression_->getSize() - 1;
		}
	}
	bool
	Line :: expressionInBrackets() const
	{
		const index :: Literal
			size = expression_->getSize();
		int bracketDepth = 0;
		int braceDepth = 0;
		if (expression_->getSymbol (1) != Math :: constants()->openBracket()) {
			return false;
		}
		if (expression_->getSymbol (size - 1) != Math :: constants()->closeBracket()) {
			return false;
		}
		for (index :: Literal i = 1; i < size; ++ i) {
			const Symbol& symbol = expression_->getSymbol (i);
			countDepth (symbol, bracketDepth, braceDepth);
			if ((1 < i) && (i < size - 1) && (bracketDepth == 0)) {
				return false;
			}
		}
		if (braceDepth != 0) {
			return false;
		}
		return true;
	}
	void
	Line :: countDepth
	(
		const Symbol& symbol,
		int& bracketDepth,
		int& braceDepth
	) const
	{
		if (symbol == Math :: constants()->openBracket()) {
			++ bracketDepth;
		}
		if (symbol == Math :: constants()->closeBracket()) {
			-- bracketDepth;
		}
		if (symbol == Math :: constants()->openBrace()) {
			++ braceDepth;
		}
		if (symbol == Math :: constants()->closeBrace()) {
			-- braceDepth;
		}
	}
	bool
	Line :: findTermType (const Symbol& symbol, String& string) const
	{
		if (symbol == Math :: constants()->equality()) {
			const value :: Literal
				_class = Math :: constants()->_class();
			string << Table :: literals()->get (_class) << space;
			return true;
		}
		if (symbol == Math :: constants()->equivalence()) {
			const value :: Literal
				wff = Math :: constants()->wff();
			string << Table :: literals()->get (wff) << space;
			return true;
		}
		return false;
	}
}
}
}
}


