/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_evaluation_Case.cpp                           */
/* Description:     FRiS case parameter parser                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/lexer/mdl_lexer.hpp"
#include "mdl/form/mdl_form.hpp"
#include "mdl/parser/mdl_parser.hpp"

namespace mdl {
namespace parser {
namespace evaluation {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Case :: Case() :
	identificatorParser_ (new parser :: Identificator()),
	location_ (),
	sign_ (true),
	identificator_ (NULL),
	name_ (value :: undefined :: NAME),
	path_ (INITIAL_PATH_CAPACITY) {
	}
	Case :: ~ Case() {
		deleteAggregateObject (identificatorParser_);
	}

using manipulator :: endLine;

	mdl :: evaluation :: Case*
	Case :: parse
	(
		Lexer* lexer,
		bool& sign,
		const bool firstPass,
		mdl :: Theory* theory
	)
	{
		/* Example:
		 *
			+ theorem xxx proof pr1 step 8
			+ theorem xxx.yyy.zzz proof pr1 step (15.23.4)
			- theorem xxx.yyy proof prf2 step (28.5)
			- theorem zzz.yyy proof 3 step 7
		 */
		location_ = lexer->getLocation();
		lexer->scan<Token :: PLUS, Token :: MINUS, Token :: CLOSE_SQ_BRACKET>();
		if (lexer->getTokenType() == Token :: CLOSE_SQ_BRACKET) {
			return NULL;
		}
		sign_ = (lexer->getTokenType() == Token :: PLUS);
		if (lexer->scan<Token :: THEOREM, Token :: CLOSE_SQ_BRACKET>() == Token :: CLOSE_SQ_BRACKET) {
			if (firstPass) {
				sign = sign_;
				return NULL;
			} else {
				Error* error = new Error (lexer->getLocation(), Error :: PARSER);
				error->message() << "plus followed by close bracket is allowed only once" << endLine;
				throw error;
			}
		}
		identificator_ = identificatorParser_->parse (lexer);
		lexer->scan<Token :: COMMA>();
		lexer->scan<Token :: PROOF>();
		lexer->scan<Token :: NAME, Token :: STEP>();
		if (lexer->getTokenType() == Token :: NAME) {
			const String& token = lexer->getToken();
			name_ = Table :: names()->add (token);
			lexer->scan<Token :: STEP>();
		} else {
			name_ = Table :: defaultName();
		}
		path_.clear();
		lexer->scan<Token :: OPEN_BRACKET, Token :: NUMBER>();
		if (lexer->getTokenType() == Token :: NUMBER) {
			const index :: Step
				stepIndex = lexer->getToken().getIntegerValue<index :: Step>();
			path_.add (stepIndex);
		} else {
			while (true) {
				const index :: Step
					stepIndex = lexer->scanNumber<index :: Step>();
				path_.add (stepIndex);
				if (lexer->scan<Token :: DOT, Token :: CLOSE_BRACKET>() == Token :: CLOSE_BRACKET) {
					break;
				}
			}
		}
		return new form :: evaluation :: term :: Case
		(
			location_,
			sign_,
			identificator_,
			name_,
			path_,
			theory
		);
	}

	// object :: Object implementation
	void
	Case :: commitSuicide() {
		delete this;
	}
	Size_t
	Case :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (identificatorParser_);
		volume += path_.getVolume();
		return volume;
	}
	Size_t
	Case :: getSizeOf() const {
		return sizeof (Case);
	}
	void
	Case :: show (String&) const {
	}
}
}
}


