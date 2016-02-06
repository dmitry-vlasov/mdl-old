/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_parser_Assertion.cpp                                 */
/* Description:     smm assertion parser                                     */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "smm/lexer/smm_lexer.hpp"
#include "smm/source/smm_source.hpp"
#include "smm/parser/smm_parser.hpp"

namespace smm {
namespace parser {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Assertion :: Assertion() :
	location_ (),
	variablesParser_ (),
	disjointedParser_ (),
	essentialParser_ (),
	floatingParser_ (),
	innerParser_ (),
	axiomaticParser_ (),
	provableParser_ (),
	proofParser_ (new parser :: Proof()),

	variablesVector_ (NULL),
	disjointedVector_ (NULL),
	essentialVector_ (NULL),
	floatingVector_ (NULL),
	innerVector_ (NULL),
	proposition_ (NULL),
	proof_ (NULL),

	essentialCounter_ (0),
	floatingCounter_ (0),
	innerCounter_ (0) {
	}
	Assertion :: ~ Assertion() {
		deleteAggregateObject (proofParser_);
	}

using manipulator :: endLine;

	const smm :: Assertion*
	Assertion :: parse (Lexer* const lexer)
	{
		location_ = lexer->getLocation();
		createComponents();
		while (true) {
			switch (lexer->scan()) {
			case Token :: VARIABLE :
				variablesVector_->add (variablesParser_.parse (lexer)); break;
			case Token :: DISJOINTED :
				disjointedVector_->add (disjointedParser_.parse (lexer)); break;
			case Token :: PREFIX_E :
				essentialVector_->add (essentialParser_.parse (lexer, essentialCounter_ ++)); break;
			case Token :: PREFIX_F :
				floatingVector_->add (floatingParser_.parse (lexer, floatingCounter_ ++)); break;
			case Token :: PREFIX_I :
				innerVector_->add (innerParser_.parse (lexer, innerCounter_ ++)); break;
			case Token :: PREFIX_A :
				proposition_ = axiomaticParser_.parse (lexer, propositionCounter_ ++);
				goto end;
			case Token :: PREFIX_P :
				proposition_ = provableParser_.parse (lexer, propositionCounter_ ++);
				proof_ = proofParser_->parse (lexer);
				goto end;
			default :
				Error* error = new Error (lexer->getLocation(), Error :: PARSER);
				error->message() << "unexpected token: " << lexer->getToken() << endLine;
				error->message() << "should be one of : $v, $d, <prefix> or $}" << endLine;
				throw error;
			}
		}
		end :
		lexer->scan<Token :: BLOCK_END>();
		return createResult();
	}

	// object :: Object implementation
	void
	Assertion :: commitSuicide() {
		delete this;
	}
	Size_t
	Assertion :: getVolume() const
	{
		Size_t volume = 0;
		volume += variablesParser_.getVolume();
		volume += disjointedParser_.getVolume();
		volume += essentialParser_.getVolume();
		volume += floatingParser_.getVolume();
		volume += innerParser_.getVolume();
		volume += axiomaticParser_.getVolume();
		volume += provableParser_.getVolume();
		volume += getAggregateVolume (proofParser_);
		volume += location_.getVolume();
		return volume;
	}
	Size_t
	Assertion :: getSizeOf() const {
		return sizeof (Assertion);
	}
	void
	Assertion :: show (String&) const {
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Assertion :: createComponents()
	{
		variablesVector_ = new vector :: Expression();
		disjointedVector_ = new vector :: Expression();
		essentialVector_ = new vector :: Expression();
		floatingVector_ = new vector :: Expression();
		innerVector_ = new vector :: Expression();
		proposition_ = NULL;
		proof_ = NULL;
		essentialCounter_ = 0;
		floatingCounter_ = 0;
		innerCounter_ = 0;
	}
	const smm :: Assertion*
	Assertion :: createResult()
	{
		return new source :: Assertion
		(
			location_,
			variablesVector_,
			disjointedVector_,
			essentialVector_,
			floatingVector_,
			innerVector_,
			proposition_,
			proof_
		);
	}

	/************************************
	 *		Static private attributes
	 ************************************/

	index :: Assertion
		Assertion :: propositionCounter_ = 0;
}
}


