/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_lexer_Lexer.cpp                                      */
/* Description:     lexer class                                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_LEXER_LEXER_CPP_
#define MDL_LEXER_LEXER_CPP_

#include "mdl/lexer/mdl_lexer.hpp"

namespace mdl {
namespace lexer {

	/****************************
	 *		Public members
	 ****************************/

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
	Lexer :: show (String&) const {
	}

	/************************************
	 *		Static private attributes
	 ************************************/

	//Position Lexer :: previous_;
	//Position Lexer :: current_;
	//Position Lexer :: lookup_;
}
}

#endif /*MDL_LEXER_LEXER_CPP_*/
