/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_auxiliary_Timers.cpp                                 */
/* Description:     processing timers class                                  */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "smm/auxiliary/smm_auxiliary.hpp"

namespace smm {
namespace auxiliary {

	/****************************
	 *		Public members
	 ****************************/

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Object implementation
	void
	Timers :: commitSuicide() {
		delete this;
	}
	Size_t
	Timers :: getVolume() const {
		return 0;
	}
	Size_t
	Timers :: getSizeOf() const {
		return sizeof (Timers);
	}
	void
	Timers :: show (String& string) const
	{
		string << "timings:" << endLine;
		if (read_.isUsed()) {
			string << tab << "read:   " << read_ << endLine;
		}
		if (verify_.isUsed()) {
			string << tab << "verify: " << verify_ << endLine;
		}
	}
}
}


