/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_lexer_NameScaner.hpp                                 */
/* Description:     name scaner                                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_LEXER_NAME_SCANER_HPP_
#define DEL_LEXER_NAME_SCANER_HPP_

#include "del/lexer/del_lexer_Token.hpp"

namespace del {
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
			(c == '}') || (c == '{') || (c == '.') ||
			(c == '(') || (c == ')') || (c == '?') ||
			(c == chars :: DELTA_POSTFIX);
	}
	static Token :: Type getTokenType() {
		return Token :: NAME;
	}
};

}
}

#endif /*DEL_LEXER_NAME_SCANER_HPP_*/
