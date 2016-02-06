/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_ignorableDifference.hpp                      */
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

enum {
	IGNORED_PERCENT_VALUE = 33 //20  //20 // 10 = 77, 5 = 55, 1 = 7
};

bool ignorableDifference
(
	const Size_t actualSize,
	const Size_t offeredSize,
	const int ignoredDiff = IGNORED_PERCENT_VALUE
);

}
}


