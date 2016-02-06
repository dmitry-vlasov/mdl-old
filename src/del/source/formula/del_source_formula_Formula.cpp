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

#pragma once

#include "del/lexer/del_lexer.hpp"
#include "del/source/del_source.hpp"

namespace del {
namespace source {
namespace formula {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Formula :: Formula
	(
		const Location location,
		const del :: Formula* image,
		const Kind kind,
		const bool isRoot,
		const bool isPrimary,
		const bool isDefinition
	) :
	location_ (location),
	signature_ (new source :: Signature<>()),
	kind_ (kind),
	image_ (image),
	isRoot_ (isRoot),
	isPrimary_ (isPrimary),
	isDefinition_ (isDefinition) {
	}
	inline
	Formula :: Formula (const del :: Formula* formula) :
	location_ (),
	signature_ (formula->getSignature()->clone()),
	kind_ (formula->getKind()),
	image_ (formula->getImage()),
	isRoot_ (formula->isRoot()),
	isPrimary_ (formula->isPrimary()),
	isDefinition_ (formula->isDefinition()) {
	}
	inline
	Formula :: Formula (const Formula& formula) :
	location_ (formula.location_),
	signature_ (formula.signature_->clone()),
	kind_ (formula.kind_),
	image_ (formula.image_),
	isRoot_ (formula.isRoot_),
	isPrimary_ (formula.isPrimary_),
	isDefinition_ (formula.isDefinition_) {
	}
	Formula :: ~ Formula() {
		deleteAggregateObject (signature_);
	}

	del :: Formula*
	Formula :: createRandom (const del :: Signature* signature)
	{
		del :: Term* term_1 = term :: Term :: createRandom (signature);
		del :: Term* term_2 = term :: Term :: createRandom (signature);
		term_1 = const_cast<del :: Term*>(term_1->simplify());
		term_2 = const_cast<del :: Term*>(term_2->simplify());
		const bool subset = rand() % 2;
		if (subset) {
			return new subset :: Subset (Location(), term_1, term_2);
			//return subset :: Subset :: create (term_1, term_2);
		} else {
			return equiv :: Identity :: create (term_1, term_2);
		}
	}

	// del :: Formula implementation
	const del :: Signature*
	Formula :: getSignature (const bool force) const {
		return signature_;
	}
	bool
	Formula :: isConnected (const del :: Symbol& symbol) const {
		return signature_->containsSymbol (symbol);
	}

	bool
	Formula :: isRoot() const {
		return isRoot_;
	}
	bool
	Formula :: isPrimary() const {
		return isPrimary_;
	}
	bool
	Formula :: isDefinition() const {
		return isDefinition_;
	}
	void
	Formula :: setRoot (const bool isRoot) {
		isRoot_ = isRoot;
	}
	void
	Formula :: setPrimary (const bool isPrimary) {
		isPrimary_ = isPrimary;
	}
	void
	Formula :: setDefinition (const bool isDefinition) {
		isDefinition_ = isDefinition;
	}

	bool
	Formula :: isEqual (const del :: Formula* formula) const
	{
		return
			(getKind() == formula->getKind()) &&
			(getType() == formula->getType());
	}
	void
	Formula :: makeDeltaCopy (const del :: Expansion* expansion) {
		signature_->makeDeltaCopy (expansion);
	}
	const del :: Formula*
	Formula :: getImage() const {
		return image_;
	}
	void
	Formula :: setImage (const del :: Formula* image) {
		image_ = image;
	}
	const Location&
	Formula :: getLocation() const {
		return location_;
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Writable implementation
	void
	Formula :: translate (String& string) const {
		replicate (string);
	}
	void
	Formula :: show (String& string) const
	{
		replicate (string);
		if (isRoot_ || isPrimary_ || isDefinition_ || isPrimitivized()) {
			string << space;
			if (isRoot_) {
				string << "#";
			}
			if (isPrimary_) {
				string << "$";
			}
			if (isDefinition_) {
				string << "d";
			}
			if (isPrimitivized()) {
				string << "p";
			}
			string << space;
		}
	}

	// object :: Object implementation
	void
	Formula :: commitSuicide() {
		delete this;
	}
	Size_t
	Formula :: getVolume() const {
		return getAggregateVolume (signature_);
	}
	Size_t
	Formula :: getSizeOf() const {
		return sizeof (Formula);
	}

	/****************************
	 *		Protected members
	 ****************************/

	bool
	Formula :: oneNonDeltaSymbol (const del :: Signature* delta) const
	{
		del :: Signature* signature = getSignature()->clone();
		signature->subtract (delta);
		const bool result = (signature->cardinality() <= 1);
		signature->commitSuicide();
		return result;
	}
}
}
}


