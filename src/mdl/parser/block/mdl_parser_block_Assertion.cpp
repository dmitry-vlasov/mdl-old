/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_block_Assertion.cpp                           */
/* Description:     assertion parser                                         */
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

	/****************************
	 *		Public members
	 ****************************/

	template<class PV>
	block :: Assertion<PV> :: Assertion() :
	location_ (),
	barIndent_(),
	name_ (value :: undefined :: NAME),
	variables_ (NULL),
	disjointeds_ (NULL),
	hypothesisVector_ (INITIAL_LINE_VECTOR_CAPACITY),
	propositionVector_ (INITIAL_LINE_VECTOR_CAPACITY),

	variablesParser_ (new parser :: header :: Variables()),
	disjointedsParser_ (new parser :: header :: Disjointeds()),
	lineParser_ (new parser :: header :: Line()),
	comments_ (NULL) {
	}
	template<class PV>
	block :: Assertion<PV> :: ~ Assertion()
	{
		deleteAggregateObject (variablesParser_);
		deleteAggregateObject (disjointedsParser_);
		deleteAggregateObject (lineParser_);
	}

	template<class PV>
	template<class PI, class PF>
	void
	block :: Assertion<PV> :: parse (Lexer* lexer, mdl :: Theory* theory)
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

		hypothesisVector_.clear();
		propositionVector_.clear();

		lexer->scan<Token :: HYP, Token :: PROP> ();
		if (lexer->getTokenType() == Token :: HYP) {
			parseHypotheses (lexer, theory);
		}
		parsePropositions <PI, PF> (lexer, theory);
	}

	// object :: Object implementation
	template<class PV>
	Size_t
	block :: Assertion<PV> :: getVolume() const {
		Size_t volume = 0;
		volume += getAggregateVolume (variablesParser_);
		volume += getAggregateVolume (disjointedsParser_);
		volume += getAggregateVolume (lineParser_);
		volume += hypothesisVector_.getVolume();
		volume += propositionVector_.getVolume();
		return volume;
	}
	template<class PV>
	Size_t
	block :: Assertion<PV> :: getSizeOf() const {
		return sizeof (Assertion);
	}
	template<class PV>
	void
	block :: Assertion<PV> :: show (String&) const {
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class PV>
	void
	block :: Assertion<PV> :: parseHypotheses (Lexer* lexer, mdl :: Theory* theory)
	{
		while (true) {
			mdl :: Hypothesis*
				hypothesis = lineParser_->parse
				<
					mdl :: Hypothesis,
					mdl :: form :: Hypothesis,
					Token :: TURNSTILE
				> (lexer, theory);

			hypothesisVector_.add (hypothesis);
			if (lexer->scan<Token :: HYP, Token :: HORISONTAL_BAR>()  != Token :: HYP) {
				break;
			}
		}
		barIndent_ = lexer->getLocation().getIndent();
		lexer->scan<Token :: PROP>();
	}
	template<class PV>
	template<class PI, class PF>
	void
	block :: Assertion<PV> :: parsePropositions (Lexer* lexer, mdl :: Theory* theory)
	{
		while (true) {
			PI* proposition = lineParser_->parse<PI, PF, Token :: TURNSTILE> (lexer, theory);
			propositionVector_.add (proposition);
			if (lexer->scan<Token :: PROP, Token :: CLOSE_BRACE>()  != Token :: PROP) {
				break;
			}
		}
	}
	template<class PV>
	void
	block :: Assertion<PV> :: parseComments (Lexer* lexer)
	{
		comments_ =
			lexer->comments().isEmpty() ?
			NULL :
			new form :: Comments (lexer->comments());
		lexer->comments().clear();
	}
}
}


