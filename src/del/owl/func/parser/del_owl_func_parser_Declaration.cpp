/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_func_parser_Declaration.cpp                      */
/* Description:     functional OWL2 declaration parser                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_FUNC_PARSER_DECLARATION_CPP_
#define DEL_OWL_FUNC_PARSER_DECLARATION_CPP_

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
	Declaration :: Declaration() :
	location_ (),
	declaration_ (NULL),
	name_ (INITIAL_NAME_CAPACITY) {
	}
	Declaration :: ~ Declaration() {
	}

	const source :: Declaration*
	Declaration :: parse (Lexer* lexer)
	{
		location_ = lexer->getLocation();
		lexer->scan<Token :: OPEN_BRACKET>();
		const Token :: Type
			tokenType = lexer->scan
			<
				Token :: CLASS,
				Token :: OBJECT_PROPERTY,
				Token :: ANNOTATION_PROPERTY
			>();
		lexer->scan<Token :: OPEN_BRACKET>();
		lexer->scan<Token :: STRING>();
		name_.copy (lexer->getToken());
		lexer->scan<Token :: CLOSE_BRACKET>();
		lexer->scan<Token :: CLOSE_BRACKET>();
		switch (tokenType) {
		case Token :: CLASS :
			declaration_ = new source :: Declaration (location_, source :: Declaration :: CLASS, name_); break;
		case Token :: OBJECT_PROPERTY :
			declaration_ = new source :: Declaration (location_, source :: Declaration :: OBJECT_PROPERTY, name_); break;
		case Token :: ANNOTATION_PROPERTY :
			declaration_ = new source :: Declaration (location_, source :: Declaration :: ANNOTATION_PROPERTY, name_); break;
		}
		return declaration_;
	}

	// object :: Object implementation
	void
	Declaration :: commitSuicide() {
		delete this;
	}
	Size_t
	Declaration :: getVolume() const
	{
		Size_t volume = 0;
		volume += name_.getVolume();
		return volume;
	}
	Size_t
	Declaration :: getSizeOf() const {
		return sizeof (Declaration);
	}
	void
	Declaration :: show (String&) const {
	}
}
}
}
}

#endif /*DEL_OWL_FUNC_PARSER_DECLARATION_CPP_*/
