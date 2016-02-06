/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_exception_OutOfMemory.hpp                    */
/* Description:     out of memory exception                                  */
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

class OutOfMemory : public Exception {
public :
	enum Class_ {
		NONE,
		STACK,
		HEAP,
		BOXED,
		STANDARD
	};
	OutOfMemory (const Class_ = NONE) throw();
	OutOfMemory (const Size_t, const Size_t, const Size_t) throw();
	OutOfMemory (const OutOfMemory&) throw();
	virtual ~ OutOfMemory() throw();

	void setClass (const Class_) throw();
	Class_ getClass() const throw();

	Size_t getFree() const;
	Size_t getDemand() const;
	Size_t getSpace() const;

	template<class S>
	void show (S&) const;

private :
	Class_ class_;
	Size_t free_;
	Size_t demand_;
	Size_t space_;
};

	template<class S>
	S&
	operator << (S&, const OutOfMemory&);
}
}
}


