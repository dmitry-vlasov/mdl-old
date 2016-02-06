/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_evaluation_function_WeightedSum.hpp             */
/* Description:     weighted sum evaluation function for proposition         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/form/evaluation/function/mdl_form_evaluation_function_Function.hpp"

namespace mdl {
namespace form {
namespace evaluation {
namespace function {

class WeightedSum :
	public Function,
	public Scalar<WeightedSum> {
public :
	typedef
		mdl :: evaluation :: Term
		Term_;
	typedef
		Term_ :: HeapNode_
		HeapNode_;
	typedef
		parameter :: vector :: Description
		DescriptionVector_;
	typedef
		parameter :: Description
		Description_;

	enum {
		LEXP        = 0,
		EXP_BARRIER = 1,
		EXP_CPLX    = 2,
		EXP_SIM     = 3,
		EXP_EQ      = 4,
		PARAMETER_VECTOR_DIMENSION = 5
	};

	WeightedSum
	(
		const index :: Arity index,
		const mdl :: Proposition*,
		mdl :: Evaluation*
	);
	WeightedSum
	(
		const Location&,
		const index :: Arity index,
		Term_* term,
		mdl :: Theory*
	);
	virtual ~ WeightedSum();

	form :: evaluation :: term :: WeightedSum* weightedSum();
	static DescriptionVector_* descriptionVector();

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	typedef
		parameter :: Triple
		Triple_;

	void initTerms();
	static void initDescriptions();

	form :: evaluation :: term :: WeightedSum* weightedSum_;

	static DescriptionVector_* descriptionVector_;
	static bool volumeCounted_;
};

}
}
}
}


