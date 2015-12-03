/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_block_Problem.cpp                             */
/* Description:     problem parser                                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PARSER_BLOCK_PROBLEM_CPP_
#define MDL_PARSER_BLOCK_PROBLEM_CPP_

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
	Problem :: Problem() :
	Ancestor_() {
	}
	Problem :: ~ Problem() {
	}

	mdl :: Assertion*
	Problem :: parse (Lexer* lexer, mdl :: Theory* theory)
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
			theory,
			true
		);
	}

	// object :: Object implementation
	void
	Problem :: commitSuicide() {
		delete this;
	}
	Size_t
	Problem :: getVolume() const
	{
		Size_t volume = 0;
		volume += Ancestor_ :: getVolume();
		return volume;
	}
	Size_t
	Problem :: getSizeOf() const {
		return sizeof (Problem);
	}
	void
	Problem :: show (String&) const {
	}

	/****************************
	 *		Private members
	 ****************************/
}
}
}

#endif /*MDL_PARSER_BLOCK_PROBLEM_CPP_*/
