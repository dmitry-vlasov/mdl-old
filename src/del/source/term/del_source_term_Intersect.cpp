/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_term_Intersect.cpp                            */
/* Description:     exists term class                                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_SOURCE_TERM_INTERSECT_CPP_
#define DEL_SOURCE_TERM_INTERSECT_CPP_

#include "del/lexer/del_lexer.hpp"

namespace del {
namespace source {
namespace term {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Intersect :: Intersect (const Location& location) :
	Term (location) {
	}
	inline
	Intersect :: Intersect
	(
		const Location& location,
		const vector :: Term& terms
	) :
	Term (location, terms) {
	}
	inline
	Intersect :: Intersect (const vector :: Term& terms) :
	Term (terms) {
	}
	inline
	Intersect :: Intersect (const del :: Term* terms[], const value :: Integer size) :
	Term (terms, size) {
	}
	inline
	Intersect :: Intersect (const Intersect& intersect) :
	Term (intersect) {
	}
	Intersect :: ~ Intersect() {
	}

	void
	Intersect :: addTerm (const del :: Term* term) {
		Term :: terms_.add (term);
	}

	// del :: Term implementation
	const del :: Symbol&
	Intersect :: getSymbol() const
	{
		Error* error = new Error (Error :: SEMANTIC);
		error->message() << "illegal variable name request: complex term (intersection)" << endLine;
		throw error;
	}
	bool
	Intersect :: isEqual (const del :: Term* term) const
	{
		if (term->getKind() != INTERSECT_KIND) {
			return false;
		}
		return Term :: isEqual (term);
	}
	const del :: Term*
	Intersect :: simplify()
	{
		Term :: simplify();
		if (!isPlain()) {
			becomePlain();
		}
		if (!isNonTop()) {
			removeTop();
		}
		removeRedundant();
		if (terms_.getSize() == 0) {
			clearTerms();
			commitSuicide();
			return new term :: Top (location_);
		}
		if (terms_.getSize() == 1) {
			const del :: Term* const
				term = getSubterm();
			clearTerms();
			commitSuicide();
			return term;
		}
		return this;
	}
	void
	Intersect :: replace (const del :: Term* oldTerm, const del :: Term* newTerm) {
		Term :: replace (oldTerm, newTerm);
	}
	value :: Integer
	Intersect :: getDepth() const {
		return 1 + Term :: getDepth();
	}
	value :: Integer
	Intersect :: getLength() const
	{
		const value :: Integer
			subtermsLength = Term :: getLength();
		const value :: Integer
			sqcapSymbols = Term :: getSize() - 1;
		return 2 + subtermsLength + sqcapSymbols;
	}

	Symbol
	Intersect :: primitivize (const char* suffix) const
	{
		if (primitivization_.isDefined()) {
			return primitivization_;
		}
		value :: Variable var = value :: undefined :: VARIABLE;
		if (Config :: keepTermNames()) {
			const value :: Integer
				size = terms_.getSize();
			Symbol
				symbolsForSubterms [size];
			for (value :: Integer i = 0; i < size; ++ i) {
				symbolsForSubterms [i] = getSubterm (i)->primitivize (suffix);
			}
			String string (256);
			string << "(";
			for (value :: Integer i = 0; i < size; ++ i) {
				string << symbolsForSubterms [i];
				if (i < size - 1) {
					string << Token :: intersect_ << '_';
				}
			}
			string << ")";
			var = Table :: variables()->add (string);
		} else {
			var = Table :: variables()->fresh (suffix);
		}
		primitivization_ = Symbol (var, false, false, true);
		return primitivization_;
	}
	bool
	Intersect :: hasTemporarySymbols() const {
		return Term :: hasTemporarySymbols();
	}
	Intersect :: Kind
	Intersect :: getKind() const {
		return INTERSECT_KIND;
	}

	// del :: Cloneable implementation
	del :: Term*
	Intersect :: clone() const {
		return new Intersect (*this);
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Writable implementation
	void
	Intersect :: translate (String& string) const {
		replicate (string);
	}
	void
	Intersect :: replicate (String& string) const
	{
		switch (Config :: outputFormat()) {
		case Config :: DEL_FORMAT : {
			string << Token :: openBracket_;
			const value :: Integer size = getSize();
			for (value :: Integer i = 0; i < size; ++ i) {
				const del :: Term* const
					term = getSubterm (i);
				term->replicate (string);
				if (i < size - 1) {
					string << Token :: intersect_;
				} else {
					string << Token :: closeBracket_;
				}
			}
			break;
		}
		case Config :: MAN_FORMAT : {
			string << owl :: man :: Token :: openBracket_;
			const value :: Integer size = getSize();
			for (value :: Integer i = 0; i < size; ++ i) {
				const del :: Term* const
					term = getSubterm (i);
				term->replicate (string);
				if (i < size - 1) {
					string << space << owl :: man :: Token :: and_ << space;
				} else {
					string << owl :: man :: Token :: closeBracket_;
				}
			}
			break;
		}
		case Config :: FUNC_FORMAT : {
			string << owl :: func :: Token :: objectIntersectionOf_;
			string << owl :: func :: Token :: openBracket_;
			const value :: Integer size = getSize();
			for (value :: Integer i = 0; i < size; ++ i) {
				const del :: Term* const
					term = getSubterm (i);
				term->replicate (string);
				if (i < size - 1) {
					string << space;
				} else {
					string << owl :: func :: Token :: closeBracket_;
				}
			}
			break;
		}
		default : break;
		}
	}

	// object :: Object implementation
	void
	Intersect :: commitSuicide() {
		delete this;
	}
	Size_t
	Intersect :: getVolume() const {
		return Term :: getVolume();
	}
	Size_t
	Intersect :: getSizeOf() const {
		return sizeof (Intersect);
	}

	/****************************
	 *		Private members
	 ****************************/

	bool
	Intersect :: isPlain() const
	{
		for (value :: Integer i = 0; i < terms_.getSize(); ++ i) {
			const del :: Term* const
				term = terms_.getValue (i);
			if (term->getKind() == INTERSECT_KIND) {
				return false;
			}
		}
		return true;
	}
	bool
	Intersect :: isNonTop() const
	{
		for (value :: Integer i = 0; i < terms_.getSize(); ++ i) {
			const del :: Term* const
				term = terms_.getValue (i);
			if (term->getKind() == TOP_KIND) {
				return false;
			}
		}
		return true;
	}
	void
	Intersect :: becomePlain()
	{
		vector :: Term plainTerms (32);

		for (value :: Integer i = 0; i < terms_.getSize(); ++ i) {
			const del :: Term* const
				term = terms_.getValue (i);
			if (term->getKind() == INTERSECT_KIND) {
				for (value :: Integer j = 0; j < term->getSize(); ++ j) {
					const del :: Term* const
						subterm = term->getSubterm (j);
					if (!contains (plainTerms, subterm)) {
						plainTerms.add (subterm->clone());
					}
				}
			} else {
				plainTerms.add (term->clone());
			}
		}
		terms_.erase();
		terms_ = plainTerms;
		for (value :: Integer i = 0; i < plainTerms.getCapacity(); ++ i) {
			plainTerms [i] = NULL;
		}
	}
	void
	Intersect :: removeTop()
	{
		const value :: Integer size = terms_.getSize();
		for (value :: Integer i = 0; i < size ; ++ i) {
			const value :: Integer index = size - i - 1;
			const del :: Term* const
				term = terms_.getValue (index);
			if (term->getKind() == TOP_KIND) {
				deleteObject (term);
				terms_.remove (index);
			}
		}
	}
	void
	Intersect :: removeRedundant()
	{
		const value :: Integer size = terms_.getSize();
		value :: Integer c = 0;
		del :: Term* terms [size];

		for (value :: Integer i = 0; i < size; ++ i) {
			del :: Term*& term_1 = const_cast<del :: Term*&>(terms_.getReference (i));
			bool isNewTerm = true;
			for (value :: Integer j = 0; j < c; ++ j) {
				del :: Term* term_2 = terms [j];
				if (term_1->isEqual (term_2)) {
					isNewTerm = false;
					break;
				}
			}
			if (isNewTerm) {
				terms [c ++] = term_1;
			} else {
				term_1->commitSuicide();
			}
			term_1 = NULL;
		}
		clearTerms();
		for (value :: Integer i = 0; i < c; ++ i) {
			const del :: Term* const
				term = terms [i];
			terms_.add (term);
		}
	}
	bool
	Intersect :: contains (const vector :: Term& terms, const del :: Term* term_1) const
	{
		for (value :: Integer k = 0; k < terms.getSize(); ++ k) {
			const del :: Term* const
				term_2 = terms.getValue (k);
			if (term_1->isEqual (term_2)) {
				return true;
			}
		}
		return false;
	}
	void
	Intersect :: clearTerms()
	{
		for (value :: Integer i = 0; i < terms_.getCapacity(); ++ i) {
			terms_.getReference (i) = NULL;
		}
		terms_.clear();
	}
}
}
}

#endif /*DEL_SOURCE_TERM_INTERSECT_CPP_*/
