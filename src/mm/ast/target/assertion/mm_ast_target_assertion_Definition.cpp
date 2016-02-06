/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_assertion_Definition.cpp                   */
/* Description:     mdl definition                                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "auxiliary/mm_auxiliary.hpp"
#include "mdl/lexer/mdl_lexer_Token.hpp"
#include "ast/mm_ast.hpp"

namespace mm {
namespace ast {
namespace target {
namespace assertion {

	/****************************
	 *		Public members
	 ****************************/

	Definition :: Definition
	(
		const value :: Label label,
		const mm :: target :: Variables* const variables,
		const mm :: target :: Disjoineds* const disjoineds,
		const mm :: target :: Comments* const comments
	) :
	ast :: target :: assertion :: Statement (label, variables, disjoineds, comments) {
	}
	Definition :: ~ Definition()
	{
		deleteAggregateObject (defiendum_);
		deleteAggregateObject (definiens_);
	}

	// target :: Definition implementation
	void
	Definition :: addDefiendum (const object :: Targetive* const defiendum) {
		defiendum_ = defiendum;
	}
	void
	Definition :: addDefiniens (const object :: Targetive* const definiens) {
		definiens_ = definiens;
	}

	// target :: Statement implementation
	void
	Definition :: addHypothesis (const object :: Targetive* const hypothesis) {
		hypotheses_.addLast (hypothesis);
	}
	void
	Definition :: addProposition (const object :: Targetive* const proposition) {
		propositions_.addLast (proposition);
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Referable implementation
	void
	Definition :: writeReference (String& string) const
	{
		string << mdl :: Token :: definition_ << space;
		Assertion :: writeReference (string);
	}

	// object :: Targetive implementation
	void
	Definition :: complete (mm :: target :: Block* const block) const
	{
		Assertion :: complete (block);
		defiendum_->complete (block);
		definiens_->complete (block);
	}

	// object :: Writable implementation
	void
	Definition :: write (String& string) const
	{
		Assertion :: write (string);
		string << tab << mdl :: Token :: openBrace_ << endLine;
		defiendum_->write (string);
		definiens_->write (string);
		if (!hypotheses_.isEmpty()) {
			Statement :: writeHypotheses (string);
		}
		string << tab << tab << mdl :: Token :: horisontalBar_ << endLine;
		Statement :: writePropositions (string);
		string << tab << mdl :: Token :: closeBrace_ << endLine;
		string << endLine;
	}

	// object :: Object implementation
	void
	Definition :: commitSuicide() {
		delete this;
	}
	Size_t
	Definition :: getVolume() const
	{
		Size_t volume = 0;
		volume += Statement :: getVolume();
		volume += getAggregateVolume (defiendum_);
		volume += getAggregateVolume (definiens_);
		return volume;
	}
	Size_t
	Definition :: getSizeOf() const {
		return sizeof (Definition);
	}
}
}
}
}


