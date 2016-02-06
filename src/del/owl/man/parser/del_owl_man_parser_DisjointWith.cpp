/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_man_parser_DisjointWith.cpp                      */
/* Description:     owl disjoint with class substrusture parser              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/owl/man/lexer/del_owl_man_lexer.hpp"
#include "del/owl/man/source/del_owl_man_source.hpp"
#include "del/owl/man/parser/del_owl_man_parser.hpp"

namespace del {
namespace owl {
namespace man {
namespace parser {

	/****************************
	 *		Public members
	 ****************************/

	inline
	DisjointWith :: DisjointWith() :
	location_ (),
	termParser_ (new parser :: Term()) {
	}
	DisjointWith :: ~ DisjointWith() {
		deleteAggregateObject (termParser_);
	}

	void
	DisjointWith :: parse (Lexer* lexer, const source :: Class* clas)
	{
		location_ = lexer->getLocation();
		const del :: Term* term = termParser_->parse (lexer);
		deleteObject (term);
		while (lexer->getTokenType() == Token :: COMMA) {
			term = termParser_->parse (lexer);
			deleteObject (term);
		}
	}

	// object :: Object implementation
	void
	DisjointWith :: commitSuicide() {
		delete this;
	}
	Size_t
	DisjointWith :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (termParser_);
		return volume;
	}
	Size_t
	DisjointWith :: getSizeOf() const {
		return sizeof (DisjointWith);
	}
	void
	DisjointWith :: show (String&) const {
	}
}
}
}
}


