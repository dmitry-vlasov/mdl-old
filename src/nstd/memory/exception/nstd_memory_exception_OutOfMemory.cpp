/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_exception_OutOfMemory.cpp                    */
/* Description:     out of memory exception                                  */
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

	/****************************
	 *		Public members
	 ****************************/

	inline
	OutOfMemory :: OutOfMemory (const Class_ c) throw() :
	Exception ("out of memory"),
	class_ (c),
	free_ (Undefined<Size_t> :: getValue()),
	demand_ (Undefined<Size_t> :: getValue()),
	space_ (Undefined<Size_t> :: getValue()) {
	}
	OutOfMemory :: OutOfMemory (const Size_t free, const Size_t demand, const Size_t space) throw() :
	Exception ("out of memory"),
	class_ (NONE),
	free_ (free),
	demand_ (demand),
	space_ (space) {
	}
	inline
	OutOfMemory :: OutOfMemory (const OutOfMemory& exception) throw() :
	Exception (exception),
	class_ (exception.class_),
	free_ (exception.free_),
	demand_ (exception.demand_),
	space_ (exception.space_) {
	}
	inline
	OutOfMemory :: ~ OutOfMemory() throw() {
	}
	inline void
	OutOfMemory :: setClass (const Class_ c) throw()
	{
		class_ = c;
		switch (class_) {
			case NONE  : message_ = "out of memory";       break;
			case STACK : message_ = "out of stack memory"; break;
			case HEAP  : message_ = "out of heap memory";  break;
			case BOXED : message_ = "out of boxed memory"; break;
			case STANDARD : message_ = "out of standard heap memory"; break;
			default    : message_ = "out of memory";
		}
	}
	inline OutOfMemory :: Class_
	OutOfMemory :: getClass() const throw() {
		return class_;
	}

	inline Size_t
	OutOfMemory :: getFree() const {
		return free_;
	}
	inline Size_t
	OutOfMemory :: getDemand() const {
		return demand_;
	}
	inline Size_t
	OutOfMemory :: getSpace() const {
		return space_;
	}

	template<class S>
	void
	OutOfMemory :: show (S& os) const
	{
		os << message_ << ". ";
		os << "free: " << free_ << ", ";
		os << "demand: " << demand_ << ", ";
		os << "space: " << space_;
	}

	/*******************************
	 *		Overloaded operator
	 *******************************/

	template<class S>
	S&
	operator << (S& os, const OutOfMemory& exception)
	{
		exception.show (os);
		return os;
	}
}
}
}


