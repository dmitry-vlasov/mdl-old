/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_allocator_Boxed.cpp                          */
/* Description:     boxed memory allocator                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_MEMORY_ALLOCATOR_BOXED_CPP_
#define NSTD_MEMORY_ALLOCATOR_BOXED_CPP_

namespace nstd {
namespace memory {
namespace allocator {

	/****************************
	 *		Public members
	 ****************************/

	template<class T>
	inline const Interval<T>
	Boxed :: allocateScalar (const Size_t size)
	{
		#ifdef MULTY_THREADED
		pthread_mutex_lock (&mutex_);
		#endif
		typedef T Type;
		Interval<Type> interval;
		try {
			interval = Space :: boxed_.template allocateScalar<Type> (size);
		} catch (...) {
			#ifdef MULTY_THREADED
			pthread_mutex_unlock (&mutex_);
			#endif
			throw;
		}
		#ifdef DEBUG_BOXED_CONTROL_ALLOCATION
		control_.checkScalarAllocation
		(
			interval.byteRepresentation()
			Space :: getBoxed().map()
		);
    	#endif
		#ifdef MULTY_THREADED
		pthread_mutex_unlock (&mutex_);
		#endif
		return interval;
	}
	template<class T>
	inline const Interval<T>
	Boxed :: allocateVector (const Size_t length, const Method method)
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
			interval = Space :: boxed_.template allocateVector<Type> (length, method);
		} catch (...) {
			#ifdef MULTY_THREADED
			pthread_mutex_unlock (&mutex_);
			#endif
			throw;
		}
		#ifdef DEBUG_BOXED_CONTROL_ALLOCATION
		control_.checkVectorAllocation
		(
			interval.byteRepresentation(),
			Space :: boxed().map()
		);
    	#endif
		#ifdef MULTY_THREADED
		pthread_mutex_unlock (&mutex_);
		#endif
		return interval;
	}
	template<class T>
	inline void
	Boxed :: dispose (const Interval<T>& interval)
	{
		#ifdef MULTY_THREADED
		pthread_mutex_lock (&mutex_);
		#endif
		typedef T Type;
		#ifdef DEBUG_BOXED_CONTROL_ALLOCATION
		control_.checkDisposal
		(
			interval.byteRepresentation()
			Space :: boxed().map()
		);
    	#endif
		try {
			Space :: boxed_.template dispose<Type> (interval);
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
	Boxed :: setControl (const void* beg, const Size_t size)
	{
		const Byte_t* begin = static_cast<const Byte_t*>(beg);
		control_.set  (Interval<>(const_cast<Byte_t*>(begin), size));
	}

	/****************************
	 *		Private members
	 ****************************/

	pthread_mutex_t Boxed :: mutex_ = PTHREAD_MUTEX_INITIALIZER;
	Control Boxed :: control_;
}
}
}

#endif /*NSTD_MEMORY_ALLOCATOR_BOXED_CPP_*/
