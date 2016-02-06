/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_exception_MemoryInitFailure.hpp              */
/* Description:     memory initialization failure exception                  */
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

class MemoryInitFailure : public Exception {
public :
	MemoryInitFailure() throw();
	MemoryInitFailure (const MemoryInitFailure&) throw();
	virtual ~ MemoryInitFailure() throw();
};

}
}
}


