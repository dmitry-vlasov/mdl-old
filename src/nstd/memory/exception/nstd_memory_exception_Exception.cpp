/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_exception_Exception.cpp                      */
/* Description:     base memory exception class                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_MEMORY_EXCEPTION_EXCEPTION_CPP_
#define NSTD_MEMORY_EXCEPTION_EXCEPTION_CPP_

#include "memory/exception/nstd_memory_exception_Exception.hpp"

namespace nstd {
namespace memory {
namespace exception {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Exception :: Exception (const char* message) throw() :
	message_ (message) {
	}
	inline
	Exception :: Exception (const Exception& exception) throw() :
	message_ (exception.message_) {
	}
	Exception :: ~ Exception() throw() {
	}

	inline const char*
	Exception :: what() const throw() {
		return message_;
	}
	inline const char*
	Exception :: getMessage() const throw() {
		return message_;
	}

	/*******************************
	 *		Overloaded operator
	 *******************************/

	template<class S>
	S&
	operator << (S& os, const Exception& exception)
	{
		os << exception.what();
		return os;
	}
}
}
}

#endif /*NSTD_MEMORY_EXCEPTION_EXCEPTION_CPP_*/
