/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_math_Math.cpp                                         */
/* Description:     static container for global metamath structures          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "math/mm_math.hpp"

namespace mm {
namespace math {

	/****************************
	 *		Public members
	 ****************************/

	void
	Math :: show (std :: ostream& os)
	{
		String string (1024);
		showRaw (string);
		os << string;
	}

using manipulator :: endLine;

	// nstd :: Static implementation
	void
	Math :: initRaw()
	{
		constants_ = new Constants();
		assertions_ = new Assertions();
	}
	void
	Math :: showRaw (String& string)
	{
		if (isInitialized()) {
			string << "math:" << endLine;
			string << *constants_;
			string << *assertions_;
		}
	}
	Size_t
	Math :: getRawVolume()
	{
		Size_t result = 0;
		result += getAggregateVolume (constants_);
		result += getAggregateVolume (assertions_);
		return result;
	}

	/********************************
	 *		Private static attributes
	 ********************************/

	Assertions*
		Math :: assertions_ = NULL;
	Constants*
		Math :: constants_ = NULL;
}
}



