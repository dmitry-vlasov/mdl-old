/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_parser_Formula.cpp                                   */
/* Description:     EL sourceula parser                                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_PARSER_FORMULA_CPP_
#define DEL_PARSER_FORMULA_CPP_

#include "del/lexer/del_lexer.hpp"
#include "del/source/del_source.hpp"
#include "del/parser/del_parser.hpp"

namespace del {
namespace parser {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Formula :: Formula() :
	termParser_ (new parser :: Term()),
	location_ (),
	term_1_ (NULL),
	term_2_ (NULL) {
	}
	Formula :: ~ Formula () {
		deleteAggregateObject (termParser_);
	}

	const del :: Formula*
	Formula :: parse (Lexer* lexer)
	{
		lexer->scanWhitespace();
		location_ = lexer->getLocation();
		term_1_ = termParser_->parse (lexer);
		if(term_1_ == NULL) {
			return NULL;
		}
		if (lexer->scan<Token :: SUBSET, Token :: EQUAL>() == Token :: SUBSET) {
			term_2_ = termParser_->parse (lexer);
			return new source :: formula :: Subset
			(
				location_,
				term_1_,
				term_2_,
				NULL,
				del :: Formula :: GENERAL_SUB_KIND,
				true,
				true
			);
		} else {
			term_2_ = termParser_->parse (lexer);
			return new source :: formula :: Identity
			(
				location_,
				term_1_,
				term_2_,
				NULL,
				true,
				true
			);
		}
		return NULL;
	}

	// object :: Object implementation
	void
	Formula :: commitSuicide() {
		delete this;
	}
	Size_t
	Formula :: getVolume() const {
		return getAggregateVolume (termParser_);
	}
	Size_t
	Formula :: getSizeOf() const {
		return sizeof (Formula);
	}
	void
	Formula :: show (String& string) const {
	}
}
}

#endif /*DEL_PARSER_FORMULA_CPP_*/
