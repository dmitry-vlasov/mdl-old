/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_formula_subset_normal_Simple.cpp              */
/* Description:     simple formula of a ⊑ b type                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/lexer/del_lexer.hpp"
#include "del/source/del_source.hpp"

namespace del {
namespace source {
namespace formula {
namespace subset {
namespace normal {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Simple :: Simple
	(
		const Location location,
		const del :: Term* term_1,
		const del :: Term* term_2,
		const del :: Formula* image,
		const bool isRoot,
		const bool isPrimary,
		const bool isDefinition
	) :
	Normal
	(
		location,
		term_1,
		term_2,
		((image == NULL) ? this : image),
		isRoot,
		isPrimary,
		isDefinition
	) {
	}
	inline
	Simple :: Simple (const del :: Formula* simple) :
	Normal (simple) {
	}
	inline
	Simple :: Simple (const Simple& simple) :
	Normal (simple) {
	}
	Simple :: ~ Simple() {
	}

	// del :: Formula implementation
	bool
	Simple :: isTrue (const del :: Model* model) const
	{
		const Symbol a = getTerm (0)->getSymbol();
		const Symbol b = getTerm (1)->getSymbol();
		return model->isTrueSubseteq (a, b);
	}
	bool
	Simple :: isTrue (const del :: Model* model, const set :: Formula* untheory) const
	{
		const Symbol a = getTerm (0)->getSymbol();
		const Symbol b = getTerm (1)->getSymbol();
		return model->isTrueSubseteq (a, b, untheory);
	}
	const del :: Term*
	Simple :: evalInterpolant (const del :: Model* model, const del :: Signature* delta) const
	{
		const Symbol a = getTerm (0)->getSymbol();
		const Symbol b = getTerm (1)->getSymbol();
		return model->evalInterpolant (a, b, delta);
	}
	bool
	Simple :: isConnected (const del :: Symbol& symbol) const
	{
		if (symbol.isRelation()) {
			return false;
		}
		const value :: Variable a = getTerm (0)->getSymbol().getVariable();
		const value :: Variable b = getTerm (1)->getSymbol().getVariable();
		const value :: Variable c = symbol.getVariable();
		return (a == c) || (b == c);
	}
	bool
	Simple :: decompose
	(
		del :: Theory* theory,
		const del :: Signature* delta,
		const bool forTheFirstTime
	)
	{
		if (forTheFirstTime) {
			if (decomposed_) {
				return false;
			}
			decomposed_ = true;
			if (nothingToDecompose (delta)) {
				return false;
			}
			return split (theory, delta);
		} else {
			return false;
		}
	}
	bool
	Simple :: apply (del :: Model* model) const
	{
		// If A' ∈ S(A) and A' ⊑ B ∈ T then S(A) := S(A) ∪ {B}
		// If c ∈ CS(A) and A ⊑ B ∈ T then CS(B) := CS(B) ∪ {c}
		bool result = false;
		const Symbol a = getTerm (0)->getSymbol();
		const Symbol b = getTerm (1)->getSymbol();

		model->predicates().registerVariable (a);
		model->predicates().registerVariable (b);

		const model :: Predicate*
			predicate_a = model->predicates().getPredicate (a);
		for (value :: Integer i = 0; i < predicate_a->getSize(); ++ i) {
			const model :: Positive*
				c = predicate_a->getNode (i);
			model :: Predicate*
				predicate_b = model->predicates().getPredicate (b);
			if (predicate_b->addNode (c->getVariable(), c, this)) {
				result = true;
			}
		}
		return result;
	}
	bool
	Simple :: extendWithCopies (del :: Theory* theory, const del :: Signature* delta) const
	{
		const Symbol a = getTerm (0)->getSymbol();
		const Symbol b = getTerm (1)->getSymbol();
		vector :: Symbol array (2);
		array.add (a);
		array.add (b);
		Iterator iterator (array, delta);
		if (iterator.isTrivial()) {
			return false;
		}
		//std :: cout << *this << std :: endl;
		//std :: cout << *delta << std :: endl;
		while (++ iterator) {
			const Symbol a_prime = iterator.getSymbol (0);
			const Symbol b_prime = iterator.getSymbol (1);

			const del :: Term* term_1_prime = NULL;
			const del :: Term* term_2_prime = NULL;
			if (a_prime.isTop()) {
				term_1_prime = new term :: Top();
			} else {
				term_1_prime = new term :: Variable (a_prime);
			}
			if (b_prime.isTop()) {
				term_2_prime = new term :: Top();
			} else {
				term_2_prime = new term :: Variable (b_prime);
			}

			del :: Formula* simple = new Simple
			(
				Location(),
				term_1_prime,
				term_2_prime,
				image_,
				isRoot_,
				isPrimary_,
				isDefinition_
			);
			//std :: cout << *simple << std :: endl;
			if (theory->containsFormula (simple)) {
				simple->commitSuicide();
			} else {
				theory->addFormula (simple);
			}
		}
		return true;
	}

	del :: Formula :: Kind
	Simple :: getKind() const {
		return SIMPLE_SUB_KIND;
	}

	// del :: Cloneable implementation
	del :: Formula*
	Simple :: clone() const
	{
		if (hasInvalidKind()) {
			return Normal :: create
			(
				term_1_->clone(),
				term_2_->clone(),
				image_,
				isRoot_,
				isPrimary_,
				isDefinition_
			);
		} else {
			return new Simple (*this);
		}
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Writable implementation
	/*void
	Simple :: replicate (String& string) const
	{
		string << location_.getIndent();
		const String& a = Table :: variables()->get (a_);
		const String& b = Table :: variables()->get (b_);
		string << a << space << Token :: subset_ << space << b;
	}
	void
	Simple :: translate (String& string) const {
		replicate (string);
	}*/

	// object :: Object implementation
	void
	Simple :: commitSuicide() {
		delete this;
	}
	Size_t
	Simple :: getVolume() const {
		return Normal :: getVolume();
	}
	Size_t
	Simple :: getSizeOf() const {
		return sizeof (Simple);
	}

	/****************************
	 *		Private members
	 ****************************/

	bool
	Simple :: split (del :: Theory* theory, const del :: Signature* delta)
	{
		if (term_1_->isOfSignature (delta) || term_2_->isOfSignature (delta)) {
			return false;
		}
		// check if some term in formula is already in delta
		if (term_1_->getKind() == del :: Term :: VARIABLE_KIND) {
			const del :: Symbol symbol = term_1_->getSymbol();
			if (delta->containsSymbol (symbol)) {
				return false;
			}
		}
		if (term_2_->getKind() == del :: Term :: VARIABLE_KIND) {
			const del :: Symbol symbol = term_2_->getSymbol();
			if (delta->containsSymbol (symbol)) {
				return false;
			}
		}
		Memory :: stack().push();
		const del :: Expansion*
			deltaExpansion = source :: Decompose :: current()->getDeltaExpansion();
		const del :: Theory*
			deltaTheory = source :: Decompose :: current()->getDeltaTheory();
		const Model*
			prebuildModel = source :: Decompose :: current()->getDeltaModel();

		Model* model = const_cast<Model*>(prebuildModel);

		del :: Term*
			leftTerm = new term :: Variable (term_1_->getPrimitivization());
		del :: Term*
			rightTerm = new term :: Variable (term_2_->getPrimitivization());
		leftTerm->makeDeltaCopy (deltaExpansion);

		del :: Formula* formula = new Subset
		(
			location_,
			leftTerm,
			rightTerm,
			image_
		);

		const bool result = formula->isTrue (model);
		if (result) {
			Del :: statistics().data()->incSplit();
			model->clearNodes();
			const del :: Term*
				interpolant = formula->evalInterpolant (model, delta)->clone();

			//std :: cout << *this << std :: endl;
			//std :: cout << *formula << std :: endl;
			//std :: cout << *interpolant << std :: endl;

			interpolant = const_cast<del :: Term*>(interpolant)->simplify();
			insertInterpolant (theory, interpolant);
			const_cast<del :: Term*>(interpolant)->commitSuicide();
			theory->removeFormula (this);
		}
		formula->commitSuicide();
		Memory :: stack().pop();
		return result;
	}
	void
	Simple :: insertInterpolant
	(
		del :: Theory* theory,
		const del :: Term* interpolant
	) const
	{
		del :: Formula* formula_1 = create (term_1_->clone(), interpolant->clone(), image_, isRoot_, isPrimary_);
		del :: Formula* formula_2 = create (interpolant->clone(), term_2_->clone(), image_, isRoot_, isPrimary_);

		if (theory->containsFormula (formula_1)) {
			formula_1->commitSuicide();
		} else {
			theory->addFormula (formula_1);
		}
		if (theory->containsFormula (formula_2)) {
			formula_2->commitSuicide();
		} else {
			theory->addFormula (formula_2);
		}
	}
}
}
}
}
}


