/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_lexer_LabelScaner.hpp                                */
/* Description:     smm scaner for assertion labels                          */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "lexer/smm_lexer.dpp"
#include "lexer/smm_lexer_Token.hpp"

namespace smm {
namespace lexer {

class LabelScaner : public ExpressionScaner<LabelScaner, Token> {
	typedef
		ExpressionScaner<LabelScaner, Token>
		Ancestor_;
public :
	LabelScaner (Source& source) :
	Ancestor_ (source) {
	}
	static bool isTerminal (const Char& ch)
	{
		const bool alphaNumeric = ch.isAlphaNumeric();
		const char c = ch.getValue();
		return !(alphaNumeric || c == '-' || c == '.');
	}
	static Token :: Type getTokenType() {
		return Token :: LABEL;
	}
};

}
}


