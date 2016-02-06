/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_lexer_HorisontalBarScaner.hpp                        */
/* Description:     horisontal bar scaner                                    */
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

class HorisontalBarScaner : public nstd :: lexer :: ExpressionScaner<HorisontalBarScaner, Token> {
	typedef
		nstd :: lexer :: ExpressionScaner<HorisontalBarScaner, Token>
		Ancestor;
public :
	HorisontalBarScaner (Source& source) :
	Ancestor (source) {
	}
	static bool isTerminal (const Char& ch) {
		const char c = ch.getValue();
		return (c != '-');
	}
	static Token :: Type getTokenType() {
		return Token :: HORISONTAL_BAR;
	}
};

}
}


