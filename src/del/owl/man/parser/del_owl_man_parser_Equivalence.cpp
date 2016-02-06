/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_man_parser_Equivalence.cpp                       */
/* Description:     owl class equivalence parser                             */
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
	Equivalence :: Equivalence() :
	location_ (),
	equivalence_ (NULL),
	termParser_ (new parser :: Term()) {
	}
	Equivalence :: ~ Equivalence() {
		deleteAggregateObject (termParser_);
	}

	const source :: Equivalence*
	Equivalence :: parse (Lexer* lexer, const source :: Class* clas)
	{
		location_ = lexer->getLocation();
		equivalence_ = new source :: Equivalence (location_, clas);

		const del :: Term* term = termParser_->parse (lexer);
		equivalence_->addTerm (term);
		while (lexer->getTokenType() == Token :: COMMA) {
			term = termParser_->parse (lexer);
			equivalence_->addTerm (term);
		}
		return equivalence_;
	}

	// object :: Object implementation
	void
	Equivalence :: commitSuicide() {
		delete this;
	}
	Size_t
	Equivalence :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (termParser_);
		return volume;
	}
	Size_t
	Equivalence :: getSizeOf() const {
		return sizeof (Equivalence);
	}
	void
	Equivalence :: show (String&) const {
	}
}
}
}
}


