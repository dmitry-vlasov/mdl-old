/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_math_Assertions.cpp                                   */
/* Description:     global metamath assertions container                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_MATH_ASSERTIONS_CPP_
#define MM_MATH_ASSERTIONS_CPP_

#include "auxiliary/mm_auxiliary.hpp"
#include "math/mm_math.hpp"

namespace mm {
namespace math {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Assertions :: Assertions() :
	axiomaticCount_ (0),
	provableCount_ (0),
	assertionVector_(INITIAL_ASSERTION_VECTOR_CAPACITY) {
	}
	Assertions :: ~ Assertions() {
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	// object :: Object implementation
	void
	Assertions :: commitSuicide() {
		delete this;
	}
	Size_t
	Assertions :: getVolume() const {
		return assertionVector_.getVolume();
	}
	Size_t
	Assertions :: getSizeOf() const {
		return sizeof (Assertions);
	}
	void
	Assertions :: show (String& string) const
	{
		string << tab << "axiomatic   " << tab << '-';
		string << space << axiomaticCount_ << endLine;
		string << tab << "provable    " << tab << '-';
		string << space << provableCount_ << endLine;
	}
}
}

#endif /*MM_MATH_ASSERTIONS_CPP_*/
