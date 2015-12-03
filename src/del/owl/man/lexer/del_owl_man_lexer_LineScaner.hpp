/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Line:       del_owl_man_lexer_LineScaner.hpp                         */
/* Description:     OWL manchester name scaner                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_MAN_LEXER_LINE_SCANER_HPP_
#define DEL_OWL_MAN_LEXER_LINE_SCANER_HPP_

#include "del/lexer/del_lexer_Token.hpp"

namespace del {
namespace owl {
namespace man {
namespace lexer {

class LineScaner : public ExpressionScaner<LineScaner, Token> {
	typedef
		ExpressionScaner<LineScaner, Token>
		Ancestor_;
public :
	LineScaner (Source& source) :
	Ancestor_ (source) {
	}
	static bool isTerminal (const Char& ch) {
		return ch.isNewLine();
	}
	static Token :: Type getTokenType() {
		return Token :: LINE;
	}
};

}
}
}
}

#endif /*DEL_OWL_MAN_LEXER_LINE_SCANER_HPP_*/
