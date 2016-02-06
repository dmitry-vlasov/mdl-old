/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_formula_equiv_Equivalence.cpp                 */
/* Description:     base class for equivalence formula                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/lexer/del_lexer.hpp"

namespace del {
namespace source {
namespace formula {
namespace equiv {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Equivalence :: Equivalence
	(
		const Location location,
		const del :: Formula* image,
		const Kind kind,
		const bool isRoot,
		const bool isPrimary,
		const bool isDefinition
	) :
	Formula (location, image, kind, isRoot, isPrimary, isDefinition) {
	}
	inline
	Equivalence :: Equivalence (const Equivalence& equivalence) :
	Formula (equivalence)
	{
		inclusion_1_ = equivalence.inclusion_1_->clone();
		inclusion_2_ = equivalence.inclusion_2_->clone();
	}
	Equivalence :: ~ Equivalence()
	{
		deleteAggregateObject (inclusion_1_);
		deleteAggregateObject (inclusion_2_);
	}

	// del :: Formula implementation
	bool
	Equivalence :: isTrivial() const
	{
		const del :: Term*
			term_1 = inclusion_1_->getTerm (0);
		const del :: Term*
			term_2 = inclusion_1_->getTerm (1);
		return term_1->isEqual (term_2);
	}
	bool
	Equivalence :: isTrue (const del :: Model* model) const
	{
		const bool true_1 = inclusion_1_->isTrue (model);
		const bool true_2 = inclusion_2_->isTrue (model);
		return (true_1 && true_2);
	}
	bool
	Equivalence :: isTrue (const del :: Model* model, const set :: Formula* untheory) const {
		throw new Error();
	}
	const del :: Term*
	Equivalence :: evalInterpolant (const del :: Model* model, const del :: Signature* delta) const {
		return inclusion_1_->evalInterpolant (model, delta);
	}
	const del :: Signature*
	Equivalence :: getSignature (const bool force) const
	{
		inclusion_1_->getSignature (force);
		inclusion_2_->getSignature (force);
		signature_->copy (inclusion_1_->getSignature());
		return signature_;
	}
	bool
	Equivalence :: decompose
	(
		del :: Theory* theory,
		const del :: Signature* signature,
		const bool forTheFirstTime
	)
	{
		const bool dec_1 = inclusion_1_->decompose (theory, signature, forTheFirstTime);
		const bool dec_2 = inclusion_2_->decompose (theory, signature, forTheFirstTime);
		return (dec_1 || dec_2);
	}

	bool
	Equivalence :: apply (del :: Model* model) const
	{
		const bool apply_1 = inclusion_1_->apply (model);
		const bool apply_2 = inclusion_2_->apply (model);
		return (apply_1 || apply_2);
	}
	bool
	Equivalence :: extendWithCopies (del :: Theory* theory, const del :: Signature* delta) const
	{
		const bool extend_1 = inclusion_1_->extendWithCopies (theory, delta);
		const bool extend_2 = inclusion_2_->extendWithCopies (theory, delta);
		return (extend_1 || extend_2);
	}

	bool
	Equivalence :: isNormal() const
	{
		const bool norm_1 = inclusion_1_->isNormal();
		const bool norm_2 = inclusion_2_->isNormal();
		return (norm_1 && norm_2);
	}
	bool
	Equivalence :: isPrimitivized() const
	{
		const bool prim_1 = inclusion_1_->isPrimitivized();
		const bool prim_2 = inclusion_2_->isPrimitivized();
		return (prim_1 && prim_2);
	}
	void
	Equivalence :: setPrimitivized (const bool isPrimitivized)
	{
		inclusion_1_->setPrimitivized (isPrimitivized);
		inclusion_2_->setPrimitivized (isPrimitivized);
	}
	bool
	Equivalence :: normalize (del :: Theory* theory) const
	{
		theory->addFormula (inclusion_1_->clone());
		theory->addFormula (inclusion_2_->clone());
		return true;
	}
	void
	Equivalence :: makeDeltaCopy (const del :: Expansion* expansion)
	{
		inclusion_1_->makeDeltaCopy (expansion);
		inclusion_2_->makeDeltaCopy (expansion);
	}
	void
	Equivalence :: makeDeltaCopy (const del :: Signature* delta)
	{
		inclusion_1_->makeDeltaCopy (delta);
		inclusion_2_->makeDeltaCopy (delta);
	}
	bool
	Equivalence :: isEqual (const del :: Formula* formula) const
	{
		if (!Formula :: isEqual (formula)) {
			return false;
		}
		const Equivalence* eq = dynamic_cast<const Equivalence*>(formula);
		return
			(inclusion_1_->isEqual (eq->inclusion_1_) && inclusion_2_->isEqual (eq->inclusion_2_)) ||
			(inclusion_1_->isEqual (eq->inclusion_2_) && inclusion_2_->isEqual (eq->inclusion_1_));
	}
	const del :: Term*
	Equivalence :: getTerm (const value :: Integer i) const {
		return inclusion_1_->getTerm (i);
	}
	void
	Equivalence :: simplify()
	{
		inclusion_1_->simplify();
		inclusion_2_->simplify();
	}
	bool
	Equivalence :: primitivize (del :: Theory* theory, del :: Signature* signature, const bool addToTheory) const
	{
		const bool prim_1 = inclusion_1_->primitivize (theory, signature, addToTheory);
		const bool prim_2 = inclusion_2_->primitivize (theory, signature, addToTheory);
		return (prim_1 || prim_2);
	}
	void
	Equivalence :: replace (const del :: Term* term_1, const del :: Term* term_2)
	{
		inclusion_1_->replace (term_1, term_2);
		inclusion_2_->replace (term_1, term_2);
	}
	del :: Formula :: Type
	Equivalence :: getType() const {
		return EQUALITY_TYPE;
	}
	bool
	Equivalence :: hasInvalidKind() const
	{
		const bool invalid_1 = inclusion_1_->hasInvalidKind();
		const bool invalid_2 = inclusion_2_->hasInvalidKind();
		return (invalid_1 || invalid_2);
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Writable implementation
	void
	Equivalence :: translate (String& string) const {
		replicate (string);
	}
	void
	Equivalence :: replicate (String& string) const
	{
		switch (Config :: outputFormat()) {
		case Config :: DEL_FORMAT : {
			string << location_.getIndent();
			inclusion_1_->getTerm (0)->replicate (string);
			string << space << Token :: equal_;
			string << suffix() << space;
			inclusion_1_->getTerm (1)->replicate (string);
			break;
		}
		case Config :: MAN_FORMAT : break;
		case Config :: FUNC_FORMAT : {
			string << location_.getIndent();
			string << owl :: func :: Token :: equivalentClasses_;
			string << owl :: func :: Token :: openBracket_;
			inclusion_1_->getTerm (0)->replicate (string);
			string << space;
			inclusion_1_->getTerm (1)->replicate (string);
			string << owl :: func :: Token :: closeBracket_;
			break;
		}
		default : break;
		}
	}

	// object :: Object implementation
	void
	Equivalence :: commitSuicide() {
		delete this;
	}
	Size_t
	Equivalence :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (inclusion_1_);
		volume += getAggregateVolume (inclusion_2_);
		volume += Formula :: getVolume();
		return volume;
	}
	Size_t
	Equivalence :: getSizeOf() const {
		return sizeof (Equivalence);
	}

	/****************************
	 *		Protected members
	 ****************************/

	const char*
	Equivalence :: suffix() const {
		return "";
	}
}
}
}
}


