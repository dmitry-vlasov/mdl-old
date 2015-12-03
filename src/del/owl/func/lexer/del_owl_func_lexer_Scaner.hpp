/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_func_lexer_Scaner.hpp                            */
/* Description:     functional OWL2 scaner                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_FUNC_LEXER_SCANER_HPP_
#define DEL_OWL_FUNC_LEXER_SCANER_HPP_

#include "del/owl/func/lexer/del_owl_func_lexer.dpp"
#include "del/owl/func/lexer/del_owl_func_lexer_Token.hpp"
#include "del/owl/func/lexer/del_owl_func_lexer_StringScaner.hpp"
#include "del/owl/func/lexer/del_owl_func_lexer_UnrecognizedScaner.hpp"
#include "del/owl/func/lexer/del_owl_func_lexer_WhitespaceScaner.hpp"

namespace del {
namespace owl {
namespace func {
namespace lexer {

class Scaner : public Object {
public :
	Scaner (Source&);
	virtual ~ Scaner();

	void scanWhitespace();
	Token :: Type scanString();
	Token :: Type scanUnrecognized();

	Token :: Type scan();

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	friend class Lexer;

	bool eofAtStart();
	bool lookahead (const Token&, const short pos = 0);
	Token :: Type consume (const Token&, const short pos = 0);
	Token :: Type finalize (const Token :: Type);

	Source& source_;
	StringScaner stringScaner_;
	WhitespaceScaner whitespaceScaner_;
	UnrecognizedScaner unrecognizedScaner_;
	bool inExpression_;
};

}
}
}
}

#include "del/owl/func/lexer/del_owl_func_lexer_Scaner.ipp"

#endif /*DEL_OWL_FUNC_LEXER_SCANER_HPP_*/
