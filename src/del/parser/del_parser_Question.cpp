/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_parser_Question.cpp                                  */
/* Description:     question parser                                          */
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
	Question :: Question() :
	formulaParser_ (new parser :: Formula()),
	location_ (),
	theory_ (value :: undefined :: THEORY),
	formula_ (NULL),
	comments_ (NULL) {
	}
	Question :: ~ Question() {
		deleteAggregateObject (formulaParser_);
	}

	const del :: Question*
	Question :: parse (Lexer* lexer)
	{
		location_ = lexer->getLocation();
		theory_ = lexer->scanTheoryName();
		lexer->scan<Token :: MODELS>();
		comments_ =
			lexer->comments().isEmpty() ?
			NULL :
			new source :: Comments (lexer->comments());
		lexer->comments().clear();
		formula_ = formulaParser_->parse (lexer);
		lexer->scan<Token :: QUESTION>();
		lexer->comments().clear();
		return new source :: Question (location_, comments_, theory_, formula_);
	}

	// object :: Object implementation
	void
	Question :: commitSuicide() {
		delete this;
	}
	Size_t
	Question :: getVolume() const {
		return getAggregateVolume (formulaParser_);
	}
	Size_t
	Question :: getSizeOf() const {
		return sizeof (Question);
	}
	void
	Question :: show (String&) const {
	}
}
}


