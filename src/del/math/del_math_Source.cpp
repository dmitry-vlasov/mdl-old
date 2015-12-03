/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File name:       del_math_Source.cpp                                      */
/* Description:     global del assertions container                          */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_MATH_SOURCE_CPP_
#define DEL_MATH_SOURCE_CPP_

#include "auxiliary/del_auxiliary.hpp"
#include "math/del_math.hpp"

namespace del {
namespace math {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Source :: Source() :
	source_ (NULL) {
	}
	Source :: ~ Source() {
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	// object :: Object implementation
	void
	Source :: commitSuicide() {
		delete this;
	}
	Size_t
	Source :: getVolume() const {
		return 0;
	}
	Size_t
	Source :: getSizeOf() const {
		return sizeof (Source);
	}
	void
	Source :: show (String& string) const
	{
		string << tab << "source   " << tab << '-';
		string << space << "1" << endLine;
	}
}
}

#endif /*DEL_MATH_SOURCE_CPP_*/
