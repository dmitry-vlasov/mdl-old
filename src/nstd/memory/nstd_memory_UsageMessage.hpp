/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_UsageMessage.hpp                             */
/* Description:     displays memory usage message                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "memory/nstd_memory_Unit.hpp"

namespace nstd {
namespace memory {

class UsageMessage {
public :
	UsageMessage
	(
		const Ptrdiff_t,
		const Ptrdiff_t,
		const char message[],
		const char delimiter = chars :: TAB,
		const bool showPreciseValue = false,
		const Unit :: Unit_ = Unit :: AUTO
	);

	template<class S>
	void show (S&) const;

private :
	const char* unit() const;

	const Unit :: Unit_ measureUnit_;
	const Ptrdiff_t overallVolume_;
	const Ptrdiff_t currentVolume_;
	const char* message_;
	const char  delimiter_;
	const bool showPreciseValue_;
};

	template<class S>
	S&
	operator << (S&, const UsageMessage&);
}
}


