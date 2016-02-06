/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_header_statement_Proposition.cpp                */
/* Description:     proposition statement class                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/math/mdl_math.hpp"
#include "mdl/form/mdl_form.hpp"

namespace mdl {
namespace form {
namespace header {
namespace statement {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Proposition :: Proposition
	(
		const Location& location,
		index :: Arity index,
		mdl :: Identificator* identificator,
		array :: Expression* expression,
		mdl :: Theory* theory
	) :
	form :: header :: statement :: Statement
	(
		location,
		index,
		identificator,
		expression,
		theory
	),
	header :: Line :: Counter(),
	experience_ (new Experience (this)),
	sourceIndex_ (counter_ ++),
	functionVector_ (INITIAL_FUNCTION_VECTOR_CAPACITY) {
		Math :: propositions()->addToSet (this);
	}
	Proposition :: ~ Proposition() {
		deleteAggregateObject (experience_);
	}

	inline void
	Proposition :: addEvaluationFunction (mdl :: evaluation :: Function* function) {
		functionVector_.add (function);
	}
	inline void
	Proposition :: replaceEvaluationFunction (const index :: Arity i, mdl :: evaluation :: Function* function) {
		functionVector_.getReference (i) = function;
	}

	// mdl :: Proposition interface
	const Location&
	Proposition :: getLocation() const {
		return location_;
	}
	index :: Assertion
	Proposition :: getSourceIndex() const {
		return sourceIndex_;
	}
	index :: Assertion
	Proposition :: getTargetIndex() const {
		return header :: Line :: Counter :: getIndex();
	}
	void
	Proposition :: incRate (const bool sign)
	{
		if (sign) {
			++ positiveRate_;
		} else {
			++ negativeRate_;
		}
	}
	value :: Integer
	Proposition :: getRate (const bool sign) const
	{
		if (sign) {
			return positiveRate_;
		} else {
			return negativeRate_;
		}
	}
	mdl :: statement :: Experience*
	Proposition :: getExperience () {
		return experience_;
	}
	mdl :: evaluation :: Function*
	Proposition :: getEvaluation (const value :: Name name)
	{
		mdl :: evaluation :: Function*
			function = getFunction (name);
		/*for (value :: Integer i = 0; i < functionVector_.getSize(); ++ i) {
			mdl :: evaluation :: Function*
				function = functionVector_.getValue (i);
			mdl :: Evaluation*
				evaluation = function->getEvaluation();
			if (evaluation->getName() == name) {
				return function;
			}
		}*/
		if (function != NULL) {
			return function;
		} else {
			assertion_->getEvaluation (name);
			return getFunction (name);
		}
	}
	const mdl :: statement :: Experience*
	Proposition :: getExperience () const {
		return experience_;
	}
	const mdl :: evaluation :: Function*
	Proposition :: getEvaluation (const value :: Name name) const
	{
		return getFunction (name);
		/*for (value :: Integer i = 0; i < functionVector_.getSize(); ++ i) {
			mdl :: evaluation :: Function*
				function = functionVector_.getValue (i);
			mdl :: Evaluation*
				evaluation = function->getEvaluation();
			if (evaluation->getName() == name) {
				return function;
			}
		}
		return NULL;*/
	}

	// object :: Buildable implementation
	void
	Proposition :: build()
	{
		Statement :: build();
		Statement :: proofNode_ =
			new form :: proof :: node :: Proposition
			(
				Statement :: assertion_,
				Statement :: index_,
				Statement :: expression_
			);
		Math :: propositions()->addToTree (this);
	}

using manipulator :: tab;
using manipulator :: endLine;
using manipulator :: underline;

	// object :: Writable implementation
	void
	Proposition :: translate (String& string) const {
		expression_->write (string);
	}
	void
	Proposition :: replicate (String& string) const
	{
		const Indent indent = location_.getIndent();
		string << indent << Token :: prop_ << space;
		if (assertion_ != NULL && (assertion_->getPropArity() > 1)) {
			string << (Statement :: index_ + 1) << space;
		}
		string << Token :: colon_ << space;
		identificator_->replicate (string);
		string << space << Token :: equality_ << space;
		string << Token :: turnstile_ << space;
		expression_->write (string, indent);
		string << Token :: semicolon_ << endLine;
	}

	// object :: Object implementation
	Size_t
	Proposition :: getVolume() const
	{
		Size_t volume = 0;
		volume += Statement :: getVolume();
		volume += getAggregateVolume (experience_);
		volume += functionVector_.getVolume();
		return volume;
	}
	Size_t
	Proposition :: getSizeOf() const {
		return sizeof (Proposition);
	}

	/****************************
	 *		Private members
	 ****************************/


	mdl :: evaluation :: Function*
	Proposition :: getFunction (const value :: Name name)
	{
		for (value :: Integer i = 0; i < functionVector_.getSize(); ++ i) {
			mdl :: evaluation :: Function*
				function = functionVector_.getValue (i);
			mdl :: Evaluation*
				evaluation = function->getEvaluation();
			if (evaluation->getName() == name) {
				return function;
			}
		}
		return NULL;
	}
	const mdl :: evaluation :: Function*
	Proposition :: getFunction (const value :: Name name) const
	{
		for (value :: Integer i = 0; i < functionVector_.getSize(); ++ i) {
			const mdl :: evaluation :: Function*
				function = functionVector_.getValue (i);
			const mdl :: Evaluation*
				evaluation = function->getEvaluation();
			if (evaluation->getName() == name) {
				return function;
			}
		}
		return NULL;
	}

	/************************************
	 *		Static private attributes
	 ************************************/

	index :: Assertion
		Proposition :: counter_ = 0;
}
}
}
}


