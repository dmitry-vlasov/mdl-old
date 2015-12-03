/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File Name:       smm_source_Assertion.cpp                                 */
/* Description:     smm assertion                                            */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_SOURCE_ASSERTION_CPP_
#define SMM_SOURCE_ASSERTION_CPP_

#include "smm/auxiliary/smm_auxiliary.hpp"
#include "smm/lexer/smm_lexer.hpp"
#include "smm/source/smm_source.hpp"

namespace smm {
namespace source {

	/****************************
	 *		Public members
	 ****************************/

	Assertion :: Assertion
	(
		const Location& location,
		const vector :: Expression* variablesVector,
		const vector :: Expression* disjointedVector,
		const vector :: Expression* essentialVector,
		const vector :: Expression* floatingVector,
		const vector :: Expression* innerVector,
		const Expression* proposition,
		const smm :: Proof* proof
	) :
	location_ (location),
	variablesVector_ (variablesVector),
	disjointedVector_ (disjointedVector),
	essentialVector_ (essentialVector),
	floatingVector_ (floatingVector),
	innerVector_ (innerVector),
	proposition_ (proposition),
	proof_ (proof),
	index_ (index :: undefined :: ASSERTION)
	{
		if (proof_ != NULL) {
			const_cast<smm :: Proof*>(proof_)->setTheorem (this);
		}
		const_cast<index :: Assertion&>(index_) = Math :: assertions()->add (this);
		checkCorrectness();
	}
	Assertion :: ~ Assertion()
	{
		deleteAggregateObject (variablesVector_);
		deleteAggregateObject (disjointedVector_);
		deleteAggregateObject (essentialVector_);
		deleteAggregateObject (floatingVector_);
		deleteAggregateObject (innerVector_);
		deleteAggregateObject (proposition_);
		deleteAggregateObject (proof_);
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// smm :: Assertion implementation
	const Expression*
	Assertion :: getDisjointed (const index :: Arity index) const
	{
		if (index > getDisjointedArity()) {
			Error* error = new Error (location_, Error :: SEMANTIC);
			error->message() << "index overflow"<< endLine;
			error->message() << "--------------"<< endLine;
			error->message() << "reference to the " << index << space;
			error->message() << "disjointed, while disjointed arity is" << space;
			error->message() << getDisjointedArity() << endLine;
			throw error;
		}
		return disjointedVector_->getValue (index);
	}
	const Expression*
	Assertion :: getEssential (const index :: Arity index) const
	{
		if (index > getEssentialArity()) {
			Error* error = new Error (location_, Error :: SEMANTIC);
			error->message() << "index overflow"<< endLine;
			error->message() << "--------------"<< endLine;
			error->message() << "reference to the " << index << space;
			error->message() << "essential, while essential arity is" << space;
			error->message() << getEssentialArity() << endLine;
			throw error;
		}
		return essentialVector_->getValue (index);
	}
	const Expression*
	Assertion :: getFloating (const index :: Arity index) const
	{
		if (index > getFloatingArity()) {
			Error* error = new Error (location_, Error :: SEMANTIC);
			error->message() << "index overflow"<< endLine;
			error->message() << "--------------"<< endLine;
			error->message() << "reference to the " << index << space;
			error->message() << "floating, while floating arity is" << space;
			error->message() << getFloatingArity() << endLine;
			throw error;
		}
		return floatingVector_->getValue (index);
	}
	const Expression*
	Assertion :: getInner (const index :: Arity index) const
	{
		if (index > getInnerArity()) {
			Error* error = new Error (location_, Error :: SEMANTIC);
			error->message() << "index overflow"<< endLine;
			error->message() << "--------------"<< endLine;
			error->message() << "reference to the " << index << space;
			error->message() << "inner variable, while inner arity is" << space;
			error->message() << getInnerArity() << endLine;
			throw error;
		}
		return innerVector_->getValue (index);
	}


	index :: Arity
	Assertion :: getDisjointedArity() const {
		return disjointedVector_->getSize();
	}
	index :: Arity
	Assertion :: getEssentialArity() const {
		return essentialVector_->getSize();
	}
	index :: Arity
	Assertion :: getFloatingArity() const {
		return floatingVector_->getSize();
	}
	index :: Arity
	Assertion :: getInnerArity() const {
		return innerVector_->getSize();
	}


	const Expression*
	Assertion :: getProposition() const {
		return proposition_;
	}
	const smm :: Proof*
	Assertion :: getProof() const {
		return proof_;
	}
	bool
	Assertion :: areDisjointed
	(
		const value :: Literal x,
		const value :: Literal y
	) const
	{
		for (index :: Arity i = 0; i < disjointedVector_->getSize(); ++ i) {
			const Expression*
				disjointed = disjointedVector_->getValue (i);
			if (disjointed->contains (x) && disjointed->contains (y)) {
				return true;
			}
		}
		return false;
	}

	index :: Assertion
	Assertion :: getIndex() const {
		return index_;
	}
	void
	Assertion :: showHeader (String& string) const
	{
		string << Token :: blockBegin_ << endLine;
		showBody (string);
		string << Token :: blockEnd_ << endLine;
	}
	void
	Assertion :: showName (String& string) const
	{
		if (proof_ == NULL) {
			string << Token :: prefix_a_;
		} else {
			string << Token :: prefix_p_;
		}
		if (Config :: noLabels()) {
			string << index_ << space;
		} else {
			string << Table :: labels()->get (index_) << space;
		}
	}

	// object :: Verifiable implementation
	void
	Assertion :: verify() const
	{
		try {
			if (proof_ != NULL) {
				proof_->verify();
			}
		} catch (Error* error) {
			error->add (location_);
			error->message() << "in theorem p" << index_ << endLine;
			show (error->message());
			throw error;
		}
	}

	// object :: Object implementation
	void
	Assertion :: commitSuicide() {
		delete this;
	}
	Size_t
	Assertion :: getVolume() const
	{
		Size_t volume = 0;
		volume += location_.getVolume();
		volume += getAggregateVolume (variablesVector_);
		volume += getAggregateVolume (disjointedVector_);
		volume += getAggregateVolume (essentialVector_);
		volume += getAggregateVolume (floatingVector_);
		volume += getAggregateVolume (innerVector_);
		volume += getAggregateVolume (proposition_);
		volume += getAggregateVolume (proof_);
		return volume;
	}
	Size_t
	Assertion :: getSizeOf() const {
		return sizeof (Assertion);
	}
	void
	Assertion :: show (String& string) const
	{
		string << Token :: blockBegin_ << endLine;
		showBody (string);
		if (proof_ != NULL) {
			string << tab << *proof_ << endLine;
		}
		string << Token :: blockEnd_ << endLine;
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Assertion :: showBody (String& string) const
	{
		for (index :: Arity i = 0; i < variablesVector_->getSize(); ++ i) {
			const Expression* variables = variablesVector_->getValue (i);
			string << tab << Token :: variable_ << space;
			string << *variables << Token :: end_ << endLine;
		}
		for (index :: Arity i = 0; i < disjointedVector_->getSize(); ++ i) {
			const Expression* disjointed = disjointedVector_->getValue (i);
			string << tab << Token :: disjointed_ << space;
			string << *disjointed << Token :: end_ << endLine;
		}
		for (index :: Arity i = 0; i < essentialVector_->getSize(); ++ i) {
			const Expression* essential = essentialVector_->getValue (i);
			string << tab << Token :: prefix_e_ << i << space;
			string << Token :: essential_ << space;
			string << *essential << Token :: end_ << endLine;
		}
		for (index :: Arity i = 0; i < floatingVector_->getSize(); ++ i) {
			const Expression* floating = floatingVector_->getValue (i);
			string << tab << Token :: prefix_f_ << i << space;
			string << Token :: floating_ << space;
			string << *floating << Token :: end_ << endLine;
		}
		for (index :: Arity i = 0; i < innerVector_->getSize(); ++ i) {
			const Expression* inner = innerVector_->getValue (i);
			string << tab << Token :: prefix_i_ << i << space;
			string << Token :: floating_ << space;
			string << *inner << Token :: end_ << endLine;
		}
		if (proof_ == NULL) {
			string << tab << Token :: prefix_a_ << index_ << space;
			string << Token :: axiomatic_ << space;
			string << *proposition_ << Token :: end_ << endLine;
		} else {
			string << tab << Token :: prefix_p_ << index_ << space;
			string << Token :: provable_ << space;
			string << *proposition_ << Token :: equality_ << endLine;
		}
	}
	void
	Assertion :: checkCorrectness()
	{
		checkVariablesCorrectness();
		checkDisjointedCorrectness();
		checkFloatingCorrectness();
		checkInnerCorrectness();
		checkVectorCorrectness (essentialVector_);
		checkExpressionCorrectness (proposition_);
	}
	void
	Assertion :: checkVariablesCorrectness() const
	{
		for (index :: Arity i = 0; i < variablesVector_->getSize(); ++ i) {
			const Expression* variables = variablesVector_->getValue (i);
			for (index :: Literal j = 0; j < variables->getSize(); ++ j) {
				const Symbol& variable = variables->getSymbol (j);
				if (Math ::constants()->contain (variable.getLiteral())) {
					Error* error = new Error (location_, Error :: SEMANTIC);
					error->message() << "symbol" << space << variable;
					error->message() << "is declared as a constant and a variable simultaneously." << endLine;
					throw error;
				}
			}
		}
	}
	bool
	Assertion :: isVariable (const value :: Literal x) const
	{
		for (index :: Arity i = 0; i < variablesVector_->getSize(); ++ i) {
			const Expression* variables = variablesVector_->getValue (i);
			for (index :: Literal j = 0; j < variables->getSize(); ++ j) {
				const Symbol& variable = variables->getSymbol (j);
				if (variable.getLiteral() == x) {
					return true;
				}
			}
		}
		return false;
	}
	void
	Assertion :: checkDisjointedCorrectness() const
	{
		for (index :: Arity i = 0; i < disjointedVector_->getSize(); ++ i) {
			const Expression* disjointed = disjointedVector_->getValue (i);
			if (disjointed->getSize() < 2) {
				Error* error = new Error (location_, Error :: SEMANTIC);
				error->message() << "less then 2 disjointed variables." << endLine;
				throw error;
			}
			for (index :: Literal j = 0; j < disjointed->getSize(); ++ j) {
				const Symbol& variable = disjointed->getSymbol (j);
				if (!isVariable (variable.getLiteral())) {
					Error* error = new Error (location_, Error :: SEMANTIC);
					error->message() << "symbol" << space << variable << space;
					error->message() << "in the disjointed declaration" << space;
					error->message() << "is not declared as variable." << endLine;
					throw error;
				}
			}
		}
	}
	void
	Assertion :: checkFloatingCorrectness() const
	{
		for (index :: Arity i = 0; i < floatingVector_->getSize(); ++ i) {
			const Expression* floating = floatingVector_->getValue (i);
			if (floating->getSize() != 2) {
				Error* error = new Error (location_, Error :: SEMANTIC);
				error->message() << "floating declaration must contain exactly 2 literals." << endLine;
				throw error;
			}
			const Symbol& type = floating->getType ();
			const Symbol& variable = floating->getVariable ();
			if (!isVariable (variable.getLiteral())) {
				Error* error = new Error (location_, Error :: SEMANTIC);
				error->message() << "variable symbol" << space << variable << space;
				error->message() << "in the floating declaration" << space;
				error->message() << "is not declared as a variable." << endLine;
				throw error;
			}
			if (!Math :: constants()->contain (type.getLiteral())) {
				Error* error = new Error (location_, Error :: SEMANTIC);
				error->message() << "type symbol" << space << type << space;
				error->message() << "in the floating declaration" << space;
				error->message() << "is not declared as a constant." << endLine;
				throw error;
			}
		}
	}
	void
	Assertion :: checkInnerCorrectness() const
	{
		for (index :: Arity i = 0; i < innerVector_->getSize(); ++ i) {
			const Expression* inner = innerVector_->getValue (i);
			if (inner->getSize() != 2) {
				Error* error = new Error (location_, Error :: SEMANTIC);
				error->message() << "inner floating declaration must contain exactly 2 literals." << endLine;
				throw error;
			}
			const Symbol& type = inner->getType ();
			const Symbol& variable = inner->getVariable ();
			if (!isVariable (variable.getLiteral())) {
				Error* error = new Error (location_, Error :: SEMANTIC);
				error->message() << "variable symbol" << space << variable << space;
				error->message() << "in the inner floating declaration" << space;
				error->message() << "is not declared as a variable." << endLine;
				throw error;
			}
			if (!Math :: constants()->contain (type.getLiteral())) {
				Error* error = new Error (location_, Error :: SEMANTIC);
				error->message() << "type symbol" << space << type << space;
				error->message() << "in the inner floating declaration" << space;
				error->message() << "is not declared as a constant." << endLine;
				throw error;
			}
		}
	}
	void
	Assertion :: checkExpressionCorrectness (const Expression* expression) const
	{
		for (index :: Literal j = 0; j < expression->getSize(); ++ j) {
			const Symbol& symbol = expression->getSymbol (j);
			if (symbol.isVariable() && !isVariable (symbol.getLiteral())) {
				Error* error = new Error (location_, Error :: SEMANTIC);
				error->message() << "symbol" << space << symbol << space;
				error->message() << "in the expression declaration" << space;
				error->message() << "is not declared as variable." << endLine;
				throw error;
			}
		}
	}
	void
	Assertion :: checkVectorCorrectness (const vector :: Expression* vector) const
	{
		for (index :: Arity i = 0; i < vector->getSize(); ++ i) {
			const Expression* expression = vector->getValue (i);
			checkExpressionCorrectness (expression);
		}
	}
}
}

#endif /*SMM_SOURCE_ASSERTION_CPP_*/

