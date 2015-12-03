/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_func_lexer_CommentScaner.cpp                     */
/* Description:     owl comment scaner                                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_FUNC_LEXER_COMMENT_SCANER_CPP_
#define DEL_OWL_FUNC_LEXER_COMMENT_SCANER_CPP_

#include "del/auxiliary/del_auxiliary.hpp"
#include "del/lexer/del_lexer.hpp"

namespace del {
namespace owl {
namespace func {
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
		const bool
			multiLine = (source_.getChar() == '*');
		++ source_;

		while (true) {
			switch (source_.getChar().getValue()) {
			case chars :: NEW_LINE :
				if (!multiLine) {
					++ source_;
					return;
				}
				break;
			case '*' : {
				const char ch = source_.getChar().getValue (1);
				if (ch == chars :: NULL_CHAR) {
					++ source_;
					return;
				}
				const bool endComment =
					(multiLine && (ch == '/')) ||
					(!multiLine && (ch == chars :: NEW_LINE));
				if (endComment) {
					++ source_;
					++ source_;
					return;
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

	// object :: Object implementation
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
	CommentScaner :: show (String&) const {
	}
}
}
}
}

#endif /*DEL_OWL_FUNC_LEXER_COMMENT_SCANER_CPP_*/
