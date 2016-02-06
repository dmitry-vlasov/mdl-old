/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File name:       del_math_Signatures.cpp                                  */
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
	Signatures :: Signatures() :
	signatureVector_ (INITIAL_SIGNATURE_VECTOR_CAPACITY) {
	}
	Signatures :: ~ Signatures() {
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	// object :: Object implementation
	void
	Signatures :: commitSuicide() {
		delete this;
	}
	Size_t
	Signatures :: getVolume() const {
		return signatureVector_.getVolume();
	}
	Size_t
	Signatures :: getSizeOf() const {
		return sizeof (Signatures);
	}
	void
	Signatures :: show (String& string) const
	{
		string << tab << "signatures   " << tab << '-';
		string << space << signatureVector_.getSize() << endLine;
	}
}
}


