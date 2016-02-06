/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_formula_subset_normal_LeftExists.cpp          */
/* Description:     simple formula of ∃r.a ⊑ b type                          */
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
	LeftExists :: LeftExists
	(
		const Location location,
		const del :: Term* term_1,
		const del :: Term* term_2,
		const del :: Formula* image,
		const bool isRoot,
		const bool isPrimary,
		const bool isDefinition
	) :
	Exists
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
	LeftExists :: LeftExists (const del :: Formula* simple) :
	Exists (simple) {
	}
	inline
	LeftExists :: LeftExists (const LeftExists& simple) :
	Exists (simple) {
	}
	LeftExists :: ~ LeftExists() {
	}

	// del :: Formula implementation
	bool
	LeftExists :: decompose
	(
		del :: Theory* theory,
		const del :: Signature* delta,
		const bool forTheFirstTime
	)
	{
		if (forTheFirstTime) {
			return false;
		} else {
			if (nothingToDecompose (delta)) {
				return false;
			}
			if (decomposed_) {
				return false;
			}
			decomposed_ = true;
			return splitExists (theory, delta, term_1_);
		}
	}
	bool
	LeftExists :: apply (del :: Model* model) const
	{
		// If (A, B) ∈ R(r) and B' ∈ S(B) and ∃r.B' ⊑ A' ∈ T then S(A) := S(A) ∪ {A'}
		// If (c, d) ∈ R(r) and d ∈ CS(A) and ∃r.A ⊑ B ∈ T then CS(B) := CS(B) ∪ {c}
		bool result = false;

		const Symbol a = term_1_->getSubterm()->getSymbol();
		const Symbol b = term_2_->getSymbol();
		model->predicates().registerVariable (a);
		model->predicates().registerVariable (b);

		const source :: term :: Exists* const
			exists = dynamic_cast<const source :: term :: Exists*>(term_1_);
		const Symbol
			r = exists->getSymbol();
		model->relations().registerRelation (r);

		const model :: Relation*
			relation = model->relations().getRelation (r);
		const model :: Predicate*
			predicate_a = model->predicates().getPredicate (a);
		model :: Predicate*
			predicate_b = model->predicates().getPredicate (b);

		for (value :: Integer i = 0; i < relation->getSize(); ++ i) {
			const model :: Positive*
				node = relation->getNode (i);
			const Symbol c = node->getPair().first_;
			const Symbol d = node->getPair().second_;
			model->predicates().registerVariable (c);
			model->predicates().registerVariable (d);

			const del :: model :: Node* nodes [2];
			nodes [0] = node;
			nodes [1] = predicate_a->find (d);
			if (nodes [1] != NULL) {
				const bool
					successAdd = predicate_b->addNode (c, nodes, 2, this);
				result = (result || successAdd);
			}
		}
		return result;
	}
	bool
	LeftExists :: extendWithCopies (del :: Theory* theory, const del :: Signature* delta) const
	{
		const Symbol a = term_1_->getSubterm()->getSymbol();
		const Symbol b = term_2_->getSymbol();
		const source :: term :: Exists* const
			exists = dynamic_cast<const source :: term :: Exists*>(term_1_);
		const Symbol r = exists->getSymbol();

		vector :: Symbol array (3);
		array.add (a);
		array.add (b);
		array.add (r);

		Iterator iterator (array, delta);
		if (iterator.isTrivial()) {
			return false;
		}
		//std :: cout << *this << std :: endl;
		//std :: cout << *delta << std :: endl;
		while (++ iterator) {
			const Symbol a_prime = iterator.getSymbol (0);
			const Symbol b_prime = iterator.getSymbol (1);
			const Symbol r_prime = iterator.getSymbol (2);

			const del :: Term* subTerm_1_prime = NULL;
			const del :: Term* term_2_prime = NULL;
			if (a_prime.isTop()) {
				subTerm_1_prime = new term :: Top();
			} else {
				subTerm_1_prime = new term :: Variable (a_prime);
			}
			if (b_prime.isTop()) {
				term_2_prime = new term :: Top();
			} else {
				term_2_prime = new term :: Variable (b_prime);
			}
			const del :: Term*
				term_1_prime = new term :: Exists (r_prime, subTerm_1_prime);

			del :: Formula* leftExists = new LeftExists
			(
				Location(),
				term_1_prime,
				term_2_prime,
				image_,
				isRoot_,
				isPrimary_,
				isDefinition_
			);
			//std :: cout << *leftExists << std :: endl;
			if (theory->containsFormula (leftExists)) {
				leftExists->commitSuicide();
			} else {
				theory->addFormula (leftExists);
			}
		}
		return true;
	}
	del :: Formula :: Kind
	LeftExists :: getKind() const {
		return Normal :: LEFT_SUB_KIND;
	}

	// del :: Cloneable implementation
	del :: Formula*
	LeftExists :: clone() const
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
			return new LeftExists (*this);
		}
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	/*// object :: Writable implementation
	void
	LeftExists :: replicate (String& string) const {
		Normal :: replicate (string);
	}
	void
	LeftExists :: translate (String& string) const {
		Normal :: translate (string);
	}*/

	// object :: Object implementation
	void
	LeftExists :: commitSuicide() {
		delete this;
	}
	Size_t
	LeftExists :: getVolume() const {
		return Normal :: getVolume();
	}
	Size_t
	LeftExists :: getSizeOf() const {
		return sizeof (LeftExists);
	}

	/****************************
	 *		Private members
	 ****************************/
}
}
}
}
}


