/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_parser_block_Floating.cpp                             */
/* Description:     floating hypothesis parser                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mm/lexer/mm_lexer.hpp"
#include "mm/auxiliary/mm_auxiliary.hpp"
#include "mm/ast/mm_ast.hpp"
#include "mm/parser/mm_parser.hpp"

namespace mm {
namespace parser {
namespace block {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Floating :: Floating (const parser :: Block* const blockParser) :
	blockParser_ (blockParser),
	label_ (value :: undefined :: LABEL),
	type_ (value :: undefined :: LITERAL),
	variable_ (value :: undefined :: LITERAL),
	location_ () {
	}
	Floating :: ~ Floating() {
	}

	const mm :: source :: Hypothesis*
	Floating :: parse (Lexer* const lexer, mm :: source :: Block* const block)
	{
		location_ = lexer->getLocation();
		// label
		const String&
			labelToken = blockParser_->getLabel();
		label_ = Table :: hypothesisLabels()->add (labelToken);

		// type
		lexer->scan<Token :: LITERAL> ();
		const String&
			typeToken = lexer->getToken();
		const value :: Literal
			type_ = Table :: literals()->add (typeToken);

		// variable
		lexer->scan<Token :: LITERAL> ();
		const String&
			variableToken = lexer->getToken();
		variable_ = Table :: literals()->add (variableToken);

		// $.
		lexer->scan<Token :: END> ();
		lexer->comments().clear();
		return new ast :: source :: Floating (location_, label_, type_, variable_, block);
	}

	// object :: Object implementation
	void
	Floating :: commitSuicide() {
		delete this;
	}
	Size_t
	Floating :: getVolume() const {
		return location_.getVolume();
	}
	Size_t
	Floating :: getSizeOf () const {
		return sizeof (Floating);
	}
	void
	Floating :: show (String&) const {
	}
}
}
}


