/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_header_Variables.cpp                          */
/* Description:     variables declarations parser                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PARSER_HEADER_VARIABLES_CPP_
#define MDL_PARSER_HEADER_VARIABLES_CPP_

namespace mdl {
namespace parser {
namespace header {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Variables :: Variables() :
	variableParser_ (new parser :: header :: Variable()),
	location_ (),
	variableVector_ (INITIAL_VARIABLE_VECTOR_CAPACITY) {
	}
	Variables :: ~ Variables() {
		deleteAggregateObject (variableParser_);
	}

	mdl :: Variables*
	Variables :: parse (Lexer* lexer, mdl :: Theory* theory)
	{
		location_ = lexer->getLocation();
		variableVector_.clear();
		lexer->scan <Token :: OPEN_BRACKET>();
		if (lexer->scan<Token :: VARIABLE, Token :: CLOSE_BRACKET>() == Token :: VARIABLE) {
			while (true) {
				variableVector_.add (variableParser_->parse<form :: header :: Variable> (lexer, theory));
				if (lexer->scan<Token :: COMMA, Token :: CLOSE_BRACKET>() == Token :: CLOSE_BRACKET) {
					break;
				} else {
					lexer->scan<Token :: VARIABLE>();
				}
			}
		}
		return new form :: Variables
		(
			location_,
			variableVector_,
			theory
		);
	}

	// object :: Object implementation
	void
	Variables :: commitSuicide() {
		delete this;
	}
	Size_t
	Variables :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (variableParser_);
		volume += variableVector_.getVolume ();
		return volume;
	}
	Size_t
	Variables :: getSizeOf() const {
		return sizeof (Variables);
	}
	void
	Variables :: show (String&) const {
	}
}
}
}

#endif /*MDL_PARSER_HEADER_VARIABLES_CPP_*/
