/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_term_Top.cpp                                  */
/* Description:     top term class                                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_SOURCE_TERM_TOP_CPP_
#define DEL_SOURCE_TERM_TOP_CPP_

#include "del/lexer/del_lexer.hpp"

namespace del {
namespace source {
namespace term {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Top :: Top () :
	location_ () {
	}
	inline
	Top :: Top (const Location& location) :
	location_ (location) {
	}
	inline
	Top :: Top (const Top& top) :
	location_ (top.location_) {
	}
	Top :: ~ Top() {
	}

	// del :: Term implementation
	void
	Top :: assemble() {
	}
	bool
	Top :: normalize (del :: Theory*, const del :: Formula*) const {
		return false;
	}
	bool
	Top :: isOfSignature (const del :: Signature*) const {
		return true;
	}
	bool
	Top :: contains (const Symbol&) const {
		return false;
	}
	void
	Top :: completeSignature (del :: Signature*) const {
	}
	void
	Top :: makeDeltaCopy (const del :: Expansion*) {
	}
	void
	Top :: makeDeltaCopy (const del :: Signature*) {
	}
	value :: Integer
	Top :: getSize() const {
		return 0;
	}
	const del :: Symbol&
	Top :: getSymbol() const {
		return symbol_;
	}
	const del :: Term*
	Top :: getSubterm (const value :: Integer) const {
		return NULL;
	}
	bool
	Top :: isEqual (const del :: Term* term) const {
		return (term->getKind() == TOP_KIND);
	}
	const del :: Term*
	Top :: simplify() {
		return this;
	}
	void
	Top :: replace (const del :: Term*, const del :: Term*) {
	}
	void
	Top :: replaceSubterm (const value :: Integer, const del :: Term*) {
	}
	void
	Top :: removeSubterm (const value :: Integer) {
	}
	value :: Integer
	Top :: getDepth() const {
		return 0;
	}
	value :: Integer
	Top :: getLength() const {
		return 1;
	}
	bool
	Top :: isPrimitivized() const {
		return true;
	}
	void
	Top :: setPrimitivized (const bool) const {
	}
	Symbol
	Top :: primitivize (const char*) const {
		return Symbol (value :: TOP, false, false, false);
	}
	Symbol
	Top :: getPrimitivization() const {
		return Symbol (value :: TOP, false, false, false);
	}
	bool
	Top :: hasTemporarySymbols() const {
		return false;
	}
	Top :: Kind
	Top :: getKind() const {
		return TOP_KIND;
	}
	Symbol
	Top :: defineSelf (del :: Theory*, const del :: Formula*, const char*, const bool) const {
		return Symbol (value :: TOP, false, false, false);
	}

	// del :: Cloneable implementation
	del :: Term*
	Top :: clone() const {
		return new Top (*this);
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Writable implementation
	void
	Top :: translate (String& string) const {
		replicate (string);
	}
	void
	Top :: replicate (String& string) const
	{
		switch (Config :: outputFormat()) {
		case Config :: DEL_FORMAT :
			string << Token :: top_; break;
		case Config :: MAN_FORMAT :
			string << owl :: man :: Token :: thing_; break;
		case Config :: FUNC_FORMAT :
			//string << "<#" << owl :: func :: Token :: owlThing_ << ">"; break;
			string << owl :: func :: Token :: owlThing_; break;
		default : break;
		}
	}

	// object :: Object implementation
	void
	Top :: commitSuicide() {
		delete this;
	}
	Size_t
	Top :: getVolume() const {
		return 0;
	}
	Size_t
	Top :: getSizeOf() const {
		return sizeof (Top);
	}

	/*********************************
	 *		Private static members
	 *********************************/

	del :: Symbol Top :: symbol_ (value :: TOP, false);
}
}
}

#endif /*DEL_SOURCE_TERM_TOP_CPP_*/
