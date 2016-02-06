/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_lexer_WhitespaceScaner.cpp                            */
/* Description:     metamath whitespace scaner                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "lexer/mm_lexer.hpp"

namespace mm {
namespace lexer {

	/****************************
	 *		Public members
	 ****************************/

	inline
	WhitespaceScaner :: WhitespaceScaner (Source& source) :
	source_ (source),
	commentScaner_ (source_) {
	}
	WhitespaceScaner :: ~ WhitespaceScaner() {
	}

	void
	WhitespaceScaner :: scan()
	{
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
			++ source_;
		}
	}
	inline WhitespaceScaner :: Comments_&
	WhitespaceScaner :: comments() {
		return commentScaner_.comments();
	}

	// nstd :: Object implementation
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
	WhitespaceScaner :: show (nstd :: String<>&) const {
	}

	/****************************
	 *		Private members
	 ****************************/

	bool
	WhitespaceScaner :: commentBegins()
	{
		const char firstChar = source_.getChar().getValue (0);
		const char secondChar = source_.getChar().getValue (1);
		if  (firstChar == '$' && secondChar == '(') {
			++ source_;
			return true;
		}
		return false;
	}
}
}


