/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_exception_LimitReached.hpp                   */
/* Description:     limit reached exception                                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_MEMORY_EXCEPTION_LIMIT_REACHED_HPP_
#define NSTD_MEMORY_EXCEPTION_LIMIT_REACHED_HPP_

#include "memory/exception/nstd_memory_exception_Exception.hpp"

namespace nstd {
namespace memory {
namespace exception {

class LimitReached : public Exception {
public :
	LimitReached() throw();
	LimitReached (const LimitReached&) throw();
	virtual ~ LimitReached() throw();
};

}
}
}

#endif /*NSTD_MEMORY_EXCEPTION_LIMIT_REACHED_HPP_*/
