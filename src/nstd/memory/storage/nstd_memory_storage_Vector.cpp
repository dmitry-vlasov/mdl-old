/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_storage_Vector.cpp                           */
/* Description:     vector memory storage                                    */
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
namespace storage {

	/****************************
	 *		Protected members
	 ****************************/

	template<class T, class E, class A>
	inline const Interval<E>
	Vector<T, E, A> :: allocateVector (const Size_t length)
	{
		const Interval<Element_>
			interval = Allocator_ :: template allocateVector<Element_> (length);
		return interval;
	}
	template<class T, class E, class A>
	inline void
	Vector<T, E, A> :: disposeVector (const Interval<Element_> interval) {
		Allocator_ :: template dispose<Element_> (interval);
	}

	template<class T, class E, class A>
	const Interval<E>
	Vector<T, E, A> :: resizeVector
	(
		Element_* array,
		const Size_t oldCapacity,
		const Size_t newCapacity,
		const bool keep
	)
	{
		const Interval<Element_>
			newInterval = Allocator_ :: template allocateVector<Element_> (newCapacity, allocator :: GREEDY);
		const Interval<Element_>
			oldInterval = Interval<Element_> (array, oldCapacity);

		if (keep && (array != NULL) && !newInterval.isEmpty()) {
			keepData (array, newInterval.beg(), oldCapacity);
		}

		const_cast<Interval<Element_>&>(oldInterval).clear();
		Allocator_ :: template dispose<Element_> (oldInterval);
		return newInterval;
	}

	/***************************
	 *		Private members
	 ***************************/

	template<class T, class E, class A>
	void
	Vector<T, E, A> :: keepData
	(
		Element_* oldArray,
		Element_* newArray,
		const Size_t capacity
	)
	{
		if (capacity == 0) {
			return;
		}
		// Duff's device
		long count = capacity;
		switch (count % 8)  // count > 0 assumed
		{
			case 0 : do { *newArray++ = *oldArray++;
			case 7 :      *newArray++ = *oldArray++;
			case 6 :      *newArray++ = *oldArray++;
			case 5 :      *newArray++ = *oldArray++;
			case 4 :      *newArray++ = *oldArray++;
			case 3 :      *newArray++ = *oldArray++;
			case 2 :      *newArray++ = *oldArray++;
			case 1 :      *newArray++ = *oldArray++;
			            } while ((count -= 8) > 0);
		}
	}
}
}
}


