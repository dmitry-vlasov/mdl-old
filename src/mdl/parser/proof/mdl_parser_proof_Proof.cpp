/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_proof_Proof.cpp                               */
/* Description:     proof parser                                             */
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

	inline
	Proof :: Proof() :
	stepParser_ (new parser :: proof :: Step()),
	qedParser_ (new parser :: proof :: Qed()),
	variableParser_ (new parser :: proof :: Variable()),
	notationParser_ (new parser :: proof :: Notation()),

	location_ (),
	comments_ (NULL),
	stepVector_ (INITIAL_STEP_VECTOR_CAPACITY),
	firstLine_ (NULL),
	line_ (NULL) {
	}
	Proof :: ~ Proof()
	{
		deleteAggregateObject (stepParser_);
		deleteAggregateObject (qedParser_);
		deleteAggregateObject (variableParser_);
		deleteAggregateObject (notationParser_);
	}

	form :: proof :: Proof*
	Proof :: parse (Lexer* lexer, mdl :: Theory* theory)
	{
		const bool create = (!Config :: shallowParsing() || lexer->isTop());
		stepVector_.clear();
		location_ = lexer->getLocation();
		firstLine_ = NULL;
		line_ = NULL;
		lexer->comments().clear();
		comments_ =
			(lexer->comments().isEmpty() || !create) ?
			NULL :
			new form :: Comments (lexer->comments(), false);
		lexer->comments().clear();

		while (true) {
			lexer->scan
			<
				Token :: STEP,
				Token :: QED,
				Token :: VARIABLE,
				Token :: NOTATION,
				Token :: CLOSE_BRACE
			>();
			if (lexer->getTokenType() == Token :: CLOSE_BRACE) {
				lexer->comments().clear();
				if (create) {
					return new form :: proof :: Proof
					(
						location_,
						comments_,
						firstLine_,
						stepVector_,
						theory
					);
				} else {
					return NULL;
				}
			}
			line_ = parseLine (lexer, theory, create);
			if (firstLine_ == NULL) {
				firstLine_ = line_;
			}
		}
		return NULL;
	}

	// object :: Object implementation
	void
	Proof :: commitSuicide() {
		delete this;
	}
	Size_t
	Proof :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (stepParser_);
		volume += getAggregateVolume (qedParser_);
		volume += getAggregateVolume (variableParser_);
		volume += getAggregateVolume (notationParser_);
		volume += stepVector_.getVolume();
		return volume;
	}
	Size_t
	Proof :: getSizeOf() const {
		return sizeof (Proof);
	}
	void
	Proof :: show (String&) const {
	}

	/****************************
	 *		Private members
	 ****************************/

	mdl :: proof :: Line*
	Proof :: parseLine (Lexer* lexer, mdl :: Theory* theory, const bool create)
	{
		switch (lexer->getTokenType()) {
		case Token :: STEP : {
			mdl :: proof :: Step*
				step = stepParser_->parse (lexer, theory, line_);
			if (create) {
				stepVector_.add (step);
			}
			return step;
		}
		case Token :: QED :
			return qedParser_->parse (lexer, theory, line_);
		case Token :: VARIABLE :
			return variableParser_->parse (lexer, theory, line_);
		case Token :: NOTATION :
			return notationParser_->parse (lexer, theory, line_);
		default :
			return NULL;
		}
	}
}
}
}


