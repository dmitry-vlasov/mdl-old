/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_ast_source_Provable.cpp                               */
/* Description:     metamath provable assertion                              */
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
#include "math/mm_math.hpp"
#include "ast/mm_ast.hpp"

namespace mm {
namespace ast {
namespace source {

	/****************************
	 *		Public members
	 ****************************/

	Provable :: Provable
	(
		const Location& location,
		const value :: Label label,
		const vector :: Literal& literalVector,
		const mm :: source :: Proof* const proof,
		mm :: source :: Block* const block,
		const mm :: source :: Comments* comments
	) :
	Assertion (location, label, literalVector, block, comments),
	isVerified_ (false),
	proof_ (proof),
	theorem_ (NULL) {
		const_cast<mm :: source :: Proof*>(proof_)->setAssertion (this);
		Math :: assertions()->add (this);
	}
	Provable :: ~ Provable()
	{
		deleteAggregateObject (proof_);
	}

	// source :: Assertion implementation
	inline void
	Provable :: applyCheck (Stack* const stack) const {
		Assertion :: applyCheck (stack);
	}
	inline const mm :: target :: Step*
	Provable :: applyTranslate (Stack* const stack) const {
		return Assertion :: applyTranslate (stack);
	}
	inline bool
	Provable :: areDisjoined
	(
		const value :: Literal variable_1,
		const value :: Literal variable_2
	) const
	{
		return Assertion :: areDisjoined (variable_1, variable_2);
	}
	inline void
	Provable :: checkDisjoined (const mm :: source :: Assertion* const theorem) const {
		Assertion :: checkDisjoined (theorem);
	}
	inline bool
	Provable :: newVariable (const value :: Literal variable) const {
		return Assertion :: newVariable (variable);
	}
	bool
	Provable :: isAxiomatic() const {
		return false;
	}
	bool
	Provable :: isProvable() const {
		return true;
	}
	bool
	Provable :: isVerified() const {
		return isVerified_;
	}

	// object :: Expressive implementation
	inline bool
	Provable :: isEqual (const mm :: Expression* const expression) const {
		return Assertion :: isEqual (expression);
	}
	inline void
	Provable :: assignTo (const mm :: Expression* const expression) {
		Assertion :: assignTo (expression);
	}

	// object :: Labeled implementation
	inline value :: Label
	Provable :: getLabel() const {
		return Assertion :: getLabel();
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Verifiable implementation
	void
	Provable :: check() const
	{
		try {
			proof_->check();
			checkProposition();
		} catch (Error* error) {
			error->add (location_);
			error->message() << "proof failed." << endLine;
			error->message() << tab << Table :: assertionLabels()->get (label_) << endLine;
			throw (error);
		}
		isVerified_ = true;
	}

	// object :: Translatable implementation
	const object :: Targetive*
	Provable :: translate() const
	{
		if (!isStatement()) {
			return NULL;
		}
		if (theorem_ != NULL) {
			return theorem_;
		}
		const mm :: target :: Comments* const
			comments = dynamic_cast<const mm :: target :: Comments*>(comments_->translate());
		const mm :: target :: Variables* const
			variables = translateVariables();
		const mm :: target :: Disjoineds* const
			disjointeds = Config :: explicitDisjointeds() ? translateDisjoineds (false) : NULL;

		mm :: target :: Theorem* const
			theorem = new ast :: target :: Theorem (label_, variables, disjointeds, comments);
		translateHypothesis (theorem);
		translateProposition (theorem);
		const mm :: object :: Targetive* const
			proof = proof_->translate();
		theorem->addProof (dynamic_cast<const mm :: target :: Proof* const>(proof));
		theorem_ = theorem;
		return theorem_;
	}
	inline bool
	Provable :: isBlock() const {
		return Assertion :: isBlock();
	}
	inline bool
	Provable :: isDisjoined() const {
		return Assertion :: isDisjoined();
	}
	inline bool
	Provable :: isFloating() const {
		return Assertion :: isFloating();
	}
	inline bool
	Provable :: isEssential() const {
		return Assertion :: isEssential();
	}

	// object :: Writable implementation
	void
	Provable :: write (String& string) const
	{
		string << tab << Table :: assertionLabels()->get (label_) << space;
		string << mm :: Token :: provable_ << space;
		string << *proposition_ << mm :: Token :: proof_ << endLine;
		string << *proof_;
	}

	// object :: Object implementation
	void
	Provable :: commitSuicide() {
		delete this;
	}
	Size_t
	Provable :: getVolume() const
	{
		Size_t volume = 0;
		volume += Assertion :: getVolume();
		volume += getAggregateVolume (proof_);
		return volume;
	}
	Size_t
	Provable :: getSizeOf() const {
		return sizeof (Provable);
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Provable :: checkProposition () const
	{
		const Expression* const
			finalExpression = proof_->getFinalExpression();

		if (!Config :: useGrammarCorrection()) {
			if (!isEqual (finalExpression)) {
				Error* error = new Error (location_, Error :: CHECKER, "obtained expression differs from the theorem statement:\n");
				error->message() << "expression: " << *finalExpression << endLine;
				throw (error);
			}
			return;
		} else {
			const_cast<mm :: source :: Assertion*>
				(static_cast<const mm :: source :: Assertion*>(this))->assignTo (finalExpression);
		}
	}
}
}
}


