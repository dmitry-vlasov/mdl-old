/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File Name:       smm_source_Proof.cpp                                     */
/* Description:     smm proof                                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_SOURCE_PROOF_CPP_
#define SMM_SOURCE_PROOF_CPP_

#include "smm/auxiliary/smm_auxiliary.hpp"
#include "smm/lexer/smm_lexer.hpp"
#include "smm/source/smm_source.hpp"

namespace smm {
namespace source {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Proof :: Proof
	(
		const Location& location,
		const vector :: Reference* referenceVector
	) :
	location_ (location),
	referenceVector_ (referenceVector) {
		initStatic();
	}
	Proof :: ~ Proof()
	{
		deleteAggregateObject (referenceVector_);
		deleteAggregateObject (substitution_);
		deleteAggregateObject (stack_);
	}

	// smm :: Proof implementation
	void
	Proof :: setTheorem (const smm :: Assertion* const theorem) {
		theorem_ = theorem;
	}

	// object :: Verifiable implementation
	void
	Proof :: verify () const
	{
		for (index :: Step i = 0; i < referenceVector_->getSize(); ++ i) {
			const Reference&
				reference = referenceVector_->getReference (i);
			try {
				verifyStep (reference);
			} catch (Error* error) {
				error->message() << "verification of step" << space;
				error->message() << i << space << "failure." << endLine;
				error->message() << "----------------------------------------" << endLine;
				error->message() << "reference" << space << i;
				error->message() << ":" << space << reference << endLine;
				error->message() << endLine;
				throw error;
			}
		}
		const Expression&
			finalExpression = *(stack_->pop());
		const Expression&
			proposition = *(theorem_->getProposition());
		if (finalExpression != proposition) {
			Error* error = new Error (Error :: VERIFICATION);
			error->message() << "final statement mismatch." << endLine;
			error->message() << "-------------------------" << endLine;
			error->message() << "final expression :" << space << finalExpression << endLine;
			error->message() << "proposition:" << space << proposition << endLine;
			error->message() << endLine;
			showStack (error);
			throw error;
		}
		if (!stack_->isEmpty()) {
			const Expression&
				stackExpression = *(stack_->pop());
			Error* error = new Error (Error :: VERIFICATION);
			error->message() << "stack is not empty at the end of the proof." << space;
			error->message() << "-------------------------------------------" << space;
			error->message() << "stack expression :" << space;
			error->message() << stackExpression << endLine;
			error->message() << endLine;
			showStack (error);
			throw error;
		}
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
		volume += getAggregateVolume (referenceVector_);
		return volume;
	}
	Size_t
	Proof :: getSizeOf() const {
		return sizeof (Proof);
	}
	void
	Proof :: show (String& string) const
	{
		for (index :: Step i = 0; i < referenceVector_->getSize(); ++ i) {
			const Reference&
				reference = referenceVector_->getReference (i);
			reference.show (string);
		}
		string << smm :: Token :: end_ << endLine;
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Proof :: verifyStep (const Reference& reference) const
	{
		switch(reference.getKind()) {
		case Token :: PREFIX_F :
			*(stack_->push()) = *(theorem_->getFloating (reference.getIndex())); break;
		case Token :: PREFIX_E :
			*(stack_->push()) = *(theorem_->getEssential (reference.getIndex())); break;
		case Token :: PREFIX_I :
			*(stack_->push()) = *(theorem_->getInner (reference.getIndex())); break;
		case Token :: PREFIX_A :
		case Token :: PREFIX_P : {
			const smm :: Assertion* assertion =
				Math :: assertions()->get (reference.getIndex());
			if (assertion == NULL) {
				Error* error = new Error (Error :: VERIFICATION);
				error->message() << "undefined assertion." << endLine;
				error->message() << "--------------------" << endLine;
				error->message() << "references by:" << space << reference << endLine;
				error->message() << endLine;
				showStack (error);
				throw error;
			}
			if (!(assertion->getIndex() < theorem_->getIndex())) {
				Error* error = new Error (Error :: VERIFICATION);
				error->message() << "application of assertion with greater index." << endLine;
				error->message() << "--------------------------------------------" << endLine;
				error->message() << "assertion index:" << space << assertion->getIndex() << endLine;
				error->message() << "theorem index:" << space << theorem_->getIndex() << endLine;
				error->message() << endLine;
				showStack (error);
				throw error;
			}
			try {
				apply (assertion); break;
			} catch (Error* error) {
				error->message() << "application of assertion" << space;
				assertion->showName (error->message());
				error->message() << "failure." << endLine;
				error->message() << "--------------------------------------------" << endLine;
				assertion->showHeader (error->message());
				error->message() << endLine;
				throw error;
			}
		}
		default : break;
		}
	}

	void
	Proof :: apply (const smm :: Assertion* assertion) const
	{
		substitution_->clear();
		applyFloating (assertion);
		applyEssential (assertion);
		try {
			substitution_->checkDisjointedRestrictions(assertion, theorem_);
		} catch (Error* error) {
			error->add (location_);
			error->message() << "disjoint restrictions violation." << endLine;
			error->message() << "--------------------------------" << endLine;
			error->message() << "substitution:" << endLine;
			substitution_->show (error->message());
			error->message() << endLine;
			showStack (error);
			throw error;
		}
		*(stack_->push()) = *(substitution_->execute (assertion->getProposition()));
	}

	void
	Proof :: applyFloating (const smm :: Assertion* assertion) const
	{
		const index :: Arity
			floatingArity = assertion->getFloatingArity();
		for (index :: Arity i = 0; i < floatingArity; ++ i) {
			const Expression* floatingExpr = assertion->getFloating (floatingArity - i - 1);
			if (stack_->isEmpty()) {
				Error* error = new Error (Error :: VERIFICATION);
				error->message() << "empty stack at floating pop." << endLine;
				throw error;
			}
			const Expression* stackExpr = stack_->pop();
			const Symbol&
				hypType = floatingExpr->getType();
			const Symbol
				stackType = stackExpr->getType();
			if (hypType != stackType) {
				Error* error = new Error (Error :: VERIFICATION);
				error->message() << "type mismatch." << endLine;
				error->message() << "--------------" << endLine;
				error->message() << "stack type:" << space << stackType << endLine;
				error->message() << "hyp type:" << space << hypType << endLine;
				error->message() << endLine;
				showStack (error);
				throw error;
			} else {
				substitution_->add (floatingExpr->getVariable().getLiteral(), stackExpr);
			}
		}
	}
	void
	Proof :: applyEssential (const smm :: Assertion* assertion) const
	{
		const index :: Arity
			essentialArity = assertion->getEssentialArity();
		for (index :: Arity i = 0; i < essentialArity; ++ i) {
			const Expression* essentialExpr = assertion->getEssential (essentialArity - i - 1);
			if (stack_->isEmpty()) {
				Error* error = new Error (Error :: VERIFICATION);
				error->message() << "empty stack at essential pop." << endLine;
				throw error;
			}
			const Expression* stackExpr = stack_->pop();
			if (*stackExpr != *(substitution_->execute (essentialExpr))) {
				Error* error = new Error (Error :: VERIFICATION);
				error->message() << "hypothesis mismatch." << endLine;
				error->message() << "--------------------" << endLine;
				error->message() << "stack expression:" << space << *stackExpr << endLine;
				error->message() << "hyp expression:" << space << *essentialExpr << endLine;
				error->message() << "substituted expression:" << space;
				error->message() << *(substitution_->execute (essentialExpr)) << endLine;
				error->message() << "substitution:" << space << endLine;
				substitution_->show (error->message());
				error->message() << endLine;
				showStack (error);
				throw error;
			}
		}
	}

	void
	Proof :: initStatic() const
	{
		if (stack_ == NULL) {
			stack_ = new stack :: Expression (INITIAL_STACK_CAPACITY);
			substitution_ = new Substitution (INITIAL_SUBSTITUTION_CAPACITY);
		}
	}
	void
	Proof :: showStack (String& string) const
	{
		if (!Config :: showStack()) {
			return;
		}
		string << "stack:" << endLine;
		string << "-----------------------" << endLine;
		if (stack_->isEmpty()) {
			string << "<is empty>" << endLine;
		} else {
			for (index :: Step i = 0; i < stack_->getVector().getSize(); ++ i) {
				const Expression* expression = stack_->getVector().getValue (i);
				string << *expression << endLine;
			}
		}
		string << "-----------------------" << endLine;
		string << endLine;
	}
	inline void
	Proof :: showStack (Error* error) const {
		showStack (error->message());
	}

	/*************************************
	 *		Private static attributes
	 *************************************/

	Substitution*
		Proof :: substitution_ = NULL;
	stack :: Expression*
		Proof :: stack_ = NULL;
}
}

#endif /*SMM_SOURCE_PROOF_CPP_*/
