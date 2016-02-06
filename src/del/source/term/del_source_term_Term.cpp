/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_term_Term.cpp                                 */
/* Description:     base term class                                          */
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
namespace term {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Term :: Term (const Location& location) :
	location_ (location),
	terms_ (),
	primitivization_ () {
	}
	inline
	Term :: Term (const Location& location, const del :: Term* term) :
	location_ (location),
	terms_ (1),
	primitivization_ () {
		terms_.add (term);
	}
	inline
	Term :: Term (const Location& location, const vector :: Term& terms) :
	location_ (location),
	terms_ (terms),
	primitivization_ () {
	}
	inline
	Term :: Term (const vector :: Term& terms) :
	location_ (),
	terms_ (terms),
	primitivization_ () {
	}
	inline
	Term :: Term (const del :: Term* terms[], const value :: Integer size) :
	location_ (),
	terms_ (terms, size),
	primitivization_ () {
	}
	inline
	Term :: Term (const del :: Term* term) :
	location_(),
	terms_ (1),
	primitivization_ () {
		terms_.add (term);
	}
	inline
	Term :: Term (const Term& term) :
	location_ (term.location_),
	terms_ (term.terms_.getSize()),
	primitivization_ (term.primitivization_)
	{
		for (value :: Integer i = 0; i < term.terms_.getSize(); ++ i) {
			const del :: Term* const
				t = term.terms_.getValue (i);
			terms_.add (t->clone());
		}
	}
	Term :: ~ Term() {
	}

	inline del :: Term*
	Term :: createRandom (const del :: Signature* signature)
	{
		const value :: Integer size = rand() % Config :: getTermMaxLength();
		const value :: Integer depth = rand() % Config :: getTermMaxDepth();
		return createRandom (signature, size, depth);
	}

	inline void
	Term :: addSubterm (const del :: Term* term) {
		terms_.add (term);
	}
	void
	Term :: replace
	(
		del :: Term*& term,
		const del :: Term* oldTerm,
		const del :: Term* newTerm
	)
	{
		if (term->getDepth() < oldTerm->getDepth()) {
			return;
		}
		if (term->getLength() < oldTerm->getLength()) {
			return;
		}
		if (term->isEqual (oldTerm)) {
			term->commitSuicide();
			term = newTerm->clone();
			return;
		}
		term->replace (oldTerm, newTerm);
	}

