/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_func_parser_Namespace.cpp                        */
/* Description:     functional OWL2 namespace parser                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_FUNC_PARSER_NAMESPACE_CPP_
#define DEL_OWL_FUNC_PARSER_NAMESPACE_CPP_

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
	Namespace :: Namespace() :
	location_ (),
	namespace_ (NULL),
	string_ (INITIAL_STRING_CAPACITY) {
	}
	Namespace :: ~ Namespace() {
	}

	const source :: Namespace*
	Namespace :: parse (Lexer* lexer)
	{
		location_ = lexer->getLocation();
		lexer->scan<Token :: OPEN_BRACKET>();
		lexer->scan<Token :: STRING>();
		string_.copy (lexer->getToken());
		lexer->scan<Token :: CLOSE_BRACKET>();
		namespace_ = new source :: Namespace (location_, string_);
		return namespace_;
	}

	// object :: Object implementation
	void
	Namespace :: commitSuicide() {
		delete this;
	}
	Size_t
	Namespace :: getVolume() const
	{
		Size_t volume = 0;
		volume += string_.getVolume();
		return volume;
	}
	Size_t
	Namespace :: getSizeOf() const {
		return sizeof (Namespace);
	}
	void
	Namespace :: show (String&) const {
	}
}
}
}
}

#endif /*DEL_OWL_FUNC_PARSER_NAMESPACE_CPP_*/
