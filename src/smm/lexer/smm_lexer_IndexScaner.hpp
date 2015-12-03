/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_lexer_IndexScaner.hpp                                */
/* Description:     smm index scaner                                         */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_LEXER_INDEX_SCANER_HPP_
#define SMM_LEXER_INDEX_SCANER_HPP_

#include "smm/lexer/smm_lexer.dpp"
#include "smm/lexer/smm_lexer_Token.hpp"

namespace smm {
namespace lexer {

class IndexScaner : public ExpressionScaner<IndexScaner, Token> {
	typedef
		ExpressionScaner<IndexScaner, Token>
		Ancestor_;
public :
	IndexScaner (Source& source) :
	Ancestor_ (source) {
	}
	inline static bool isTerminal (const Char& ch) {
		return !ch.isNumber();
	}
	inline static Token :: Type getTokenType() {
		return Token :: INDEX;
	}
};

}
}

#endif /*SMM_LEXER_INDEX_SCANER_HPP_*/
