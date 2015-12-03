/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_exception_MemoryInitFailure.cpp              */
/* Description:     memory initialization failure exception                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_MEMORY_EXCEPTION_MEMORY_INIT_FAILURE_CPP_
#define NSTD_MEMORY_EXCEPTION_MEMORY_INIT_FAILURE_CPP_

namespace nstd {
namespace memory {
namespace exception {

	/****************************
	 *		Public members
	 ****************************/

	inline
	MemoryInitFailure :: MemoryInitFailure() throw() :
	Exception ("memory init failure") {
	}
	inline
	MemoryInitFailure :: MemoryInitFailure (const MemoryInitFailure& exception) throw() :
	Exception (exception) {
	}
	MemoryInitFailure :: ~ MemoryInitFailure() throw() {
	}
}
}
}

#endif /*NSTD_MEMORY_EXCEPTION_MEMORY_INIT_FAILURE_CPP_*/
