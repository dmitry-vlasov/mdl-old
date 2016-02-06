/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File String:     del_owl_func_lexer_UnrecognizedScaner.hpp                */
/* Description:     functional OWL2 scaner for unrecognized strings          */
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

class UnrecognizedScaner {
public :
	UnrecognizedScaner (Source& source) :
	source_ (source),
	inParentheses_ (false),
	bracketDepth_ (0) {
	}
	Token :: Type scan ()
	{
		bracketDepth_ = 0;
		while (!isTerminal (source_.getChar()) &&
			!source_.getChar().isEOF()) {
			++ source_;
		}
		if (source_.getChar().isEOF()) {
			return Token :: EOF_;
		} else {
			return Token :: UNRECOGNIZED;
		}
	}

private :
	bool isTerminal (const Char& ch)
	{
		switch (ch.getValue()) {
		case '"' :
			if (ch.getValue (-1) != '\\') {
				inParentheses_ = !inParentheses_;
			} break;
		case '(' :
			if (!inParentheses_) {
				++ bracketDepth_;
			} break;
		}
		const bool result =
			!inParentheses_ &&
			(bracketDepth_ == 0) &&
			(
				ch.isWhitespace() ||
				ch.isNewLine() ||
				(ch == '(') || (ch == ')')
			);
		if (!inParentheses_ && (ch.getValue() == ')')) {
			-- bracketDepth_;
		}
		return result;
	}

	Source& source_;
	bool inParentheses_;
	int bracketDepth_;
};

}
}
}
}


