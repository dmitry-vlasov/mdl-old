/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_lexer_Scaner.cpp                                     */
/* Description:     general scaner                                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_LEXER_SCANER_CPP_
#define MDL_LEXER_SCANER_CPP_

#include "mdl/lexer/mdl_lexer.hpp"

namespace mdl {
namespace lexer {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Scaner :: Scaner (Source& source) :
	source_ (source),
	horisontalBarScaner_ (source),
	literalScaner_ (source_),
	nameScaner_ (source_),
	numberScaner_ (source_),
	realScaner_ (source_),
	whitespaceScaner_ (source_),
	inExpression_ (false) {
	}
	Scaner :: ~ Scaner() {
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

#endif /*MDL_LEXER_SCANER_CPP_*/
