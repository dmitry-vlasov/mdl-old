/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_term_Exists.cpp                               */
/* Description:     exists term class                                        */
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
	Exists :: Exists
	(
		const Location& location,
		const value :: Relation relation,
		const vector :: Term& terms
	) :
	term :: Term (location, terms),
	symbol_ (relation, true) {
	}
	inline
	Exists :: Exists
	(
		const Location& location,
		const value :: Relation relation,
		const del :: Term* term
	) :
	term :: Term (location, term),
	symbol_ (relation, true) {
	}
	inline
	Exists :: Exists
	(
		const value :: Relation relation,
		const del :: Term* term
	) :
	term :: Term (term),
	symbol_ (relation, true) {
	}
	inline
	Exists :: Exists
	(
		const del :: Symbol symbol,
		const del :: Term* term
	) :
	term :: Term (term),
	symbol_ (symbol) {
	}
	inline
	Exists :: Exists (const Exists& exists) :
	term :: Term (exists),
	symbol_ (exists.symbol_) {
	}
	Exists :: ~ Exists() {
	}

using manipulator :: endLine;

	// del :: Term implementation
	bool
	Exists :: isOfSignature (const del :: Signature* signature) const
	{
		return
			Term :: isOfSignature (signature) &&
			signature->containsSymbol (symbol_);
	}
	bool
	Exists :: contains (const Symbol& symbol) const
	{
		if (symbol.isRelation() && (symbol_ == symbol)) {
			return true;
		}
		return Term :: contains (symbol);
	}
	void
	Exists :: completeSignature (del :: Signature* signature) const
	{
		signature->addSymbol (symbol_);
		Term :: completeSignature (signature);
	}
	void
	Exists :: makeDeltaCopy (const del :: Expansion* expansion)
	{
		symbol_ = expansion->addPostfixToSymbol (symbol_);
		Term :: makeDeltaCopy (expansion);
	}
	void
	Exists :: makeDeltaCopy (const del :: Signature* delta)
	{
		if (!delta->containsSymbol (symbol_)) {
			symbol_.setAsterisk (true);
		}
		Term :: makeDeltaCopy (delta);
	}
	const del :: Symbol&
	Exists :: getSymbol() const {
		return symbol_;
	}
	bool
	Exists :: isEqual (const del :: Term* term) const
	{
		if (term->getKind() != EXISTS_KIND) {
			return false;
		}
		const Exists* const
			exists = dynamic_cast<const Exists*>(term);
		if (symbol_ != exists->symbol_) {
			return false;
		}
		return term :: Term :: isEqual (term);
	}
	const del :: Term*
	Exists :: simplify()
	{
		term :: Term :: simplify();
		return this;
	}
	void
	Exists :: replace (const del :: Term* oldTerm, const del :: Term* newTerm) {
		term :: Term :: replace (oldTerm, newTerm);
	}
	value :: Integer
	Exists :: getDepth() const {
		return Term :: getDepth() + 1;
	}
	value :: Integer
	Exists :: getLength() const {
		return Term :: getLength() + 2;
	}

	Symbol
	Exists :: primitivize (const char* suffix) const
	{
		if (primitivization_.isDefined()) {
			return primitivization_;
		}
		value :: Variable var = value :: undefined :: VARIABLE;
		if (Config :: keepTermNames()) {
			const Symbol
				symbolForSubterm = getSubterm()->primitivize (suffix);
			String string (256);
			string << Token :: exists_;
			string << symbol_;
			string << Token :: dot_ << '_';
			string << symbolForSubterm;
			var = Table :: variables()->add (string);
		} else {
			var = Table :: variables()->fresh (suffix);
		}
		primitivization_ = Symbol (var, false, false, true);
		return primitivization_;
	}
	bool
	Exists :: hasTemporarySymbols() const
	{
		return
			symbol_.isTemporary() ?
			true :
			Term :: hasTemporarySymbols();
	}
	Exists :: Kind
	Exists :: getKind() const {
		return EXISTS_KIND;
	}

	// del :: Cloneable implementation
	del :: Term*
	Exists :: clone() const {
		return new Exists (*this);
	}

using manipulator :: space;
using manipulator :: tab;

	// object :: Writable implementation
	void
	Exists :: translate (String& string) const {
		replicate (string);
	}
	void
	Exists :: replicate (String& string) const
	{
		switch (Config :: outputFormat()) {
		case Config :: DEL_FORMAT : {
			string << Token :: exists_;
			string << symbol_;
			string << Token :: dot_;
			const del :: Term* const
				term = getSubterm();
			term->replicate (string);
			break;
		}
		case Config :: MAN_FORMAT : {
			string << owl :: man :: Token :: openBracket_;
			string << symbol_;
			string << space << owl :: man :: Token :: some_ << space;
			const del :: Term* const
				term = getSubterm();
			term->replicate (string);
			string << owl :: man :: Token :: closeBracket_;
			break;
		}
		case Config :: FUNC_FORMAT : {
			string << owl :: func :: Token :: objectSomeValuesFrom_;
			string << owl :: func :: Token :: openBracket_;
			string << symbol_;
			string << space;
			const del :: Term* const
				term = getSubterm();
			term->replicate (string);
			string << owl :: func :: Token :: closeBracket_;
			break;
		}
		default : break;
		}
	}

	// object :: Object implementation
	void
	Exists :: commitSuicide() {
		delete this;
	}
	Size_t
	Exists :: getVolume() const
	{
		Size_t volume = 0;
		volume += term :: Term :: getVolume();
		volume += symbol_.getVolume();
		return volume;
	}
	Size_t
	Exists :: getSizeOf() const {
		return sizeof (Exists);
	}

	/****************************
	 *		Private members
	 ****************************/
}
}
}


