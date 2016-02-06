/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_unit_Standard.cpp                            */
/* Description:     standard heap memory space                               */
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
namespace unit {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Standard :: Standard() :
	map_ (),
	allocated_ (0),
	disposed_ (0),
	overall_ (0)
	{
		#ifdef DEBUG_STANDARD_MEMORY_LEAKS
		map_.create (true);
		#else
		map_.create (false);
		#endif
	}

	inline void
	Standard :: create() {
	}
	inline void
	Standard :: destroy()
	{
		const Ptrdiff_t
			allocated = overall_ - disposed_;
		if (allocated != 0) {
			map_.show (std :: cout, false);
			map_.destroy();
			throw exception :: MemoryLeaks (allocated, "standard heap memory leaks");
		} else {
			map_.destroy();
		}
	}
	inline bool
	Standard :: isEmpty() const {
		return (allocated_ == 0);
	}
	inline bool
	Standard :: isUsed() const {
		return (overall_ > 0);
	}
	inline bool
	Standard :: isCreated() const {
		return isUsed();
	}

	inline Map&
	Standard :: map() {
		return map_;
	}

	inline Size_t
	Standard :: getUsedVolume() const {
		return 0;
	}
	inline Size_t
	Standard :: getAllocatedVolume() const {
		return allocated_;
	}
	inline Size_t
	Standard :: getDisposedVolume() const {
		return disposed_;
	}
	inline Size_t
	Standard :: getOverallVolume() const {
		return overall_;
	}

	template<class S>
	inline void
	Standard :: show (S& string)
	{
		string << "standard heap allocation summary:" << chars :: NEW_LINE;
		string << "---------------------------------" << chars :: NEW_LINE;
		if (isUsed()) {
			string << UsageMessage (overall_, overall_,   "total     memory") << chars :: NEW_LINE;
			string << UsageMessage (overall_, allocated_, "allocated memory") << chars :: NEW_LINE;
			string << UsageMessage (overall_, disposed_,  "disposed  memory") << chars :: NEW_LINE;
		} else {
			string << "standard heap was not used." << chars :: NEW_LINE;
		}
		string << chars :: NEW_LINE;
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class T>
	inline const Interval<T>
	Standard :: allocateScalar (const Size_t size)
	{
		typedef T Type;
		try {
			Interval<Type> interval;
			interval.allocateScalar (size);
			allocated_ += interval.getVolume();
			overall_ += interval.getVolume();
			#ifdef DEBUG_STANDARD_MAP
			map_.allocate (interval);
			#endif
			return interval;
		} catch (...) {
			exception :: OutOfMemory outOfMemory;
			outOfMemory.setClass (exception :: OutOfMemory :: STANDARD);
			throw outOfMemory;
		}
	}
	template<class T>
	inline const Interval<T>
	Standard :: allocateVector (const Size_t length)
	{
		typedef T Type;
		try {
			Interval<Type> interval;
			interval.allocateVector (length);
			allocated_ += interval.getVolume();
			overall_ += interval.getVolume();
			#ifdef DEBUG_STANDARD_MAP
			map_.allocate (interval);
			#endif
			return interval;
		} catch (...) {
			exception :: OutOfMemory outOfMemory;
			outOfMemory.setClass (exception :: OutOfMemory :: STANDARD);
			throw outOfMemory;
		}
	}
	template<class T>
	inline void
	Standard :: dispose (const Interval<T> interval)
	{
		typedef T Type;
		if (interval.isNull()) {
			return;
		}
		allocated_ -= interval.getVolume();
		disposed_ += interval.getVolume();
		#ifdef DEBUG_STANDARD_MAP
		map_.dispose (interval);
		#endif
		const_cast<Interval<Type>&> (interval).destroy();
	}
}
}
}


