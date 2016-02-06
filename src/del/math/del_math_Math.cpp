/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File name:       del_math_Math.cpp                                        */
/* Description:     static container for global del structures               */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/math/del_math.hpp"

namespace del {
namespace math {

	/****************************
	 *		Public members
	 ****************************/

using manipulator :: endLine;

	// nstd :: Static implementation
	void
	Math :: initRaw()
	{
		theories_ = new Theories();
		signatures_ = new Signatures();
		source_ = new Source();
	}
	void
	Math :: showRaw (String& string)
	{
		if (isInitialized()) {
			string << "math:" << endLine;
			string << *theories_;
			string << *signatures_;
			string << *source_;
		}
	}
	Size_t
	Math :: getRawVolume()
	{
		Size_t result = 0;
		result += getAggregateVolume (theories_);
		result += getAggregateVolume (signatures_);
		result += getAggregateVolume (source_);
		return result;
	}

	/********************************
	 *		Private static attributes
	 ********************************/

	Theories*
		Math :: theories_ = NULL;
	Signatures*
		Math :: signatures_ = NULL;
	Source*
		Math :: source_ = NULL;
}
}



