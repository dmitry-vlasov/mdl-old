/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_func_parser_EqClasses.cpp                        */
/* Description:     functional OWL2 equivalent classes parser                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

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
	EqClasses :: EqClasses() :
	location_ (),
	termParser_ (new parser :: Term()) {
	}
	EqClasses :: ~ EqClasses() {
		deleteAggregateObject (termParser_);
	}

	const del :: Formula*
	EqClasses :: parse (Lexer* lexer)
	{
		location_ = lexer->getLocation();
		lexer->scan<Token :: OPEN_BRACKET>();
		const del :: Term* term_1 = termParser_->parse (lexer);
		const del :: Term* term_2 = termParser_->parse (lexer);
		lexer->scan<Token :: CLOSE_BRACKET>();
		return new del :: source :: formula :: Identity (location_, term_1, term_2);
	}

	// object :: Object implementation
	void
	EqClasses :: commitSuicide() {
		delete this;
	}
	Size_t
	EqClasses :: getVolume() const {
		return getAggregateVolume (termParser_);
	}
	Size_t
	EqClasses :: getSizeOf() const {
		return sizeof (EqClasses);
	}
	void
	EqClasses :: show (String&) const {
	}
}
}
}
}


