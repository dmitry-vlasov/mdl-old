/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_expression_Substitution.ipp                           */
/* Description:     metamath substitution                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mm {
namespace expression {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Substitution :: Substitution (const Size_t initialCapacity) :
	variables_ (initialCapacity),
	expressions_ (initialCapacity),
	result_ (INITIAL_SUBSTITUTION_RESULT) {
	}
	Substitution :: ~ Substitution() {
	}

	inline void
	Substitution :: add
	(
		const value :: Literal variable,
		const Expression* const expression
	)
	{
		variables_.add (variable);
		*(expressions_.push()) = *expression;
	}

	inline void
	Substitution :: clear()
	{
		variables_.clear();
		expressions_.clear();
		result_.clear();
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	// object :: Object implementation
	inline void
	Substitution :: commitSuicide() {
		delete this;
	}
	inline Size_t
	Substitution :: getVolume() const
	{
		Size_t volume = 0;
		volume += variables_.getVolume();
		volume += expressions_.getVolume();
		volume += result_.getVolume();
		return volume;
	}
	inline Size_t
	Substitution :: getSizeOf() const {
		return sizeof (Substitution);
	}
	template<class T>
	void
	Substitution :: show (T& string) const
	{
		for (index :: Arity i = 0; i < variables_.getSize(); i ++) {
			string << tab << Table :: literals()->get (variables_ [i]);
			string << space << '/' << space;
			string << *(expressions_ [i]) << endLine;
		}
	}

	/****************************
	 *		Operators
	 ****************************/

	template<class T>
	inline T&
	operator << (T& s, const Substitution& substitution)
	{
		substitution.show (s);
		return s;
	}

	std :: ostream&
	operator << (std :: ostream& os, const Substitution& substitution)
	{
		enum {
			INITIAL_STRING_CAPACITY = 256 //1024
		};
		String string (INITIAL_STRING_CAPACITY);
		substitution.show (string);
		os << string;
		return os;
	}
}
}


