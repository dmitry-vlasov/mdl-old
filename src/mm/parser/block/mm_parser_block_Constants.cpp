/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_parser_block_Constants.cpp                            */
/* Description:     constants parser                                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_PARSER_BLOCK_CONSTANTS_CPP_
#define MM_PARSER_BLOCK_CONSTANTS_CPP_

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
	Constants :: Constants() :
	literalVector_ (INITIAL_CONSTANT_VECTOR_CAPACITY),
	location_ () {
	}
	Constants :: ~ Constants() {
	}

	const mm :: source :: Constants*
	Constants :: parse (Lexer* const lexer, mm :: source :: Block* const block)
	{
		location_ = lexer->getLocation();
		literalVector_.clear();
		while (lexer->scan<Token :: LITERAL, Token :: END> () == Token :: LITERAL) {
			const String&
				token = lexer->getToken();
			const value :: Literal
				constant = Table :: literals()->add (token);
			literalVector_.add (constant);
		}
		lexer->scanComments();
		const mm :: source :: Comments*
			comments = new ast :: source :: Comments (lexer->comments());
		lexer->comments().clear();
		return new ast :: source :: Constants (location_, comments, literalVector_, block);
	}

	// object :: Object implementation
	void
	Constants :: commitSuicide() {
		delete this;
	}
	Size_t
	Constants :: getVolume() const
	{
		Size_t volume = 0;
		volume += literalVector_.getVolume();
		volume += location_.getVolume();
		return volume;
	}
	Size_t
	Constants :: getSizeOf () const {
		return sizeof (Constants);
	}
	void
	Constants :: show (String&) const {
	}
}
}
}

#endif /*MM_PARSER_BLOCK_CONSTANTS_CPP_*/
