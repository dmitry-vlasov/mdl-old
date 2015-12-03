/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_ast_target_assertion_Axiom.cpp                        */
/* Description:     mdl axiom                                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_TARGET_ASSERTION_AXIOM_CPP_
#define MM_AST_TARGET_ASSERTION_AXIOM_CPP_

#include "mdl/lexer/mdl_lexer_Token.hpp"
#include "auxiliary/mm_auxiliary.hpp"
#include "ast/mm_ast.hpp"

namespace mm {
namespace ast {
namespace target {
namespace assertion {

	/****************************
	 *		Public members
	 ****************************/

	Axiom :: Axiom
	(
		const value :: Label label,
		const mm :: target :: Variables* const variables,
		const mm :: target :: Disjoineds* const disjoineds,
		const mm :: target :: Comments* const comments
	) :
	ast :: target :: assertion :: Statement (label, variables, disjoineds, comments) {
	}
	Axiom :: ~ Axiom() {
	}

	// target :: Statement implementation
	inline void
	Axiom :: addHypothesis (const object :: Targetive* const hypothesis) {
		Statement :: addHypothesis (hypothesis);
	}
	inline void
	Axiom :: addProposition (const object :: Targetive* const proposition) {
		Statement ::  addProposition (proposition);
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Referable implementation
	void
	Axiom :: writeReference (String& string) const
	{
		string << mdl :: Token :: axiom_ << space;
		Statement :: writeReference (string);
	}

	// object :: Targetive implementation
	inline void
	Axiom :: complete (mm :: target :: Block* const block) const {
		Assertion :: complete (block);
	}

	// object :: Writable implementation
	void
	Axiom :: write (String& string) const
	{
		Statement :: write (string);
		string << endLine;
	}

	// object :: Object implementation
	void
	Axiom :: commitSuicide() {
		delete this;
	}
	Size_t
	Axiom :: getVolume() const {
		return Statement :: getVolume();
	}
	Size_t
	Axiom :: getSizeOf() const {
		return sizeof (Axiom);
	}
}
}
}
}

#endif /*MM_AST_TARGET_ASSERTION_AXIOM_CPP_*/
