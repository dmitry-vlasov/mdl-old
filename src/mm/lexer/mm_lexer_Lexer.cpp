/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_lexer_Lexer.cpp                                       */
/* Description:     metamath lexer class                                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_LEXER_LEXER_CPP_
#define MM_LEXER_LEXER_CPP_

#include "lexer/mm_lexer.hpp"

namespace mm {
namespace lexer {

	/****************************
	 *		Public members
	 ****************************/

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
		volume += source_.getVolume();
		volume += scaner_.getVolume();
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
}
}

#endif /*MM_LEXER_LEXER_CPP_*/