	// del :: Term implementation
	void
	Term :: assemble() {
	}
	bool
	Term :: normalize (del :: Theory* theory, const del :: Formula* image) const
	{
		for (value :: Integer i = 0; i < terms_.getSize(); ++ i) {
			const del :: Term* const
				subterm = terms_.getValue (i);
			if (subterm->isDeep()) {
				return subterm->normalize (theory, image);
			}
			if (subterm->isAtomic()) {
				continue;
			} else {
				subterm->defineSelf (theory, image, "T");
				return true;
			}
		}
		return false;
	}
	bool
	Term :: isOfSignature (const del :: Signature* signature) const
	{
		for (value :: Integer i = 0; i < terms_.getSize(); ++ i) {
			const del :: Term* const
				term = terms_.getValue (i);
			if (!term->isOfSignature (signature)) {
				return false;
			}
		}
		return true;
	}
	bool
	Term :: contains (const del :: Symbol& symbol) const
	{
		for (value :: Integer i = 0; i < terms_.getSize(); ++ i) {
			const del :: Term* const
				term = terms_.getValue (i);
			if (term->contains (symbol)) {
				return true;
			}
		}
		return false;
	}
	void
	Term :: makeDeltaCopy (const del :: Expansion* expansion)
	{
		for (value :: Integer i = 0; i < terms_.getSize(); ++ i) {
			del :: Term* const
				term = const_cast<del :: Term*>(terms_.getValue (i));
			term->makeDeltaCopy (expansion);
		}
		primitivization_.undefine();
	}
	void
	Term :: makeDeltaCopy (const del :: Signature* delta)
	{
		for (value :: Integer i = 0; i < terms_.getSize(); ++ i) {
			del :: Term* const
				term = const_cast<del :: Term*>(terms_.getValue (i));
			term->makeDeltaCopy (delta);
		}
		primitivization_.undefine();
	}
	void
	Term :: completeSignature (del :: Signature* signature) const
	{
		for (value :: Integer i = 0; i < terms_.getSize(); ++ i) {
			const del :: Term* const
				term = terms_.getValue (i);
			term->completeSignature (signature);
		}
	}
	value :: Integer
	Term :: getSize() const {
		return terms_.getSize();
	}
	const del :: Term*
	Term :: getSubterm (const value :: Integer i) const {
		return terms_.getValue (i);
	}
	bool
	Term :: isEqual (const del :: Term* term) const
	{
		if (getDepth() != term->getDepth()) {
			return false;
		}
		if (getLength() != term->getLength()) {
			return false;
		}
		if (!isSubset (term, this)) {
			return false;
		}
		if (!isSubset (this, term)) {
			return false;
		}
		return true;
	}
	const del :: Term*
	Term :: simplify()
	{
		for (value :: Integer i = 0; i < terms_.getSize(); ++ i) {
			const del :: Term*&
				term = terms_.getReference (i);
			term = const_cast<del :: Term*&>(term)->simplify();
		}
		return NULL;
	}
	void
	Term :: replace (const del :: Term* oldTerm, const del :: Term* newTerm)
	{
		for (value :: Integer i = 0; i < terms_.getSize(); ++ i) {
			const del :: Term*&
				term = terms_.getReference (i);
			replace (const_cast<del :: Term*&>(term), oldTerm, newTerm);
		}
	}
	void
	Term :: replaceSubterm (const value :: Integer index, const del :: Term* newTerm)
	{
		const del :: Term*&
			term = terms_.getReference (index);
		const_cast<del :: Term*>(term)->commitSuicide();
		term = newTerm;
	}
	void
	Term :: removeSubterm (const value :: Integer index)
	{
		const del :: Term*&
			term = terms_.getReference (index);
		const_cast<del :: Term*>(term)->commitSuicide();
		terms_.remove (index);
	}
	// maximum subterm depth
	value :: Integer
	Term :: getDepth() const
	{
		value :: Integer depth = 0;
		for (value :: Integer i = 0; i < terms_.getSize(); ++ i) {
			const del :: Term*
				term = terms_.getValue (i);
			const value :: Integer
				termDepth = term->getDepth();
			if (termDepth > depth) {
				depth = termDepth;
			}
		}
		return depth;
	}
	// sum of subterm length
	value :: Integer
	Term :: getLength() const
	{
		value :: Integer length = 0;
		for (value :: Integer i = 0; i < terms_.getSize(); ++ i) {
			const del :: Term*
				term = terms_.getValue (i);
			const value :: Integer
				termLength = term->getLength();
			if (termLength > length) {
				length = termLength;
			}
		}
		return length;
	}
	bool
	Term :: isPrimitivized() const {
		return primitivization_.isDefined();
	}
	void
	Term :: setPrimitivized (const bool isPrimitivized) const
	{
		if (isPrimitivized) {
			primitivize ("F");
		} else {
			primitivization_.undefine();
		}
	}
	Symbol
	Term :: getPrimitivization() const {
		return primitivization_;
	}
	bool
	Term :: hasTemporarySymbols() const
	{
		for (value :: Integer i = 0; i < terms_.getSize(); ++ i) {
			const del :: Term*
				term = terms_.getValue (i);
			if (term->hasTemporarySymbols()) {
				return true;
			}
		}
		return false;
	}
	Symbol
	Term :: defineSelf
	(
		del :: Theory* theory,
		const del :: Formula* image,
		const char* suffix,
		const bool inNormalFormula
	) const
	{
		const Symbol symbol = primitivize (suffix);
		del :: Term* const varTerm = new term :: Variable (symbol);
		del :: Term* defTerm = clone();
		del :: Formula* const
			formula_1 = formula :: Subset :: create
			(
				new term :: Variable (symbol),
				clone(),
				image,
				false, // isRoot
				false, // isPrimary
				false  // isDefinition
			);
		del :: Formula* const
			formula_2 = formula :: Subset :: create
			(
				clone(),
				new term :: Variable (symbol),
				image,
				false, // isRoot
				false, // isPrimary
				true   // isDefinition
			);
		theory->replaceTerm (defTerm, varTerm);
		if (inNormalFormula) {
			formula_1->normalize (theory);
			if (defTerm->getKind() == INTERSECT_KIND) {
				formula_1->commitSuicide();
			} else {
				theory->addFormula (formula_1);
			}
		} else {
			theory->addFormula (formula_1);
		}
		theory->addFormula (formula_2);
		defTerm->commitSuicide();
		varTerm->commitSuicide();
		return symbol;
	}

