/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_parser_block_Axiomatic.cpp                            */
/* Description:     axiomatic assertion parser                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "lexer/mm_lexer.hpp"
#include "ast/mm_ast.hpp"
#include "math/mm_math.hpp"
#include "parser/mm_parser.hpp"

namespace mm {
namespace parser {
namespace block {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Axiomatic :: Axiomatic (const parser :: Block* const blockParser) :
	parser :: Assertion (blockParser) {
	}
	Axiomatic :: ~ Axiomatic() {
	}

	const mm :: source :: Assertion*
	Axiomatic :: parse (Lexer* const lexer, mm :: source :: Block* const block)
	{
		parseHeader<Token :: END> (lexer);
		const mm :: source :: Comments*
			comments = new ast :: source :: Comments (lexer->comments());
		lexer->comments().clear();
		return new ast :: source :: Axiomatic
		(
			location_,
			label_,
			literalVector_,
			block,
			comments
		);
	}

	// object :: Object implementation
	void
	Axiomatic :: commitSuicide() {
		delete this;
	}
	Size_t
	Axiomatic :: getVolume() const {
		return parser :: Assertion :: getVolume();
	}
	Size_t
	Axiomatic :: getSizeOf() const {
		return sizeof (Axiomatic);
	}
	void
	Axiomatic :: show (String&) const {
	}
}
}
}


