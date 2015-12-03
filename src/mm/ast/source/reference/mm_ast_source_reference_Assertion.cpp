/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_ast_source_reference_Assertion.cpp                    */
/* Description:     proof reference to assertion                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_SOURCE_REFERENCE_ASSERTION_CPP_
#define MM_AST_SOURCE_REFERENCE_ASSERTION_CPP_

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
	Assertion :: Assertion
	(
		const Location& location,
		const mm :: source :: Assertion* const assertion
	) :
	assertion_ (assertion) {
	}
	Assertion :: ~ Assertion() {
	}

using manipulator :: endLine;
using manipulator :: tab;

	// source :: Reference implementation
	void
	Assertion :: operateCheck
	(
		Stack* const stack,
		const mm :: source :: Assertion* const provable
	) const
	{
		if (!assertion_->isVerified()) {
			Error* error = new Error (Error :: CHECKER);
			error->message() << "reference to the unverified assertion in proof." << endLine;
			throw error;
		}
		try {
			assertion_->applyCheck (stack);
			assertion_->checkDisjoined (provable);
		} catch (Error* error) {
			error->message() << "assertion application failed." << endLine;
			error->message() << tab << *this << endLine;
			throw error;
		}
	}
	const mm :: target :: Step*
	Assertion :: operateTranslate
	(
		Stack* const stack,
		const mm :: source :: Assertion* const,
		const mm :: source :: Proof* const
	) const
	{
		try {
			return assertion_->applyTranslate (stack);
		} catch (Error* error) {
			error->message() << "assertion application failed." << endLine;
			error->message() << tab << *this << endLine;
			throw error;
		}
	}

using manipulator :: space;

	// object :: Writable implementation
	void
	Assertion :: write (String& string) const
	{
		const value :: Label
			label = assertion_->getLabel();
		string << Table :: assertionLabels()->get (label) << space;
	}

	// object :: Object implementation
	void
	Assertion :: commitSuicide() {
		delete this;
	}
	Size_t
	Assertion :: getVolume() const {
		return 0;
	}
	Size_t
	Assertion :: getSizeOf() const {
		return sizeof (Assertion);
	}
}
}
}
}

#endif /* MM_AST_SOURCE_REFERENCE_ASSERTION_CPP_ */
