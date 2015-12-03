/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_allocator_Stack.cpp                          */
/* Description:     stack allocator                                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_MEMORY_ALLOCATOR_STACK_CPP_
#define NSTD_MEMORY_ALLOCATOR_STACK_CPP_

namespace nstd {
namespace memory {
namespace allocator {

	/****************************
	 *		Public members
	 ****************************/

	template<class T>
	inline const Interval<T>
	Stack :: allocateScalar (const Size_t size)
	{
		typedef T Type;
		const Interval<Type>&
			interval = Space :: stack().template allocateScalar<Type> (size);
		return interval;
	}
	template<class T>
	inline const Interval<T>
	Stack :: allocateVector (const Size_t length, const Method)
	{
		typedef T Type;
		if (length == 0) {
			return Interval<Type>();
		}
		const Interval<Type>&
			interval = Space :: stack().template allocateVector<Type> (length);
		return interval;
	}
	template<class T>
	inline void
	Stack :: dispose (const Interval<T>&) {
	}
}
}
}

#endif /*NSTD_MEMORY_ALLOCATOR_STACK_CPP_*/

