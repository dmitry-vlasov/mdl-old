/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_ast_source_reference_Hypothesis.cpp                   */
/* Description:     proof reference to hypothesis                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "auxiliary/mm_auxiliary.hpp"
#include "lexer/mm_lexer.hpp"
#include "ast/mm_ast.hpp"

namespace mm {
namespace ast {
namespace source {
namespace reference {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Hypothesis :: Hypothesis
	(
		const Location& location,
		const mm :: source :: Hypothesis* const hypothesis
	) :
	//location_ (location),
	hypothesis_ (hypothesis) {
	}
	Hypothesis :: ~ Hypothesis() {
	}

using manipulator :: endLine;
using manipulator :: tab;

	// source :: Reference implementation
	void
	Hypothesis :: operateCheck
	(
		Stack* const stack,
		const mm :: source :: Assertion* const assertion
	) const
	{
		try {
			hypothesis_->pushSelf (stack);
		} catch (Error* error) {
			error->message() << "hypothesis push failed." << endLine;
			error->message() << tab  << *this << endLine;
			throw error;
		}
	}
	const mm :: target :: Step*
	Hypothesis :: operateTranslate
	(
		Stack* const stack,
		const mm :: source :: Assertion* const assertion,
		const mm :: source :: Proof* const proof
	) const
	{
		try {
			hypothesis_->pushSelf (stack);
			return hypothesis_->needDeclaration (assertion, proof);
		} catch (Error* error) {
			error->message() << "hypothesis push failed." << endLine;
			error->message() << tab  << *this << endLine;
			throw error;
		}
	}

using manipulator :: space;

	// object :: Writable implementation
	void
	Hypothesis :: write (String& string) const {
		const value :: Label
			label = hypothesis_->getLabel();
		string << Table :: hypothesisLabels()->get (label) << space;
	}

	// object :: Object implementation
	void
	Hypothesis :: commitSuicide() {
		delete this;
	}
	Size_t
	Hypothesis :: getVolume() const {
		return 0;
	}
	Size_t
	Hypothesis :: getSizeOf() const {
		return sizeof (Hypothesis);
	}
}
}
}
}


