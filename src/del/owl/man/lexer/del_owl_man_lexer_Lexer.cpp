/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_man_lexer_Lexer.cpp                              */
/* Description:     OWL manchester lexer class                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_MAN_LEXER_OWL_LEXER_CPP_
#define DEL_OWL_MAN_LEXER_OWL_LEXER_CPP_

#include "del/owl/man/lexer/del_owl_man_lexer.hpp"

namespace del {
namespace owl {
namespace man {
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
}
}
}
}

#endif /*DEL_OWL_MAN_LEXER_OWL_LEXER_CPP_*/
