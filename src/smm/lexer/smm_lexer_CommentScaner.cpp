/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_lexer_CommentScaner.cpp                              */
/* Description:     smm comment scaner                                       */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_LEXER_COMMENT_SCANER_CPP_
#define SMM_LEXER_COMMENT_SCANER_CPP_

#include "smm/lexer/smm_lexer.hpp"

namespace smm {
namespace lexer {

	/****************************
	 *		Public members
	 ****************************/

	inline
	CommentScaner :: CommentScaner (Source& source) :
	source_ (source) {
	}
	CommentScaner :: ~ CommentScaner() {
	}

	void
	CommentScaner :: scan()
	{
		++ source_;
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
				break;
			}
			case chars :: NULL_CHAR :
				throw new Error (Error :: LEXER, "end of file reached within the comment.\n");
			}
			++ source_;
		}
	}

	// nstd :: Object implementation
	void
	CommentScaner :: commitSuicide() {
		delete this;
	}
	Size_t
	CommentScaner :: getVolume() const {
		return 0;
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

#endif /*SMM_LEXER_COMMENT_SCANER_CPP_*/
