/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_evaluation_term_Barrier.cpp                     */
/* Description:     barrier function                                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_EVALUATION_TERM_BARRIER_CPP_
#define MDL_FORM_EVALUATION_TERM_BARRIER_CPP_

#include <math.h>

namespace mdl {
namespace form {
namespace evaluation {
namespace term {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Barrier :: Barrier (Term_* termA, Term_* termB, Term_* termX) :
	location_ (),
	termA_ (termA),
	termB_ (termB),
	termX_ (termX) {
	}
	inline
	Barrier :: Barrier
	(
		const Location& location,
		const vector :: value :: Real& parameters,
		const mdl :: evaluation :: parser :: vector :: Term& termVector,
		mdl :: Theory* theory
	) :
	location_ (location),
	termA_ (termVector [0]),
	termB_ (termVector [1]),
	termX_ (termVector [2]) {
	}
	Barrier :: ~ Barrier()
	{
		deleteAggregateObject (termA_);
		deleteAggregateObject (termB_);
		deleteAggregateObject (termX_);
	}

	// evaluation :: Term implementation
	index :: Arity
	Barrier :: getArity() const {
		return 3;
	}
	value :: Real
	Barrier :: eval (const HeapNode_* node) const
	{
		const value :: Real a = termA_->eval (node);
		const value :: Real b = termB_->eval (node);
		const value :: Real x = termX_->eval (node);
		if (x < a + b) {
			return 0;
		} else {
			return 1 - exp ((x - (a + b))/b);
		}
	}
	value :: Real
	Barrier :: eval (const value :: Real values[]) const
	{
		const value :: Real a = values [0];
		const value :: Real b = values [1];
		const value :: Real x = values [2];
		if (x < a + b) {
			return 0;
		} else {
			return 1 - exp ((x - (a + b))/b);
		}
	}
	Barrier :: Term_*
	Barrier :: getSubTerm (const index :: Arity i)
	{
		switch (i) {
		case 0  : return termA_;
		case 1  : return termB_;
		case 2  : return termX_;
		default : return NULL;
		}
	}
	const Barrier :: Term_*
	Barrier :: getSubTerm (const index :: Arity i) const
	{
		switch (i) {
		case 0  : return termA_;
		case 1  : return termB_;
		case 2  : return termX_;
		default : return NULL;
		}
	}

	// object :: Buildable implementation
	void
	Barrier :: build()
	{
		termA_->build();
		termB_->build();
		termX_->build();
	}

using manipulator :: endLine;
using manipulator :: space;

	// object :: Writable implementation
	void
	Barrier :: replicate (String& string) const
	{
		/*
		 *                    /
		 *                    |  0,   x < a + b
		 * barrier(a, b, x) = <
		 *                    |  1 - exp ((x - (a + b))/b)
		 *                    \
		 */
		string << Indent (depth_ + 2) << Token :: barrier_;
		string << endLine;
		string << Indent (depth_ + 2) << Token :: openBracket_ << endLine;
		termA_->replicate (string);
		string << endLine;
		termB_->replicate (string);
		string << endLine;
		termX_->replicate (string);
		string << endLine;
		string << Indent (depth_ + 2) << Token :: closeBracket_;
	}

	// object :: Object implementation
	void
	Barrier :: commitSuicide() {
		delete this;
	}
	Size_t
	Barrier :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (termA_);
		volume += getAggregateVolume (termB_);
		volume += getAggregateVolume (termX_);
		return volume;
	}
	Size_t
	Barrier :: getSizeOf() const {
		return sizeof (Barrier);
	}
}
}
}
}

#endif /*MDL_FORM_EVALUATION_TERM_BARRIER_CPP_*/
