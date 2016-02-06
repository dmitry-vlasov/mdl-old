/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_Expression.cpp                                */
/* Description:     expression parser                                        */
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

	/****************************
	 *		Public members
	 ****************************/

	inline
	Expression :: Expression (const bool variablesAreReplaceable) :
	variablesAreReplaceable_ (variablesAreReplaceable),
	literalVector_ (INITIAL_LITERAL_VECTOR_CAPACITY) {
	}
	Expression :: ~ Expression () {
	}

	array :: Expression*
	Expression :: parse (Lexer* lexer, const bool create)
	{
		literalVector_.clear();
		while (lexer->scan <Token :: LITERAL, Token :: SEMICOLON>() == Token :: LITERAL) {
			if (create) {
				const String&
					token = lexer->getToken();
				const value :: Literal
					literal = Table :: literals()->add (token);
				literalVector_.add (literal);
			}
		}
		array :: Expression* expression =
			create ?
			new array :: Expression (literalVector_, variablesAreReplaceable_) :
			NULL;
		return expression;
	}

	// object :: Object implementation
	void
	Expression :: commitSuicide() {
		delete this;
	}
	Size_t
	Expression :: getVolume() const {
		return literalVector_.getVolume();
	}
	Size_t
	Expression :: getSizeOf() const {
		return sizeof (Expression);
	}
	void
	Expression :: show (String& string) const
	{
		for (index :: Literal i = 0; i < literalVector_.getSize(); i ++) {
			const value :: Literal
				literal = literalVector_.getValue (i);
			string << Table :: literals()->get (literal) << " ";
		}
	}
}
}


