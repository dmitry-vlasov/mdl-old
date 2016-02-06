/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_exception_MemoryLeaks.cpp                    */
/* Description:     memory leaking failure exception                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "memory/exception/nstd_memory_exception_Exception.hpp"

namespace nstd {
namespace memory {
namespace exception {

	/****************************
	 *		Public members
	 ****************************/

	inline
	MemoryLeaks :: MemoryLeaks
	(
		const Ptrdiff_t leak,
		const char* message
	) throw() :
	Exception (message),
	leak_ (leak) {
	}
	inline
	MemoryLeaks :: MemoryLeaks (const MemoryLeaks& exception) throw() :
	Exception (exception),
	leak_ (exception.leak_) {
	}
	MemoryLeaks :: ~ MemoryLeaks() throw() {
	}

	inline Ptrdiff_t
	MemoryLeaks :: getLeak() const throw() {
		return leak_;
	}
}
}
}


