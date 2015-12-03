/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_parser_Minimize.cpp                                  */
/* Description:     question parser                                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_PARSER_MINIMIZE_CPP_
#define DEL_PARSER_MINIMIZE_CPP_

#include "del/lexer/del_lexer.hpp"
#include "del/source/del_source.hpp"
#include "del/parser/del_parser.hpp"

namespace del {
namespace parser {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Minimize :: Minimize() :
	location_ (),
	theory_ (value :: undefined :: THEORY),
	comments_ (NULL) {
	}
	Minimize :: ~ Minimize() {
	}

	const del :: Minimize*
	Minimize :: parse (Lexer* lexer)
	{
		location_ = lexer->getLocation();
		lexer->scan<Token :: OPEN_BRACKET>();
		theory_ = lexer->scanTheoryName();
		lexer->scan<Token :: CLOSE_BRACKET>();
		comments_ =
			lexer->comments().isEmpty() ?
			NULL :
			new source :: Comments (lexer->comments());
		lexer->comments().clear();
		return new source :: Minimize
		(
			location_,
			comments_,
			theory_
		);
	}

	// object :: Object implementation
	void
	Minimize :: commitSuicide() {
		delete this;
	}
	Size_t
	Minimize :: getVolume() const {
		return 0;
	}
	Size_t
	Minimize :: getSizeOf() const {
		return sizeof (Minimize);
	}
	void
	Minimize :: show (String&) const {
	}
}
}

#endif /*DEL_PARSER_MINIMIZE_CPP_*/
