/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_lexer_WhitespaceScaner.hpp                            */
/* Description:     metamath whitespace scaner                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_LEXER_WHITESPACE_SCANER_HPP_
#define MM_LEXER_WHITESPACE_SCANER_HPP_

#include "lexer/mm_lexer_CommentScaner.hpp"

namespace mm {
namespace lexer {

class WhitespaceScaner : public nstd :: Object {
public :
	typedef
		CommentScaner :: Comments_
		Comments_;

	WhitespaceScaner (Source&);
	virtual ~ WhitespaceScaner();

	void scan();
	Comments_& comments();

	// nstd :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (nstd :: String<>&) const;

private :
	bool commentBegins();

	Source& source_;
	CommentScaner commentScaner_;
};

}
}

#endif /*MM_LEXER_WHITESPACE_SCANER_HPP_*/
