/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_auxiliary_Timers.cpp                                  */
/* Description:     processing timers class                                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "auxiliary/mm_auxiliary.hpp"

namespace mm {
namespace auxiliary {

	/****************************
	 *		Public members
	 ****************************/

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Object interface'
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
			string << tab << "read:      " << read_ << endLine;
		}
		if (check_.isUsed()) {
			string << tab << "check:     " << check_ << endLine;
		}
		if (translate_.isUsed()) {
			string << tab << "translate: " << translate_ << endLine;
		}
		if (write_.isUsed()) {
			string << tab << "write:     " << write_ << endLine;
		}
	}
}
}


