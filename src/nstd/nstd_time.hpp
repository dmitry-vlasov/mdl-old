/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_time.hpp                                            */
/* Description:     time constants                                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace nstd {
namespace time {

	// Type for real number representation of time (seconds).
	typedef double Time;

	const Time
		SECOND = 1;
	const Time
		MINUTE = SECOND * 60;
	const Time
		HOUR = MINUTE * 60;
	const Time
		DAY = HOUR * 24;
	const Time
		MILLISECOND = SECOND / 1000;
	const Time
		MICROSECOND = MILLISECOND / 1000;
}
	using time :: Time;
}


