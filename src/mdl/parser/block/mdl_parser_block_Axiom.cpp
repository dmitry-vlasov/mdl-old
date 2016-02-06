/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_block_Axiom.cpp                               */
/* Description:     axiom parser                                             */
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

	inline
	Axiom :: Axiom() :
	Ancestor_() {
	}
	Axiom :: ~ Axiom() {
	}

	mdl :: Assertion*
	Axiom :: parse (Lexer* lexer, mdl :: Theory* theory)
	{
		Ancestor_ :: parse
		<
			mdl :: statement :: Axiomatic,
			mdl :: form :: statement :: Axiomatic
		> (lexer, theory);
		Ancestor_ :: parseComments (lexer);
		return new form :: block :: Axiom
		(
			location_,
			comments_,
			barIndent_,
			name_,
			variables_,
			disjointeds_,
			hypothesisVector_,
			propositionVector_,
			theory
		);
	}

	// object :: Object implementation
	void
	Axiom :: commitSuicide() {
		delete this;
	}
	Size_t
	Axiom :: getVolume() const {
		return Ancestor_ :: getVolume();
	}
	Size_t
	Axiom :: getSizeOf() const {
		return sizeof (Axiom);
	}
	void
	Axiom :: show (String&) const {
	}
}
}
}


