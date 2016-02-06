/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_expression_Substitution.hpp                           */
/* Description:     metamath substitution                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "expression/mm_expression_Expression.hpp"

namespace mm {
namespace expression {

class Substitution : public Scalar<Substitution> {
private :
	enum { INITIAL_SUBSTITUTION_CAPACITY = 32 };
public :
	Substitution (const Size_t = INITIAL_SUBSTITUTION_CAPACITY);
	~ Substitution();

	void add (const value :: Literal, const Expression* const);

	const Expression* execute (const Expression* const) const;

	void checkDisjoinedRestrictions
	(
		const mm :: source :: Assertion* const assertion,
		const mm :: source :: Assertion* const theorem
	) const;

	void clear();

	// nstd :: Object interface
	void commitSuicide();
	Size_t getVolume() const;
	Size_t getSizeOf() const;
	template<class T>
	void show (T&) const;

private :
	void insertExpression (const index :: Arity) const;

	void checkDisjoinedVariablesPair
	(
		const Expression* const exp_1,
		const Expression* const exp_2,
		const mm :: source :: Assertion* const theorem
	) const;
	void checkSingleDisjoinedRestriction
	(
		const Expression* const exp_1,
		const Expression* const exp_2,
		const value :: Literal v_1,
		const value :: Literal v_2,
		const mm :: source :: Assertion* const theorem
	) const;
	void throwDisjoinedViolationError
	(
		const Expression* const exp_1,
		const Expression* const exp_2,
		const value :: Literal v_1,
		const value :: Literal v_2,
		Error* error
	) const;

	mm :: vector :: Literal variables_;
	vector :: Expression expressions_;
	mutable Expression result_;
	enum {
		INITIAL_SUBSTITUTION_RESULT = 256
	};
};

	template<class T>
	T&
	operator << (T&, const Substitution&);
	std :: ostream&
	operator << (std :: ostream&, const Substitution&);
}
}

#include "expression/mm_expression_Substitution.ipp"


