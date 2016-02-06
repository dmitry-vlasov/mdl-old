/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_func_parser_Term.cpp                             */
/* Description:     functional OWL2 term parser                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/source/term/del_source_term.hpp"
#include "del/owl/func/lexer/del_owl_func_lexer.hpp"
#include "del/owl/func/source/del_owl_func_source.hpp"
#include "del/owl/func/parser/del_owl_func_parser.hpp"

namespace del {
namespace owl {
namespace func {
namespace parser {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Term :: Term() :
	location_ (),
	name_ (INITIAL_NAME_CAPACITY),
	term_ (NULL),
	subterms_ (INITIAL_SUBTERMS_CAPACITY),
	termParser_ (NULL) {
	}
	Term :: ~ Term()
	{
		for (value :: Integer i = 0; i < subterms_.getCapacity(); ++ i) {
			subterms_[i] = NULL;
		}
		deleteAggregateObject (termParser_);
	}

	const del :: Term*
	Term :: parse (Lexer* lexer)
	{
		lexer->scan
		<
			Token :: CLOSE_BRACKET,
			Token :: OBJECT_SOME_VALUES_FROM,
			Token :: OBJECT_INTERSECTION_OF,
			Token :: OWL_THING,
			Token :: STRING
		>();
		switch (lexer->getTokenType()) {
		case Token :: CLOSE_BRACKET :
			return NULL;
		case Token :: OBJECT_SOME_VALUES_FROM : {
			lexer->scan<Token :: OPEN_BRACKET>();
			lexer->scan<Token :: STRING>();
			String name;
			name.copy (lexer->getToken());
			const value :: Relation
				relation = Table :: relations()->add (name);
			if (termParser_ == NULL) {
				termParser_ = new parser :: Term();
			}
			const del :: Term*
				subterm = termParser_->parse (lexer);
			term_ = new del :: source :: term :: Exists
				(
					location_,
					relation,
					subterm
				);
			lexer->scan<Token :: CLOSE_BRACKET>();
			break;
		}
		case Token :: OBJECT_INTERSECTION_OF : {
			lexer->scan<Token :: OPEN_BRACKET>();
			if (termParser_ == NULL) {
				termParser_ = new parser :: Term();
			}
			subterms_.clear();
			while (true) {
				const del :: Term*
					term = termParser_->parse (lexer);
				if (term == NULL) {
					break;
				}
				subterms_.add (term);
			}
			term_ = new del :: source :: term :: Intersect (location_, subterms_);
			subterms_.clear();
			break;
		}
		case Token :: OWL_THING : {
			term_ = new del :: source :: term :: Top (location_);
			break;
		}
		case Token :: STRING : {
			String name;
			name.copy (lexer->getToken());
			const value :: Variable
				variable = Table :: variables()->add (name);
			term_ = new del :: source :: term :: Variable (location_, variable);
			break;
		}
		}
		return term_;
	}

	// object :: Object implementation
	void
	Term :: commitSuicide() {
		delete this;
	}
	Size_t
	Term :: getVolume() const
	{
		Size_t volume = 0;
		volume += name_.getVolume();
		volume += subterms_.getRawVolume();
		volume += getAggregateVolume (termParser_);
		return volume;
	}
	Size_t
	Term :: getSizeOf() const {
		return sizeof (Term);
	}
	void
	Term :: show (String&) const {
	}

	/****************************
	 *		Private members
	 ****************************/


}
}
}
}


