/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_evaluation_Function.cpp                       */
/* Description:     evaluation function for proposition parser               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PARSER_EVALUATION_FUNCTION_CPP_
#define MDL_PARSER_EVALUATION_FUNCTION_CPP_

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
	Function :: Function() :
	termParser_ (new parser :: evaluation :: Term()),
	location_ (),
	index_ (index :: undefined :: ARITY),
	term_ (NULL) {
	}
	Function :: ~ Function() {
		deleteAggregateObject (termParser_);
	}

	mdl :: evaluation :: Function*
	Function :: parse (Lexer* lexer, mdl :: Theory* theory)
	{
		location_ = lexer->getLocation();
		if (lexer->scan<Token :: PROP, Token :: CLOSE_BRACE>() == Token :: CLOSE_BRACE) {
			return NULL;
		}
		lexer->scan<Token :: NUMBER>();
		index_ = lexer->getToken().getIntegerValue<index :: Arity>();
		lexer->scan<Token :: EQUALITY>();
		term_ = termParser_->parse (lexer, theory);

		if (dynamic_cast<form :: evaluation :: term :: WeightedSum*>(term_) == NULL) {
			return new form :: evaluation :: function :: Function (location_, index_ - 1, term_, theory);
		} else {
			return new form :: evaluation :: function :: WeightedSum (location_, index_ - 1, term_, theory);
		}
	}

	// object :: Object implementation
	void
	Function :: commitSuicide() {
		delete this;
	}
	Size_t
	Function :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (termParser_);
		return volume;
	}
	Size_t
	Function :: getSizeOf() const {
		return sizeof (Function);
	}
	void
	Function :: show (String&) const {
	}
}
}
}

#endif /*MDL_PARSER_EVALUATION_FUNCTION_CPP_*/
