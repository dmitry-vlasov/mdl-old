/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_formula_Formula.cpp                           */
/* Description:     general formula class                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_SOURCE_FORMULA_TERMAL_CPP_
#define DEL_SOURCE_FORMULA_TERMAL_CPP_

#include "del/lexer/del_lexer.hpp"
#include "del/source/del_source.hpp"

namespace del {
namespace source {
namespace formula {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Termal :: Termal
	(
		const Location location,
		const del :: Term* const term_1,
		const del :: Term* const term_2,
		const del :: Formula* image,
		const Kind kind,
		const bool isRoot,
		const bool isPrimary,
		const bool isDefinition
	) :
	Formula (location, image, kind, isRoot, isPrimary, isDefinition),
	term_1_ (term_1),
	term_2_ (term_2)
	{
		term_1_->completeSignature (signature_);
		term_2_->completeSignature (signature_);
	}
	inline
	Termal :: Termal (const del :: Formula* formula) :
	Formula (formula),
	term_1_ (formula->getTerm(0)->clone()),
	term_2_ (formula->getTerm(1)->clone()) {
	}
	inline
	Termal :: Termal (const Termal& formula) :
	Formula (formula),
	term_1_ (formula.term_1_->clone()),
	term_2_ (formula.term_2_->clone()) {
	}
	Termal :: ~ Termal()
	{
		deleteAggregateObject (term_1_);
		deleteAggregateObject (term_2_);
	}

	// del :: Formula implementation
	const del :: Signature*
	Termal :: getSignature (const bool force) const
	{
		if (force) {
			const_cast<del :: Signature*>(signature_)->commitSuicide();
			signature_ = new source :: Signature<>();
			term_1_->completeSignature (signature_);
			term_2_->completeSignature (signature_);
		}
		return Formula :: getSignature();
	}
	void
	Termal :: makeDeltaCopy (const del :: Expansion* expansion)
	{
		const_cast<del :: Term*>(term_1_)->makeDeltaCopy (expansion);
		const_cast<del :: Term*>(term_2_)->makeDeltaCopy (expansion);
	}
	void
	Termal :: makeDeltaCopy (const del :: Signature* delta)
	{
		const_cast<del :: Term*>(term_1_)->makeDeltaCopy (delta);
		const_cast<del :: Term*>(term_2_)->makeDeltaCopy (delta);
	}
	bool
	Termal :: isPrimitivized() const {
		return (term_1_->isPrimitivized() && term_2_->isPrimitivized());
	}
	void
	Termal :: setPrimitivized (const bool isPrimitivized)
	{
		term_1_->setPrimitivized (isPrimitivized);
		term_2_->setPrimitivized (isPrimitivized);
	}
	bool
	Termal :: isEqual (const del :: Formula* formula) const
	{
		if (!Formula :: isEqual (formula)) {
			return false;
		}
		return
			term_1_->isEqual (formula->getTerm (0)) &&
			term_2_->isEqual (formula->getTerm (1));
	}
	const del :: Term*
	Termal :: getTerm (const value :: Integer i) const
	{
		switch (i) {
		case 0 :  return term_1_;
		case 1 :  return term_2_;
		default : return NULL;
		}
	}
	void
	Termal :: simplify()
	{
		const del :: Term* const
			term_1 = const_cast<del :: Term*>(term_1_)->simplify();
		const_cast<const del :: Term*&>(term_1_) = term_1;

		const del :: Term* const
			term_2 = const_cast<del :: Term*>(term_2_)->simplify();
		const_cast<const del :: Term*&>(term_2_) = term_2;
	}
	bool
	Termal :: primitivize (del :: Theory* theory, del :: Signature* delta, const bool addToTheory) const
	{
		if (isPrimitivized()) {
			return false;
		}
		const Symbol var_1 =
				term_1_->isPrimitivized() ?
				term_1_->getPrimitivization() :
				prepareTerm	(term_1_, theory, delta);
		const Symbol var_2 =
				term_2_->isPrimitivized() ?
				term_2_->getPrimitivization() :
				prepareTerm	(term_2_, theory, delta);
		if (addToTheory) {
			const del :: Term* term_1 =
				var_1.isTop() ?
				static_cast<const del :: Term*>(new term :: Top ()) :
				static_cast<const del :: Term*>(new term :: Variable (var_1));
			const del :: Term* term_2 =
				var_2.isTop() ?
				static_cast<const del :: Term*>(new term :: Top ()) :
				static_cast<const del :: Term*>(new term :: Variable (var_2));
			del :: Formula*
				formula = new subset :: normal :: Primitive
				(
					location_,
					term_1,
					term_2,
					image_,
					true,
					isPrimary_
				);
			theory->addFormula (formula);
		}
		return true;
	}
	void
	Termal :: replace (const del :: Term* oldTerm, const del :: Term* newTerm)
	{
		term :: Term :: replace (const_cast<del :: Term*&>(term_1_), oldTerm, newTerm);
		term :: Term :: replace (const_cast<del :: Term*&>(term_2_), oldTerm, newTerm);
	}

	Termal :: Kind
	Termal :: getKind() const
	{
		if (isSimpleR()) {
			kind_ = SIMPLE_SUB_KIND;
		} else if (isConjR()) {
			kind_ = CONJ_SUB_KIND;
		} else if (isRightR()) {
			kind_ = RIGHT_SUB_KIND;
		} else if (isLeftR()) {
			kind_ = LEFT_SUB_KIND;
		} else {
			kind_ = GENERAL_SUB_KIND;
		}
		return kind_;
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Writable implementation
	void
	Termal :: translate (String& string) const {
		replicate (string);
	}

	// object :: Object implementation
	void
	Termal :: commitSuicide() {
		delete this;
	}
	Size_t
	Termal :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (term_1_);
		volume += getAggregateVolume (term_2_);
		volume += Formula :: getVolume();
		return volume;
	}
	Size_t
	Termal :: getSizeOf() const {
		return sizeof (Termal);
	}

	/****************************
	 *		Private members
	 ****************************/

	bool
	Termal :: isSimpleR() const
	{
		// a ⊑ b
		return (term_1_->isAtomic() && term_2_->isAtomic());
	}
	bool
	Termal :: isConjR() const
	{
		// a_1 ⊓ ··· ⊓ a_n ⊑ b
		return
			(term_1_->getKind() == del :: Term :: INTERSECT_KIND) &&
			!term_1_->isDeep() &&
			term_2_->isAtomic();
	}
	bool
	Termal :: isRightR() const
	{
		// a ⊑ ∃r.b
		return
			term_1_->isAtomic() &&
			(term_2_->getKind() == del :: Term :: EXISTS_KIND) &&
			!term_2_->isDeep();
	}
	bool
	Termal :: isLeftR() const
	{
		// ∃r.a ⊑ b
		return
			(term_1_->getKind() == del :: Term :: EXISTS_KIND) &&
			!term_1_->isDeep() &&
			term_2_->isAtomic();
	}
	Symbol
	Termal :: prepareTerm
	(
		const del :: Term* complexTerm,
		del :: Theory* theory,
		del :: Signature* delta
	) const
	{
		const Symbol symbol = complexTerm->defineSelf (theory, image_, "C", isNormal());
		if ((delta != NULL) && (complexTerm->isOfSignature (delta))) {
			delta->addSymbol (symbol);
		}
		return symbol;
	}
}
}
}

#endif /*DEL_SOURCE_FORMULA_TERMAL_CPP_*/
