/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_math_Constants.cpp                                   */
/* Description:     global smm constants container                           */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "smm/auxiliary/smm_auxiliary.hpp"
#include "smm/math/smm_math.hpp"

namespace smm {
namespace math {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Constants :: Constants() :
	constantSet_ (INITIAL_CONSTANTS_CAPACITY),
	constantCount_ (0) {
	}
	Constants :: ~ Constants() {
	}

	void
	Constants :: add (const smm :: Constants* const constants)
	{
		constants->addTo (constantSet_);
		++ constantCount_;
	}
	bool
	Constants :: contain (const value :: Literal symb)
	{
		const index :: Literal
			index = constantSet_.find (symb);
		return (index != index :: undefined :: LITERAL);
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	// object :: Object implementation
	void
	Constants :: commitSuicide() {
		delete this;
	}
	Size_t
	Constants :: getVolume() const {
		return constantSet_.getVolume();
	}
	Size_t
	Constants :: getSizeOf() const {
		return sizeof (Constants);
	}
	void
	Constants :: show (String& string) const
	{
		string << tab << "constants   " << tab;
		string << '-' << space << constantCount_ << endLine;
	}
}
}


