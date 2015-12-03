/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_lexer_RealScaner.hpp                                 */
/* Description:     real number scaner                                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_LEXER_REAL_SCANER_HPP_
#define MDL_LEXER_REAL_SCANER_HPP_

#include "mdl/lexer/mdl_lexer_Token.hpp"

namespace mdl {
namespace lexer {

class RealScaner : public ExpressionScaner<RealScaner, Token> {
	typedef
		ExpressionScaner<RealScaner, Token>
		Ancestor_;
public :
	RealScaner (Source& source) :
	Ancestor_ (source) {
	}
	static bool isTerminal (const Char& ch) {
		return !isNonTerminal (ch);
	}
	static Token :: Type getTokenType() {
		return Token :: REAL_NUMBER;
	}
private :
	static bool isNonTerminal (const Char& ch)
	{
		const char c =  ch.getValue();
		return
			(('0' <= c) && (c <= '9')) ||
			(c == '+') || (c == '-') ||
			(c == '.') || (c == 'e');
	}
};

}
}

#endif /*MDL_LEXER_REAL_SCANER_HPP_*/
