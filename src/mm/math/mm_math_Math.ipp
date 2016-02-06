/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_math_Math.ipp                                         */
/* Description:     static container for global metamath structures          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mm {
namespace math {

	/****************************
	 *		Public members
	 ****************************/

	inline Assertions*
	Math :: assertions() {
		return assertions_;
	}
	inline Constants*
	Math :: constants() {
		return constants_;
	}
	inline void
	Math :: release()
	{
		deleteAggregateObject (constants_);
		deleteAggregateObject (assertions_);
	}
}
}


