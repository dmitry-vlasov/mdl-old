/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_Unit.hpp                                     */
/* Description:     displays memory volume in proper units                   */
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

class Unit {
public :
	enum Unit_ {
		BYTE     = size :: BYTE,
		KILOBYTE = size :: KILOBYTE,
		MEGABYTE = size :: MEGABYTE,
		GIGABYTE = size :: GIGABYTE,
		AUTO     = -1
	};

	template<class S>
	static void show (S&, const Ptrdiff_t);
	static const char* unit (const Unit_);
	static Unit_ calculate (const Ptrdiff_t);
};

}
}


