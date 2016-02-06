/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_lexer_NameScaner.hpp                                 */
/* Description:     name scaner                                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/lexer/mdl_lexer_Token.hpp"

namespace mdl {
namespace lexer {

class NameScaner : public ExpressionScaner<NameScaner, Token> {
	typedef
		ExpressionScaner<NameScaner, Token>
		Ancestor_;
public :
	NameScaner (Source& source) :
	Ancestor_ (source) {
	}
	static bool isTerminal (const Char& ch)
	{
		const char c = ch.getValue();
		return
			(c <= ' ') || (c == ';') || (c == ',') ||
			(c == '.') || (c == '(') || (c == ')') || (c == ':');
	}
	static Token :: Type getTokenType() {
		return Token :: NAME;
	}
};

}
}


