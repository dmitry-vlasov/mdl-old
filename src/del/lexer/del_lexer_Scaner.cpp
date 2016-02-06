/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_lexer_Scaner.cpp                                     */
/* Description:     general scaner                                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/lexer/del_lexer.hpp"

namespace del {
namespace lexer {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Scaner :: Scaner (Source& source) :
	source_ (source),
	nameScaner_ (source_),
	pathScaner_ (source_),
	whitespaceScaner_ (source_),
	inExpression_ (false) {
	}
	Scaner :: ~ Scaner() {
	}

	inline Scaner :: Comments_&
	Scaner :: comments() {
		return whitespaceScaner_.comments();
	}
	inline void
	Scaner :: scanComments() {
		whitespaceScaner_.scan();
	}
	inline void
	Scaner :: scanWhitespace() {
		whitespaceScaner_.scan();
	}


	// object :: Object implementation
	void
	Scaner :: commitSuicide() {
		delete this;
	}
	Size_t
	Scaner :: getVolume() const
	{
		Size_t volume = 0;
		volume += whitespaceScaner_.getVolume();
		return volume;
	}
	Size_t
	Scaner :: getSizeOf() const {
		return sizeof (Scaner);
	}
	void
	Scaner :: show (String&) const {
	}

	/****************************
	 *		Private members
	 ****************************/

	bool
	Scaner :: eofAtStart()
	{
		whitespaceScaner_.scan();
		source_.startToken();
		return source_.getChar().isEOF();
	}
	bool
	Scaner :: lookahead (const Token& token, short pos)
	{
		int i = 0;
		for (
				const char* str = token.getString() + pos;
				*str != chars :: NULL_CHAR;
				str ++
			)
		{
			const char ch = source_.getChar().getValue (i ++);
			if (source_.getChar().isWhitespace() || (*str != ch)) {
				return false;
			}
			if (*str != ch) {
				return false;
			}
		}
		return true;
	}

	Token :: Type
	Scaner :: consume (const Token& token, short pos)
	{
		for (
				const char* str = token.getString() + pos;
				*str != chars :: NULL_CHAR;
				str ++
			)
		{
			const char ch = source_.getChar().getValue();
			if (source_.getChar().isWhitespace() || (*str != ch)) {
				return nameScaner_.scan();
			}
			++ source_;
			if (*str != ch) {
				return nameScaner_.scan();
			}
		}
		return token.getType();
	}

	Token :: Type
	Scaner :: finalize (const Token :: Type type) {
		source_.stopToken();
		return type;
	}
}
}


