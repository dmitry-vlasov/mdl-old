/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_expression_Expression.hpp                             */
/* Description:     metamath symbolic expression                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "interface/mm_interface.dpp"
#include "expression/mm_expression_Symbol.hpp"

namespace mm {
namespace expression {

class Expression : public Scalar<Expression> {
private :
	enum { INITIAL_EXPRESSION_CAPACITY = 64 };
public :
	Expression (const Size_t = INITIAL_EXPRESSION_CAPACITY);
	Expression (const Expression&);
	Expression
	(
		const Location&,
		const mm :: vector :: Literal&,
		const mm :: source :: Block* const
	);
	~ Expression();

	index :: Literal getSize() const;
	const Symbol& getType () const;
	const Symbol& getSymbol (const index :: Literal) const;
	const Symbol& operator [] (const index :: Literal) const;
	void addSymbol (const Symbol&);

	void copy (const Expression* const);
	void copy (const Symbol, const Symbol);
	bool operator == (const Expression&) const;
	bool operator != (const Expression&) const;
	void operator = (const Expression&);

	void collectVariables (mm :: vector :: Literal&) const;

	bool isStatement() const;
	bool isTerm() const;
	bool isTrivial() const;

	void write (String&) const;
	void writeType (String&) const;
	void writeBody (String&) const;

	void init();
	void clear();

	// nstd :: Object interface
	void commitSuicide();
	Size_t getSizeOf() const;
	Size_t getVolume() const;
	void show (String&) const;

private :
	vector :: Symbol expression_;
};

	template<class T>
	T&
	operator << (T&, const Expression&);

namespace vector {

	typedef
		Vector
		<
			expression :: Expression,
			storage :: ByPointer,
			allocator :: Heap
		>
		Expression;
}
}
}

#include "expression/mm_expression_Expression.ipp"


