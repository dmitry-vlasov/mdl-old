/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_interface_Symbol.cpp                                 */
/* Description:     signature class                                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/interface/del_interface.hpp"
#include "del/lexer/del_lexer_Token.hpp"
#include "del/auxiliary/del_auxiliary.hpp"

namespace del {
namespace interface {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Symbol :: Symbol() :
	value_ (value :: undefined :: SYMBOL),
	isRelation_ (false),
	isAsterisk_ (false),
	isTemporary_ (false) {
	}
	inline
	Symbol :: Symbol
	(
		const value :: Symbol name,
		const bool isRelation,
		const bool isAsterisk,
		const bool isTemporary
	) :
	value_ (name),
	isRelation_ (isRelation),
	isAsterisk_ (isAsterisk),
	isTemporary_ (isTemporary) {
	}
	inline
	Symbol :: Symbol (const Symbol& symbol) :
	value_ (symbol.value_),
	isRelation_ (symbol.isRelation_),
	isAsterisk_ (symbol.isAsterisk_),
	isTemporary_ (symbol.isTemporary_) {
	}

	Symbol :: ~ Symbol() {
	}

	inline void
	Symbol :: operator = (const Symbol& symbol)
	{
		value_ = symbol.value_;
		isRelation_ = symbol.isRelation_;
		isAsterisk_ = symbol.isAsterisk_;
		isTemporary_ = symbol.isTemporary_;
	}

	const String&
	Symbol :: getString() const
	{
		if (isRelation_) {
			return Table :: relations()->get (value_);
		} else {
			return Table :: variables()->get (value_);
		}
	}

using manipulator :: endLine;

	// del :: Symbol interface
	value :: Variable
	Symbol :: getVariable() const
	{
		if (isRelation()) {
			Error* error = new Error (Error :: SEMANTIC);
			error->message() << "illegal concept name request: relation" << endLine;
			throw error;
		}
		return value_;
	}
	value :: Relation
	Symbol :: getRelation() const
	{
		if (isVariable()) {
			Error* error = new Error (Error :: SEMANTIC);
			error->message() << "illegal relation name request: variable" << endLine;
			throw error;
		}
		return value_;
	}
	inline value :: Symbol
	Symbol :: getValue() const {
		return value_;
	}
	inline bool
	Symbol :: isVariable() const {
		return !isRelation_;
	}
	inline bool
	Symbol :: isRelation() const {
		return isRelation_;
	}
	inline bool
	Symbol :: isAsterisk() const {
		return isAsterisk_;
	}
	inline bool
	Symbol :: isTemporary() const {
		return isTemporary_;
	}
	inline bool
	Symbol :: isTop() const {
		return (value_== value :: TOP) && !isRelation_;
	}
	inline bool
	Symbol :: isUndefined() const
	{
		if (isRelation_) {
			return (value_== value :: undefined :: RELATION);
		} else {
			return (value_== value :: undefined :: VARIABLE);
		}
	}
	inline bool
	Symbol :: isDefined() const {
		return !isUndefined();
	}

	inline void
	Symbol :: undefine()
	{
		if (isRelation_) {
			value_= value :: undefined :: RELATION;
		} else {
			value_= value :: undefined :: VARIABLE;
		}
	}
	inline void
	Symbol :: setAsterisk (const bool isAsterisk) {
		isAsterisk_ = isAsterisk;
	}

	// Writable interface
	void
	Symbol :: translate (String& string) const
	{
		if (Config :: outputFormat() == Config :: FUNC_FORMAT) {
			writeFuncFormat (string);
			return;
		}
		if (isTemporary_) {
			string << chars :: TEMPORARY_PREFIX;
		}
		if (isRelation_) {
			if (value_ != value :: undefined :: RELATION) {
				string << Table :: relations()->get (value_);
			} else {
				string << "<undef>";
			}
		} else {
			if (value_ == value :: TOP) {
				string << Token :: top_;
			} else if (value_ != value :: undefined :: VARIABLE) {
				string << Table :: variables()->get (value_);
			} else {
				string << "<undef>";
			}
		}
		if (isAsterisk_) {
			string << chars :: DELTA_POSTFIX;
		}
	}
	inline void
	Symbol :: replicate (String& string) const {
		translate (string);
	}

	// Object interface
	inline void
	Symbol :: show (String& string) const {
		replicate (string);
	}
	inline void
	Symbol :: show (std :: ostream& os) const
	{
		if (isTemporary_) {
			os << chars :: TEMPORARY_PREFIX;
		}
		if (isRelation_) {
			if (value_ != value :: undefined :: RELATION) {
				os << Table :: relations()->get (value_);
			} else {
				os << "<undef>";
			}
		} else {
			if (value_ == value :: TOP) {
				os << Token :: top_;
			} else if (value_ != value :: undefined :: VARIABLE) {
				os << Table :: variables()->get (value_);
			} else {
				os << "<undef>";
			}
		}
		if (isAsterisk_) {
			os << chars :: DELTA_POSTFIX;
		}
	}
	Size_t
	Symbol :: getVolume() const {
		return 0;
	}
	Size_t
	Symbol :: getSizeOf() const {
		return sizeof (Symbol);
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Symbol :: writeFuncFormat (String& string) const
	{
		if (isRelation_) {
			if (value_ != value :: undefined :: RELATION) {
				writeFuncSymbolString (string, Table :: relations()->get (value_));
			} else {
				if (ENCLOSE_SYMBOL_IN_FUNC_FORMAT) {
					string << "<#undef>";
				} else {
					string << "undef";
				}
			}
		} else {
			if (value_ == value :: TOP) {
				if (ENCLOSE_SYMBOL_IN_FUNC_FORMAT) {
					string << "<#" << del :: owl :: func :: Token :: owlThing_ << ">";
				} else {
					string << del :: owl :: func :: Token :: owlThing_;
				}
			} else if (value_ != value :: undefined :: VARIABLE) {
				writeFuncSymbolString (string, Table :: variables()->get (value_));
			} else {
				if (ENCLOSE_SYMBOL_IN_FUNC_FORMAT) {
					string << "<#undef>";
				} else {
					string << "undef";
				}
			}
		}
	}
	void
	Symbol :: writeFuncSymbolString (String& string, const String& symbol) const
	{
		if (ENCLOSE_SYMBOL_IN_FUNC_FORMAT && (symbol.getFirstValue() != '<')) {
			string << "<#";
		}
		string << symbol;
		if (ENCLOSE_SYMBOL_IN_FUNC_FORMAT && (symbol.getFirstValue() != '<')) {
			string << ">";
		}
	}

	/****************************
	 *		Operators
	 ****************************/

	bool
	operator == (const Symbol& symbol_1, const Symbol& symbol_2)
	{
		return
			(symbol_1.getValue() == symbol_2.getValue()) &&
			(symbol_1.isRelation() == symbol_2.isRelation()) &&
			(symbol_1.isAsterisk() == symbol_2.isAsterisk());
	}
	inline bool
	operator != (const Symbol& symbol_1, const Symbol& symbol_2) {
		return !operator == (symbol_1, symbol_2);
	}
	bool
	operator < (const Symbol& symbol_1, const Symbol& symbol_2)
	{
		return
			(symbol_1.isRelation() && symbol_2.isVariable()) ||
			(
				(symbol_1.isRelation() && symbol_2.isRelation()) &&
				(
					(!symbol_1.isAsterisk() && symbol_2.isAsterisk()) ||
					(
						(symbol_1.isAsterisk() == symbol_2.isAsterisk()) &&
						(symbol_1.getValue() < symbol_2.getValue())
					)
				)
			) ||
			(
				(symbol_1.isVariable() && symbol_2.isVariable()) &&
				(
					(!symbol_1.isAsterisk() && symbol_2.isAsterisk()) ||
					(
						(symbol_1.isAsterisk() == symbol_2.isAsterisk()) &&
						(symbol_1.getValue() < symbol_2.getValue())
					)
				)
			);
	}
	inline bool
	operator > (const Symbol& symbol_1, const Symbol& symbol_2) {
		return operator < (symbol_2, symbol_1);
	}
	inline bool
	operator <= (const Symbol& symbol_1, const Symbol& symbol_2) {
		return operator < (symbol_1, symbol_2) || (symbol_1 == symbol_2);
	}
	inline bool
	operator >= (const Symbol& symbol_1, const Symbol& symbol_2) {
		return operator > (symbol_1, symbol_2) || (symbol_1 == symbol_2);
	}

	String&
	operator << (String& string, const Symbol& symbol)
	{
		symbol.show (string);
		return string;
	}
	std :: ostream&
	operator << (std :: ostream& os, const Symbol& symbol)
	{
		symbol.show (os);
		return os;
	}
}
}


