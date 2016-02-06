/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_formula_subset_normal_Conjunction.cpp         */
/* Description:     simple formula of a_1 ⊓  ... ⊓ a_n ⊑ b type               */
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
	Conjunction :: Conjunction
	(
		const Location location,
		const del :: Term* const term_1,
		const del :: Term* const term_2,
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
	Conjunction :: Conjunction (const del :: Formula* conjunction) :
	Normal (conjunction) {
	}
	inline
	Conjunction :: Conjunction (const Conjunction& conjunction) :
	Normal (conjunction) {
	}
	Conjunction :: ~ Conjunction() {
	}

	// del :: Formula implementation
	bool
	Conjunction :: decompose
	(
		del :: Theory* theory,
		const del :: Signature* delta,
		const bool forTheFirstTime
	)
	{
		if (forTheFirstTime) {
			return false;
		} else {
			if (decomposed_) {
				return false;
			}
			decomposed_ = true;
			if (nothingToDecompose (delta)) {
				return false;
			}
			return splitConj (theory, delta);
		}
	}
	bool
	Conjunction :: apply (del :: Model* model) const
	{
		// If A1...An ∈ S(A) and A1⊓...⊓An ⊑ B ∈ T then S(A) := S(A) ∪ {B}
		// If c ∈ CS(A1)⋂...⋂CS(An) and A1⊓...⊓An ⊑ B ∈ T then CS(B) := CS(B) ∪ {c}
		bool result = false;
		const Symbol a_1 = term_1_->getSubterm()->getSymbol();
		const Symbol b = term_2_->getSymbol();
		model->predicates().registerVariable (a_1);
		model->predicates().registerVariable (b);
		const model :: Predicate*
			predicate_a_1 = model->predicates().getPredicate (a_1);
		const value :: Integer size = term_1_->getSize();
		for (value :: Integer i = 0; i < predicate_a_1->getSize(); ++ i) {
			const model :: Positive*
				c = predicate_a_1->getNode (i);
			const del :: model :: Node* nodes [size];
			bool success = true;
			for (value :: Integer j = 0; j < size; ++ j) {
				const Symbol a_j = term_1_->getSubterm (j)->getSymbol();
				model->predicates().registerVariable (a_j);
				const model :: Predicate*
					predicate_a_j = model->predicates().getPredicate (a_j);
				nodes [j] = predicate_a_j->find (c->getVariable());
				if (nodes [j] == NULL) {
					success = false;
					break;
				}
			}
			if (success) {
				model :: Predicate*
					predicate_b = model->predicates().getPredicate (b);
				const bool successAdd =
					predicate_b->addNode (c->getVariable(), nodes, size, this);
				result = (result || successAdd);
			}
		}
		return result;
	}
	bool
	Conjunction :: extendWithCopies (del :: Theory* theory, const del :: Signature* delta) const
	{
		const value :: Integer size = term_1_->getSize();
		vector :: Symbol array (size + 1);
		const Symbol b = getTerm (1)->getSymbol();
		array.add (b);
		for (value :: Integer i = 0; i < size; ++ i) {
			const Symbol a_i = term_1_->getSubterm (i)->getSymbol();
			array.add (a_i);
		}

		Iterator iterator (array, delta);
		if (iterator.isTrivial()) {
			return false;
		}
		//std :: cout << *this << std :: endl;
		//std :: cout << *delta << std :: endl;
		while (++ iterator) {
			const Symbol b_prime = iterator.getSymbol (0);
			const del :: Term* term_2_prime = NULL;
			if (b_prime.isTop()) {
				term_2_prime = new term :: Top();
			} else {
				term_2_prime = new term :: Variable (b_prime);
			}

			const del :: Term* subTerms_prime [size];
			for (value :: Integer i = 0; i < size; ++ i) {
				const Symbol a_i_prime = iterator.getSymbol (i + 1);
				if (a_i_prime.isTop()) {
					subTerms_prime [i] = new term :: Top();
				} else {
					subTerms_prime [i] = new term :: Variable (a_i_prime);
				}
			}
			const del :: Term* term_1_prime = new term :: Intersect (subTerms_prime, size);

			del :: Formula* conjunction = new Simple
			(
				Location(),
				term_1_prime,
				term_2_prime,
				image_,
				isRoot_,
				isPrimary_,
				isDefinition_
			);
			//std :: cout << *conjunction << std :: endl;
			if (theory->containsFormula (conjunction)) {
				conjunction->commitSuicide();
			} else {
				theory->addFormula (conjunction);
			}
		}
		return true;
	}
	del :: Formula :: Kind
	Conjunction :: getKind() const {
		return CONJ_SUB_KIND;
	}

	// del :: Cloneable implementation
	del :: Formula*
	Conjunction :: clone() const
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
			return new Conjunction (*this);
		}
	}

	// object :: Object implementation
	void
	Conjunction :: commitSuicide() {
		delete this;
	}
	Size_t
	Conjunction :: getVolume() const
	{
		Size_t volume = 0;
		volume += Normal :: getVolume();
		return volume;
	}
	Size_t
	Conjunction :: getSizeOf() const {
		return sizeof (Conjunction);
	}

	/****************************
	 *		Private members
	 ****************************/

	bool
	Conjunction :: splitConj
	(
		del :: Theory* theory,
		const del :: Signature* delta
	)
	{
		Memory :: stack().push();
		IndexSet_ indexSet (INITIAL_INDEX_SET_CAPACITY);

		value :: Integer count = 0;
		for (value :: Integer i = 0; i < term_1_->getSize(); ++ i) {
			const del :: Term*
				subterm = term_1_->getSubterm (i);
			const del :: Symbol
				symbol = subterm->getSymbol();
			if (delta->containsSymbol (symbol) || symbol.isTop()) {
				indexSet.add (i);
				++ count;
			}
		}
		findDeltaIndexes (theory, delta, indexSet);
		const bool result = (indexSet.getSize() > count);
		if (result) {
			const del :: Term* interpolant = findIndexSetInterpolant (theory, delta, indexSet);
			deleteObject (term_1_);
			term_1_ = interpolant;
			term_1_ = const_cast<del :: Term*>(term_1_)->simplify();
			Del :: statistics().data()->incConjunction (indexSet.getSize() - count);
		}
		Memory :: stack().pop();
		return result;
	}
	void
	Conjunction :: findDeltaIndexes
	(
		del :: Theory* theory,
		const del :: Signature* delta,
		IndexSet_& indexSet
	)
	{
		for (value :: Integer i = 0; i < term_1_->getSize(); ++ i) {
			if (indexSet.contains (i)) {
				continue;
			}
			indexSet.addValue (i);
			if (indexesAreDelta (theory, delta, indexSet)) {
				findDeltaIndexes (theory, delta, indexSet);
				return;
			} else {
				indexSet.removeValue (i);
			}
		}
	}

	del :: Signature*
	Conjunction :: prepareDelta
	(
		const del :: Signature* delta,
		IndexSet_& indexSet
	) const
	{
		del :: Signature*
			deltaPrime = new source :: Signature<>();
		for (value :: Integer i = 0; i < term_1_->getSize(); ++ i) {
			if (indexSet.contains (i)) {
				continue;
			}
			const del :: Term*
				subterm = term_1_->getSubterm (i);
			const del :: Symbol
				symbol = subterm->getSymbol();
			if (!delta->containsSymbol (symbol) && !symbol.isTop()) {
				deltaPrime->addSymbol (symbol);
			}
		}
		return deltaPrime;
	}
	del :: Theory*
	Conjunction :: prepareTheory
	(
		del :: Theory* theory,
		const del :: Signature* deltaPrime
	) const
	{
		del :: Theory* theoryCopy = theory->clone();
		theoryCopy->removeFormula (this);
		theoryCopy->extendWithCopies (deltaPrime);
		theoryCopy->repair();
		return theoryCopy;
	}
	del :: Formula*
	Conjunction :: prepareFormula
	(
		del :: Theory* theoryCopy,
		const del :: Signature* deltaPrime
	) const
	{
		del :: Term*
			leftTerm = const_cast<del :: Term*>(term_1_->clone());
		del :: Term*
			rightTerm = const_cast<del :: Term*>(term_1_->clone());
		leftTerm->makeDeltaCopy (deltaPrime);
		del :: Formula* formula = new Subset
		(
			location_,
			leftTerm,
			rightTerm,
			image_
		);
		formula->setPrimitivized (false);
		formula->primitivize (theoryCopy, NULL, false);
		theoryCopy->normalize();
		return formula;
	}

	inline bool
	Conjunction :: indexesAreDelta
	(
		del :: Theory* theory,
		const del :: Signature* delta,
		IndexSet_& indexSet
	) {
		return indexesAreDeltaOld (theory, delta, indexSet);
	}

	bool
	Conjunction :: indexesAreDeltaNew
	(
		del :: Theory* theory,
		const del :: Signature* delta,
		IndexSet_& indexSet
	)
	{
		del :: Signature* deltaPrime = prepareDelta (delta, indexSet);
		del :: Theory* theoryCopy = prepareTheory (theory, deltaPrime);
		del :: Formula* formula = prepareFormula (theoryCopy, deltaPrime);

		Memory :: stack().push();
		const Model* prebuildModel = source :: Decompose :: current()->getDeltaModel();
		Model* model = prebuildModel->clone();
		model->build (theoryCopy);
		const bool result = formula->isTrue (model);
		model->commitSuicide();
		Memory :: stack().pop();

		formula->commitSuicide();
		deltaPrime->commitSuicide();
		theoryCopy->commitSuicide();
		return result;
	}
	bool
	Conjunction :: indexesAreDeltaOld
	(
		del :: Theory* theory,
		const del :: Signature* delta,
		IndexSet_& indexSet
	)
	{
		del :: Theory* theoryCopy = theory->clone();
		theoryCopy->removeFormula (this);
		del :: Theory* deltaTheory = theoryCopy->clone();

		del :: Signature*
			deltaPrime = new source :: Signature<>(delta);
		for (value :: Integer i = 0; i < term_1_->getSize(); ++ i) {
			if (indexSet.contains (i)) {
				continue;
			}
			const del :: Term*
				subterm = term_1_->getSubterm (i);
			const del :: Symbol
				symbol = subterm->getSymbol();
			deltaPrime->addSymbol (symbol);
		}
		del :: Expansion* deltaExpansion = new source :: Expansion<> (deltaPrime);
		deltaTheory->makeDeltaCopy (deltaExpansion);
		deltaTheory->unite (theoryCopy);
		del :: Term*
			leftTerm = const_cast<del :: Term*>(term_1_->clone());
		del :: Term*
			rightTerm = const_cast<del :: Term*>(term_1_->clone());
		leftTerm->makeDeltaCopy (deltaExpansion);

		del :: Formula* formula = new Subset
		(
			location_,
			leftTerm,
			rightTerm,
			image_
		);
		formula->setPrimitivized (false);
		formula->primitivize (deltaTheory, NULL, false);
		deltaTheory->normalize();

		Memory :: stack().push();
		Model* model = new model :: Structure<allocator :: Heap>();
		model->build (deltaTheory);
		const bool result = formula->isTrue (model);
		model->commitSuicide();
		Memory :: stack().pop();

		formula->commitSuicide();
		deltaExpansion->commitSuicide();
		deltaPrime->commitSuicide();
		deltaTheory->commitSuicide();
		theoryCopy->commitSuicide();
		return result;
	}

	const del :: Term*
	Conjunction :: findIndexSetInterpolant
	(
		del :: Theory* theory,
		const del :: Signature* delta,
		IndexSet_& indexSet
	)
	{
		return findIndexSetInterpolantOld (theory, delta, indexSet);
	}
	const del :: Term*
	Conjunction :: findIndexSetInterpolantNew
	(
		del :: Theory* theory,
		const del :: Signature* delta,
		IndexSet_& indexSet
	)
	{
		del :: Signature* deltaPrime = prepareDelta (delta, indexSet);
		del :: Theory* theoryCopy = prepareTheory (theory, deltaPrime);
		del :: Formula* formula = prepareFormula (theoryCopy, deltaPrime);

		Memory :: stack().push();
		const Model* prebuildModel = source :: Decompose :: current()->getDeltaModel();
		Model* model = new model :: Structure<allocator :: Heap> (prebuildModel);
		model->build (theoryCopy);
		const del :: Term* interpolant = formula->evalInterpolant (model, deltaPrime);
		interpolant = interpolant->clone();
		model->commitSuicide();
		Memory :: stack().pop();

		formula->commitSuicide();
		deltaPrime->commitSuicide();
		theoryCopy->commitSuicide();
		return interpolant;
	}
	const del :: Term*
	Conjunction :: findIndexSetInterpolantOld
	(
		del :: Theory* theory,
		const del :: Signature* delta,
		IndexSet_& indexSet
	)
	{
		del :: Theory* theoryCopy = theory->clone();
		theoryCopy->removeFormula (this);
		del :: Theory* deltaTheory = theoryCopy->clone();
		del :: Signature*
			deltaPrime = new source :: Signature<>(delta);
		for (value :: Integer i = 0; i < term_1_->getSize(); ++ i) {
			if (indexSet.contains (i)) {
				continue;
			}
			const del :: Term*
				subterm = term_1_->getSubterm (i);
			const del :: Symbol
				symbol = subterm->getSymbol();
			deltaPrime->addSymbol (symbol);
		}
		del :: Expansion* deltaExpansion = new source :: Expansion<> (deltaPrime);
		deltaTheory->makeDeltaCopy (deltaExpansion);
		deltaTheory->unite (theoryCopy);
		del :: Term*
			leftTerm = const_cast<del :: Term*>(term_1_->clone());
		del :: Term*
			rightTerm = const_cast<del :: Term*>(term_1_->clone());
		leftTerm->makeDeltaCopy (deltaExpansion);
		del :: Formula* formula = new Subset
		(
			location_,
			leftTerm,
			rightTerm,
			image_
		);
		formula->setPrimitivized (false);
		formula->primitivize (deltaTheory, NULL, false);
		formula->getSignature (true);
		deltaTheory->normalize();
		deltaTheory->getSignature (true);

		Memory :: stack().push();
		Model* model = new model :: Structure<allocator :: Heap>();
		model->build (deltaTheory);
		const del :: Term*
			interpolant = formula->evalInterpolant (model, deltaPrime);
		interpolant = interpolant->clone();
		model->commitSuicide();
		Memory :: stack().pop();

		formula->commitSuicide();
		deltaExpansion->commitSuicide();
		deltaPrime->commitSuicide();
		deltaTheory->commitSuicide();
		theoryCopy->commitSuicide();
		return interpolant;
	}

	void
	Conjunction :: removeIndexSet (const del :: Signature* delta, IndexSet_& indexSet)
	{
		bool removed = false;
		for (value :: Integer i = 0; i < indexSet.getSize(); ++ i) {
			const value :: Integer j = indexSet.getSize() - i - 1;
			const value :: Integer index = indexSet.getValue (j);
			const del :: Term*
				subterm = term_1_->getSubterm (index);
			const del :: Symbol
				symbol = subterm->getSymbol();
			if (!delta->containsSymbol (symbol)) {
				const_cast<del :: Term*>(term_1_)->removeSubterm (index);
				removed = true;
			}
		}
		if (removed) {
			term_1_ = const_cast<del :: Term*>(term_1_)->simplify();
		}
	}
}
}
}
}
}


