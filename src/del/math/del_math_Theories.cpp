/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File name:       del_math_Theories.cpp                                    */
/* Description:     global del assertions container                          */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "auxiliary/del_auxiliary.hpp"
#include "math/del_math.hpp"

namespace del {
namespace math {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Theories :: Theories() :
	theoryVector_ (INITIAL_THEORY_VECTOR_CAPACITY) {
	}
	Theories :: ~ Theories() {
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	// object :: Object implementation
	void
	Theories :: commitSuicide() {
		delete this;
	}
	Size_t
	Theories :: getVolume() const {
		return theoryVector_.getVolume();
	}
	Size_t
	Theories :: getSizeOf() const {
		return sizeof (Theories);
	}
	void
	Theories :: show (String& string) const
	{
		string << tab << "theories   " << tab << '-';
		string << space << theoryVector_.getSize() << endLine;
	}
}
}


