/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_parser_block_Essential.cpp                            */
/* Description:     essential hypothesis parser                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_PARSER_BLOCK_ESSENTIAL_CPP_
#define MM_PARSER_BLOCK_ESSENTIAL_CPP_

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
	Essential :: Essential (const parser :: Block* const blockParser) :
	blockParser_ (blockParser),
	label_ (value :: undefined :: LABEL),
	literalVector_ (INITIAL_LITERAL_VECTOR_CAPACITY),
	location_ () {
	}
	Essential :: ~ Essential() {
	}

	const mm :: source :: Hypothesis*
	Essential :: parse (Lexer* const lexer, mm :: source :: Block* const block)
	{
		literalVector_.clear();
		location_ = lexer->getLocation();
		const String&
			labelToken = blockParser_->getLabel();
		label_ = Table :: hypothesisLabels()->add (labelToken);

		if (!Config :: useGrammarCorrection()) {
			readExpression (lexer);
		} else {
			const vector :: Literal* const
				correctExpression = auxiliary :: Corrector :: getExpression (labelToken);
			if (correctExpression == NULL) {
				readExpression (lexer);
			} else {
				scanExpression (lexer);
				copyExpression (correctExpression);
			}
		}
		lexer->comments().clear();
		return new ast :: source :: Essential (location_, label_, literalVector_, block);
	}

	// object :: Object implementation
	void
	Essential :: commitSuicide() {
		delete this;
	}
	Size_t
	Essential :: getVolume() const
	{
		Size_t volume = 0;
		volume += literalVector_.getVolume();
		volume += location_.getVolume();
		return volume;
	}
	Size_t
	Essential :: getSizeOf () const {
		return sizeof (Essential);
	}
	void
	Essential :: show (String&) const {
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Essential :: readExpression (Lexer* const lexer)
	{
		while (lexer->scan<Token :: LITERAL, Token :: END> () != Token :: END) {
			const String&
				token = lexer->getToken();
			const value :: Literal
				literal = Table :: literals()->add (token);
			literalVector_.add (literal);
		}
	}
	void
	Essential :: scanExpression (Lexer* const lexer)
	{
		while (lexer->scan<Token :: LITERAL, Token :: END> () != Token :: END) {
		}
	}
	void
	Essential :: copyExpression (const vector :: Literal* const correctExpression)
	{
		for (index :: Literal i = 0; i < correctExpression->getSize(); i++) {
			const value :: Literal
				literal = correctExpression->getValue (i);
			literalVector_.add (literal);
		}
	}
}
}
}

#endif /*MM_PARSER_BLOCK_ESSENTIAL_CPP_*/
