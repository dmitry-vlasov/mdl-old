/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_expression_Expression.hpp                            */
/* Description:     smm symbolic expression                                  */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "smm/interface/smm_interface.dpp"
#include "smm/expression/smm_expression_Symbol.hpp"

namespace smm {
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
		const smm :: vector :: Literal&
	);
	~ Expression();

	index :: Literal getSize() const;
	const Symbol& getType () const;
	const Symbol& getVariable () const;
	const Symbol& getSymbol (const index :: Literal) const;
	const Symbol& operator [] (const index :: Literal) const;
	void addSymbol (const Symbol&);
	bool contains (const value :: Literal) const;

	void copy (const Expression* const);
	void copy (const Symbol, const Symbol);
	bool operator == (const Expression&) const;
	bool operator != (const Expression&) const;
	void operator = (const Expression&);

	void init();
	void clear();

	// object :: Object interface
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

#include "expression/smm_expression_Expression.ipp"


