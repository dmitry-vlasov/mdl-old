/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_func_parser_Unrecognized.cpp                     */
/* Description:     functional OWL2 parser for unrecognized objects          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_FUNC_PARSER_UNRECOGNIZED_CPP_
#define DEL_OWL_FUNC_PARSER_UNRECOGNIZED_CPP_

#include "del/owl/func/lexer/del_owl_func_lexer.hpp"
#include "del/owl/func/source/del_owl_func_source.hpp"
#include "del/owl/func/parser/del_owl_func_parser.hpp"

namespace del {
namespace owl {
namespace func {
namespace parser {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Unrecognized :: Unrecognized() :
	location_ (),
	unrecognized_ (NULL),
	stringVector_ (INITIAL_STRING_VECTOR_CAPACITY) {
	}
	Unrecognized :: ~ Unrecognized() {
	}

	const source :: Unrecognized*
	Unrecognized :: parse (const String& name, Lexer* lexer)
	{
		location_ = lexer->getLocation();
		lexer->scan<Token :: OPEN_BRACKET>();
		stringVector_.clear();
		while (true) {
			if (lexer->scanUnrecognized() == Token :: CLOSE_BRACKET) {
				break;
			}
			String* string = stringVector_.push();
			string->copy (lexer->getToken());
		}
		unrecognized_ = new source :: Unrecognized (location_, name, stringVector_);
		return unrecognized_;
	}

	// object :: Object implementation
	void
	Unrecognized :: commitSuicide() {
		delete this;
	}
	Size_t
	Unrecognized :: getVolume() const
	{
		Size_t volume = 0;
		volume += stringVector_.getVolume();
		return volume;
	}
	Size_t
	Unrecognized :: getSizeOf() const {
		return sizeof (Unrecognized);
	}
	void
	Unrecognized :: show (String&) const {
	}
}
}
}
}

#endif /*DEL_OWL_FUNC_PARSER_UNRECOGNIZED_CPP_*/
