/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_proof_Notation.cpp                            */
/* Description:     proof notation parser                                    */
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
	Notation :: Notation() :
	variablesParser_ (new parser :: header :: Variables()),
	lineParser_ (new parser :: header :: Line()),

	location_(),
	literal_ (value :: undefined :: LITERAL),
	variables_ (NULL),
	abbreviation_ (NULL),
	meaning_ (NULL) {
	}
	Notation :: ~ Notation()
	{
		deleteAggregateObject (variablesParser_);
		deleteAggregateObject (lineParser_);
	}

	mdl :: proof :: Notation*
	Notation :: parse
	(
		Lexer* lexer,
		mdl :: Theory* theory,
		mdl :: proof :: Line* line
	)
	{
		location_ = lexer->getLocation();
		literal_ = lexer->scanLiteral();
		variables_ = variablesParser_->parse (lexer, theory);

		lexer->scan<Token :: OPEN_BRACE>();
		lexer->scan<Token :: ABBREVIATION>();
		abbreviation_ = lineParser_->parse
		<
			mdl :: proof :: Term,
			mdl :: form :: proof :: notation :: Abbreviation,
			Token :: SHARP
		> (lexer, theory);
		lexer->scan<Token :: MEANING>();
		meaning_ = lineParser_->parse
		<
			mdl :: proof :: Term,
			mdl :: form :: proof :: notation :: Meaning,
			Token :: SHARP
		> (lexer, theory);
		lexer->scan<Token :: CLOSE_BRACE>();
		return new form :: proof :: Notation
		(
			line,
			location_,
			literal_,
			variables_,
			abbreviation_,
			meaning_,
			theory
		);
	}

	// object :: Object implementation
	void
	Notation :: commitSuicide() {
		delete this;
	}
	Size_t
	Notation :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (variablesParser_);
		volume += getAggregateVolume (lineParser_);
		return volume;
	}
	Size_t
	Notation :: getSizeOf() const {
		return sizeof (Notation);
	}
	void
	Notation :: show (String&) const {
	}
}
}
}


