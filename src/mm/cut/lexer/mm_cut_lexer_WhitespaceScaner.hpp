/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_cut_lexer_WhitespaceScaner.hpp                        */
/* Description:     mm source file cutting lexer white space scaner          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_CUT_LEXER_WHITESPACE_SCANER_HPP_
#define MM_CUT_LEXER_WHITESPACE_SCANER_HPP_

#include "mm/cut/lexer/mm_cut_lexer.dpp"

namespace mm {
namespace cut {
namespace lexer {

class WhitespaceScaner : public nstd :: Object {
public :
	WhitespaceScaner (Source&);
	virtual ~ WhitespaceScaner();

	void scan();

	// nstd :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (nstd :: String<>&) const;

private :
	Source& source_;
};

}
}
}

#endif /*MM_CUT_LEXER_WHITESPACE_SCANER_HPP_*/
