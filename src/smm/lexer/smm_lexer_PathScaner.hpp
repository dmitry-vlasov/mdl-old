/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_lexer_PathScaner.hpp                                 */
/* Description:     smm path scaner                                          */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_LEXER_PATH_SCANER_HPP_
#define SMM_LEXER_PATH_SCANER_HPP_

#include "smm/lexer/smm_lexer.dpp"
#include "smm/lexer/smm_lexer_Token.hpp"

namespace smm {
namespace lexer {

class PathScaner : public ExpressionScaner<PathScaner, Token> {
	typedef
		ExpressionScaner<PathScaner, Token>
		Ancestor_;
public :
	PathScaner (Source& source) :
	Ancestor_ (source) {
	}
	static bool isTerminal (const Char& ch)
	{
		const bool alphaNumeric = ch.isAlphaNumeric();
		const char c = ch.getValue();
		return
		!(
			alphaNumeric ||
			c == '-' ||
			c == chars :: EXTENSION_DELIMITER ||
			c == chars :: DIR_DELIMITER
		);
	}
	static Token :: Type getTokenType() {
		return Token :: PATH;
	}
};

}
}

#endif /*SMM_LEXER_PATH_SCANER_HPP_*/
