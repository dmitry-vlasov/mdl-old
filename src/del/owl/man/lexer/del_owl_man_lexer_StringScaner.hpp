/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File String:     del_owl_man_lexer_StringScaner.hpp                       */
/* Description:     manchester OWL name scaner                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/lexer/del_lexer_Token.hpp"

namespace del {
namespace owl {
namespace man {
namespace lexer {

class StringScaner : public ExpressionScaner<StringScaner, Token> {
	typedef
		ExpressionScaner<StringScaner, Token>
		Ancestor_;
public :
	StringScaner (Source& source) :
	Ancestor_ (source) {
	}
	static bool isTerminal (const Char& ch)
	{
		return
			ch.isWhitespace() ||
			ch.isNewLine() ||
			(ch.getValue() == '>');
	}
	static Token :: Type getTokenType() {
		return Token :: STRING;
	}
};

}
}
}
}


