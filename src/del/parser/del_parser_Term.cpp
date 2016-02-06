/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_parser_Term.cpp                                      */
/* Description:     EL term parser                                           */
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
	Term :: Term() :
	termParser_ (NULL),
	location_ (),
	variable_ (value :: undefined :: VARIABLE),
	relation_ (value :: undefined :: RELATION),
	signature_ (value :: undefined :: SIGNATURE),
	term_ (NULL),
	term_1_ (NULL),
	term_2_ (NULL),
	terms_ (INITIAL_TERM_VECTOR_CAPACITY) {
	}
	Term :: ~ Term ()
	{
		for (value :: Integer i = 0; i < terms_.getCapacity(); ++ i) {
			terms_[i] = NULL;
		}
		deleteAggregateObject (termParser_);
	}

	const del :: Term*
	Term :: parse (Lexer* lexer)
	{
		location_ = lexer->getLocation();
		terms_.clear();
		const Token :: Type
			token = lexer->scan
			<
				Token :: EXISTS,
				Token :: OPEN_BRACKET,
				Token :: TOP,
				Token :: NAME,
				Token :: COPY,
				Token :: CLOSE_BRACE
			>();
		switch (token) {
		case Token :: EXISTS : {
			relation_ = lexer->scanRelationName();
			lexer->scan<Token :: DOT>();
			if (termParser_ == NULL) {
				termParser_ = new parser :: Term();
			}
			const del :: Term* const
				term = termParser_->parse (lexer);
			terms_.add (term);
			term_ = new source :: term :: Exists (location_, relation_, terms_);
			terms_.clear();
			return term_;
		}
		case Token :: OPEN_BRACKET : {
			if (termParser_ == NULL) {
				termParser_ = new parser :: Term();
			}
			while (true) {
				const del :: Term* const
					term = termParser_->parse (lexer);
				terms_.add (term);
				if (lexer->scan<Token :: INTERSECT, Token :: CLOSE_BRACKET>() == Token :: CLOSE_BRACKET) {
					break;
				}
			}
			if (terms_.getSize() < 2) {
				return NULL;
			}
			term_ = new source :: term :: Intersect (location_, terms_);
			terms_.clear();
			return term_;
		}
		case Token :: TOP : {
			term_ = new source :: term :: Top (location_);
			return term_;
		}
		case Token :: NAME : {
			variable_ = Table :: variables()->add (lexer->getToken());
			term_ = new source :: term :: Variable (location_, variable_);
			return term_;
		}
		case Token :: COPY : {
			lexer->scan<Token :: OPEN_BRACKET>();
			if (termParser_ == NULL) {
				termParser_ = new parser :: Term();
			}
			const del :: Term* const
				term = termParser_->parse (lexer);
			lexer->scan<Token :: COMMA>();
			signature_ = lexer->scanSignatureName();
			lexer->scan<Token :: CLOSE_BRACKET>();
			const del :: Signature* const
				sign = Math :: signatures()->get (signature_);
			del :: Expansion* const
				expansion = new source :: Expansion<> (sign);
			const_cast<del :: Term*>(term)->makeDeltaCopy (expansion);
			expansion->commitSuicide();
			return term;
		}
		case Token :: CLOSE_BRACE :
		default :
			return NULL;
		}
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
		volume += getAggregateVolume (termParser_);
		volume += terms_.getRawVolume();
		return volume;
	}
	Size_t
	Term :: getSizeOf() const {
		return sizeof (Term);
	}
	void
	Term :: show (String& string) const {
	}
}
}


