/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_formula_Equivalence_Decompose_Theory.cpp      */
/* Description:     decomposition subset formula routines                    */
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

	/****************************
	 *		Private members
	 ****************************/

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	bool
	Equivalence :: splitFormula
	(
		del :: Theory* theory,
		const del :: Signature* delta
	)
	{
		// check if some term in formula is already in delta
		if (term_1_->isVariable()) {
			const value :: Variable var = term_1_->getSymbol().getVariable();
			if (delta->containsVariable (var)) {
				return false;
			}
		}
		if (term_2_->isVariable()) {
			const value :: Variable var = term_2_->getSymbol().getVariable();
			if (delta->containsVariable (var)) {
				return false;
			}
		}
		Memory :: stack().push();
		const del :: Expansion*
			deltaExpansion = source :: Decompose :: current()->getDeltaExpansion();
		const del :: Theory*
			deltaTheory = source :: Decompose :: current()->getDeltaTheory();
		const model :: Model<allocator :: Heap>*
			prebuildModel = dynamic_cast<const model :: Model<>*>
				(source :: Decompose :: current()->getDeltaModel());
		del :: Model*
			deltaModel = new model :: Model<allocator :: Stack>(*prebuildModel);
		del :: Formula*
			formula = clone();
		const_cast<del :: Term*>(formula->getTerm(0))->makeDeltaCopy (deltaExpansion);
		const bool result = formula->isTrue (deltaModel);
		if (result) {
			Del :: statistics().data()->incSplit();
			deltaModel->clearNodes();
			const del :: Term*
				interpolant = formula->evalInterpolant (deltaModel, delta);
			insertInterpolant (theory, interpolant);
			const_cast<del :: Term*>(interpolant)->commitSuicide();
			theory->removeFormula (this);
		}
		if (deltaModel != NULL) {
			deltaModel->commitSuicide();
		}
		Memory :: stack().pop();
		formula->commitSuicide();
		return result;
	}
	bool
	Equivalence :: splitConj
	(
		del :: Theory* theory,
		const del :: Signature* delta
	)
	{
		Memory :: stack().push();
		IndexSet_ indexSet (INITIAL_INDEX_SET_CAPACITY);

		value :: Integer fictiveCount = 0;
		for (value :: Integer i = 0; i < term_1_->getSize(); ++ i) {
			const del :: Term*
				subterm = term_1_->getSubterm (i);
			const value :: Variable
				variable = subterm->getSymbol().getVariable();
			if (delta->containsVariable (variable) ||
				(variable == value :: TOP)) {
				indexSet.add (i);
				++ fictiveCount;
			}
		}
		findDeltaIndexes (theory, delta, indexSet);
		const bool result = (indexSet.getSize() > fictiveCount);
		if (result) {
			const del :: Term*
				interpolant = findIndexSetInterpolant (theory, delta, indexSet);
			if (interpolant == NULL) {
				removeIndexSet (delta, indexSet);
			} else {
				interpolant = const_cast<del :: Term*>(interpolant)->makePlain();
				insertInterpolant (theory, interpolant);
				const_cast<del :: Term*>(interpolant)->commitSuicide();
				theory->removeFormula (this);
			}
			Del :: statistics().data()->incConjunctionLeft (indexSet.getSize() - fictiveCount);
		}
		Memory :: stack().pop();
		return result;
	}
	void
	Equivalence :: findDeltaIndexes
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
	bool
	Equivalence :: indexesAreDelta
	(
		del :: Theory* theory,
		const del :: Signature* delta,
		IndexSet_& indexSet
	)
	{
		del :: Theory* deltaTheory = theory->clone();
		deltaTheory->removeFormula (this);
		del :: Signature*
			deltaPrime = new source :: Signature<>(delta);
		for (value :: Integer i = 0; i < term_1_->getSize(); ++ i) {
			if (indexSet.contains (i)) {
				continue;
			}
			const del :: Term*
				subterm = term_1_->getSubterm (i);
			const value :: Variable
				variable = subterm->getSymbol().getVariable();
			deltaPrime->addVariable (variable);
		}

		del :: Expansion* deltaExpansion = new source :: Expansion<> (deltaPrime);
		deltaTheory->makeDeltaCopy (deltaExpansion);
		deltaTheory->unite (theory);

		del :: Term*
			leftTerm = const_cast<del :: Term*>(term_1_->clone());
		del :: Term*
			rightTerm = const_cast<del :: Term*>(term_1_->clone());
		leftTerm->makeDeltaCopy (deltaExpansion);

		del :: Formula* formula = new Equivalence
		(
			location_,
			leftTerm,
			rightTerm,
			image_
		);
		formula->prepare (deltaTheory);

		Memory :: stack().push();
		model :: Model<allocator :: Stack> model;
		model.build (deltaTheory);
		const bool result = formula->isTrue (&model);
		Memory :: stack().pop();

		formula->commitSuicide();
		deltaExpansion->commitSuicide();
		deltaTheory->commitSuicide();
		deltaPrime->commitSuicide();
		return result;
	}
	const del :: Term*
	Equivalence :: findIndexSetInterpolant
	(
		del :: Theory* theory,
		const del :: Signature* delta,
		IndexSet_& indexSet
	)
	{
		del :: Theory* deltaTheory = theory->clone();
		deltaTheory->removeFormula (this);
		del :: Signature*
			deltaPrime = new source :: Signature<>(delta);
		for (value :: Integer i = 0; i < term_1_->getSize(); ++ i) {
			if (indexSet.contains (i)) {
				continue;
			}
			const del :: Term*
				subterm = term_1_->getSubterm (i);
			const value :: Variable
				variable = subterm->getSymbol().getVariable();
			deltaPrime->addVariable (variable);
		}

		del :: Expansion* deltaExpansion = new source :: Expansion<> (deltaPrime);
		deltaTheory->makeDeltaCopy (deltaExpansion);
		deltaTheory->unite (theory);

		del :: Term*
			leftTerm = const_cast<del :: Term*>(term_1_->clone());
		del :: Term*
			rightTerm = const_cast<del :: Term*>(term_1_->clone());
		leftTerm->makeDeltaCopy (deltaExpansion);

		del :: Formula* formula = new Equivalence
		(
			location_,
			leftTerm,
			rightTerm,
			image_
		);
		formula->prepare (deltaTheory);

		Memory :: stack().push();
		del :: Model* model = new model :: Model<allocator :: Stack>();
		model->build (deltaTheory);
		const del :: Term*
			interpolant = formula->evalInterpolant (model, delta);
		Memory :: stack().pop();

		formula->commitSuicide();
		deltaExpansion->commitSuicide();
		deltaTheory->commitSuicide();
		deltaPrime->commitSuicide();

		return interpolant;
	}
	bool
	Equivalence :: splitExists
	(
		del :: Theory* theory,
		const del :: Signature* delta,
		const del :: Term* term
	)
	{
		const value :: Variable
			variable = term->getSubterm(0)->getSymbol().getVariable();
		if (delta->containsVariable (variable)) {
			return false;
		}
		const Symbol symbol (variable, false);

		Memory :: stack().push();
		const del :: Expansion*
			deltaExpansion = source :: Decompose :: current()->getDeltaExpansion();
		const del :: Theory*
			deltaTheory = source :: Decompose :: current()->getDeltaTheory();
		const model :: Model<allocator :: Heap>*
			prebuildModel = dynamic_cast<const model :: Model<>*>(source :: Decompose :: current()->getDeltaModel());

		del :: Term*
			subterm_1 = const_cast<del :: Term*>(term->getSubterm(0)->clone());
		subterm_1->makeDeltaCopy (deltaExpansion);
		del :: Term*
			subterm_2 = const_cast<del :: Term*>(term->getSubterm(0)->clone());
		del :: Formula*
			formula = new Equivalence (location_, subterm_1, subterm_2, image_);

		Memory :: stack().push();
		model :: Model<allocator :: Stack> model;// (*prebuildModel);

		if (Counter :: stop (1)) {
			std :: cout << *this << std :: endl;
		}

		model.build (deltaTheory);
		const bool result = formula->isTrue (&model);

		if (result) {
			model.clearNodes();
			const del :: Term*
				interpolant = formula->evalInterpolant (&model, delta);
			const_cast<del :: Term*>(term)->replaceSubterm (0, interpolant);
			Del :: statistics().data()->incFictivization();
		}
		Memory :: stack().pop();
		formula->commitSuicide();
		return result;
	}
	void
	Equivalence :: insertInterpolant
	(
		del :: Theory* theory,
		const del :: Term* interpolant
	) const
	{
		const del :: Term*
			interpolant_1 = interpolant->clone();
		const del :: Term*
			interpolant_2 = interpolant->clone();

		del :: Formula* formula_1 = new Equivalence
		(
			location_,
			term_1_->clone(),
			interpolant_1,
			image_,
			COMPLEX_KIND,
			isRoot_
		);
		del :: Formula* formula_2 = new Equivalence
		(
			location_,
			interpolant_2,
			term_2_->clone(),
			image_,
			COMPLEX_KIND,
			isRoot_
		);
		theory->addFormula (formula_1);
		theory->addFormula (formula_2);
	}
	void
	Equivalence :: removeIndexSet (const del :: Signature* delta, IndexSet_& indexSet)
	{
		bool removed = false;
		for (value :: Integer i = 0; i < indexSet.getSize(); ++ i) {
			const value :: Integer j = indexSet.getSize() - i - 1;
			const value :: Integer index = indexSet.getValue (j);
			const del :: Term*
				subterm = term_1_->getSubterm (index);
			const value :: Variable
				variable = subterm->getSymbol().getVariable();
			if (!delta->containsVariable (variable)) {
				const_cast<del :: Term*>(term_1_)->removeSubterm (index);
				removed = true;
			}
		}
		if (removed) {
			term_1_ = const_cast<del :: Term*>(term_1_)->makePlain();
		}
	}
}
}
}


