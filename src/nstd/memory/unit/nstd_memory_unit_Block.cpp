/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_unit_Block.cpp                               */
/* Description:     a chunk of memory                                        */
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

	/*************************
	 *		Public members
	 *************************/

	template<class T>
	inline Block*
	Block :: create () {
		return new Block (sizeof (T));
	}
	template<class T>
	inline Block*
	Block :: create (const Size_t size) {
		return new Block (size);
	}
	inline
	Block :: ~ Block() {
		const_cast<Interval<>&>(block_).destroy();
	}

	template<class T>
	const Interval<T>
	Block :: allocateScalar (const Size_t size)
	{
		typedef T Type;
		if (free_.getLength() >= size) {
			Type* const memory = free_.beg<Type>();
			free_.shiftBeg (size);
			return Interval<Type> (memory);
		} else {
			return Interval<Type>();
		}
	}
	template<class T>
	const Interval<T>
	Block :: allocateVector (const Size_t length, const allocator :: Method method)
	{
		typedef T Type;
		const Size_t bytes = length * sizeof (Type);

		if (free_.getLength() >= bytes) {
			Type* const memory = free_.beg<Type>();
			Size_t allocated = 0;
			Size_t newLength = 0;
			if (method == allocator :: GREEDY && ignorableDifference (bytes, free_.getLength())) {
				newLength = free_.getLength() / sizeof (Type);
				allocated = newLength * sizeof (Type);
			} else {
				newLength = length;
				allocated = bytes;
			}
			free_.shiftBeg (allocated);
			return Interval<Type> (memory, newLength);
		} else {
			return Interval<Type>();
		}
	}

	inline bool
	Block :: isFilled() const {
		return free_.isEmpty();
	}
	inline void
	Block :: clear() {
		free_ = block_;
	}

	inline bool
	Block :: contains (const void* pointer) const {
		return block_.contains (pointer);
	}
	inline bool
	Block :: containsInFree (const void* pointer) const {
		return free_.contains (pointer);
	}
	inline bool
	Block :: containsInUsed (const void* pointer) const {
		return
			block_.contains (pointer) &&
			!free_.contains (pointer);
	}

	inline Size_t
	Block :: getOverallVolume() const {
		return block_.getVolume();
	}
	inline Size_t
	Block :: getAllocatedVolume() const {
		return block_.getVolume() - free_.getVolume();
	}
	inline Size_t
	Block :: getFreeVolume() const {
		return free_.getVolume();
	}

	/*************************
	 *		Private members
	 *************************/

	inline
	Block :: Block (const Size_t size):
	block_ (),
	free_ ()
	{
		const_cast<Interval<>&>(block_).allocateVector (size);
		free_ = block_;
	}
}
}
}


