/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_lexer_LiteralScaner.hpp                               */
/* Description:     metamath literal scaner                                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_LEXER_LITERAL_SCANER_HPP_
#define MM_LEXER_LITERAL_SCANER_HPP_

#include "lexer/mm_lexer.dpp"
#include "lexer/mm_lexer_Token.hpp"

namespace mm {
namespace lexer {

class LiteralScaner : public ExpressionScaner<LiteralScaner, Token> {
	typedef
		ExpressionScaner<LiteralScaner, Token>
		Ancestor_;
public :
	LiteralScaner (Source& source) :
	Ancestor_ (source) {
	}
	static bool isTerminal (const Char& ch) {
		const char c = ch.getValue();
		return (c < '!') || (c == '$') || (c > '~');
	}
	static Token :: Type getTokenType() {
		return Token :: LITERAL;
	}
};

}
}

#endif /*MM_LEXER_LITERAL_SCANER_HPP_*/
