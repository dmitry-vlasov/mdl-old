/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_formula_subset_normal_Exists.cpp              */
/* Description:     simple formula of a ⊑ ∃r.b or ∃r.a ⊑ b type              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_SOURCE_FORMULA_SUBSET_NORMAL_EXISTS_CPP_
#define DEL_SOURCE_FORMULA_SUBSET_NORMAL_EXISTS_CPP_

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
	Exists :: Exists
	(
		const Location location,
		const del :: Term* term_1,
		const del :: Term* term_2,
		const del :: Formula* image,
		const bool isRoot,
		const bool isPrimary,
		const bool isDefinition
	) :
	Normal (location, term_1, term_2, image, isRoot, isPrimary, isDefinition) {
	}
	inline
	Exists :: Exists (const del :: Formula* simple) :
	Normal (simple) {
	}
	inline
	Exists :: Exists (const Exists& simple) :
	Normal (simple) {
	}
	Exists :: ~ Exists() {
	}

	// del :: Formula implementation

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Object implementation
	void
	Exists :: commitSuicide() {
		delete this;
	}
	Size_t
	Exists :: getVolume() const {
		return Normal :: getVolume();
	}
	Size_t
	Exists :: getSizeOf() const {
		return sizeof (Exists);
	}

	/****************************
	 *		Protected members
	 ****************************/

	bool
	Exists :: splitExists
	(
		del :: Theory* theory,
		const del :: Signature* delta,
		const del :: Term*& term
	) {
		return splitExistsMed (theory, delta, term);
	}

	/****************************
	 *		Private members
	 ****************************/

	del :: Signature*
	Exists :: prepareDelta
	(
		const del :: Signature* delta,
		const del :: Term* term
	) const
	{
		del :: Signature*
			deltaPrime = new source :: Signature<>();
		const del :: Symbol
			relation = term->getSymbol();
		if (!delta->containsSymbol (relation)) {
			deltaPrime->addSymbol (relation);
		}
		return deltaPrime;
	}
	del :: Theory*
	Exists :: prepareTheory
	(
		del :: Theory* theory,
		const del :: Signature* deltaPrime,
		const del :: Term* term
	) const
	{
		del :: Theory* theoryCopy = theory->clone();
		theoryCopy->removeFormula (this);
		theoryCopy->extendWithCopies (deltaPrime);
		theoryCopy->repair();
		return theoryCopy;
	}
	del :: Formula*
	Exists :: prepareFormula
	(
		del :: Theory* theoryCopy,
		const del :: Signature* deltaPrime,
		const del :: Term* term
	) const
	{
		del :: Term* leftTerm = const_cast<del :: Term*>(term->clone());
		del :: Term* rightTerm = const_cast<del :: Term*>(term->clone());
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

	bool
	Exists :: splitExistsNew
	(
		del :: Theory* theory,
		const del :: Signature* delta,
		const del :: Term*& term
	)
	{
		const del :: Symbol
			concept = term->getSubterm(0)->getSymbol();
		if (delta->containsSymbol (concept) || concept.isTop()) {
			return false;
		}

		del :: Signature* deltaPrime = prepareDelta (delta, term);
		del :: Theory* theoryCopy = prepareTheory (theory, deltaPrime, term);
		del :: Formula* formula = prepareFormula (theoryCopy, deltaPrime, term);

		Memory :: stack().push();
		const Model* prebuildModel = source :: Decompose :: current()->getDeltaModel();
		Model* model = prebuildModel->clone();

		if (!model->isEqual (prebuildModel)) {
			std :: cout << std :: endl << "FUCK DIS SHIT" << std :: endl;
		}

	/*	std :: cout << std :: endl << "Prebuild model volume = ";
		memory :: Unit :: show (std :: cout, prebuildModel->getVolume());
		std :: cout << std :: endl;
		std :: cout << std :: endl << "Initial model volume = ";
		memory :: Unit :: show (std :: cout, model->getVolume());
		std :: cout << std :: endl;*/

		Timer timer;
		timer.start();
		model->build (theoryCopy);
		timer.stop();
		if (timer.getSeconds() > 1) {
			std :: cout << "model built in " << timer << std :: endl << std :: endl;
			std :: cout << "Model volume = ";
			memory :: Unit :: show (std :: cout, model->getVolume());
			std :: cout << std :: endl << "Prebuild model volume = ";
			memory :: Unit :: show (std :: cout, prebuildModel->getVolume());
			std :: cout << std :: endl;
			//throw new Error*();
		}

		const bool result = formula->isTrue (model);
		if (result) {
			if (term == term_1_) {
				Del :: statistics().data()->incExistsLeft();
			} else {
				Del :: statistics().data()->incExistsRight();
			}
			model->clearNodes();
			const del :: Term*
				interpolant = formula->evalInterpolant (model, delta);
			deleteObject (term);
			term = interpolant->clone();
			term = const_cast<del :: Term*>(term)->simplify();
		}
		model->commitSuicide();
		Memory :: stack().pop();

		formula->commitSuicide();
		theoryCopy->commitSuicide();
		deltaPrime->commitSuicide();
		return result;
	}
	bool
	Exists :: splitExistsMed
	(
		del :: Theory* theory,
		const del :: Signature* delta,
		const del :: Term*& term
	)
	{
		const del :: Symbol
			concept = term->getSubterm(0)->getSymbol();
		if (delta->containsSymbol (concept) || concept.isTop()) {
			return false;
		}
		Memory :: stack().push();
		del :: Theory* theoryCopy = theory->clone();
		theoryCopy->removeFormula (this);
		del :: Theory* deltaTheory = theoryCopy->clone();

		del :: Signature*
			deltaPrime = new source :: Signature<>(delta);
		const del :: Symbol
			relation = term->getSymbol();
		deltaPrime->addSymbol (relation);

		del :: Expansion* deltaExpansion = new source :: Expansion<> (deltaPrime);
		deltaTheory->makeDeltaCopy (deltaExpansion);
		deltaTheory->unite (theoryCopy);

		del :: Term*
			leftTerm = const_cast<del :: Term*>(term->clone());
		del :: Term*
			rightTerm = const_cast<del :: Term*>(term->clone());
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
		const Model* prebuildModel = source :: Decompose :: current()->getDeltaModel();

		Timer timer;
		timer.start();
		model->build (deltaTheory);
		timer.stop();
		if (timer.getSeconds() > 1) {
			std :: cout << "model built in " << timer << std :: endl << std :: endl;
			std :: cout << "Model volume = ";
			memory :: Unit :: show (std :: cout, model->getVolume());
			std :: cout << std :: endl << "Prebuild model volume = ";
			memory :: Unit :: show (std :: cout, prebuildModel->getVolume());
			std :: cout << std :: endl;
			//throw new Error*();
		}

		const bool result = formula->isTrue (model);
		if (result) {
			if (term == term_1_) {
				Del :: statistics().data()->incExistsLeft();
			} else {
				Del :: statistics().data()->incExistsRight();
			}
			model->clearNodes();
			const del :: Term*
				interpolant = formula->evalInterpolant (model, delta);

			//std :: cout << *this << std :: endl;
			//std :: cout << *formula << std :: endl;
			//std :: cout << *interpolant << std :: endl;

			deleteObject (term);
			term = interpolant->clone();
			term = const_cast<del :: Term*>(term)->simplify();
		}
		model->commitSuicide();
		Memory :: stack().pop();

		formula->commitSuicide();
		deltaExpansion->commitSuicide();
		deltaPrime->commitSuicide();
		deltaTheory->commitSuicide();
		theoryCopy->commitSuicide();
		Memory :: stack().pop();
		return result;
	}
	bool
	Exists :: splitExistsOld
	(
		del :: Theory* theory,
		const del :: Signature* delta,
		const del :: Term*& term
	)
	{
		const del :: Symbol
			symbol = term->getSubterm(0)->getSymbol();
		if (delta->containsSymbol (symbol) || symbol.isTop()) {
			return false;
		}
		Memory :: stack().push();
		const del :: Expansion*
			deltaExpansion = source :: Decompose :: current()->getDeltaExpansion();
		const del :: Theory*
			deltaTheory = source :: Decompose :: current()->getDeltaTheory();
		const Model*
			prebuildModel = source :: Decompose :: current()->getDeltaModel();

		del :: Term*
			subterm_1 = const_cast<del :: Term*>(term->getSubterm(0)->clone());
		subterm_1->makeDeltaCopy (deltaExpansion);
		del :: Term*
			subterm_2 = const_cast<del :: Term*>(term->getSubterm(0)->clone());
		del :: Formula*
			formula = new Subset (location_, subterm_1, subterm_2, image_);

		Memory :: stack().push();
		Model* model = new model :: Structure<allocator :: Heap>();
		model->build (deltaTheory);

		const bool result = formula->isTrue (model);
		if (result) {
			if (term == term_1_) {
				Del :: statistics().data()->incExistsLeft();
			} else {
				Del :: statistics().data()->incExistsRight();
			}
			model->clearNodes();
			const del :: Term*
				interpolant = formula->evalInterpolant (model, delta);

			const del :: Term* a = term->getSubterm(0)->clone();
			const del :: Term* d = interpolant->clone();
			d = const_cast<del :: Term*>(d)->simplify();
			del :: Formula* def = subset :: Subset :: create (d, a, NULL, false, false, true);

			bool newDef = true;
			for (value :: Integer i = 0; i < theory->getSize(); ++ i) {
				const del :: Formula* form = theory->getFormula (i);
				if (def->isEqual (form) && form->isDefinition()) {
					newDef = false;
					break;
				}
			}
			if (newDef) {
				theory->addFormula (def);
			} else {
				def->commitSuicide();
			}
		}
		model->commitSuicide();
		Memory :: stack().pop();
		formula->commitSuicide();
		return result;
	}
}
}
}
}
}

#endif /*DEL_SOURCE_FORMULA_SUBSET_NORMAL_EXISTS_CPP_*/
