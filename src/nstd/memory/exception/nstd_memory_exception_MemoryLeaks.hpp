/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_exception_MemoryLeaks.hpp                    */
/* Description:     memory leaking failure exception                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_MEMORY_EXCEPTION_MEMORY_LEAKS_HPP_
#define NSTD_MEMORY_EXCEPTION_MEMORY_LEAKS_HPP_

#include "memory/exception/nstd_memory_exception_Exception.hpp"

namespace nstd {
namespace memory {
namespace exception {

class MemoryLeaks : public Exception {
public :
	MemoryLeaks (const Ptrdiff_t, const char* = "memory leaks") throw();
	MemoryLeaks (const MemoryLeaks&) throw();
	virtual ~ MemoryLeaks() throw();

	virtual Ptrdiff_t getLeak() const throw();

private :
	const Ptrdiff_t leak_;
};

}
}
}

#endif /*NSTD_MEMORY_EXCEPTION_MEMORY_LEAKS_HPP_*/
