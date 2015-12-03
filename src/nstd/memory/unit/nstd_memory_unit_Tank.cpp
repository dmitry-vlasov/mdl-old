/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_unit_Tank.cpp                                */
/* Description:     base class for memory managers                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_MEMORY_UNIT_TANK_CPP_
#define NSTD_MEMORY_UNIT_TANK_CPP_

namespace nstd {
namespace memory {
namespace unit {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Tank :: Tank () :
	space_ (),
	free_ () {
	}

	inline void
	Tank :: create (const Size_t volume)
	{
		const_cast<Interval<>&> (space_).allocateVector (volume);
		free_ = space_;
	}
	inline void
	Tank :: clear (const bool wipe)
	{
		free_ = space_;
		if (wipe) {
			free_.clear();
		}
	}
	void
	Tank :: destroy()
	{
		const_cast<Interval<>&>(space_).destroy();
		free_ = space_;
	}

	inline bool
	Tank :: isRegular() const {
		return space_.isRegular();
	}
	inline bool
	Tank :: isEmpty() const {
		return (free_ == space_);
	}
	inline bool
	Tank :: isFull() const {
		return free_.isEmpty();
	}

	inline bool
	Tank :: contains (const void* pointer) const {
		return space_.contains (pointer);
	}
	inline bool
	Tank :: containsInFree (const void* pointer) const {
		return free_.contains (pointer);
	}
	inline bool
	Tank :: containsInUsed (const void* pointer) const {
		return
			space_.contains (pointer) &&
			!free_.contains (pointer);
	}

	template<class T>
	const Interval<T>
	Tank :: allocateScalar (const Size_t size)
	{
		typedef T Type;
		if (free_.getVolume() < size) {
			throw exception :: OutOfMemory (free_.getVolume(), size, space_.getVolume());
		}
		Type* memory = NULL;
		free_.shiftEnd (-size);
		memory = free_.template end<Type>();
		return Interval<T> (memory);
	}
	template<class T>
	const Interval<T>
	Tank :: allocateVector (const Size_t length)
	{
		typedef T Type;
		const Size_t size = length * sizeof (Type);

		if (free_.getVolume() < size) {
			throw exception :: OutOfMemory (free_.getVolume(), size, space_.getVolume());
		}
		Type* memory = NULL;
		free_.shiftEnd (-size);
		memory = free_.template end<Type>();
		return Interval<T> (memory, length);
	}

	Size_t
	Tank :: getOverallVolume() const {
		return space_.getVolume();
	}
	Size_t
	Tank :: getAllocatedVolume() const
	{
		if (space_.isNull()) {
			return 0;
		}
		Byte_t* const beg = free_.end();
		Byte_t* const end = space_.end();

		const Interval<>
			used = Interval<> (beg, end);
		return used.getVolume();
	}
	Size_t
	Tank :: getFreeVolume() const {
		return free_.getVolume();
	}

	template<class S>
	void
	Tank :: show
	(
		S& string,
		const char message[],
		const int indent
	) const
	{
		const Size_t space = getOverallVolume();
		const Size_t used = getAllocatedVolume();
		chars :: shift (string, indent);
		string << UsageMessage (space, used, message) << chars :: NEW_LINE;
	}
}
}
}

#endif /*NSTD_MEMORY_UNIT_TANK_CPP_*/