	// object :: Object implementation
	void
	Term :: commitSuicide() {
		delete this;
	}
	Size_t
	Term :: getVolume() const
	{
		Size_t volume = 0;
		volume += terms_.getVolume();
		return volume;
	}
	Size_t
	Term :: getSizeOf() const {
		return sizeof (Term);
	}

	/****************************
	 *		Protected members
	 ****************************/

	bool
	Term :: isSubset (const del :: Term* term_1, const del :: Term* term_2) const
	{
		for (value :: Integer i = 0; i < term_1->getSize(); ++ i) {
			const del :: Term* const
				term_a = term_1->getSubterm (i);
			bool isIncluded = false;
			for (value :: Integer j = 0; j < term_2->getSize(); ++ j) {
				const del :: Term* const
					term_b = term_2->getSubterm (j);
				if (term_a->isEqual (term_b)) {
					isIncluded = true;
					break;
				}
			}
			if (!isIncluded) {
				return false;
			}
		}
		return true;
	}
	del :: Term*
	Term :: createRandom
	(
		const del :: Signature* signature,
		const value :: Integer size,
		const value :: Integer depth
	)
	{
		if (depth <= 1) {
			return createRandomSizeOne (signature);
		}
		switch (size) {
		case 1 :
			return createRandomSizeOne (signature);
		case 2 :
			return createRandomSizeTwo (signature);
		case 3 :
			return createRandomSizeThree (signature, depth);
		default :
			return createRandomSizeFourOrMore (signature, size, depth);
		}
	}
	del :: Term*
	Term :: createRandomSizeOne (const del :: Signature* signature)
	{
		const value :: Integer tp = rand() % 10;
		switch (tp) {
		case 0 :
			return new Top();
		default :
			return new Variable (signature->getRandomConcept());
		}
	}
	del :: Term*
	Term :: createRandomSizeTwo (const del :: Signature* signature)
	{
		const value :: Integer tp = rand() % 4;
		switch (tp) {
		case 0 :
			return new Top();
		case 1 :
			return new Variable (signature->getRandomConcept());
		case 2 : {
			del :: Term* term = createRandomSizeOne (signature);
			return new Exists (signature->getRandomRelation(), term);
		}
		default : {
			const del :: Term* terms [2];
			terms [0] = createRandomSizeOne (signature);
			terms [1] = createRandomSizeOne (signature);
			return new Intersect (terms, 2);
		}
		}
	}
	del :: Term*
	Term :: createRandomSizeThree
	(
		const del :: Signature* signature,
		const value :: Integer depth
	)
	{
		const value :: Integer tp = rand() % 4;
		switch (tp) {
		case 0 :
			return new Top();
		case 1 :
			return new Variable (signature->getRandomConcept());
		case 2 : {
			del :: Term* term = createRandomSizeTwo (signature);
			return new Exists (signature->getRandomRelation(), term);
		}
		default : {
			const value :: Integer n = 2 + (rand() % 2);
			const del :: Term* terms [n];
			for (value :: Integer i = 0; i < n; ++ i) {
				terms [i] = createRandomSizeOne (signature);
			}
			return new Intersect (terms, n);
		}
		}
	}
	del :: Term*
	Term :: createRandomSizeFourOrMore
	(
		const del :: Signature* signature,
		const value :: Integer size,
		const value :: Integer depth
	)
	{
		const value :: Integer tp = rand() % 4;
		switch (tp) {
		case 0 :
			return new Top();
		case 1 :
			return new Variable (signature->getRandomConcept());
		case 2 : {
			del :: Term* term = createRandom (signature, size - 1, depth - 1);
			return new Exists (signature->getRandomRelation(), term);
		}
		default : {
			const value :: Integer n = 2 + (rand() % 2);
			const del :: Term* terms [n];
			for (value :: Integer i = 0; i < n; ++ i) {
				terms [i] = createRandom (signature, size - n, depth - 1);
			}
			return new Intersect (terms, n);
		}
		}
	}
}
}
}


