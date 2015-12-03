/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_storage_Array.cpp                            */
/* Description:     array memory storage                                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_MEMORY_STORAGE_ARRAY_CPP_
#define NSTD_MEMORY_STORAGE_ARRAY_CPP_

namespace nstd {
namespace memory {
namespace storage {

	/****************************
	 *		Protected members
	 ****************************/

	template<class T, class E, class A>
	inline const Interval<E>
	Array<T, E, A> :: allocateArray (const Size_t length) {
		const Interval<Element_>
			interval = Allocator_ :: template allocateVector<Element_> (length);
		return interval;
	}
	template<class T, class E, class A>
	inline void
	Array<T, E, A> :: disposeArray (const Interval<Element_> interval) {
		Allocator_ :: template dispose<Element_> (interval);
	}
}
}
}

#endif /*NSTD_MEMORY_STORAGE_ARRAY_CPP_*/
