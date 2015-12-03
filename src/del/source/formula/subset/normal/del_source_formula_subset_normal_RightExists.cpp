/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_formula_subset_l_RightExists.cpp              */
/* Description:     simple formula of a ⊑ ∃r.b type                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_SOURCE_FORMULA_SUBSET_NORMAL_RIGHT_EXISTS_CPP_
#define DEL_SOURCE_FORMULA_SUBSET_NORMAL_RIGHT_EXISTS_CPP_

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
	RightExists :: RightExists
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
	RightExists :: RightExists (const del :: Formula* simple) :
	Exists (simple) {
	}
	inline
	RightExists :: RightExists (const RightExists& simple) :
	Exists (simple) {
	}
	RightExists :: ~ RightExists() {
	}

	// del :: Formula implementation
	bool
	RightExists :: decompose
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
			return splitExists (theory, delta, term_2_);
		}
	}
	bool
	RightExists :: apply (del :: Model* model) const
	{
		// If A' ∈ S(A) and A' ⊑ ∃r.B ∈ T then R(r) := R(r) ∪ {(A, B)}
		// If A ∈ S(c) and A ⊑ ∃r.B ∈ T then R(r) := R(r) ∪ {(c, B)}
		bool result = false;
		/*const value :: Variable a = term_1_->getSymbol().getVariable();
		const value :: Variable b = term_2_->getSubterm()->getSymbol().getVariable();

		const source :: term :: Exists* const
			exists = dynamic_cast<const source :: term :: Exists*>(term_2_);
		const value :: Relation
			r = exists->getSymbol().getRelation();

		const ConceptSet_*
			coClosure = conceptMap_.getCoClosure (a);
		for (value :: Integer i = 0; i < coClosure->getSize(); ++ i) {
			const Concept_*
				c = coClosure->getConcept (i);
			if (relationMap_.addRelationFor (r, c->getVariable(), b, c, formula)) {
				result = true;
			}
		}*/
		const Symbol a = term_1_->getSymbol();
		const Symbol b = term_2_->getSubterm()->getSymbol();
		model->predicates().registerVariable (a);
		model->predicates().registerVariable (b);

		const source :: term :: Exists* const
			exists = dynamic_cast<const source :: term :: Exists*>(term_2_);
		const Symbol
			r = exists->getSymbol();
		model->relations().registerRelation (r);

		const model :: Predicate*
			predicate_a = model->predicates().getPredicate (a);
		for (value :: Integer i = 0; i < predicate_a->getSize(); ++ i) {
			const model :: Positive*
				c = predicate_a->getNode (i);
			model :: Relation*
				relation = model->relations().getRelation (r);

			if (relation->addNode (c->getVariable(), b, c, this)) {
				result = true;
			}
		}
		return result;
	}
	bool
	RightExists :: extendWithCopies (del :: Theory* theory, const del :: Signature* delta) const
	{
		const Symbol a = term_1_->getSymbol();
		const Symbol b = term_2_->getSubterm()->getSymbol();
		const source :: term :: Exists* const
			exists = dynamic_cast<const source :: term :: Exists*>(term_2_);
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

			const del :: Term* term_1_prime = NULL;
			const del :: Term* subTerm_2_prime = NULL;
			if (a_prime.isTop()) {
				term_1_prime = new term :: Top();
			} else {
				term_1_prime = new term :: Variable (a_prime);
			}
			if (b_prime.isTop()) {
				subTerm_2_prime = new term :: Top();
			} else {
				subTerm_2_prime = new term :: Variable (b_prime);
			}
			const del :: Term*
				term_2_prime = new term :: Exists (r_prime, subTerm_2_prime);

			del :: Formula* rightExists = new RightExists
			(
				Location(),
				term_1_prime,
				term_2_prime,
				image_,
				isRoot_,
				isPrimary_,
				isDefinition_
			);
			//std :: cout << *rightExists << std :: endl;
			if (theory->containsFormula (rightExists)) {
				rightExists->commitSuicide();
			} else {
				theory->addFormula (rightExists);
			}
		}
		return true;
	}
	del :: Formula :: Kind
	RightExists :: getKind() const {
		return Normal :: RIGHT_SUB_KIND;
	}

	// del :: Cloneable implementation
	del :: Formula*
	RightExists :: clone() const
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
			return new RightExists (*this);
		}
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	/*// object :: Writable implementation
	void
	RightExists :: replicate (String& string) const {
		Normal :: replicate (string);
	}
	void
	RightExists :: translate (String& string) const {
		Normal :: translate (string);
	}*/

	// object :: Object implementation
	void
	RightExists :: commitSuicide() {
		delete this;
	}
	Size_t
	RightExists :: getVolume() const {
		return Normal :: getVolume();
	}
	Size_t
	RightExists :: getSizeOf() const {
		return sizeof (RightExists);
	}

	/****************************
	 *		Private members
	 ****************************/
}
}
}
}
}

#endif /*DEL_SOURCE_FORMULA_SUBSET_NORMAL_RIGHT_EXISTS_CPP_*/
