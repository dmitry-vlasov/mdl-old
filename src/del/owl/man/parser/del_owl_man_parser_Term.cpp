/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_man_parser_Term.cpp                              */
/* Description:     manchester OWL term parser                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_MAN_PARSER_TERM_CPP_
#define DEL_OWL_MAN_PARSER_TERM_CPP_

#include "del/source/term/del_source_term.hpp"
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
	Term :: Term() :
	location_ (),
	tokenVector_ (INITIAL_TOKEN_VECTOR_CAPACITY) {
	}
	Term :: ~ Term() {
	}

	const del :: Term*
	Term :: parse (Lexer* lexer)
	{
		lexer->setIdleScan (false);
		location_ = lexer->getLocation();
		bool inTerm = true;
		while (inTerm) {
			lexer->scan();
			switch (lexer->getTokenType()) {
			case Token :: NAME :
			case Token :: SOME :
			case Token :: AND :
			case Token :: OPEN_BRACKET :
			case Token :: CLOSE_BRACKET : {
				Token_* token = new Token_();
				tokenVector_.add (token);
				token->string_.copy (lexer->getToken());
				token->type_ = lexer->getTokenType();
				token->location_ = lexer->getLocation();
				break;
			}
			default :
				lexer->setIdleScan();
				inTerm = false;
			}
		}
		if (tokenVector_.getSize() == 0) {
			Error* error = new Error (lexer->getLocation(), Error :: PARSER);
			error->message() << "syntax error: empty term." << endLine;
			throw error;
		}
		parseTerm();
		if (tokenVector_.getSize() != 1) {
			Error* error = new Error (lexer->getLocation(), Error :: PARSER);
			error->message() << "syntax error." << endLine;
			throw error;
		}
		Token_*
			topToken = tokenVector_.popLast();
		const del :: Term*
			term = topToken->term_;
		topToken->commitSuicide();
		//std :: cout << *term << std :: endl;
		return term;
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
		volume += tokenVector_.getVolume();
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

	void
	Term :: parseTerm()
	{
		parseVariables();
		while (tryToGetUp());
	}
	void
	Term :: parseVariables()
	{
		for (value :: Integer i = 0; i < tokenVector_.getSize(); ++ i) {
			Token_* currentToken = tokenVector_.getValue (i);
			if (currentToken->type_ != Token :: NAME) {
				continue;
			}
			if (i < tokenVector_.getSize() - 1) {
				Token_* nextToken = tokenVector_.getValue (i + 1);
				if (nextToken->type_ == Token :: SOME) {
					continue;
				}
			}
			//if (currentToken->string_ == "owl:Thing") {
			//	currentToken->term_ = new del :: source :: term :: Top (currentToken->location_);
			//}
			if (currentToken->type_ == Token :: THING) {
				currentToken->term_ = new del :: source :: term :: Top (currentToken->location_);
			} else {
				const value :: Variable
					variable = Table :: variables()->add (currentToken->string_);
				currentToken->term_ = new del :: source :: term :: Variable
				(
					currentToken->location_,
					variable
				);
			}
		}
	}
	bool
	Term :: tryToGetUp()
	{
		bool result = false;
		if (parseSome()) {
			result = true;
		}
		if (parseBrackets()) {
			result = true;
		}
		if (parseAnd()) {
			result = true;
		}
		return result;
	}
	bool
	Term :: parseSomeOnce()
	{
		if (tokenVector_.getSize() == 0) {
			return false;
		}
		for (value :: Integer i = 1; i < tokenVector_.getSize() - 1; ++ i) {
			Token_* currentToken = tokenVector_.getValue (i);
			if (currentToken->type_ != Token :: SOME) {
				continue;
			}
			Token_* previousToken = tokenVector_.getValue (i - 1);
			Token_* nextToken = tokenVector_.getValue (i + 1);
			if (previousToken->type_ != Token :: NAME) {
				Error* error = new Error (previousToken->location_, Error :: PARSER);
				error->message() << "syntax error: relation name expected," << endLine;
				error->message() << "while \"" << previousToken->string_ << "\" got." << endLine;
				throw error;
			}
			if (nextToken->term_ == NULL) {
				continue;
			}
			const value :: Relation
				relation = Table :: relations()->add (previousToken->string_);
			currentToken->term_ = new del :: source :: term :: Exists
			(
				currentToken->location_,
				relation,
				nextToken->term_
			);
			currentToken->type_ = Token :: UNKNOWN;

			tokenVector_.getValue (i + 1)->commitSuicide();
			tokenVector_.remove (i + 1);
			tokenVector_.getValue (i - 1)->commitSuicide();
			tokenVector_.remove (i - 1);

			//showTokenStack();

			return true;
		}
		return false;
	}
	bool
	Term :: parseSome()
	{
		bool result = false;
		while (parseSomeOnce()) {
			result = true;
		}
		return result;
	}
	bool
	Term :: parseBracketsOnce()
	{
		if (tokenVector_.getSize() == 0) {
			return false;
		}
		for (value :: Integer i = 1; i < tokenVector_.getSize() - 1; ++ i) {
			Token_* previousToken = tokenVector_.getValue (i - 1);
			if (previousToken->type_ != Token :: OPEN_BRACKET) {
				continue;
			}
			Token_* nextToken = tokenVector_.getValue (i + 1);
			if (nextToken->type_ != Token :: CLOSE_BRACKET) {
				continue;
			}
			Token_* currentToken = tokenVector_.getValue (i);
			if (currentToken->term_ == NULL) {
				continue;
			}
			tokenVector_.getValue (i + 1)->commitSuicide();
			tokenVector_.remove (i + 1);
			tokenVector_.getValue (i - 1)->commitSuicide();
			tokenVector_.remove (i - 1);

			//showTokenStack();

			return true;
		}
		return false;
	}
	bool
	Term :: parseBrackets()
	{
		bool result = false;
		while (parseBracketsOnce()) {
			result = true;
		}
		return result;
	}
	bool
	Term :: parseAndOnce()
	{
		if (tokenVector_.getSize() == 0) {
			return false;
		}
		for (value :: Integer i = 1; i < tokenVector_.getSize() - 1; ++ i) {
			Token_* previousToken = tokenVector_.getValue (i - 1);
			if (previousToken->term_ == NULL) {
				continue;
			}
			Token_* nextToken = tokenVector_.getValue (i + 1);
			if (nextToken->term_ == NULL) {
				continue;
			}
			Token_* currentToken = tokenVector_.getValue (i);
			if (currentToken->type_ != Token :: AND) {
				continue;
			}
			bool success = true;
			value :: Integer border = i;
			for (value :: Integer j = i + 2; j < tokenVector_.getSize() - 1; j += 2) {
				Token_* andToken = tokenVector_.getValue (j);
				Token_* termToken = tokenVector_.getValue (j + 1);
				if (andToken->type_ == Token :: AND) {
					if (termToken->term_ != NULL) {
						border = j;
					} else {
						success = false;
					}
				} else {
					success = false;
				}
			}
			if (success) {
				del :: source :: term :: Intersect*
					term = new del :: source :: term :: Intersect (currentToken->location_);
				for (value :: Integer j = i - 1; j < border + 2; j += 2) {
					Token_* token = tokenVector_.getValue (j);
					term->addSubterm (token->term_);
					token->term_ = NULL;
				}
				currentToken->term_ = term;
				for (value :: Integer j = border + 1; j > i; --j) {
					tokenVector_.getValue (j)->commitSuicide();
					tokenVector_.remove (j);
				}
				currentToken->type_ = Token :: UNKNOWN;
				nextToken->term_ = NULL;
				previousToken->term_ = NULL;
				tokenVector_.getValue (i - 1)->commitSuicide();
				tokenVector_.remove (i - 1);

				//showTokenStack();

				return true;
			} else {
				return false;
			}
		}
		return false;
	}
	bool
	Term :: parseAnd()
	{
		bool result = false;
		while (parseAndOnce()) {
			result = true;
		}
		return result;
	}

	void
	Term :: showTokenStack() const
	{
		std :: cout << std :: endl;
		for (value :: Integer j = 0; j < tokenVector_.getSize(); ++ j) {
			Token_* token = tokenVector_.getValue (j);
			if (token->term_ == NULL) {
				std :: cout << token->string_ << " ";
			} else {
				std :: cout << *token->term_ << " * ";
			}
		}
		std :: cout << std :: endl << std :: endl;
	}
}
}
}
}

#endif /*DEL_OWL_MAN_PARSER_TERM_CPP_*/
