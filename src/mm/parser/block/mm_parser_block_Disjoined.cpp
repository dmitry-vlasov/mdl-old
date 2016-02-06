/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_parser_block_Disjoined.cpp                            */
/* Description:     disjoined parser                                         */
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
	Disjoined :: Disjoined() :
	literalVector_ (INITIAL_DISJOINED_VECTOR_CAPACITY),
	location_ () {
	}
	Disjoined :: ~ Disjoined() {
	}

	const mm :: source :: Disjoined*
	Disjoined :: parse (Lexer* const lexer, mm :: source :: Block* const block)
	{
		location_ = lexer->getLocation();
		literalVector_.clear();
		while (lexer->scan<Token :: LITERAL, Token :: END> () == Token :: LITERAL) {
			const String&
				token = lexer->getToken();
			const value :: Literal
				variable = Table :: literals()->add (token);
			literalVector_.add (variable);
		}
		lexer->comments().clear();
		return new ast :: source :: Disjoined (location_, literalVector_, block);
	}

	// object :: Object implementation
	void
	Disjoined :: commitSuicide() {
		delete this;
	}
	Size_t
	Disjoined :: getVolume() const
	{
		Size_t volume = 0;
		volume += literalVector_.getVolume();
		volume += location_.getVolume();
		return volume;
	}
	Size_t
	Disjoined :: getSizeOf () const {
		return sizeof (Disjoined);
	}
	void
	Disjoined :: show (String&) const {
	}
}
}
}


