/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_parser_block_Proof.cpp                                */
/* Description:     metamath proof parser                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_PARSER_BLOCK_PROOF_CPP_
#define MM_PARSER_BLOCK_PROOF_CPP_

#include "lexer/mm_lexer.hpp"
#include "ast/mm_ast.hpp"
#include "parser/mm_parser.hpp"

namespace mm {
namespace parser {
namespace block {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Proof :: Proof() :
	referenceParser_ (new parser :: Reference()),
	location_ () {
	}
	Proof :: ~ Proof() {
		deleteAggregateObject (referenceParser_);
	}

	const mm :: source :: Proof*
	Proof :: parse (Lexer* const lexer, mm :: source :: Block* const block)
	{
		location_ = lexer->getLocation();
		mm :: source :: Proof* const
			proof = new ast :: source :: Proof (location_);

		while (lexer->scan<Token :: IDENTIFICATOR, Token :: END> () != Token :: END) {
			const mm :: source :: Reference* const
				reference = referenceParser_->parse (lexer, block);
			proof->addReference (reference);
		}
		lexer->scanComments();
		const mm :: source :: Comments*
			proofComments = new ast :: source :: Comments (lexer->comments(), true);
		proof->addComments (proofComments);
		return proof;
	}

	// object :: Object implementation
	void
	Proof :: commitSuicide() {
		delete this;
	}
	Size_t
	Proof :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (referenceParser_);
		volume += location_.getVolume();
		return volume;
	}
	Size_t
	Proof :: getSizeOf() const {
		return sizeof (Proof);
	}
	void
	Proof :: show (String&) const {
	}
}
}
}

#endif /*MM_PARSER_BLOCK_PROOF_CPP_*/
