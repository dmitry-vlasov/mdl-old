/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_man_lexer_Scaner.hpp                             */
/* Description:     manchester OWL scaner                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_MAN_LEXER_SCANER_HPP_
#define DEL_OWL_MAN_LEXER_SCANER_HPP_

#include "del/owl/man/lexer/del_owl_man_lexer.dpp"
#include "del/owl/man/lexer/del_owl_man_lexer_LineScaner.hpp"
#include "del/owl/man/lexer/del_owl_man_lexer_NameScaner.hpp"
#include "del/owl/man/lexer/del_owl_man_lexer_StringScaner.hpp"
#include "del/owl/man/lexer/del_owl_man_lexer_WhitespaceScaner.hpp"
#include "del/owl/man/lexer/del_owl_man_lexer_UpToEmptyLineScaner.hpp"

namespace del {
namespace owl {
namespace man {
namespace lexer {

class Scaner : public Object {
public :
	typedef
		WhitespaceScaner :: Comments_
		Comments_;

	Scaner (Source&);
	virtual ~ Scaner();

	Comments_& comments();
	void scanComments();
	void scanWhitespace();
	void scanString();
	void scanLine();
	void scanUpToEmptyLine();

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
	NameScaner nameScaner_;
	LineScaner lineScaner_;
	UpToEmptyLineScaner upToEmptyLineScaner_;
	StringScaner stringScaner_;
	WhitespaceScaner whitespaceScaner_;
	bool inExpression_;
};

}
}
}
}

#include "del/owl/man/lexer/del_owl_man_lexer_Scaner.ipp"

#endif /*DEL_OWL_MAN_LEXER_SCANER_HPP_*/
