/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_allocator_Direct.cpp                         */
/* Description:     direct allocator to the standard heap memory             */
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
namespace allocator {

	/****************************
	 *		Public members
	 ****************************/

	template<class T>
	inline const Interval<T>
	Direct :: allocateScalar (const Size_t size)
	{
		#ifdef MULTY_THREADED
		pthread_mutex_lock (&mutex_);
		#endif
		typedef T Type;
		Interval<Type> interval;
		try {
			interval.allocateScalar (size);
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
	Direct :: allocateVector (const Size_t length, const Method)
	{
		#ifdef MULTY_THREADED
		pthread_mutex_lock (&mutex_);
		#endif
		typedef T Type;
		Interval<Type> interval;
		try {
			interval.allocateVector (length);
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
	Direct :: dispose (const Interval<T>& interval)
	{
		#ifdef MULTY_THREADED
		pthread_mutex_lock (&mutex_);
		#endif
		typedef T Type;
		if (interval.isNull()) {
			return;
		}
		try {
			const_cast<Interval<Type>&> (interval).destroy();
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

	pthread_mutex_t Direct :: mutex_ = PTHREAD_MUTEX_INITIALIZER;
}
}
}


