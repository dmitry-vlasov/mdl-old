/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_lexer_Scaner.hpp                                      */
/* Description:     metamath scaner                                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "lexer/mm_lexer_IdentificatorScaner.hpp"
#include "lexer/mm_lexer_LiteralScaner.hpp"
#include "lexer/mm_lexer_PathScaner.hpp"
#include "lexer/mm_lexer_WhitespaceScaner.hpp"

namespace mm {
namespace lexer {

class Scaner : public nstd :: Object {
public :
	typedef
		WhitespaceScaner :: Comments_
		Comments_;

	Scaner (Source&);
	virtual ~ Scaner();

	Token :: Type scan();
	Comments_& comments();
	void scanComments();

	// nstd :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (nstd :: String<>&) const;

private :
	Token :: Type scanSingleChar();
	Token :: Type finalize (const Token :: Type);

	Source& source_;

	LiteralScaner literalScaner_;
	IdentificatorScaner identificatorScaner_;
	PathScaner pathScaner_;
	WhitespaceScaner whitespaceScaner_;

	bool inExpression_;
	bool inProof_;
	bool inInclude_;
};

}
}


