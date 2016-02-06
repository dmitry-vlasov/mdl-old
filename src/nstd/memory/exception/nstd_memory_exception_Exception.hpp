/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_exception_Exception.hpp                      */
/* Description:     base memory exception class                              */
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
namespace exception {

class Exception : public std :: exception {
public :
	Exception (const char* = "memory exception") throw();
	Exception (const Exception&) throw();
	virtual ~ Exception() throw();

	virtual const char* what() const throw();
	virtual const char* getMessage() const throw();

protected :
	const char* message_;
};

	template<class S>
	S&
	operator << (S&, const Exception&);
}
}
}


