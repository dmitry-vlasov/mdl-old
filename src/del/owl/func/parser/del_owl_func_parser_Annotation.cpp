/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_func_parser_Annotation.cpp                       */
/* Description:     functional OWL2 annotation parser                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_FUNC_PARSER_ANNOTATION_CPP_
#define DEL_OWL_FUNC_PARSER_ANNOTATION_CPP_

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
	Annotation :: Annotation() :
	location_ (),
	annotation_ (NULL),
	string_1_ (INITIAL_STRING_CAPACITY),
	string_2_ (INITIAL_STRING_CAPACITY) {
	}
	Annotation :: ~ Annotation() {
	}

	const source :: Annotation*
	Annotation :: parse (Lexer* lexer)
	{
		location_ = lexer->getLocation();
		lexer->scan<Token :: OPEN_BRACKET>();
		lexer->scan<Token :: STRING>();
		string_1_.copy (lexer->getToken());
		lexer->scan<Token :: STRING>();
		string_2_.copy (lexer->getToken());
		lexer->scan<Token :: CLOSE_BRACKET>();
		annotation_ = new source :: Annotation (location_, string_1_, string_2_);
		return annotation_;
	}

	// object :: Object implementation
	void
	Annotation :: commitSuicide() {
		delete this;
	}
	Size_t
	Annotation :: getVolume() const
	{
		Size_t volume = 0;
		volume += string_1_.getVolume();
		volume += string_2_.getVolume();
		return volume;
	}
	Size_t
	Annotation :: getSizeOf() const {
		return sizeof (Annotation);
	}
	void
	Annotation :: show (String&) const {
	}
}
}
}
}

#endif /*DEL_OWL_FUNC_PARSER_ANNOTATION_CPP_*/
