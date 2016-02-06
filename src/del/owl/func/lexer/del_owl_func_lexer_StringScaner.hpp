/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File String:     del_owl_func_lexer_StringScaner.hpp                      */
/* Description:     functional OWL2 name scaner                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/owl/func/lexer/del_owl_func_lexer_Token.hpp"

namespace del {
namespace owl {
namespace func {
namespace lexer {

class StringScaner {
public :
	StringScaner (Source& source) :
	source_ (source),
	inParentheses_ (false) {
	}
	Token :: Type scan ()
	{
		while (!isTerminal (source_.getChar()) &&
			!source_.getChar().isEOF()) {
			++ source_;
		}
		if (source_.getChar().isEOF()) {
			return Token :: EOF_;
		} else {
			return Token :: STRING;
		}
	}

private :
	bool isTerminal (const Char& ch)
	{
		if (ch.getValue() == '"' &&
			ch.getValue (-1) != '\\') {
			inParentheses_ = !inParentheses_;
		}
		return
			!inParentheses_ &&
			(
				ch.isWhitespace() ||
				ch.isNewLine() ||
				(ch == '(') || (ch == ')')
			);
	}

	Source& source_;
	bool inParentheses_;
};

}
}
}
}


