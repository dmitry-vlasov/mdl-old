/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_unit_Boxed.cpp                               */
/* Description:     boxed memory manager                                     */
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

	Boxed :: Boxed () :
	map_ (),
	disposed_ (),
	main_ (),
	reserve_ (),
	current_ (&main_),
	maxVolume_ (0),
	isFast_ (false) {
	}

	void
	Boxed :: create
	(
		const Size_t mainVolume,
		const Size_t reserveVolume
	)
	{
		#ifdef DEBUG_BOXED_MEMORY_LEAKS
		map_.create (true);
		#else
		map_.create (false);
		#endif
		disposed_.create();
		main_.create (mainVolume);
		reserve_.create (reserveVolume);
	}
	void
	Boxed :: clear (const bool wipe)
	{
		map_.clear();
		main_.clear (wipe);
		reserve_.clear (wipe);
		disposed_.clear();
		current_ = &main_;
	}
	inline void
	Boxed :: destroy ()
	{
		Ptrdiff_t allocated = 0;
		allocated += current_->getAllocatedVolume();
		allocated -= disposed_.getFreeVolume();
		allocated -= disposed_.getWastedVolume();

		disposed_.destroy();
		main_.destroy();
		reserve_.destroy();
		if (allocated != 0) {
			map_.show (std :: cout, false);
			map_.destroy();
			throw exception :: MemoryLeaks (allocated, "boxed memory leaks");
		} else {
			map_.destroy();
		}
	}
	inline bool
	Boxed :: isCreated() const {
		return main_.isRegular();
	}
	inline bool
	Boxed :: isFast() const {
		return isFast_;
	}
 	inline void
	Boxed :: setFast (bool isFast) {
 		isFast_ = isFast;
 	}

	inline Map&
	Boxed :: map() {
		return map_;
	}
	inline const Tank
	Boxed :: getMain() const {
		return main_;
	}
	inline const Tank
	Boxed :: getReserve() const {
		return reserve_;
	}

	bool
	Boxed :: contains (const void* pointer) const {
		return
			main_.contains (pointer) ||
			reserve_.contains (pointer);
	}
	bool
	Boxed :: containsInFree (const void* pointer) const {
		return
			main_.containsInFree (pointer) ||
			reserve_.containsInFree (pointer);
	}
	bool
	Boxed :: containsInUsed (const void* pointer) const {
		return
			main_.containsInUsed (pointer) ||
			reserve_.containsInUsed (pointer);
	}

	Size_t
	Boxed :: getUsedVolume () const
	{
		Size_t volume = 0;
		volume += disposed_.getUsedVolume();
		volume += map_.getVolume();
		return volume;
	}
	inline Size_t
	Boxed :: getOverallVolume () const
	{
		return
			main_.getOverallVolume() +
			reserve_.getOverallVolume();
	}
	inline Size_t
	Boxed :: getAllocatedVolume () const
	{
		Size_t result = 0;
		result += current_->getAllocatedVolume();
		result -= disposed_.getFreeVolume();
		result -= disposed_.getWastedVolume();
		return result;
	}
	inline Size_t
	Boxed :: getDisposedVolume () const {
		return disposed_.getFreeVolume ();
	}
	inline Size_t
	Boxed :: getFreeVolume () const
	{
		Size_t result = 0;
		result += current_->getFreeVolume();
		result += disposed_.getFreeVolume();
		return result;
	}

	inline Size_t
	Boxed :: getMainVolume() const {
		return main_.getOverallVolume();
	}
	inline Size_t
	Boxed :: getReserveVolume() const {
		return reserve_.getOverallVolume();
	}
	inline Size_t
	Boxed :: getMaxVolume() const {
		return maxVolume_;
	}

	inline void
	Boxed :: verifyDisposed() {
		disposed_.verify();
	}

	template<class S>
	inline void
	Boxed :: show (S& string) const
	{
		if (isFast_) {
			string << "boxed (fast) allocation summary:" << chars :: NEW_LINE;
			string << "--------------------------------" << chars :: NEW_LINE;
		} else {
			string << "boxed allocation summary:" << chars :: NEW_LINE;
			string << "-------------------------" << chars :: NEW_LINE;
		}
		if (isCreated()) {
			main_.show    (string, "main    box");
			reserve_.show (string, "reserve box");
			string << UsageMessage (main_.getOverallVolume(), maxVolume_, "max boxed size") << chars :: NEW_LINE;
			if (!isFast_ || disposed_.getFreeVolume() > 0) {
				disposed_.show (string, getOverallVolume(), false);
			}
		} else {
			string << "boxed memory space was not created." << chars :: NEW_LINE;
		}
		string << chars :: NEW_LINE;
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class T>
	const Interval<T>
	Boxed :: allocateScalar (const Size_t size)
	{
		typedef T Type;
		try {
			Interval<Type> interval;
			if (isFast_) {
				interval = current_->template allocateScalar<Type>(size);
			} else {
				interval = disposed_.template allocateScalar<Type>(size);
				if (interval.isEmpty()) {
					interval = current_->template allocateScalar<Type>(size);
				}
			}
			maxVolume_ =
				(maxVolume_ < getAllocatedVolume()) ?
				getAllocatedVolume() :
				maxVolume_;

			#ifdef DEBUG_BOXED_MAP
			map_.allocate (interval);
			#endif
			return interval;
		} catch (exception :: OutOfMemory& outOfMemory) {
			current_ =
				(current_ == &main_) ?
				&reserve_ :
				&main_;
			disposed_.clear();
			outOfMemory.setClass (exception :: OutOfMemory :: BOXED);
			throw;
		}
	}
	template<class T>
	const Interval<T>
	Boxed :: allocateVector
	(
		const Size_t length,
		const allocator :: Method method
	)
	{
		typedef T Type;
		try {
			Interval<Type> interval;
			if (isFast_) {
				interval = current_->template allocateVector<Type> (length);
			} else {
				interval = disposed_. template allocateVector<Type> (length, method);
				if (interval.isEmpty()) {
					interval = current_->template allocateVector<Type> (length);
				}
			}
			maxVolume_ =
				(maxVolume_ < getAllocatedVolume()) ?
				getAllocatedVolume() :
				maxVolume_;
			#ifdef DEBUG_BOXED_MAP
			map_.allocate (interval);
			#endif
			return interval;
		} catch (exception :: OutOfMemory& outOfMemory) {
			current_ =
				(current_ == &main_) ?
				&reserve_ :
				&main_;
			disposed_.clear();
			outOfMemory.setClass (exception :: OutOfMemory :: BOXED);
			throw;
		}
	}
	template<class T>
	inline void
	Boxed :: dispose (const Interval<T>& interval)
	{
		disposed_. template dispose<T> (interval);
		#ifdef DEBUG_BOXED_MAP
		map_.dispose (interval);
		#endif
	}
}
}
}


