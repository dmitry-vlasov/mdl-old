/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_expression_Symbol.hpp                                 */
/* Description:     metamath symbol                                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "expression/mm_expression.dpp"

namespace mm {
namespace expression {

class Symbol : public Scalar<Symbol> {
public :
	Symbol();
	Symbol (const value :: Literal, const bool = false);
	~ Symbol();

	value :: Literal getLiteral() const;
	bool isVariable() const;
	bool isConstant() const;

	bool operator == (const Symbol&) const;
	bool operator != (const Symbol&) const;
	void operator = (const Symbol&);

	void setLiteral (const value :: Literal);
	void setVariable (const bool = true);

	template<class T>
	void write (T&) const;

	// nstd :: Object interface
	void commitSuicide();
	Size_t getSizeOf() const;
	Size_t getVolume() const;
	template<class S>
	void show (S&) const;

private :
	value :: Literal  literal_;
	bool isVariable_;
};

	template<class T>
	T&
	operator << (T&, const Symbol&);
	std :: ostream&
	operator << (std :: ostream&, const Symbol&);

namespace vector {

	typedef
		Vector <expression :: Symbol, storage :: ByValue, allocator :: Heap>
		Symbol;
}
}
}

#include "expression/mm_expression_Symbol.ipp"


