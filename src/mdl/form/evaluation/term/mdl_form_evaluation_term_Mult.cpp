/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_evaluation_term_Mult.cpp                        */
/* Description:     multiplication evaluation function                       */
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
	Mult :: Mult (const value :: Real constant) :
	location_ (),
	constant_ (constant),
	termVector_ (INITIAL_TERM_VECTOR_CAPACITY) {
	}
	inline
	Mult :: Mult
	(
		Term_* term,
		const value :: Real constant
	) :
	location_ (),
	constant_ (constant),
	termVector_ (INITIAL_TERM_VECTOR_CAPACITY) {
		termVector_.add (term);
	}
	inline
	Mult :: Mult
	(
		Term_* term_1,
		Term_* term_2,
		const value :: Real constant
	) :
	location_ (),
	constant_ (constant),
	termVector_ (INITIAL_TERM_VECTOR_CAPACITY)
	{
		termVector_.add (term_1);
		termVector_.add (term_2);
	}
	inline
	Mult :: Mult
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
	Mult :: ~ Mult() {
	}

	void
	Mult :: addTerm (Term_* term) {
		termVector_.add (term);
	}

	// evaluation :: Term implementation
	index :: Arity
	Mult :: getArity() const {
		return termVector_.getSize();
	}
	value :: Real
	Mult :: eval (const HeapNode_* node) const
	{
		value :: Real mult = constant_;
		for (index :: Arity i = 0; i < termVector_.getSize(); ++ i) {
			const Term_*  term = termVector_.getValue (i);
			mult *= term->eval (node);
		}
		return mult;
	}
	value :: Real
	Mult :: eval (const value :: Real values[]) const
	{
		value :: Real mult = constant_;
		for (index :: Arity i = 0; i < getArity(); ++ i) {
			mult *= values [i];
		}
		return mult;
	}
	Mult :: Term_*
	Mult :: getSubTerm (const index :: Arity i) {
		return termVector_.getValue (i);
	}
	const Mult :: Term_*
	Mult :: getSubTerm (const index :: Arity i) const {
		return termVector_.getValue (i);
	}

	// object :: Buildable implementation
	void
	Mult :: build()
	{
		for (index :: Arity i = 0; i < termVector_.getSize(); ++ i) {
			Term_*  term = termVector_.getValue (i);
			term->build();
		}
	}

using manipulator :: endLine;

	// object :: Writable implementation
	void
	Mult :: replicate (String& string) const
	{
		string << Indent (depth_ + 2) << Token :: mult_ << Token :: openSqBracket_;
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
	Mult :: commitSuicide() {
		delete this;
	}
	Size_t
	Mult :: getVolume() const {
		return termVector_.getVolume();
	}
	Size_t
	Mult :: getSizeOf() const {
		return sizeof (Mult);
	}
}
}
}
}


