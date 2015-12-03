/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_term_Variable.cpp                             */
/* Description:     variable term class                                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_SOURCE_TERM_VARIABLE_CPP_
#define DEL_SOURCE_TERM_VARIABLE_CPP_

#include "del/lexer/del_lexer.hpp"

namespace del {
namespace source {
namespace term {

	/****************************
	 *		Public members
	 ****************************/

using manipulator :: endLine;

	inline
	Variable :: Variable (const Symbol symbol) :
	location_ (),
	symbol_ (symbol)
	{
 		if (symbol.isTop()) {
			Error* error = new Error();
			error->message() << "creating a top-valued concept" << endLine;
			throw error;
		}
	}
	inline
	Variable :: Variable (const value :: Variable name, const bool isTemporary) :
	location_ (),
	symbol_ (name, false, false, isTemporary)
	{
		if (name == value :: TOP) {
			Error* error = new Error();
			error->message() << "creating a top-valued concept" << endLine;
			throw error;
		}
	}
	inline
	Variable :: Variable
	(
		const Location& location,
		const value :: Variable name,
		const bool isTemporary
	) :
	location_ (location),
	symbol_ (name, false, false, isTemporary)
	{
		if (name == value :: TOP) {
			Error* error = new Error();
			error->message() << "creating a top-valued concept" << endLine;
			throw error;
		}
	}
	inline
	Variable :: Variable (const Variable& variable) :
	location_ (variable.location_),
	symbol_ (variable.symbol_) {
	}
	Variable :: ~ Variable() {
	}

	// del :: Term implementation
	void
	Variable :: assemble() {
	}
	bool
	Variable :: normalize (del :: Theory*, const del :: Formula*) const {
		return false;
	}
	bool
	Variable :: isOfSignature (const del :: Signature* signature) const {
		return signature->containsSymbol (symbol_);
	}
	bool
	Variable :: contains (const Symbol& symbol) const {
		return (symbol == symbol_);
	}
	void
	Variable :: completeSignature (del :: Signature* signature) const {
		signature->addSymbol (symbol_);
	}
	void
	Variable :: makeDeltaCopy (const del :: Expansion* expansion) {
		symbol_ = expansion->addPostfixToSymbol (symbol_);
	}
	void
	Variable :: makeDeltaCopy (const del :: Signature* delta)
	{
		if (!delta->containsSymbol (symbol_)) {
			symbol_.setAsterisk (true);
		}
	}
	value :: Integer
	Variable :: getSize() const {
		return 0;
	}
	const del :: Symbol&
	Variable :: getSymbol() const {
		return symbol_;
	}
	const del :: Term*
	Variable :: getSubterm (const value :: Integer) const {
		return NULL;
	}
	bool
	Variable :: isEqual (const del :: Term* term) const
	{
		if (term->getKind() != VARIABLE_KIND) {
			return false;
		}
		return (symbol_ == term->getSymbol());
	}
	const del :: Term*
	Variable :: simplify() {
		return this;
	}
	void
	Variable :: replace (const del :: Term*, const del :: Term*) {
	}
	void
	Variable :: replaceSubterm (const value :: Integer, const del :: Term*) {
	}
	void
	Variable :: removeSubterm (const value :: Integer) {
	}
	value :: Integer
	Variable :: getDepth() const {
		return 0;
	}
	value :: Integer
	Variable :: getLength() const {
		return 1;
	}
	bool
	Variable :: isPrimitivized() const {
		return true;
	}
	void
	Variable :: setPrimitivized (const bool) const {
	}
	Symbol
	Variable :: primitivize (const char*) const {
		return symbol_;
	}
	Symbol
	Variable :: getPrimitivization() const {
		return symbol_;
	}
	bool
	Variable :: hasTemporarySymbols() const {
		return symbol_.isTemporary();
	}
	Variable :: Kind
	Variable :: getKind() const {
		return VARIABLE_KIND;
	}
	Symbol
	Variable :: defineSelf (del :: Theory*, const del :: Formula*, const char*, const bool) const {
		return symbol_;
	}

	// del :: Cloneable implementation
	del :: Term*
	Variable :: clone() const {
		return new Variable (*this);
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Writable implementation
	void
	Variable :: translate (String& string) const {
		replicate (string);
	}
	void
	Variable :: replicate (String& string) const {
		string << symbol_;
	}

	// object :: Object implementation
	void
	Variable :: commitSuicide() {
		delete this;
	}
	Size_t
	Variable :: getVolume() const {
		return symbol_.getVolume();
	}
	Size_t
	Variable :: getSizeOf() const {
		return sizeof (Variable);
	}

	/****************************
	 *		Private members
	 ****************************/
}
}
}

#endif /*DEL_SOURCE_TERM_VARIABLE_CPP_*/
