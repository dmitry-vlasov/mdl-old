/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_func_parser_Prefix.cpp                           */
/* Description:     functional OWL2 prefix parser                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_FUNC_PARSER_PREFIX_CPP_
#define DEL_OWL_FUNC_PARSER_PREFIX_CPP_

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
	Prefix :: Prefix() :
	location_ (),
	annotation_ (NULL),
	string_ (INITIAL_STRING_CAPACITY) {
	}
	Prefix :: ~ Prefix() {
	}

	const source :: Prefix*
	Prefix :: parse (Lexer* lexer)
	{
		location_ = lexer->getLocation();
		lexer->scan<Token :: OPEN_BRACKET>();
		lexer->scan<Token :: STRING>();
		string_.copy (lexer->getToken());
		lexer->scan<Token :: CLOSE_BRACKET>();
		annotation_ = new source :: Prefix (location_, string_);
		return annotation_;
	}

	// object :: Object implementation
	void
	Prefix :: commitSuicide() {
		delete this;
	}
	Size_t
	Prefix :: getVolume() const
	{
		Size_t volume = 0;
		volume += string_.getVolume();
		return volume;
	}
	Size_t
	Prefix :: getSizeOf() const {
		return sizeof (Prefix);
	}
	void
	Prefix :: show (String&) const {
	}
}
}
}
}

#endif /*DEL_OWL_FUNC_PARSER_PREFIX_CPP_*/
