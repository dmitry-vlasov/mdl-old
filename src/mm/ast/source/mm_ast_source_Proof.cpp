/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_ast_source_Proof.cpp                                  */
/* Description:     metamath proof                                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_SOURCE_PROOF_CPP_
#define MM_AST_SOURCE_PROOF_CPP_

#include "auxiliary/mm_auxiliary.hpp"
#include "lexer/mm_lexer.hpp"
#include "ast/mm_ast.hpp"

namespace mm {
namespace ast {
namespace source {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Proof :: Proof (const Location& location) :
	location_ (location),
	comments_ (NULL),
	assertion_ (NULL),
	referenceList_ (),
	proof_ (NULL) {
		initStatic();
	}
	Proof :: ~ Proof()
	{
		deleteAggregateObject (comments_);
		deleteAggregateObject (stack_);
	}

	// source :: Proof implementation
	void
	Proof :: setAssertion (const mm :: source :: Assertion* const assertion) {
		assertion_ = assertion;
	}
	void
	Proof :: addReference (const mm :: source :: Reference* const reference) {
		referenceList_.addLast (reference);
	}
	const Expression*
	Proof :: getFinalExpression() const
	{
		const mm :: stack :: Line* const
			finalLine = stack_->pop();
		if (!stack_->isEmpty()) {
			Error* error = new Error (location_, Error :: CHECKER);
			error->message() << "proof stack must contain exactly one expression" << endLine;
			showStack (error);
			throw error;
		}
		return finalLine->getExpression();
	}
	bool
	Proof :: newVariable (const value :: Literal variable) const {
		const bool result = !variables_.contains (variable);
		if (result) {
			variables_.add (variable);
		}
		return result;
	}
	void
	Proof :: addComments (const mm :: source :: Comments* comments) {
		comments_ = comments;
	}

	// object :: Verifiable implementation
	void
	Proof :: check() const
	{
		const list :: source :: Reference :: Node_*
			node = referenceList_.getFirst();
		const mm :: source :: Reference*
			reference = NULL;
		try {
			while (node != NULL) {
				reference = node->getValue();
				reference->operateCheck (stack_, assertion_);
				node = node->getNext();
			}
		} catch (Error* error) {
			error->add (location_);
			error->message() << "proof check failed." << endLine;
			showStack (error);
			throw error;
		}
	}

	// object :: Translatable implementation
	const object :: Targetive*
	Proof :: translate() const
	{
		const mm :: target :: Comments* const
			comments = new ast :: target :: Comments (comments_, true);
		mm :: target :: Proof* const
			proof = new ast :: target :: Proof (comments);
		const list :: source :: Reference :: Node_*
			node = referenceList_.getFirst();
		const mm :: source :: Reference*
			reference = NULL;
		while (node != NULL) {
			reference = node->getValue();
			const mm :: target :: Step* const
				step = reference->operateTranslate (stack_, assertion_, this);
			if (step != NULL) {
				proof->addStep (step);
			}
			node = node->getNext();
		}
		proof->finalize();
		return proof;
	}
	bool
	Proof :: isBlock() const {
		return false;
	}
	bool
	Proof :: isDisjoined() const {
		return false;
	}
	bool
	Proof :: isFloating() const {
		return false;
	}
	bool
	Proof :: isEssential() const {
		return false;
	}

	// object :: Writable implementation
	void
	Proof :: write (String& string) const
	{
		string << tab;
		const list :: source :: Reference :: Node_*
			node = referenceList_.getFirst();
		const mm :: source :: Reference*
			reference = NULL;
		while (node != NULL) {
			reference = node->getValue();
			reference->write (string);
			node = node->getNext();
		}
		string << mm :: Token :: end_ << endLine;
	}

	// object :: Object implementation
	void
	Proof :: commitSuicide() {
		delete this;
	}
	Size_t
	Proof :: getVolume() const
	{
		Size_t volume = 0;
		volume += location_.getVolume();
		volume += getAggregateVolume (comments_);
		volume += variables_.getVolume();
		volume += referenceList_.getVolume();
		if (!staticVolumeCounted_) {
			volume += getAggregateVolume (stack_);
			staticVolumeCounted_ = true;
		}
		return volume;
	}
	Size_t
	Proof :: getSizeOf() const {
		return sizeof (Proof);
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Proof :: initStatic() const
	{
		if (stack_ == NULL) {
			stack_ = new Stack (INITIAL_STACK_CAPACITY);
		}
	}
	void
	Proof :: showStack (Error* error) const
	{
		error->message() << "stack:" << endLine;
		error->message() << "-----------------------" << endLine;
		stack_->show (error->message());
		error->message() << "-----------------------" << endLine;
	}

	/********************************
	 *		Private static attributes
	 ********************************/

	bool
		Proof :: staticVolumeCounted_ = false;
	mm :: Stack*
		Proof :: stack_ = NULL;
}
}
}

#endif /*MM_AST_SOURCE_PROOF_CPP_*/
