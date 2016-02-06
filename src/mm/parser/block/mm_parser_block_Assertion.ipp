/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_parser_block_Assertion.ipp                            */
/* Description:     assertion parser                                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "parser/mm_parser_Block.hpp"

namespace mm {
namespace parser {
namespace block {

	/****************************
	 *		Protected members
	 ****************************/

	template<Token :: Type ending>
	void
	Assertion :: parseHeader (Lexer* const lexer)
	{
		location_ = lexer->getLocation();
		const String&
			labelToken = blockParser_->getLabel();
		label_ = Table :: assertionLabels()->add (labelToken);

		if (!Config :: useGrammarCorrection()) {
			readExpression<ending> (lexer);
		} else {
			const vector :: Literal* const
				correctExpression = auxiliary :: Corrector :: getExpression (labelToken);
			if (correctExpression == NULL) {
				readExpression<ending> (lexer);
			} else {
				scanExpression<ending> (lexer);
				copyExpression (correctExpression);
			}
		}
	}

	/****************************
	 *		Private members
	 ****************************/

	template<Token :: Type ending>
	void
	Assertion :: readExpression (Lexer* const lexer)
	{
		literalVector_.clear();
		while (lexer->scan<Token :: LITERAL, ending> () != ending) {
			const String&
				token = lexer->getToken();
			const value :: Literal
				literal = Table :: literals()->add (token);
			literalVector_.add (literal);
		}
	}
	template<Token :: Type ending>
	void
	Assertion :: scanExpression (Lexer* const lexer)
	{
		while (lexer->scan<Token :: LITERAL, ending> () != ending) {
		}
	}
}
}
}


