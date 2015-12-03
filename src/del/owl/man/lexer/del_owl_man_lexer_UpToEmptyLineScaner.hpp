/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Line:       del_owl_lexer_man_UpToEmptyLineScaner.hpp                */
/* Description:     owl scaner up to the empty line                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_MAN_LEXER_UP_TO_EMPTY_LINE_SCANER_HPP_
#define DEL_OWL_MAN_LEXER_UP_TO_EMPTY_LINE_SCANER_HPP_

#include "del/lexer/del_lexer_Token.hpp"

namespace del {
namespace owl {
namespace man {
namespace lexer {

class UpToEmptyLineScaner : public ExpressionScaner<UpToEmptyLineScaner, Token> {
	typedef
		ExpressionScaner<UpToEmptyLineScaner, Token>
		Ancestor_;
public :
	UpToEmptyLineScaner (Source& source) :
	Ancestor_ (source) {
	}
	static bool isTerminal (const Char& ch)
	{
		Char nextCh (ch);
		++ nextCh;
		return (ch.isNewLine() && nextCh.isNewLine());
	}
	static Token :: Type getTokenType() {
		return Token :: TO_THE_EMPTY_LINE;
	}
};

}
}
}
}

#endif /*DEL_OWL_MAN_LEXER_UP_TO_EMPTY_LINE_SCANER_HPP_*/
