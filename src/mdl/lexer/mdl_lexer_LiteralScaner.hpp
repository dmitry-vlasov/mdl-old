/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_lexer_LiteralScaner.hpp                              */
/* Description:     literal scaner                                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_LEXER_LITERAL_SCANER_HPP_
#define MDL_LEXER_LITERAL_SCANER_HPP_

#include "mdl/lexer/mdl_lexer_Token.hpp"

namespace mdl {
namespace lexer {

class LiteralScaner : public ExpressionScaner<LiteralScaner, Token> {
	typedef
		ExpressionScaner<LiteralScaner, Token>
		Ancestor_;
public :
	LiteralScaner (Source& source) :
	Ancestor_ (source) {
	}
	static const bool isTerminal (const Char& ch) {
		return
			((ch.getValue() == ';') && (ch.getValue (-1) != '\\')) ||
			ch.isWhitespace();
	}
	static Token :: Type getTokenType() {
		return Token :: LITERAL;
	}
};

}
}

#endif /*MDL_LEXER_LITERAL_SCANER_HPP_*/
