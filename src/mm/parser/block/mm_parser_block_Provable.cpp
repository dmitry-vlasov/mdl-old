/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_parser_block_Provable.cpp                             */
/* Description:     provable assertion parser                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_PARSER_BLOCK_PROVABLE_CPP_
#define MM_PARSER_BLOCK_PROVABLE_CPP_

#include "ast/mm_ast.hpp"
#include "parser/mm_parser.hpp"

namespace mm {
namespace parser {
namespace block {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Provable :: Provable (const parser :: Block* const blockParser) :
	parser :: Assertion (blockParser),
	proofParser_ (new parser :: Proof()),
	proof_ (NULL) {
	}
	Provable :: ~ Provable() {
		deleteAggregateObject (proofParser_);
	}

	const mm :: source :: Assertion*
	Provable :: parse (Lexer* const lexer, mm :: source :: Block* const block)
	{
		parseHeader<Token :: PROOF> (lexer);
		const mm :: source :: Comments*
			comments = new ast :: source :: Comments (lexer->comments());
		lexer->comments().clear();
		proof_ = proofParser_->parse (lexer, block);
		return new ast :: source :: Provable
		(
			location_,
			label_,
			literalVector_,
			proof_,
			block,
			comments
		);
	}

	// object :: Object implementation
	void
	Provable :: commitSuicide() {
		delete this;
	}
	Size_t
	Provable :: getVolume() const {
		Size_t volume = 0;
		volume += parser :: Assertion :: getVolume();
		volume += getAggregateVolume (proofParser_);
		return volume;
	}
	Size_t
	Provable :: getSizeOf() const {
		return sizeof (Provable);
	}
	void
	Provable :: show (String&) const {
	}
}
}
}

#endif /*MM_PARSER_BLOCK_PROVABLE_CPP_*/
