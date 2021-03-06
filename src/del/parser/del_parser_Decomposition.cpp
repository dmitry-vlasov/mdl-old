/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_parser_Decomposition.cpp                             */
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
	Decomposition :: Decomposition() :
	location_ (),
	theory_ (value :: undefined :: THEORY),
	signature_ (value :: undefined :: SIGNATURE),
	components_ (INITIAL_COMPONENTS_CAPACITY),
	isStrong_ (false),
	comments_ (NULL) {
	}
	Decomposition :: ~ Decomposition() {
	}

	const del :: Decomposition*
	Decomposition :: parse (Lexer* lexer)
	{
		location_ = lexer->getLocation();
		isStrong_ = (lexer->scan<Token :: SIGNATURE, Token :: THEORY>() == Token :: THEORY);
		lexer->scan<Token :: OPEN_BRACKET>();
		theory_ = lexer->scanTheoryName();
		lexer->scan<Token :: COMMA>();
		signature_ = lexer->scanSignatureName();
		lexer->scan<Token :: CLOSE_BRACKET>();
		lexer->scan<Token :: EQUALITY>();
		lexer->scan<Token :: OPEN_BRACKET>();
		components_.clear();
		while (true) {
			if (isStrong_) {
				const value :: Theory
					th = lexer->scanTheoryName();
				components_.add (th);
			} else {
				const value :: Signature
					sign = lexer->scanSignatureName();
				components_.add (sign);
			}
			if (lexer->scan<Token :: UNION, Token :: CLOSE_BRACKET>() == Token :: CLOSE_BRACKET) {
				break;
			}
		}
		comments_ =
			lexer->comments().isEmpty() ?
			NULL :
			new source :: Comments (lexer->comments());
		lexer->comments().clear();
		return new source :: Decomposition
		(
			location_,
			comments_,
			theory_,
			signature_,
			components_,
			isStrong_
		);
	}

	// object :: Object implementation
	void
	Decomposition :: commitSuicide() {
		delete this;
	}
	Size_t
	Decomposition :: getVolume() const {
		return components_.getVolume();
	}
	Size_t
	Decomposition :: getSizeOf() const {
		return sizeof (Decomposition);
	}
	void
	Decomposition :: show (String&) const {
	}
}
}


