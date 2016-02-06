/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_ast_source_Assertion.cpp                              */
/* Description:     metamath assertion                                       */
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

	/****************************
	 *		Public members
	 ****************************/

	Assertion :: Assertion
	(
		const Location& location,
		const value :: Label label,
		const vector :: Literal& literalVector,
		mm :: source :: Block* const block,
		const mm :: source :: Comments* comments
	) :
	location_ (location),
	label_ (label),
	disjoined_ (block->getDisjoined()),
	hypothesis_ (block->getHypothesis()),
	comments_ (comments),
	proposition_ (NULL),
	variables_ (),
	statement_ (NULL)
	{
		initStatic();
		try {
			proposition_ = new Expression (location, literalVector, block);
			block->pushAssertion (this);
			computeVariables();
		} catch (Error* error) {
			error->add (location_);
			throw error;
		}
	}
	Assertion :: ~ Assertion()
	{
		deleteAggregateObject (comments_);
		deleteAggregateObject (proposition_);
		deleteAggregateObject (substitution_);
		deleteAggregateObject (localStack_);
		deleteAggregateObject (arguments_);
	}

	// mm :: Assertion implementation
	void
	Assertion :: applyCheck (Stack* const stack) const
	{
		substitution_->clear();
		unify (stack, hypothesis_);
		// true means check
		checkHypothesis (hypothesis_, true);
		pushPropositionCheck (stack);
	}
	const mm :: target :: Step*
	Assertion :: applyTranslate (Stack* const stack) const
	{
		substitution_->clear();
		arguments_->clear();
		unify (stack, hypothesis_);
		// false means not check, i.e. translation
		checkHypothesis (hypothesis_, false);
		return pushPropositionTranslate (stack);
	}
	bool
	Assertion :: areDisjoined
	(
		const value :: Literal variable_1,
		const value :: Literal variable_2
	) const
	{
		if (disjoined_ != NULL) {
			return disjoined_->areDisjoined (variable_1, variable_2);
		} else {
			return false;
		}
	}
	void
	Assertion :: checkDisjoined (const mm :: source :: Assertion* const theorem) const {
		substitution_->checkDisjoinedRestrictions (this, theorem);
	}
	bool
	Assertion :: newVariable (const value :: Literal variable) const {
		return !variables_.contains (variable);
	}

	// object :: Expressive implementation
	bool
	Assertion :: isEqual (const mm :: Expression* const expression) const {
		return (*proposition_ == *expression);
	}
	void
	Assertion :: assignTo (const mm :: Expression* const expression) {
		const_cast<Expression&>(*proposition_) = *expression;
	}

	// object :: Labeled implementation
	value :: Label
	Assertion :: getLabel() const {
		return label_;
	}

	// object :: Translatable implementation
	bool
	Assertion :: isBlock() const {
		return false;
	}
	bool
	Assertion :: isDisjoined() const {
		return false;
	}
	bool
	Assertion :: isFloating() const {
		return false;
	}
	bool
	Assertion :: isEssential() const {
		return false;
	}

	// object :: Object implementation
	Size_t
	Assertion :: getVolume() const
	{
		Size_t volume = 0;
		volume += location_.getVolume();
		volume += getAggregateVolume (proposition_);
		volume += variables_.getVolume();
		volume += getAggregateVolume (comments_);
		if (!staticVolumeCounted_) {
			volume += getAggregateVolume (substitution_);
			volume += getAggregateVolume (localStack_);
			volume += getAggregateVolume (arguments_);
			staticVolumeCounted_ = true;
		}
		return volume;
	}
	Size_t
	Assertion :: getSizeOf() const {
		return sizeof (Assertion);
	}

	/****************************
	 *		Protected members
	 ****************************/

	void
	Assertion :: translateDefinition (mm :: target :: Statement* const statement) const
	{
		if (!isDefinition()) {
			return;
		}
		mm :: target :: Definition*
			definition = dynamic_cast<mm :: target :: Definition*>(statement);
		const mm :: target :: Term* const
			defiendum = new ast :: target :: term :: Defiendum (proposition_);
		const mm :: target :: Term* const
			definiens = new ast :: target :: term :: Definiens (proposition_);
		definition->addDefiendum (defiendum);
		definition->addDefiniens (definiens);
	}
	void
	Assertion :: translateProposition (mm :: target :: Statement* const statement) const
	{
		const mm :: target :: Proposition*
			mdlProposition = NULL;
		if (isDefinition()) {
			mdlProposition = new ast :: target :: proposition :: Definition (proposition_);
		} else {
			mdlProposition = new ast :: target :: proposition :: Statement (proposition_);
		}
		statement->addProposition (mdlProposition);
		statement_ = statement;
	}
	void
	Assertion :: translateTerm (mm :: target :: Syntactic* const syntactic) const
	{
		const mm :: target :: Term* const
			term = new ast :: target :: term :: Rule (proposition_);
		syntactic->addTerm (term);
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Assertion :: computeVariables()
	{
		const mm :: source :: Hypothesis*
			hypothesis = hypothesis_;
		proposition_->collectVariables (variables_);
		while (hypothesis != NULL) {
			hypothesis->collectEssentialVariables (variables_);
			hypothesis = hypothesis->getPrevious();
		}
	}
	inline void
	Assertion :: computeDisjoineds () const
	{
		disjoined_ =
			(disjoined_ == NULL) ?
			NULL :
			new ast :: source :: Disjoined (disjoined_, variables_);
	}
	void
	Assertion :: unify
	(
		Stack* const stack,
		const mm :: source :: Hypothesis* const hypothesis
	) const
	{
		if (hypothesis == NULL) {
			return;
		}
		const stack :: Line* const
			line = (hypothesis->isRelevant (variables_)) ? stack->pop() : NULL;

		unify (stack, hypothesis->getPrevious());

		if (line != NULL) {
			hypothesis->checkFloating (line->getExpression(), substitution_);
			hypothesis->pushSelf (localStack_, line);
		}
	}
	void
	Assertion :: checkHypothesis
	(
		const mm :: source :: Hypothesis* const hypothesis,
		const bool isChecking
	) const
	{
		if (hypothesis == NULL) {
			return;
		}
		const stack :: Line* const
			line = (hypothesis->isRelevant (variables_)) ? localStack_->pop() : NULL;

		if (line != NULL) {
			hypothesis->checkEssential (line, substitution_);
		}
		checkHypothesis (hypothesis->getPrevious(), isChecking);

		if (!isChecking && (line != NULL) && (line->getExpression()->isStatement())) {
			const mm :: target :: Step* const
				step = line->getStep();
			arguments_->add (step);
		}
	}
	stack :: Line*
	Assertion :: pushPropositionCheck (Stack* const stack) const
	{
		stack :: Line* line = stack->push();
		const Expression* const
			expression = substitution_->execute (proposition_);
		line->copyExpression (expression);
		return line;
	}
	const mm :: target :: Step*
	Assertion :: pushPropositionTranslate (Stack* const stack) const
	{
		stack :: Line* line = pushPropositionCheck (stack);
		if (line->isTerm()) {
			return NULL;
		}

		const mm :: target :: Step* const
			step = new ast :: target :: step :: Assertion
			(
				statement_,
				arguments_,
				line->getExpression()
			);
		line->setStep (step);
		return step;
	}

	/********************************
	 *		Translation part
	 ********************************/

	mm :: target :: Variables*
	Assertion :: translateVariables (const mm :: source :: Hypothesis* const hypothesis) const
	{
		if (hypothesis == NULL) {
			return new ast :: target :: Variables();
		}
		mm :: target :: Variables* const
			variables = translateVariables (hypothesis->getPrevious());
		if (hypothesis->isFloating()) {
			if (hypothesis->isRelevant (variables_)) {
				const mm :: target :: Typing* const
					variable = dynamic_cast<const mm :: target :: Typing* const>
						(hypothesis->translate());
				variables->addVariable (variable);
			}
		}
		return variables;
	}
	mm :: target :: Disjoineds*
	Assertion :: translateDisjoineds
	(
		const mm :: source :: Disjoined* const disjoined,
		const bool axiomatic
	) const
	{
		if (disjoined == NULL) {
			return new ast :: target :: Disjoineds (axiomatic);
		}
		mm :: target :: Disjoineds* const
			targetDisjoineds = translateDisjoineds (disjoined->getPrevious(), axiomatic);
		const mm :: target :: Disjoined* const
			targetDisjoined = dynamic_cast<const mm :: target :: Disjoined*>(disjoined->translate());
		targetDisjoineds->addDisjoined (targetDisjoined);
		return targetDisjoineds;
	}
	void
	Assertion :: translateHypothesis
	(
		mm :: target :: Statement* const statement,
		const mm :: source :: Hypothesis* const mmHypothesis
	) const
	{
		if (mmHypothesis == NULL) {
			return;
		}
		translateHypothesis (statement, mmHypothesis->getPrevious());
		if (mmHypothesis->isEssential()) {
			const mm :: object :: Targetive* const
				mdlHypothesis = mmHypothesis->translate();
			statement->addHypothesis (mdlHypothesis);
		}
	}

	/********************************
	 *		Static private attributes
	 ********************************/

	bool
		Assertion :: staticVolumeCounted_ = false;
	mm :: Substitution*
		Assertion :: substitution_ = NULL;
	vector :: target :: Step*
		Assertion :: arguments_ = NULL;
	mm :: Stack*
		Assertion :: localStack_ = NULL;
}
}
}



