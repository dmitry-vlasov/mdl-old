/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_ast_source_hypothesis_Essential.cpp                   */
/* Description:     essential metamath hypothesis                            */
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
namespace hypothesis {

	/****************************
	 *		Public members
	 ****************************/

	Essential :: Essential
	(
		const Location& location,
		const value :: Label label,
		const vector :: Literal& literalVector,
		mm :: source :: Block* const block
	) :
	location_ (location),
	label_ (label),
	expression_ (NULL),
	previous_ (block->getHypothesis()),
	index_ (0),
	step_ (NULL)
	{
		try {
			expression_ = new Expression (location, literalVector, block);
			block->pushHypothesis (this);
			getIndex();
			step_ = new target :: step :: Hypothesis (index_);
		} catch (Error* error) {
			error->add (location_);
			throw error;
		}
	}
	Essential :: ~ Essential()
	{
		deleteAggregateObject (expression_);
		deleteAggregateObject (step_);
	}

using manipulator :: endLine;

	// source :: Hypothesis implementation
	bool
	Essential :: isRelevant (const vector :: Literal&) const {
		return true;
	}
	void
	Essential :: checkFloating (const Expression*, Substitution* const) const {
	}
	void
	Essential :: checkEssential
	(
		const stack :: Line* stackLine,
		const Substitution* const substitution
	) const
	{
		const Expression* const
			expression = substitution->execute (expression_);
		const Expression* const
			stackExpression = stackLine->getExpression();
		if (!Config :: useGrammarCorrection()) {
			if (*stackExpression != *expression) {
				Error* error = new Error (location_, Error :: CHECKER);
				error->message() << "hypothesis does not match stack expression." << endLine;
				error->message() << "hypothesis: " << *expression_ << endLine;
				error->message() << "unified hypothesis: " << *expression << endLine;
				error->message() << "stack expression: " << *(stackLine->getExpression()) << endLine;
				throw error;
			}
			return;
		}
		const_cast<stack :: Line*>(stackLine)->copyExpression (expression);
		if (stackLine->getHypothesis() != NULL) {
			const_cast<stack :: Line*>(stackLine)->copyHypothesis (expression);
			stackLine->setHypothesis (NULL);
		}
	}
	void
	Essential :: collectEssentialVariables (vector :: Literal& variables) const {
		expression_->collectVariables (variables);
	}
	void
	Essential :: pushSelf (mm :: Stack* const stack, const stack :: Line* const line) const
	{
		mm :: stack :: Line*
			newLine = stack->push();
		if (line == NULL) {
			newLine->copyExpression (expression_);
			newLine->setHypothesis (this);
			newLine->setStep (step_);
		} else {
			newLine->setLine (line);
			line->setHypothesis (NULL);
		}
	}
	const mm :: target :: Step*
	Essential :: needDeclaration
	(
		const mm :: source :: Assertion* const,
		const mm :: source :: Proof* const
	) const {
		return NULL;
	}
	const mm :: source :: Hypothesis*
	Essential :: getPrevious() const {
		return previous_;
	}

	// object :: Expressive implementation
	bool
	Essential :: isEqual (const Expression* const expression) const {
		return (*expression_ == *expression);
	}
	void
	Essential :: assignTo (const Expression* const expression) {
		const_cast<Expression&>(*expression_) = *expression;
	}

	// object :: Labeled interface
	value :: Label
	Essential :: getLabel() const {
		return label_;
	}

	// object :: Translatable implementation
	const object :: Targetive*
	Essential :: translate() const {
		return new ast :: target :: Hypothesis (expression_, index_);
	}
	bool
	Essential :: isBlock() const {
		return false;
	}
	bool
	Essential :: isDisjoined() const {
		return false;
	}
	bool
	Essential :: isFloating() const {
		return false;
	}
	bool
	Essential :: isEssential() const {
		return true;
	}

using manipulator :: space;
using manipulator :: tab;

	// object :: Writable implementation
	void
	Essential :: write (String& string) const
	{
		const String&
			label = Table :: assertionLabels()->get (label_);
		string << tab << label << space;
		string << mm :: Token :: essential_ << space;
		string << *expression_ << mm :: Token :: end_ << endLine;
	}

	// object :: Object implementation
	void
	Essential :: commitSuicide() {
		delete this;
	}
	Size_t
	Essential :: getVolume() const
	{
		Size_t volume = 0;
		volume += location_.getVolume();
		volume += getAggregateVolume (expression_);
		volume += getAggregateVolume (step_);
		return volume;
	}
	Size_t
	Essential :: getSizeOf() const {
		return sizeof (Essential);
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Essential :: getIndex () const
	{
		const mm :: source :: Hypothesis*
			hypothesis = this;
		while (hypothesis != NULL) {
			if (hypothesis->isEssential()) {
				++ const_cast<index :: Arity&> (index_);
			}
			hypothesis = hypothesis->getPrevious();
		}
	}
}
}
}
}


