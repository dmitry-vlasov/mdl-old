/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_ignorableDifference.cpp                      */
/* Description:     function for ignorable difference in a greedy allocation */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace nstd {
namespace memory {

	bool ignorableDifference
	(
		const Size_t actualSize,
		const Size_t offeredSize,
		const int ignoredDiff
	)
	{
		const double
			factor = static_cast<double>(offeredSize - actualSize) * 100 / offeredSize;
		return (factor <= ignoredDiff);
	}

}
}


