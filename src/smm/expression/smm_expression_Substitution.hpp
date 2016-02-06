/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_expression_Substitution.hpp                          */
/* Description:     smm substitution                                         */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "smm/expression/smm_expression_Expression.hpp"

namespace smm {
namespace expression {

class Substitution : public Scalar<Substitution> {
private :
	enum { INITIAL_SUBSTITUTION_CAPACITY = 32 };
public :
	Substitution (const Size_t = INITIAL_SUBSTITUTION_CAPACITY);
	~ Substitution();

	void add (const value :: Literal, const Expression* const);

	const Expression* execute (const Expression* const) const;

	void checkDisjointedRestrictions
	(
		const smm :: Assertion* const assertion,
		const smm :: Assertion* const theorem
	) const;

	void clear();

	// object :: Object interface
	void commitSuicide();
	Size_t getVolume() const;
	Size_t getSizeOf() const;
	template<class T>
	void show (T&) const;

private :
	void insertExpression (const index :: Arity) const;

	void checkDisjointedVariablesPair
	(
		const Expression* const exp_1,
		const Expression* const exp_2,
		const smm :: Assertion* const theorem
	) const;
	void checkSingleDisjointedRestriction
	(
		const Expression* const exp_1,
		const Expression* const exp_2,
		const value :: Literal v_1,
		const value :: Literal v_2,
		const smm :: Assertion* const theorem
	) const;
	void throwDisjointedViolationError
	(
		const Expression* const exp_1,
		const Expression* const exp_2,
		const value :: Literal v_1,
		const value :: Literal v_2,
		Error* error
	) const;

	smm :: vector :: Literal variables_;
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

#include "smm/expression/smm_expression_Substitution.ipp"


