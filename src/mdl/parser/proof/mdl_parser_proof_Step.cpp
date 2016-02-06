/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_proof_Step.cpp                                */
/* Description:     proof step parser                                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace parser {
namespace proof {

	/****************************
	 *		Public members
	 ****************************/

	Step :: Step() :
	identificatorParser_ (new parser :: Identificator()),
	linkParser_(new parser :: proof :: Link()),
	expressionParser_ (new parser :: Expression (false)),
	proofParser_ (NULL),

	location_(),
	comments_ (NULL),
	index_ (index :: undefined :: STEP),
	type_ (NULL),
	link_ (NULL),
	expression_ (NULL),
	proof_ (NULL) {
	}
	Step :: ~ Step()
	{
		deleteAggregateObject (identificatorParser_);
		deleteAggregateObject (linkParser_);
		deleteAggregateObject (expressionParser_);
		deleteAggregateObject (proofParser_);
	}

	mdl :: proof :: Step*
	Step :: parse
	(
		Lexer* lexer,
		mdl :: Theory* theory,
		mdl :: proof :: Line* line
	)
	{
		const bool create = (!Config :: shallowParsing() || lexer->isTop());
		location_ = lexer->getLocation();
		index_ = lexer->scanNumber<index :: Step>() - 1;

		lexer->scan<Token :: COLON>();
		type_ = identificatorParser_->parse (lexer, create);
		lexer->scan<Token :: EQUALITY>();

		lexer->scan
		<
			Token :: QUESTION,
			Token :: CLAIM,
			Token :: AXIOM,
			Token :: THEOREM,
			Token :: DEFINITION
		>();
		switch (lexer->getTokenType ()) {
		case Token :: QUESTION :
			return parseQuestion (lexer, theory, line, create);
		case Token :: CLAIM :
			return parseClaim (lexer, theory, line, create);
		case Token :: AXIOM :
		case Token :: THEOREM :
		case Token :: DEFINITION :
			return parseAssertion (lexer, theory, line, create);
		default :
			return NULL;
		}
	}

	// object :: Object implementation
	void
	Step :: commitSuicide() {
		delete this;
	}
	Size_t
	Step :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (identificatorParser_);
		volume += getAggregateVolume (linkParser_);
		volume += getAggregateVolume (expressionParser_);
		volume += getAggregateVolume (proofParser_);
		return volume;
	}
	Size_t
	Step :: getSizeOf() const {
		return sizeof (Step);
	}
	void
	Step :: show (String&) const {
	}

	/****************************
	 *		Private members
	 ****************************/

	mdl :: proof :: Step*
	Step :: parseQuestion
	(
		Lexer* lexer,
		mdl :: Theory* theory,
		mdl :: proof :: Line* line,
		const bool create
	)
	{
		lexer->getLocation();
		lexer->scan<Token :: TURNSTILE>();
		comments_ =
			(lexer->comments().isEmpty() || !create) ?
			NULL :
			new form :: Comments (lexer->comments());
		lexer->comments().clear();
		expression_ = expressionParser_->parse (lexer, create);
		if (create) {
			return new form :: proof :: step :: Question
			(
				line,
				location_,
				comments_,
				index_,
				type_,
				expression_,
				theory
			);
		} else {
			return NULL;
		}
	}
	mdl :: proof :: Step*
	Step :: parseAssertion
	(
		Lexer* lexer,
		mdl :: Theory* theory,
		mdl :: proof :: Line* line,
		const bool create
	)
	{
		link_ = linkParser_->parse (lexer, theory);
		lexer->getLocation();
		lexer->scan<Token :: TURNSTILE>();
		comments_ =
			(lexer->comments().isEmpty() || !create) ?
			NULL :
			new form :: Comments (lexer->comments());
		lexer->comments().clear();
		expression_ = expressionParser_->parse (lexer, create);
		if (create) {
			return new form :: proof :: step :: Assertion
			(
				line,
				location_,
				comments_,
				index_,
				type_,
				link_,
				expression_,
				theory
			);
		} else {
			return NULL;
		}
	}
	mdl :: proof :: Step*
	Step :: parseClaim
	(
		Lexer* lexer,
		mdl :: Theory* theory,
		mdl :: proof :: Line* line,
		const bool create
	)
	{
		if (proofParser_ == NULL) {
			proofParser_ = new parser :: Proof (true);
		}
		link_ = linkParser_->parse (lexer, theory, false);
		lexer->getLocation();
		lexer->scan<Token :: TURNSTILE>();
		comments_ =
			(lexer->comments().isEmpty() || !create) ?
			NULL :
			new form :: Comments (lexer->comments());
		lexer->comments().clear();
		expression_ = expressionParser_->parse (lexer, create);
		lexer->scan <Token :: PROOF>();
		proof_ = proofParser_->parse (lexer, theory);
		if (create) {
			return new form :: proof :: step :: Claim
			(
				line,
				location_,
				comments_,
				index_,
				type_,
				link_,
				expression_,
				proof_,
				theory
			);
		} else {
			return NULL;
		}
	}
}
}
}


