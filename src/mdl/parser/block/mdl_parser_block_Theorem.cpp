/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_block_Theorem.cpp                             */
/* Description:     theorem parser                                           */
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
	Theorem :: Theorem() :
	Ancestor_ () {
	}
	Theorem :: ~ Theorem() {
	}

	mdl :: Assertion*
	Theorem :: parse (Lexer* lexer, mdl :: Theory* theory)
	{
		Ancestor_ :: parse
		<
			mdl :: statement :: Provable,
			mdl :: form :: statement :: Provable
		> (lexer, theory);
		Ancestor_ :: parseComments (lexer);
		return new form :: Theorem
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
	Theorem :: commitSuicide() {
		delete this;
	}
	Size_t
	Theorem :: getVolume() const
	{
		Size_t volume = 0;
		volume += Ancestor_ :: getVolume();
		return volume;
	}
	Size_t
	Theorem :: getSizeOf() const {
		return sizeof (Theorem);
	}
	void
	Theorem :: show (String&) const {
	}
}
}
}


