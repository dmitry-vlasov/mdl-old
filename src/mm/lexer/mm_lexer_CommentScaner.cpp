/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_lexer_CommentScaner.cpp                               */
/* Description:     metamath comment scaner                                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "auxiliary/mm_auxiliary.hpp"
#include "lexer/mm_lexer.hpp"

namespace mm {
namespace lexer {

	/****************************
	 *		Public members
	 ****************************/

	inline
	CommentScaner :: CommentScaner (Source& source) :
	source_ (source),
	comments_ () {
	}
	CommentScaner :: ~ CommentScaner() {
	}

	void
	CommentScaner :: scan()
	{
		Comment_* const
			comment = Config :: removeComments() ? NULL : comments_.push();
		++ source_;
		while (true) {
			const char ch = source_.getChar().getValue();
			switch (ch) {
			case '$' : {
				++ source_;
				const char ch_1 = source_.getChar().getValue();
				if (ch_1 == ')') {
					++ source_;
					return;
				}
				if (!Config :: removeComments()) {
					*comment << source_.getChar().getValue();
				}
				break;
			}
			case chars :: NULL_CHAR :
				throw new Error (Error :: LEXER, "end of file reached within the comment.\n");
			}
			if (!Config :: removeComments()) {
				*comment << source_.getChar().getValue();
			}
			++ source_;
		}
	}
	inline CommentScaner :: Comments_&
	CommentScaner :: comments() {
		return comments_;
	}

	// nstd :: Object implementation
	void
	CommentScaner :: commitSuicide() {
		delete this;
	}
	Size_t
	CommentScaner :: getVolume() const {
		return comments_.getVolume();
	}
	Size_t
	CommentScaner :: getSizeOf() const {
		return sizeof (CommentScaner);
	}
	void
	CommentScaner :: show (nstd :: String<>&) const {
	}
}
}


