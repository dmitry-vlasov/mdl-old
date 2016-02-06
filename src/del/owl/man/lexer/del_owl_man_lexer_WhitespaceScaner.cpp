/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_man_lexer_WhitespaceScaner.cpp                   */
/* Description:     whitespace scaner                                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/owl/man/lexer/del_owl_man_lexer.hpp"

namespace del {
namespace owl {
namespace man {
namespace lexer {

	/****************************
	 *		Public members
	 ****************************/

	inline
	WhitespaceScaner :: WhitespaceScaner (Source& source) :
	source_ (source),
	commentScaner_ (source_),
	emptyline_ (false) {
	}
	WhitespaceScaner :: ~ WhitespaceScaner() {
	}

	void
	WhitespaceScaner :: scan()
	{
		emptyline_ = false;
		while (true) {
			if (commentBegins()) {
				commentScaner_.scan();
				continue;
			}
			if (source_.getChar().isEOF()) {
				return;
			}
			if (!source_.getChar().isWhitespace()) {
				return;
			}
			const bool endline_1 = source_.getChar().isNewLine();
			++ source_;
			const bool endline_2 = source_.getChar().isNewLine();
			emptyline_ = emptyline_ || (endline_1 && endline_2);
		}
	}
	inline bool
	WhitespaceScaner :: emptyline() const {
		return emptyline_;
	}
	inline WhitespaceScaner :: Comments_&
	WhitespaceScaner :: comments() {
		return commentScaner_.comments();
	}

	// object :: Object implementation
	void
	WhitespaceScaner :: commitSuicide() {
		delete this;
	}
	Size_t
	WhitespaceScaner :: getVolume() const {
		return commentScaner_.getVolume();
	}
	Size_t
	WhitespaceScaner :: getSizeOf() const {
		return sizeof (WhitespaceScaner);
	}
	void
	WhitespaceScaner :: show (String&) const {
	}

	/****************************
	 *		Private members
	 ****************************/

	bool
	WhitespaceScaner :: commentBegins()
	{
		if  (source_.getChar() == '/') {
			if (source_.getChar().getValue(1) == '*') {
				++ source_;
				return true;
			}
			if (source_.getChar().getValue(1) == '/') {
				++ source_;
				return true;
			}
			return false;
		}
		return false;
	}
}
}
}
}


