/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_lexer_PathScaner.hpp                                 */
/* Description:     path scaner                                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_LEXER_PATH_SCANER_HPP_
#define DEL_LEXER_PATH_SCANER_HPP_

#include "del/lexer/del_lexer_Token.hpp"

namespace del {
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

#endif /*DEL_LEXER_PATH_SCANER_HPP_*/
