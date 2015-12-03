/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_man_parser_Subclass.cpp                          */
/* Description:     manchester OWL subclass parser                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_MAN_PARSER_SUBCLASS_CPP_
#define DEL_OWL_MAN_PARSER_SUBCLASS_CPP_

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
	Subclass :: Subclass() :
	location_ (),
	subclass_ (NULL),
	termParser_ (new parser :: Term()) {
	}
	Subclass :: ~ Subclass() {
		deleteAggregateObject (termParser_);
	}

	const source :: Subclass*
	Subclass :: parse (Lexer* lexer, const source :: Class* clas)
	{
		location_ = lexer->getLocation();
		subclass_ = new source :: Subclass (location_, clas);

		const del :: Term* term = termParser_->parse (lexer);
		subclass_->addTerm (term);
		while (lexer->getTokenType() == Token :: COMMA) {
			term = termParser_->parse (lexer);
			subclass_->addTerm (term);
		}
		return subclass_;
	}

	// object :: Object implementation
	void
	Subclass :: commitSuicide() {
		delete this;
	}
	Size_t
	Subclass :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (termParser_);
		return volume;
	}
	Size_t
	Subclass :: getSizeOf() const {
		return sizeof (Subclass);
	}
	void
	Subclass :: show (String&) const {
	}
}
}
}
}

#endif /*DEL_OWL_MAN_PARSER_SUBCLASS_CPP_*/
