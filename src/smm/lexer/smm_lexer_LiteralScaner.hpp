/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_lexer_LiteralScaner.hpp                              */
/* Description:     smm literal scaner                                       */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_LEXER_LITERAL_SCANER_HPP_
#define SMM_LEXER_LITERAL_SCANER_HPP_

#include "smm/lexer/smm_lexer.dpp"
#include "smm/lexer/smm_lexer_Token.hpp"

namespace smm {
namespace lexer {

class LiteralScaner : public ExpressionScaner<LiteralScaner, Token> {
	typedef
		ExpressionScaner<LiteralScaner, Token>
		Ancestor_;
public :
	LiteralScaner (Source& source) :
	Ancestor_ (source) {
	}
	static bool isTerminal (const Char& ch)
	{
		if (Config :: asciiOnly()) {
			const char c = ch.getValue();
			return (c < '!') || (c == '$') || (c > '~');
		} else {
			return (ch.getValue() == '$') || ch.isWhitespace();
		}
	}
	static Token :: Type getTokenType() {
		return Token :: LITERAL;
	}
};

}
}

#endif /*SMM_LEXER_LITERAL_SCANER_HPP_*/
