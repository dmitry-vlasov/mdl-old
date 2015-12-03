/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_lexer_CommentScaner.hpp                               */
/* Description:     metamath comment scaner                                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_LEXER_COMMENT_SCANER_HPP_
#define MM_LEXER_COMMENT_SCANER_HPP_

#include "lexer/mm_lexer.dpp"
#include "lexer/mm_lexer_Token.hpp"

namespace mm {
namespace lexer {

class CommentScaner : public nstd :: Object {
public :
	typedef
		Comments<allocator :: Heap>
		Comments_;
	typedef
		Comments_ :: Comment_
		Comment_;

	CommentScaner (Source&);
	virtual ~ CommentScaner();

	void scan();
	Comments_& comments();

	// nstd :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (nstd :: String<>&) const;

private :
	Source& source_;
	Comments_ comments_;
};

}
}

#endif /*MM_LEXER_COMMENT_SCANER_HPP_*/
