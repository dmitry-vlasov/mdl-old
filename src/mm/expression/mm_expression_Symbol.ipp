/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_expression_Symbol.ipp                                 */
/* Description:     metamath symbol                                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_EXPRESSION_SYMBOL_IPP_
#define MM_EXPRESSION_SYMBOL_IPP_

#include "auxiliary/mm_auxiliary.hpp"

namespace mm {
namespace expression {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Symbol :: Symbol() :
	literal_ (value :: undefined :: LITERAL),
	isVariable_ (false) {
	}
	inline
	Symbol :: Symbol
	(
		const value :: Literal literal,
		const bool isVariable
	) :
	literal_ (literal),
	isVariable_ (isVariable) {
	}
	Symbol :: ~ Symbol() {
	}

	inline value :: Literal
	Symbol :: getLiteral() const {
		return literal_;
	}
	inline bool
	Symbol :: isVariable() const {
		return isVariable_;
	}
	inline bool
	Symbol :: isConstant() const {
		return !isVariable_;
	}

	inline bool
	Symbol :: operator == (const Symbol& symbol) const {
		return
			(literal_ == symbol.literal_) &&
			(isVariable_ == symbol.isVariable_);
	}
	inline bool
	Symbol :: operator != (const Symbol& symbol) const {
		return !(operator == (symbol));
	}
	inline void
	Symbol :: operator = (const Symbol& symbol) {
		literal_ = symbol.literal_;
		isVariable_ = symbol.isVariable_;
	}

	inline void
	Symbol :: setLiteral (const value :: Literal literal) {
		literal_ = literal;
	}
	inline void
	Symbol :: setVariable (const bool isVariable) {
		isVariable_ = isVariable;
	}

using manipulator :: space;

	template<class T>
	inline void
	Symbol :: write (T& string) const
	{
		if (Config :: useSymbolCorrection()) {
			const String* symbol = Table :: literals()->getUnicode (literal_);
			if (symbol != NULL) {
				string << *symbol << space;
				return;
			}
		}
		string << Table :: literals()->get (literal_) << space;
	}

	// object :: Object implementation
	inline void
	Symbol :: commitSuicide() {
		delete this;
	}
	inline Size_t
	Symbol :: getSizeOf() const {
		return sizeof (Symbol);
	}
	inline Size_t
	Symbol :: getVolume() const {
		return 0;
	}
	template<class S>
	inline void
	Symbol :: show (S& string) const {
		string << Table :: literals()->get (literal_) << space;
	}

	/*******************************
	 *		Overloaded operators
	 *******************************/

	template<class T>
	inline T&
	operator << (T& string, const Symbol& symbol) {
		symbol.write (string);
		return string;
	}
	std :: ostream&
	operator << (std :: ostream& os, const Symbol& symbol)
	{
		enum {
			INITIAL_STRING_CAPACITY = 32
		};
		String string (INITIAL_STRING_CAPACITY);
		symbol.write (string);
		os << string;
		return os;
	}
}
}

#endif /* MM_EXPRESSION_SYMBOL_IPP_ */
