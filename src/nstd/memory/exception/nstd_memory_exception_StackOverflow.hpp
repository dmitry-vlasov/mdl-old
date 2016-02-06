/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_exception_StackOverflow.hpp                  */
/* Description:     stack overflow exception                                 */
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

class StackOverflow : public Exception {
public :
	StackOverflow() throw();
	StackOverflow (const StackOverflow&) throw();
	virtual ~ StackOverflow() throw();
};

}
}
}


