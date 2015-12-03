/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_allocator_Heap.cpp                           */
/* Description:     heap allocator                                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_MEMORY_ALLOCATOR_HEAP_CPP_
#define NSTD_MEMORY_ALLOCATOR_HEAP_CPP_

namespace nstd {
namespace memory {
namespace allocator {

	/****************************
	 *		Public members
	 ****************************/

	template<class T>
	inline const Interval<T>
	Heap :: allocateScalar (const Size_t size)
	{
		#ifdef MULTY_THREADED
		pthread_mutex_lock (&mutex_);
		#endif
		typedef T Type;
		Interval<Type> interval;
		try {
			interval = Space :: heap_.template allocateScalar<Type> (size);
		} catch (...) {
			#ifdef MULTY_THREADED
			pthread_mutex_unlock (&mutex_);
			#endif
			throw;
		}
		#ifdef DEBUG_HEAP_CONTROL_ALLOCATION
		control_.checkScalarAllocation
		(
			interval.byteRepresentation(),
			Space :: heap().map()
		);
    	#endif
		#ifdef MULTY_THREADED
		pthread_mutex_unlock (&mutex_);
		#endif
		return interval;
	}
	template<class T>
	inline const Interval<T>
	Heap :: allocateVector (const Size_t length, const Method method)
	{
		#ifdef MULTY_THREADED
		pthread_mutex_lock (&mutex_);
		#endif
		typedef T Type;
		if (length == 0) {
			return Interval<Type>();
		}
		Interval<Type> interval;
		try {
			interval = Space :: heap_.template allocateVector<Type> (length, method);
		} catch (...) {
			#ifdef MULTY_THREADED
			pthread_mutex_unlock (&mutex_);
			#endif
			throw;
		}
		#ifdef DEBUG_HEAP_CONTROL_ALLOCATION
		control_.checkVectorAllocation
		(
			interval.byteRepresentation(),
			Space :: heap().map()
		);
    	#endif
		#ifdef MULTY_THREADED
		pthread_mutex_unlock (&mutex_);
		#endif
		return interval;
	}
	template<class T>
	inline void
	Heap :: dispose (const Interval<T>& interval)
	{
		#ifdef MULTY_THREADED
		pthread_mutex_lock (&mutex_);
		#endif
		typedef T Type;
		#ifdef DEBUG_HEAP_CONTROL_ALLOCATION
		control_.checkDisposal
		(
			interval.byteRepresentation(),
			Space :: heap().map()
		);
    	#endif
		try {
			Space :: heap_.template dispose<Type> (interval);
		} catch (...) {
			#ifdef MULTY_THREADED
			pthread_mutex_unlock (&mutex_);
			#endif
			throw;
		}
		#ifdef MULTY_THREADED
		pthread_mutex_unlock (&mutex_);
		#endif
	}
	inline void
	Heap :: setControl (const void* beg, const Size_t size)
	{
		const Byte_t* begin = static_cast<const Byte_t*>(beg);
		control_.set  (Interval<>(const_cast<Byte_t*>(begin), size));
	}

	/****************************
	 *		Private members
	 ****************************/

	pthread_mutex_t Heap :: mutex_ = PTHREAD_MUTEX_INITIALIZER;
	Control Heap :: control_;
}
}
}

#endif /*NSTD_MEMORY_ALLOCATOR_HEAP_CPP_*/
