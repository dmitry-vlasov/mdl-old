/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_cut_lexer_Lexer.hpp                                   */
/* Description:     mm source file cutting lexer                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_CUT_LEXER_LEXER_CPP_
#define MM_CUT_LEXER_LEXER_CPP_

#include "mm/cut/lexer/mm_cut_lexer.hpp"

namespace mm {
namespace cut {
namespace lexer {

	/****************************
	 *		Public members
	 ****************************/

	inline const Source&
	Lexer :: getSource() const {
		return source_;
	}

using manipulator :: endLine;

	// object :: Object implementation
	void
	Lexer :: commitSuicide() {
		delete this;
	}
	Size_t
	Lexer :: getVolume() const
	{
		Size_t volume = 0;
		volume += whitespaceScaner_.getVolume();
		volume += source_.getVolume();
		volume += token_.getVolume();
		return volume;
	}
	Size_t
	Lexer :: getSizeOf() const {
		return sizeof (Lexer);
	}
	void
	Lexer :: show (nstd :: String<>&) const {
	}

	/****************************
	 *		Private members
	 ****************************/

	bool
	Lexer :: divisorBegins() const
	{
		const char char0 = source_.getChar().getValue (0);
		const char char1 = source_.getChar().getValue (1);
		const char char2 = source_.getChar().getValue (2);
		const char char3 = source_.getChar().getValue (3);
		if  (char0 == '$' && char1 == '(' && char2 == '\n' &&
			(char3 == '#' || char3 == '=')) {
			return true;
		}
		return false;
	}
	bool
	Lexer :: eofAtStart()
	{
		whitespaceScaner_.scan();
		source_.startToken();
		return source_.getChar().isEOF();
	}
	Token :: Type
	Lexer :: consume (const Token& token, short pos)
	{
		for (
				const char* str = token.getString() + pos;
				*str != chars :: NULL_CHAR;
				str ++
			)
		{
			const char ch = source_.getChar().getValue();
			++ source_;
			if (*str != ch) {
				return Token :: UNKNOWN;
			}
		}
		return token.getType();
	}

	Token :: Type
	Lexer :: finalize (const Token :: Type type) {
		source_.stopToken();
		return type;
	}
}
}
}

#endif /*MM_CUT_LEXER_LEXER_CPP_*/
