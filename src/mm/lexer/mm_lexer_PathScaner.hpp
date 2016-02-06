/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_lexer_PathScaner.hpp                                  */
/* Description:     metamath path scaner                                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "lexer/mm_lexer.dpp"
#include "lexer/mm_lexer_Token.hpp"

namespace mm {
namespace lexer {

class PathScaner : public ExpressionScaner<PathScaner, Token> {
	typedef
		ExpressionScaner<PathScaner, Token>
		Ancestor_;
public :
	PathScaner (Source& source) :
	Ancestor_ (source) {
	}
	static bool isTerminal (const Char& ch) {
		return ch.isWhitespace();
	}
	static Token :: Type getTokenType() {
		return Token :: PATH;
	}
};

}
}


