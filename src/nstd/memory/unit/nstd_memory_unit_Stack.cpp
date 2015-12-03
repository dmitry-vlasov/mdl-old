/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_unit_Stack.cpp                               */
/* Description:     stack memory                                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_MEMORY_UNIT_STACK_CPP_
#define NSTD_MEMORY_UNIT_STACK_CPP_

namespace nstd {
namespace memory {
namespace unit {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Stack :: Stack () :
	Tank (),
	stack_ (),
	maxVolume_ (0) {
	}

	inline void
	Stack :: create (const Size_t volume) {
		Tank :: create (volume);
	}
	inline void
	Stack :: destroy()
	{
		const Size_t allocated = getAllocatedVolume();
		Tank :: destroy();
		if (allocated != 0) {
			throw exception :: MemoryLeaks (allocated, "stack memory leaks");
		}
	}
	inline bool
	Stack :: isCreated() const {
		return Tank :: isRegular();
	}

	inline void
	Stack :: push() {
		stack_.push (free_.end());
	}
	inline void
	Stack :: pop()
	{
		const Size_t
			volume = space_.getVolume() - free_.getVolume();
		if (volume > maxVolume_) {
			maxVolume_ = volume;
		}
		free_.end_ = stack_.pop();
	}
	inline void
	Stack :: clear (const bool wipe)
	{
		stack_.clear();
		Tank :: clear (wipe);
	}
	inline bool
	Stack :: isEmpty() const {
		return stack_.isEmpty();
	}

	inline void
	Stack :: memorizeState() {
		stack_.memorizeState();
	}
	inline void
	Stack :: recallState()
	{
		stack_.recallState();
		if (stack_.isEmpty()) {
			clear (false);
		} else {
			free_.end_ = stack_.get();
		}
	}

	inline Size_t
	Stack :: getMaxVolume() {
		return maxVolume_;
	}
	inline Stack :: Index_
	Stack :: getMaxDepth() const {
		return stack_.getMaxDepth();
	}
	inline Stack :: Index_
	Stack :: getDepth() const {
		return stack_.getDepth();
	}

	inline Size_t
	Stack :: getUsedVolume() const {
		return 0;
	}
	inline Size_t
	Stack :: getOverallVolume() const {
		return Tank :: getOverallVolume();
	}
	inline Size_t
	Stack :: getAllocatedVolume() const {
		return Tank :: getAllocatedVolume();
	}
	inline Size_t
	Stack :: getFreeVolume() const {
		return Tank :: getFreeVolume();
	}

using manipulator :: endLine;

	template<class S>
	inline void
	Stack :: show (S& string, const int indent) const
	{
		chars :: shift (string, indent);
		string << "stack allocation summary:" << chars :: NEW_LINE;
		chars :: shift (string, indent);
		string << "-------------------------" << chars :: NEW_LINE;

		const Size_t overallVolume = getOverallVolume();
		chars :: shift (string, indent);
		string << UsageMessage (overallVolume, overallVolume, "total stack volume") << chars :: NEW_LINE;

		Tank :: show (string, "stack mem used", indent);

		chars :: shift (string, indent);
		string << UsageMessage (space_.getVolume(), maxVolume_, "max stack size") << chars :: NEW_LINE;
		stack_.show (string, indent + 1);
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class T>
	inline const Interval<T>
	Stack :: allocateScalar (const Size_t size)
	{
		if (stack_.isEmpty()) {
			throw exception :: Exception ("empty stack allocation.");
		}
		typedef T Type;
		try {
			return Tank :: template allocateScalar<Type> (size);
		} catch (exception :: OutOfMemory& error) {
			error.setClass (exception :: OutOfMemory :: STACK);
			throw;
		}
	}
	template<class T>
	inline const Interval<T>
	Stack :: allocateVector (const Size_t length)
	{
		if (stack_.isEmpty()) {
			throw exception :: Exception ("empty stack allocation.");
		}
		typedef T Type;
		try {
			return Tank :: template allocateVector<Type> (length);
		} catch (exception :: OutOfMemory& error) {
			error.setClass (exception :: OutOfMemory :: STACK);
			throw;
		}
	}
}
}
}

#endif /*NSTD_MEMORY_UNIT_STACK_CPP_*/
