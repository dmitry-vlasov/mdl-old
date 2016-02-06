/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_formula_Equivalence_Normalize.cpp             */
/* Description:     normalization subset formula routines                    */
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

	// normalization routines
	void
	Equivalence :: transformIntersection (del :: Theory* theory) const
	{
		for (value :: Integer i = 0; i < term_2_->getSize(); ++ i) {
			const del :: Term* const
				conjTerm = Formula :: term_2_->getSubterm (i);
			const del :: Formula* const formula = new Equivalence
			(
				location_,
				Formula :: term_1_->clone(),
				conjTerm->clone(),
				image_,
				COMPLEX_KIND,
				isRoot_
			);
			theory->addFormula (formula);
		}
		Del :: statistics().data()->incConjunctionRight();
	}
	void
	Equivalence :: transformComplexExists (del :: Theory* theory, const del :: Term* complexExists) const
	{
		const value :: Variable
			var = Table :: variables()->fresh ("X");
		const del :: Term* const
			term_1_1 = new term :: Variable (location_, var, complexExists->getSubterm());

		const del :: Term* const
			term_1_2 = complexExists->getSubterm()->clone();
		const del :: Term* const
			term_2_1 = new term :: Variable (location_, var, complexExists->getSubterm());
		const del :: Term* const
			term_2_2 = complexExists->getSubterm()->clone();

		const del :: Formula* const first = new formula :: Equivalence
		(
			location_,
			term_1_1,
			term_1_2,
			image_
		);
		const del :: Formula* const second = new formula :: Equivalence
		(
			location_,
			term_2_2,
			term_2_1,
			image_
		);
		theory->addFormula (clone());
		theory->replace (complexExists->getSubterm(), term_1_1);
		theory->addFormula (first);
		theory->addFormula (second);
	}
	void
	Equivalence :: transformRightExists
	(
		del :: Theory* theory,
		del :: Term*& term
	) const
	{
		/* If A1 ⊓ ··· ⊓ An ⊓ ∃r1.B1 ⊓ ··· ∃rm.Bm ⊑ ∃r.B in T, remove it,
		 * remove it, take a new concept names Z1...Zm and add
		 * A1 ⊓ ··· ⊓ An ⊓ Z1 ⊓ ... ⊓ Zm ⊑ X, ∃r1 .B1 ≡ Z1 ... ∃rm .Bm ≡ Zm
		 * and X ≡ ∃r.B to T */

		const value :: Variable
			var = Table :: variables()->fresh ("Y");
		const del :: Term* const
			varTerm = new term :: Variable (location_, var, term);


		const del :: Formula* const first = new formula :: Identity
		(
			location_,
			term,
			varTerm,
			image_
		);
		term = varTerm->clone();
		const del :: Formula* const
			second = clone();
		theory->addFormula (first);
		theory->addFormula (second);
	}
	void
	Equivalence :: transformExisisVector (del :: Theory* theory, del :: Term* term) const
	{
		if (!term->isIntersection()) {
			return;
		}
		term :: Intersect*
			existsIntersection = dynamic_cast<term :: Intersect*>(term);
		term :: Intersect*
			intersection = dynamic_cast<term :: Intersect*>(const_cast<del :: Term*>(term_1_));

		for (value :: Integer i = 0; i < existsIntersection->getSize(); ++ i) {
			const value :: Variable
				var = Table :: variables()->fresh ("U");
			const del :: Term* const
				subterm = existsIntersection->getSubterm (i);
			const del :: Term* const
				varTerm = new term :: Variable (location_, var, subterm);

			intersection->addTerm (varTerm);

			const del :: Formula* const first = new formula :: Identity
			(
				location_,
				subterm->clone(),
				varTerm->clone(),
				image_
			);
			theory->addFormula (first);
		}
		existsIntersection->commitSuicide();
	}
	void
	Equivalence :: transformSingleExists (del :: Theory* theory) const
	{
		/* If ∃r1.B1 ⊑ ∃r2.B2 in T , remove it,
		 * take a new concept name X and add ∃r1.B1 ⊑ X
		 * and X ⊑ ∃r2.B2 to T */
		if (!term_1_->isExists() || !term_2_->isExists()) {
			return;
		}
		const value :: Variable
			var = Table :: variables()->fresh ("W");
		const del :: Term* const
			term_1_1 = term_1_->clone();
		const del :: Term* const
			term_1_2 = new term :: Variable (location_, var, term_1_1);
		const del :: Term* const
			term_2_1 = new term :: Variable (location_, var);
		const del :: Term* const
			term_2_2 = term_2_->clone();

		const del :: Formula* const first = new formula :: Identity
		(
			location_,
			term_1_1,
			term_1_2,
			image_
		);
		const del :: Formula* const second = new formula :: Equivalence
		(
			location_,
			term_2_1,
			term_2_2,
			image_
		);
		theory->addFormula (first);
		theory->addFormula (second);
	}
}
}
}


