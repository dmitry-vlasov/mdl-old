/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_parser_Answer.cpp                                    */
/* Description:     answer parser                                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/lexer/del_lexer.hpp"
#include "del/source/del_source.hpp"
#include "del/parser/del_parser.hpp"

namespace del {
namespace parser {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Answer :: Answer() :
	formulaParser_ (new parser :: Formula()),
	location_ (),
	theory_ (value :: undefined :: THEORY),
	formula_ (NULL),
	comments_ (NULL) {
	}
	Answer :: ~ Answer() {
		deleteAggregateObject (formulaParser_);
	}

	const del :: Answer*
	Answer :: parse (Lexer* lexer)
	{
		location_ = lexer->getLocation();
		theory_ = lexer->scanTheoryName();
		const bool
			positive = (lexer->scan<Token :: MODELS, Token :: DOES_NOT_MODEL>() == Token :: MODELS);
		comments_ =
			lexer->comments().isEmpty() ?
			NULL :
			new source :: Comments (lexer->comments());
		lexer->comments().clear();
		formula_ = formulaParser_->parse (lexer);
		lexer->scan<Token :: ASSERTION>();
		lexer->comments().clear();
		return new source :: Answer (location_, comments_, theory_, positive, formula_);
	}

	// object :: Object implementation
	void
	Answer :: commitSuicide() {
		delete this;
	}
	Size_t
	Answer :: getVolume() const {
		return getAggregateVolume (formulaParser_);
	}
	Size_t
	Answer :: getSizeOf() const {
		return sizeof (Answer);
	}
	void
	Answer :: show (String&) const {
	}
}
}


