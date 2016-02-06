/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_formula_subset_Subset.hpp                     */
/* Description:     subset formula class                                     */
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

	/****************************
	 *		Public members
	 ****************************/

	inline
	Subset :: Subset
	(
		const del :: Term* const term_1,
		const del :: Term* const term_2,
		const del :: Formula* image,
		const Kind kind,
		const bool isRoot,
		const bool isPrimary,
		const bool isDefinition
	) :
	Termal
	(
		Location(),
		term_1,
		term_2,
		((image == NULL) ? this : image),
		kind,
		isRoot,
		isPrimary,
		isDefinition
	) {
	}
	inline
	Subset :: Subset
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
	Termal
	(
		location,
		term_1,
		term_2,
		((image == NULL) ? this : image),
		kind,
		isRoot,
		isPrimary,
		isDefinition
	) {
	}
	inline
	Subset :: Subset (const del :: Formula* formula) :
	Termal (formula) {
	}
	inline
	Subset :: Subset (const Subset& subset) :
	Termal (subset) {
	}
	Subset :: ~ Subset() {
	}

	del :: Formula*
	Subset :: createTautology (const del :: Symbol& symbol)
	{
		del :: Formula* tautology = NULL;
		if (symbol.isRelation()) {
			tautology = new del :: source :: formula :: Subset
			(
				new del :: source :: term :: Exists (
					symbol,
					new del :: source :: term :: Top ()
				),
				new del :: source :: term :: Top ()
			);
		} else {
			tautology = new del :: source :: formula :: Subset
			(
				new del :: source :: term :: Variable (symbol),
				new del :: source :: term :: Variable (symbol)
			);
		}
		return tautology;
	}
	del :: Formula*
	Subset :: create
	(
		const del :: Term* const term_1,
		const del :: Term* const term_2,
		const del :: Formula* image,
		const bool isRoot,
		const bool isPrimary,
		const bool isDefinition
	)
	{
		const del :: Formula :: Kind
			kind = del :: Formula :: getKind (term_1, term_2);
		switch (kind) {
		case del :: Formula :: SIMPLE_SUB_KIND :
			return new normal :: Simple (Location(), term_1, term_2, image, isRoot, isPrimary, isDefinition);
		case del :: Formula :: CONJ_SUB_KIND :
			return new normal :: Conjunction (Location(), term_1, term_2, image, isRoot, isPrimary, isDefinition);
		case del :: Formula :: RIGHT_SUB_KIND :
			return new normal :: RightExists (Location(), term_1, term_2, image, isRoot, isPrimary, isDefinition);
		case del :: Formula :: LEFT_SUB_KIND :
			return new normal :: LeftExists (Location(), term_1, term_2, image, isRoot, isPrimary, isDefinition);
		case del :: Formula :: GENERAL_SUB_KIND :
			return new Subset (Location(), term_1, term_2, image, GENERAL_SUB_KIND, isRoot, isPrimary, isDefinition);
		default :
			Error* error = new Error (Error :: SEMANTIC);
			error->message() << "non-normal formula" << endLine;
			throw error;
		}
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// del :: Formula implementation
	bool
	Subset :: isTrivial() const
	{
		if (term_1_->isEqual (term_2_)) {
			return true;
		}
		if (term_2_->getKind() == del :: Term :: TOP_KIND) {
			return true;
		}
		return false;
	}
	bool
	Subset :: isTrue (const del :: Model* model) const
	{
		if (getKind() != SIMPLE_SUB_KIND) {
			if (!isPrimitivized()) {
				Error* error = new Error();
				error->message() << "non-simple formula truth value request." << endLine;
				throw error;
			}
			const Symbol a = term_1_->getPrimitivization();
			const Symbol b = term_2_->getPrimitivization();
			return model->isTrueSubseteq (a, b);
		} else {
			const Symbol a = term_1_->getSymbol();
			const Symbol b = term_2_->getSymbol();
			return model->isTrueSubseteq (a, b);
		}
	}
	bool
	Subset :: isTrue (const del :: Model* model, const set :: Formula* untheory) const
	{
		if (getKind() != SIMPLE_SUB_KIND) {
			return false;
		}
		const Symbol a = term_1_->getSymbol();
		const Symbol b = term_2_->getSymbol();
		return model->isTrueSubseteq (a, b, untheory);
	}
	const del :: Term*
	Subset :: evalInterpolant (const del :: Model* model, const del :: Signature* delta) const
	{
		if (getKind() != SIMPLE_SUB_KIND) {
			if (!isPrimitivized()) {
				Error* error = new Error();
				error->message() << "non-simple formula truth value request." << endLine;
				throw error;
			}
			const Symbol a = term_1_->getPrimitivization();
			const Symbol b = term_2_->getPrimitivization();
			return model->evalInterpolant (a, b, delta);
		}
		const Symbol a = term_1_->getSymbol();
		const Symbol b = term_2_->getSymbol();
		return model->evalInterpolant (a, b, delta);
	}
	bool
	Subset :: decompose (del :: Theory* theory, const del :: Signature* delta, const bool)
	{
		if (term_1_->isOfSignature (delta) ||
			term_2_->isOfSignature (delta)) {
			return false;
		}
		std :: cout << std :: endl;
		std :: cout << "minimal theory in input:" << std :: endl;
		std :: cout << *Decompose :: current()->getMinimalTheory() << std :: endl << std :: endl;

		std :: cout << "delta:" << std :: endl;
		std :: cout << *delta << std :: endl << std :: endl;

		std :: cout << "theory being decomposed:" << std :: endl;
		std :: cout << *theory << std :: endl << std :: endl;

		std :: cout << "error formula:" << std :: endl;
		std :: cout << *this << std :: endl;
		throw new Error();
	}

	bool
	Subset :: apply (Model*) const
	{
		std :: cout << *this << std :: endl;
		throw new Error();
	}
	bool
	Subset :: extendWithCopies (del :: Theory*, const del :: Signature*) const  {
		return false;
	}

	bool
	Subset :: isNormal() const {
		return false;
	}
	bool
	Subset :: normalize (del :: Theory* theory) const
	{
		if (term_2_->getKind() == del :: Term :: INTERSECT_KIND) {
			return normalizeIntersection (theory);
		}
		if (term_1_->normalize (theory, image_)) {
			theory->addFormula (clone());
			return true;
		}
		if (term_2_->normalize (theory, image_)) {
			theory->addFormula (clone());
			return true;
		}
		return normalizeInclusion (theory);
	}

	Subset :: Type
	Subset :: getType() const {
		return SUBSET_TYPE;
	}
	bool
	Subset :: hasInvalidKind() const {
		return false;
	}

	// del :: Cloneable implementation
	del :: Formula*
	Subset :: clone() const {
		return new Subset (*this);
	}

	// object :: Writable implementation
	void
	Subset :: replicate (String& string) const
	{
		switch (Config :: outputFormat()) {
		case Config :: DEL_FORMAT : {
			string << location_.getIndent();
			term_1_->replicate (string);
			string << space << Token :: subset_;
			string << suffix() << space;
			term_2_->replicate (string);
			break;
		}
		case Config :: MAN_FORMAT : break;
		case Config :: FUNC_FORMAT : {
			string << location_.getIndent();
			string << owl :: func :: Token :: subclassOf_;
			string << owl :: func :: Token :: openBracket_;
			term_1_->replicate (string);
			string << space;
			term_2_->replicate (string);
			string << owl :: func :: Token :: closeBracket_;
			break;
		}
		default : break;
		}
	}
	void
	Subset :: translate (String& string) const {
		replicate (string);
	}

	// object :: Object implementation
	void
	Subset :: commitSuicide() {
		delete this;
	}
	Size_t
	Subset :: getVolume() const
	{
		Size_t volume = 0;
		volume += Termal :: getVolume();
		return volume;
	}
	Size_t
	Subset :: getSizeOf() const {
		return sizeof (Subset);
	}

	/****************************
	 *		Protected members
	 ****************************/

	const char*
	Subset :: suffix() const {
		return "";
	}

	/****************************
	 *		Private members
	 ****************************/

	bool
	Subset :: normalizeIntersection (del :: Theory* theory) const
	{
		/* Replace each C ⊑ C1 ⊓ C2 ... ⊓ Cn
		 * by C ⊑ C1, C ⊑ C2 ... C ⊑ Cn */
		for (value :: Integer i = 0; i < term_2_->getSize(); ++ i) {
			const del :: Formula* const formula = new Subset
			(
				location_,
				term_1_->clone(),
				term_2_->getSubterm (i)->clone(),
				image_,
				GENERAL_SUB_KIND,
				isRoot_,
				isPrimary_,
				false
			);
			theory->addFormula (formula);
		}
		return true;
	}
	bool
	Subset :: normalizeInclusion (del :: Theory* theory) const
	{
		/* If C ⊑ D , remove it, take a new concept name X
		 * and add C ≡ X and X ⊑ D to T */

		const Symbol symbol = term_1_->defineSelf (theory, image_, "I");
		const del :: Formula* const formula = new formula :: Subset
		(
			location_,
			new term :: Variable (symbol),
			term_2_->clone(),
			image_,
			GENERAL_SUB_KIND,
			isRoot_,
			isPrimary_,
			false // isDefinition_
		);
		theory->addFormula (formula);
		return true;
	}
}
}
}
}


