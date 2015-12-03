/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_block_Rule.cpp                                */
/* Description:     grammar rule parser                                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PARSER_BLOCK_RULE_CPP_
#define MDL_PARSER_BLOCK_RULE_CPP_

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
	Rule :: Rule() :
	variablesParser_ (new parser :: header :: Variables()),
	lineParser_ (new parser :: header :: Line()),

	location_ (),
	comments_ (NULL),
	name_ (value :: undefined :: NAME),
	variables_ (NULL),
	term_ (NULL) {
	}
	Rule :: ~ Rule()
	{
		deleteAggregateObject (variablesParser_);
		deleteAggregateObject (lineParser_);
	}

	mdl :: Rule*
	Rule :: parse (Lexer* lexer, mdl :: Theory* theory)
	{
		location_ = lexer->getLocation();
		name_ = lexer->scanName();
		variables_ = variablesParser_->parse (lexer, theory);

		lexer->scan <Token :: OPEN_BRACE>();
		lexer->scan <Token :: TERM>();
		term_ = lineParser_->parse
		<
			mdl :: term :: Rule,
			mdl :: form :: term :: Rule,
			Token :: SHARP
		> (lexer, theory);
		lexer->scan <Token :: CLOSE_BRACE>();
		comments_ =
			lexer->comments().isEmpty() ?
			NULL :
			new form :: Comments (lexer->comments());
		lexer->comments().clear();
		return new form :: Rule
		(
			location_,
			comments_,
			name_,
			variables_,
			term_,
			theory
		);
	}

	// object :: Object implementation
	void
	Rule :: commitSuicide() {
		delete this;
	}
	Size_t
	Rule :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (variablesParser_);
		volume += getAggregateVolume (lineParser_);
		return volume;
	}
	Size_t
	Rule :: getSizeOf() const {
		return sizeof (Rule);
	}
	void
	Rule :: show (String&) const {
	}
}
}
}

#endif /*MDL_PARSER_BLOCK_RULE_CPP_*/
