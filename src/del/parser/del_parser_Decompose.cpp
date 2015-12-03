/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_parser_Decompose.cpp                                 */
/* Description:     question parser                                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_PARSER_DECOMPOSE_CPP_
#define DEL_PARSER_DECOMPOSE_CPP_

#include "del/lexer/del_lexer.hpp"
#include "del/source/del_source.hpp"
#include "del/parser/del_parser.hpp"

namespace del {
namespace parser {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Decompose :: Decompose() :
	location_ (),
	theory_ (value :: undefined :: THEORY),
	signature_ (value :: undefined :: SIGNATURE),
	isStrong_ (false),
	comments_ (NULL) {
	}
	Decompose :: ~ Decompose() {
	}

	const del :: Decompose*
	Decompose :: parse (Lexer* lexer)
	{
		location_ = lexer->getLocation();
		isStrong_ = (lexer->scan<Token :: SIGNATURE, Token :: THEORY>() == Token :: THEORY);
		lexer->scan<Token :: OPEN_BRACKET>();
		theory_ = lexer->scanTheoryName();
		lexer->scan<Token :: COMMA>();
		signature_ = lexer->scanSignatureName();
		lexer->scan<Token :: CLOSE_BRACKET>();
		comments_ =
			lexer->comments().isEmpty() ?
			NULL :
			new source :: Comments (lexer->comments());
		lexer->comments().clear();
		return new source :: Decompose
		(
			location_,
			comments_,
			theory_,
			signature_,
			isStrong_
		);
	}

	// object :: Object implementation
	void
	Decompose :: commitSuicide() {
		delete this;
	}
	Size_t
	Decompose :: getVolume() const {
		return 0;
	}
	Size_t
	Decompose :: getSizeOf() const {
		return sizeof (Decompose);
	}
	void
	Decompose :: show (String&) const {
	}
}
}

#endif /*DEL_PARSER_DECOMPOSE_CPP_*/
