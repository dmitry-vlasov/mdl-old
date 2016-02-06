/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_evaluation_term_Sum.cpp                         */
/* Description:     summation evaluation function                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace form {
namespace evaluation {
namespace term {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Sum :: Sum
	(
		const index :: Arity dimension,
		const value :: Real constant,
		Term_* terms[]
	) :
	location_(),
	constant_ (constant),
	termVector_ (terms, dimension) {
	}
	inline
	Sum :: Sum
	(
		const Location& location,
		const value :: Real constant,
		const mdl :: evaluation :: parser :: vector :: Term& termVector,
		mdl :: Theory* theory
	) :
	location_ (location),
	constant_ (constant),
	termVector_ (termVector) {
	}
	Sum :: ~ Sum() {
	}

	void
	Sum :: addTerm (Term_* term) {
		termVector_.add (term);
	}

	// evaluation :: Term implementation
	index :: Arity
	Sum :: getArity() const {
		return termVector_.getSize();
	}
	value :: Real
	Sum :: eval (const HeapNode_* node) const
	{
		value :: Real sum = constant_;
		for (index :: Arity i = 0; i < termVector_.getSize(); ++ i) {
			const Term_*  term = termVector_.getValue (i);
			sum += term->eval (node);
		}
		return sum;
	}
	value :: Real
	Sum :: eval (const value :: Real values[]) const
	{
		value :: Real sum = constant_;
		for (index :: Arity i = 0; i < getArity(); ++ i) {
			sum += values [i];
		}
		return sum;
	}
	Sum :: Term_*
	Sum :: getSubTerm (const index :: Arity i) {
		return termVector_.getValue (i);
	}
	const Sum :: Term_*
	Sum :: getSubTerm (const index :: Arity i) const {
		return termVector_.getValue (i);
	}

	// object :: Buildable implementation
	void
	Sum :: build()
	{
		for (index :: Arity i = 0; i < termVector_.getSize(); ++ i) {
			Term_*  term = termVector_.getValue (i);
			term->build();
		}
	}

	// object :: Writable implementation
	void
	Sum :: replicate (String& string) const
	{
		string << Indent (depth_ + 2);
		string << Token :: sum_ << Token :: openSqBracket_;
		string << constant_ << Token :: closeSqBracket_ << endLine;
		string << Indent (depth_ + 2) << Token :: openBracket_ << endLine;
		for (index :: Arity i = 0; i < termVector_.getSize(); ++ i) {
			const Term_*  term = termVector_.getValue (i);
			term->replicate (string);
			string << endLine;
		}
		string << Indent (depth_ + 2) << Token :: closeBracket_;
	}

	// object :: Object implementation
	void
	Sum :: commitSuicide() {
		delete this;
	}
	Size_t
	Sum :: getVolume() const {
		return termVector_.getVolume();
	}
	Size_t
	Sum :: getSizeOf() const {
		return sizeof (Sum);
	}
}
}
}
}


