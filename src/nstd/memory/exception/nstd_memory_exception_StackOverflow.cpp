/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_exception_StackOverflow.cpp                  */
/* Description:     stack overflow exception                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_MEMORY_EXCEPTION_STACK_OVERFLOW_CPP_
#define NSTD_MEMORY_EXCEPTION_STACK_OVERFLOW_CPP_

namespace nstd {
namespace memory {
namespace exception {

	/****************************
	 *		Public members
	 ****************************/

	inline
	StackOverflow :: StackOverflow() throw() :
	Exception ("stack overflow") {
	}
	inline
	StackOverflow :: StackOverflow (const StackOverflow& exception) throw() :
	Exception (exception) {
	}
	StackOverflow :: ~ StackOverflow() throw() {
	}
}
}
}

#endif /*NSTD_MEMORY_EXCEPTION_STACK_OVERFLOW_CPP_*/
