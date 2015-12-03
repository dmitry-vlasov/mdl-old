/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_allocator_Standard.cpp                       */
/* Description:     allocator to the standard heap memory                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_MEMORY_ALLOCATOR_STANDARD_CPP_
#define NSTD_MEMORY_ALLOCATOR_STANDARD_CPP_

namespace nstd {
namespace memory {
namespace allocator {

	/****************************
	 *		Public members
	 ****************************/

	template<class T>
	inline const Interval<T>
	Standard :: allocateScalar (const Size_t size)
	{
		#ifdef MULTY_THREADED
		pthread_mutex_lock (&mutex_);
		#endif
		typedef T Type;
		Interval<Type> interval;
		try {
			interval = Space :: standard_.template allocateScalar<Type> (size);
		} catch (...) {
			#ifdef MULTY_THREADED
			pthread_mutex_unlock (&mutex_);
			#endif
			throw;
		}
		#ifdef MULTY_THREADED
		pthread_mutex_unlock (&mutex_);
		#endif
		return interval;
	}
	template<class T>
	inline const Interval<T>
	Standard :: allocateVector (const Size_t length, const Method)
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
			interval = Space :: standard_.template allocateVector<Type> (length);
		} catch (...) {
			#ifdef MULTY_THREADED
			pthread_mutex_unlock (&mutex_);
			#endif
			throw;
		}
		#ifdef MULTY_THREADED
		pthread_mutex_unlock (&mutex_);
		#endif
		return interval;
	}
	template<class T>
	inline void
	Standard :: dispose (const Interval<T>& interval)
	{
		#ifdef MULTY_THREADED
		pthread_mutex_lock (&mutex_);
		#endif
		typedef T Type;
		try {
			Space :: standard_.template dispose<Type> (interval);
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

	/****************************
	 *		Private members
	 ****************************/

	pthread_mutex_t Standard :: mutex_ = PTHREAD_MUTEX_INITIALIZER;
}
}
}

#endif /*NSTD_MEMORY_ALLOCATOR_STANDARD_CPP_*/
