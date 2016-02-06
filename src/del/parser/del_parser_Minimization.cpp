/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_parser_Minimization.cpp                              */
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
	Minimization :: Minimization() :
	location_ (),
	theory_ (value :: undefined :: THEORY),
	minimization_ (value :: undefined :: THEORY),
	comments_ (NULL) {
	}
	Minimization :: ~ Minimization() {
	}

	const del :: Minimization*
	Minimization :: parse (Lexer* lexer)
	{
		location_ = lexer->getLocation();
		theory_ = lexer->scanTheoryName();
		lexer->scan<Token :: EQUALITY>();
		lexer->scan<Token :: OPEN_BRACKET>();
		minimization_ = lexer->scanTheoryName();
		comments_ =
			lexer->comments().isEmpty() ?
			NULL :
			new source :: Comments (lexer->comments());
		lexer->comments().clear();
		return new source :: Minimization
		(
			location_,
			comments_,
			theory_,
			minimization_
		);
	}

	// object :: Object implementation
	void
	Minimization :: commitSuicide() {
		delete this;
	}
	Size_t
	Minimization :: getVolume() const {
		return 0;
	}
	Size_t
	Minimization :: getSizeOf() const {
		return sizeof (Minimization);
	}
	void
	Minimization :: show (String&) const {
	}
}
}


