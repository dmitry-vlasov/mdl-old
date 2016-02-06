/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_lexer_Char.cpp                                      */
/* Description:     lexer char wrapper                                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace nstd {
namespace lexer {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Char :: Char () :
	char_ (NULL) {
	}
	inline
	Char :: Char (const char* const ch) :
	char_ (ch) {
	}
	inline
	Char :: Char (const Char& ch) :
	char_ (ch.char_) {
	}

	inline char
	Char :: getValue (const Ptrdiff_t dist) const {
		return *(char_ + dist);
	}
	inline const char*
	Char :: getString() const {
		return char_;
	}

	inline bool
	Char :: isAlphabet() const
	{
		const char ch = getValue();
		const bool upperCaseLiteral = ('A' <= ch) && (ch <= 'Z');
		const bool lowerCaseLiteral = ('a' <= ch) && (ch <= 'z');
		const bool underline = (ch == chars :: UNDERLINE);
		return (lowerCaseLiteral || upperCaseLiteral || underline);
	}
	inline bool
	Char :: isAlphaNumeric () const {
		return isNumber() || isAlphabet ();
	}
	inline bool
	Char :: isWhitespace() const {
		const char ch = getValue();
		return (0 <= ch) && (ch <= chars :: SPACE);
	}
	inline bool
	Char :: isNumber() const {
		const char ch = getValue();
		return ('0' <= ch) && (ch <= '9');
	}
	inline bool
	Char :: isEOF() const {
		return (getValue() == chars :: NULL_CHAR);
	}
	inline bool
	Char :: isNewLine() const {
		return (getValue() == chars :: NEW_LINE);
	}

	inline void
	Char :: operator ++ () {
		++ char_;
	}
	inline void
	Char :: operator = (const Char& ch) {
		char_ = ch.char_;
	}
	inline bool
	Char :: operator == (const Char& ch) const {
		return (char_ == ch.char_);
	}
	inline bool
	Char :: operator != (const Char& ch) const {
		return !(operator == (ch));
	}
	inline bool
	Char :: operator == (const char ch) const {
		return (ch == *char_);
	}
	inline bool
	Char :: operator != (const char ch) const {
		return !(operator == (ch));
	}

using manipulator :: space;
using manipulator :: tab;
using manipulator :: endLine;

	// nstd :: Object implementation
	Size_t 
	Char :: getVolume() const {
		return 0;
	}
	Size_t 
	Char :: getSizeOf() const {
		return sizeof (Char);
	}
	void 
	Char :: show (String<>& string) const
	{
		string << "char:"  << tab << getValue() << endLine;
		string << "string:" << tab << char_ << endLine;
	}
}
}


