/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_math_Assertions.cpp                                  */
/* Description:     global smm assertions container                          */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "auxiliary/smm_auxiliary.hpp"
#include "math/smm_math.hpp"

namespace smm {
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


