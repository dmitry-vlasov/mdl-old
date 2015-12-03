/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_lexer_NumberScaner.hpp                               */
/* Description:     number scaner                                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_LEXER_NUMBER_SCANER_HPP_
#define MDL_LEXER_NUMBER_SCANER_HPP_

#include "mdl/lexer/mdl_lexer_Token.hpp"

namespace mdl {
namespace lexer {

class NumberScaner : public ExpressionScaner<NumberScaner, Token> {
	typedef
		ExpressionScaner<NumberScaner, Token>
		Ancestor_;
public :
	NumberScaner (Source& source) :
	Ancestor_ (source) {
	}
	static bool isTerminal (const Char& ch) {
		const char c =  ch.getValue();
		return (c < '0') || (c > '9');
	}
	static Token :: Type getTokenType() {
		return Token :: NUMBER;
	}
};

}
}

#endif /*MDL_LEXER_NUMBER_SCANER_HPP_*/
