/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_parser_block_Variables.cpp                            */
/* Description:     variables parser                                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_PARSER_BLOCK_VARIABLES_CPP_
#define MM_PARSER_BLOCK_VARIABLES_CPP_

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
	Variables :: Variables() :
	literalVector_ (INITIAL_VARIABLE_VECTOR_CAPACITY),
	location_ () {
	}
	Variables :: ~ Variables() {
	}

	const mm :: source :: Variables*
	Variables :: parse (Lexer* const lexer, mm :: source :: Block* const block)
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
		return new ast :: source :: Variables (location_, literalVector_, block);
	}

	// object :: Object implementation
	void
	Variables :: commitSuicide() {
		delete this;
	}
	Size_t
	Variables :: getVolume() const
	{
		Size_t volume = 0;
		volume += literalVector_.getVolume();
		volume += location_.getVolume();
		return volume;
	}
	Size_t
	Variables :: getSizeOf () const {
		return sizeof (Variables);
	}
	void
	Variables :: show (String&) const {
	}
}
}
}

#endif /*MM_PARSER_BLOCK_VARIABLES_CPP_*/
