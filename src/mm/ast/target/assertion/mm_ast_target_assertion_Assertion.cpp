/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_ast_target_assertion_Assertion.cpp                    */
/* Description:     mdl assertion base class                                 */
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

	Assertion :: Assertion
	(
		const value :: Label label,
		const mm :: target :: Variables* const variables,
		const mm :: target :: Disjoineds* const disjoineds,
		const mm :: target :: Comments* const comments
	) :
	label_ (label),
	variables_ (variables),
	disjoineds_ (disjoineds),
	comments_ (comments) {
	}
	Assertion :: ~ Assertion()
	{
		deleteAggregateObject (variables_);
		deleteAggregateObject (disjoineds_);
		deleteAggregateObject (comments_);
	}

using manipulator :: space;
using manipulator :: tab;
using manipulator :: endLine;

	// object :: Referable implementation
	void
	Assertion :: writeReference (String& string) const {
		string << Table :: assertionLabels()->getCorrectName (label_) << space;
	}
	void
	Assertion :: writeIdentificator (String& string) const {
		string << Table :: assertionLabels()->getCorrectName (label_) << space;
	}

	// object :: Targetive implementation
	void
	Assertion :: complete (mm :: target :: Block* const block) const
	{
		variables_->complete (block);
		if (disjoineds_ != NULL) {
			disjoineds_->complete (block);
		}
	}

	// object :: Writable implementation
	void
	Assertion :: write (String& string) const
	{
		comments_->write (string);
		string << tab;
		writeReference (string);
		variables_->write (string);
		if (disjoineds_ != NULL) {
			disjoineds_->write (string);
		}
		string << endLine;
	}

	// object :: Object implementation
	Size_t
	Assertion :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (variables_);
		volume += getAggregateVolume (disjoineds_);
		volume += getAggregateVolume (comments_);
		return volume;
	}
	Size_t
	Assertion :: getSizeOf() const {
		return sizeof (Assertion);
	}
}
}
}
}



