/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_assertion_Theorem.cpp                      */
/* Description:     mdl theorem                                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

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

	inline
	Theorem :: Theorem
	(
		const value :: Label label,
		const mm :: target :: Variables* const variables,
		const mm :: target :: Disjoineds* const disjointeds,
		const mm :: target :: Comments* const comments
	) :
	ast :: target :: assertion :: Statement (label, variables, disjointeds, comments),
	proof_ (NULL) {
	}
	Theorem :: ~ Theorem() {
		deleteAggregateObject (proof_);
	}

	// target :: Theorem implementation
	void
	Theorem :: addProof (const mm :: target :: Proof* const proof)
	{
		proof_ = proof;
		const_cast<mm :: target :: Proof*>(proof)->setTheorem (this);
	}

	// target :: Statement implementation
	void
	Theorem :: addHypothesis (const object :: Targetive* const hypothesis) {
		Statement :: addHypothesis (hypothesis);
	}
	void
	Theorem :: addProposition (const object :: Targetive* const proposition) {
		Statement :: addProposition (proposition);
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Referable implementation
	void
	Theorem :: writeReference (String& string) const
	{
		if (Config :: removeProofs() || Config :: implicitSteps()) {
			string << mdl :: Token :: problem_ << space;
		} else {
			string << mdl :: Token :: theorem_ << space;
		}
		Statement :: writeReference (string);
	}

	// object :: Targetive implementation
	void
	Theorem :: complete (mm :: target :: Block* const block) const
	{
		Statement :: complete (block);
		proof_->complete (block);
	}

	// object :: Writable implementation
	void
	Theorem :: write (String& string) const
	{
		Statement :: write (string);
		string << endLine;
		proof_->write (string);
		string << endLine;
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
		volume += Statement :: getVolume();
		volume += getAggregateVolume (proof_);
		return volume;
	}
	Size_t
	Theorem :: getSizeOf() const {
		return sizeof (Theorem);
	}
}
}
}
}


