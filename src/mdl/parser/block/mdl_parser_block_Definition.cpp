/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_block_Definition.dpp                          */
/* Description:     definition parser                                        */
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

	Definition :: Definition() :
	Ancestor_ (),
	lineParser_ (new parser :: header :: Line()),
	defiendum_ (NULL),
	definiens_ (NULL) {
	}
	Definition :: ~ Definition() {
		deleteAggregateObject (lineParser_);
	}

	mdl :: Definition*
	Definition :: parse (Lexer* lexer, mdl :: Theory* theory)
	{
		location_ = lexer->getLocation();
		name_ = lexer->scanName();
		variables_ = variablesParser_->parse (lexer, theory);

		if (lexer->scan<Token :: OPEN_BRACE, Token :: DISJOINTED>() == Token :: DISJOINTED) {
			disjointeds_ = disjointedsParser_->parse (lexer, theory);
			lexer->scan<Token :: OPEN_BRACE>();
		} else {
			disjointeds_ = new form :: Disjointeds();
		}

		lexer->scan<Token :: DEFIENDUM>();
		defiendum_ = lineParser_->parse
		<
			mdl :: term :: Definition,
			mdl :: form :: term :: Defiendum,
			Token :: SHARP
		> (lexer, theory);
		lexer->scan<Token :: DEFINIENS>();
		definiens_ = lineParser_->parse
		<
			mdl :: term :: Definition,
			mdl :: form :: term :: Definiens,
			Token :: SHARP
		>(lexer, theory);

		hypothesisVector_.clear();
		propositionVector_.clear();

		if (lexer->scan<Token :: HYP, Token :: HORISONTAL_BAR>() == Token :: HYP) {
			parseHypotheses (lexer, theory);
		} else {
			barIndent_ = lexer->getLocation().getIndent();
			lexer->scan<Token :: PROP>();
		}

		parsePropositions
		<
			mdl :: statement :: Definition,
			mdl :: form :: statement :: Definition
		> (lexer, theory);
		Ancestor_ :: parseComments (lexer);
		return new form :: Definition
		(
			location_,
			comments_,
			barIndent_,
			name_,
			variables_,
			disjointeds_,
			defiendum_,
			definiens_,
			hypothesisVector_,
			propositionVector_,
			theory
		);
	}

	// object :: Object implementation
	void
	Definition :: commitSuicide() {
		delete this;
	}
	Size_t
	Definition :: getVolume() const
	{
		Size_t volume = 0;
		volume += Ancestor_ :: getVolume();
		volume += getAggregateVolume (lineParser_);
		return volume;
	}
	Size_t
	Definition :: getSizeOf() const {
		return sizeof (Definition);
	}
	void
	Definition :: show (String&) const {
	}
}
}
}


