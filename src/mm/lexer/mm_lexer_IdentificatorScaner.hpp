/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_lexer_IdentificatorScaner.hpp                         */
/* Description:     metamath identificator scaner                            */
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

class IdentificatorScaner : public ExpressionScaner<IdentificatorScaner, Token> {
	typedef
		ExpressionScaner<IdentificatorScaner, Token>
		Ancestor_;
public :
	IdentificatorScaner (Source& source) :
	Ancestor_ (source) {
	}
	static bool isTerminal (const Char& ch)
	{
		const bool alphaNumeric = ch.isAlphaNumeric();
		const char c = ch.getValue();
		return !(alphaNumeric || c == '-' || c == '.');
	}
	static Token :: Type getTokenType() {
		return Token :: IDENTIFICATOR;
	}
};

}
}


