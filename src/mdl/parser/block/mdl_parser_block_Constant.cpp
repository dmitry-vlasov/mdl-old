/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_block_Constant.cpp                            */
/* Description:     constant parser                                          */
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
namespace block {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Constant :: Constant() :
	location_(),
	comments_ (NULL),
	symbol_ (NULL),
	ascii_ (NULL),
	latex_ (NULL) {
	}
	Constant :: ~ Constant() {
	}

using manipulator :: endLine;

	mdl :: Constant*
	Constant :: parse  (Lexer* lexer, mdl :: Theory* theory)
	{
		location_ = lexer->getLocation();
		lexer->scan<Token :: OPEN_BRACE>();
		symbol_ = NULL; ascii_ = NULL; latex_ = NULL;
		bool end = false;
		while (!end) {
			lexer->scan
			<
				Token :: SYMBOL,
				Token :: ASCII,
				Token :: LATEX,
				Token :: CLOSE_BRACE
			>();
			switch (lexer->getTokenType()) {
			case Token :: SYMBOL : {
				if (symbol_ != NULL) {
					Error* error = new Error (location_, Error :: PARSER);
					error->message() << "symbol " << *symbol_ << " already declared" << endLine;
					throw error;
				} else {
					symbol_ = parseEntry (lexer);
				}
				break;
			}
			case Token :: ASCII : {
				if (ascii_ != NULL) {
					Error* error = new Error (location_, Error :: PARSER);
					error->message() << "ascii " << *ascii_ << " already declared" << endLine;
					throw error;
				} else {
					ascii_ = parseEntry (lexer);
				}
				break;
			}
			case Token :: LATEX : {
				if (latex_ != NULL) {
					Error* error = new Error (location_, Error :: PARSER);
					error->message() << "latex " << *latex_ << " already declared" << endLine;
					throw error;
				} else {
					latex_ = parseEntry (lexer);
				}
			}
			break;
			case Token :: CLOSE_BRACE :
			default :
				end = true;
			}
		}
		comments_ =
			lexer->comments().isEmpty() ?
			NULL :
			new form :: Comments (lexer->comments());
		lexer->comments().clear();
		if (symbol_ == NULL) {
			Error* error = new Error (location_, Error :: PARSER);
			error->message() << "symbol is not declared" << endLine;
			throw error;
		}
		if (ascii_ == NULL) {
			ascii_ = new String (*symbol_);
		}
		return new form :: Constant (location_, comments_, symbol_, ascii_, latex_, theory);
	}

using manipulator :: endLine;
using manipulator :: space;

	// object :: Object implementation
	void
	Constant :: commitSuicide() {
		delete this;
	}
	Size_t
	Constant :: getVolume() const {
		return 0;
	}
	Size_t
	Constant :: getSizeOf() const {
		return sizeof (Constant);
	}
	void
	Constant :: show (String&) const {
	}

	/****************************
	 *		Private members
	 ****************************/

	mdl :: String*
	Constant :: parseEntry  (Lexer* lexer)
	{
		lexer->scan <Token :: LITERAL>();
		const String& token = lexer->getToken();
		String* string = new String (token);
		lexer->scan <Token :: SEMICOLON>();
		return string;
	}
}
}
}


