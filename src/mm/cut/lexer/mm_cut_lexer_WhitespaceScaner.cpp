/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_cut_lexer_WhitespaceScaner.cpp                        */
/* Description:     mm source file cutting lexer white space scaner          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_CUT_LEXER_WHITESPACE_SCANER_CPP_
#define MM_CUT_LEXER_WHITESPACE_SCANER_CPP_

#include "mm/cut/lexer/mm_cut_lexer.hpp"

namespace mm {
namespace cut {
namespace lexer {

	/****************************
	 *		Public members
	 ****************************/

	inline
	WhitespaceScaner :: WhitespaceScaner (Source& source) :
	source_ (source) {
	}
	WhitespaceScaner :: ~ WhitespaceScaner() {
	}

	void
	WhitespaceScaner :: scan()
	{
		while (true) {
			if (source_.getChar().isEOF()) {
				return;
			}
			if (!source_.getChar().isWhitespace()) {
				return;
			}
			++ source_;
		}
	}

	// nstd :: Object implementation
	void
	WhitespaceScaner :: commitSuicide() {
		delete this;
	}
	Size_t
	WhitespaceScaner :: getVolume() const {
		return 0;
	}
	Size_t
	WhitespaceScaner :: getSizeOf() const {
		return sizeof (WhitespaceScaner);
	}
	void
	WhitespaceScaner :: show (nstd :: String<>&) const {
	}
}
}
}

#endif /*MM_CUT_LEXER_WHITESPACE_SCANER_CPP_*/
