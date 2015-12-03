/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_unit_Heap.cpp                                */
/* Description:     heap memory unit                                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_MEMORY_UNIT_HEAP_CPP_
#define NSTD_MEMORY_UNIT_HEAP_CPP_

namespace nstd {
namespace memory {
namespace unit {

	/****************************
	 *		Public members
	 ****************************/

	Heap :: Heap() :
	isCreated_ (false),
	map_ (),
	block_ (),
	disposed_ (),
	voidBlockIndex_ (0),
	usefulBlockIndex_ (0)
	{
		for (Index_ i = 0; i < BLOCK_ARRAY_SIZE; i++) {
			block_[i] = NULL;
		}
	}

	inline void
	Heap :: create()
	{
		#ifdef DEBUG_HEAP_MEMORY_LEAKS
		map_.create (true);
		#else
		map_.create (false);
		#endif
		disposed_.create();
		isCreated_ = true;
	}
	void
	Heap :: destroy()
	{
		Ptrdiff_t allocated = 0;
		for (Index_ i = 0; i < voidBlockIndex_; i ++ )  {
			allocated += block_[i]->getAllocatedVolume();
		}
		allocated -= disposed_.getFreeVolume();
		allocated -= disposed_.getWastedVolume();
		for (Index_ i = 0; i < voidBlockIndex_; i ++ )  {
			delete block_[i];
		}
		disposed_.destroy();
		if (allocated != 0) {
			map_.show (std :: cout, false);
			map_.destroy();
			throw exception :: MemoryLeaks (allocated, "heap memory leaks");
		} else {
			map_.destroy();
		}
		isCreated_ = false;
	}
	inline bool
	Heap :: isEmpty() const
	{
		const Size_t
			allocatedVolume = getAllocatedVolume();
		return (allocatedVolume == 0);
	}
	inline bool
	Heap :: isCreated() const {
		return isCreated_;
	}

	inline Map&
	Heap :: map() {
		return map_;
	}

	bool
	Heap :: contains (const void* pointer) const
	{
		for (Index_ i = 0; i < voidBlockIndex_; i ++ )  {
			if (block_[i]->contains (pointer)) {
				return true;
			}
		}
		return false;
	}
	bool
	Heap :: containsInFree (const void* pointer) const
	{
		for (Index_ i = 0; i < voidBlockIndex_; i ++ )  {
			if (block_[i]->containsInFree (pointer)) {
				return true;
			}
		}
		return false;
	}
	bool
	Heap :: containsInUsed (const void* pointer) const
	{
		for (Index_ i = 0; i < voidBlockIndex_; i ++ )  {
			if (block_[i]->containsInUsed (pointer)) {
				return true;
			}
		}
		return false;
	}

	Size_t
	Heap :: getUsedVolume() const
	{
		Size_t volume = 0;
		volume += disposed_.getUsedVolume();
		volume += map_.getVolume();
		return volume;
	}
	Size_t
	Heap :: getAllocatedVolume() const
	{
		Size_t result = 0;
		for (Index_ i = 0; i < voidBlockIndex_; i ++ )  {
			result += block_[i]->getAllocatedVolume();
		}
		result -= disposed_.getFreeVolume();
		result -= disposed_.getWastedVolume();
		return result;
	}
	Size_t
	Heap :: getFreeVolume() const
	{
		Size_t result = 0;
		for (Index_ i = 0; i < voidBlockIndex_; i ++ )  {
			result += block_[i]->getFreeVolume();
		}
		result += disposed_.getFreeVolume();
		return result;
	}
	Size_t
	Heap :: getOverallVolume() const
	{
		Size_t result = 0;
		for (Index_ i = 0; i < voidBlockIndex_; i ++ )  {
			result += block_[i]->getOverallVolume();
		}
		return result;
	}
	Size_t
	Heap :: getDisposedVolume () const {
		return disposed_.getFreeVolume();
	}

	inline void
	Heap :: verifyDisposed() {
		disposed_.verify();
	}

	template<class S>
	void
	Heap :: show
	(
		S& string,
		const bool showDisposed,
		const bool showFragmentation
	)
	{
		string << "heap allocation summary:" << chars :: NEW_LINE;
		string << "------------------------" << chars :: NEW_LINE;
		if (isCreated()) {
			const Size_t overall = getOverallVolume();
			string << UsageMessage (overall, overall,              "total     memory") << chars :: NEW_LINE;
			string << UsageMessage (overall, getFreeVolume(),      "free      memory") << chars :: NEW_LINE;
			string << UsageMessage (overall, getAllocatedVolume(), "allocated memory") << chars :: NEW_LINE;
			string << UsageMessage (overall, getDisposedVolume(),  "disposed  memory") << chars :: NEW_LINE;

			if (showDisposed) {
				string << chars :: NEW_LINE;
				disposed_.show (string, overall, showFragmentation);
			}
		} else {
			string << "heap memory space was not created." << chars :: NEW_LINE;
		}
		string << chars :: NEW_LINE;
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class T>
	const Interval<T>
	Heap :: allocateScalar (const Size_t size)
	{
		typedef T Type;
		Interval<Type> interval;
		interval = disposed_. template allocateScalar<Type> (size);
		if (!interval.isEmpty()) {
			goto end;
		}
		if (DEFAULT_BLOCK_SIZE < size) {
			block_ [voidBlockIndex_++] = Block :: template create<Type> (size);
			interval = block_[voidBlockIndex_ - 1]->allocateScalar<Type> (size);
			goto end;
		}
		for (Index_ i = usefulBlockIndex_; i < voidBlockIndex_; i ++ )  {
			if (block_[i]->isFilled()) {
				swapBlocks (i, usefulBlockIndex_ ++);
				continue;
			}
			interval = block_[i]->allocateScalar<Type> (size);
			if (!interval.isEmpty()) {
				if (block_[i]->isFilled()) {
					swapBlocks (i, usefulBlockIndex_ ++);
				}
				goto end;
			}
		}
		try {
			block_ [voidBlockIndex_++] = Block :: template create<Byte_t> (DEFAULT_BLOCK_SIZE);
		} catch (...) {
			exception :: OutOfMemory outOfMemory;
			outOfMemory.setClass (exception :: OutOfMemory :: HEAP);
			throw outOfMemory;
		}
		interval = block_[voidBlockIndex_- 1]->allocateScalar<Type> (size);
		end :
		#ifdef DEBUG_HEAP_MAP
		map_.allocate (interval);
		#endif
		return interval;
	}
	template<class T>
	const Interval<T>
	Heap :: allocateVector (const Size_t length, const allocator :: Method method)
	{
		typedef T Type;
		Interval<Type> interval;
		interval = disposed_. template allocateVector<Type> (length, method);
		if (!interval.isEmpty()) {
			goto end;
		}
		if (DEFAULT_BLOCK_SIZE < length * sizeof (Type)) {
			block_ [voidBlockIndex_++] = Block :: template create<Type> (length);
			interval = block_[voidBlockIndex_- 1]->allocateVector<Type> (length, method);
			goto end;
		}
		for (Index_ i = usefulBlockIndex_; i < voidBlockIndex_; i ++ )  {
			if (block_[i]->isFilled()) {
				swapBlocks (i, usefulBlockIndex_ ++);
				continue;
			}
			interval = block_[i]->allocateVector<Type> (length, method);
			if (!interval.isEmpty()) {
				if (block_[i]->isFilled()) {
					swapBlocks (i, usefulBlockIndex_ ++);
				}
				goto end;
			}
		}
		try {
			block_ [voidBlockIndex_++] = Block :: template create<Byte_t> (DEFAULT_BLOCK_SIZE);
		} catch (...) {
			exception :: OutOfMemory outOfMemory;
			outOfMemory.setClass (exception :: OutOfMemory :: HEAP);
			throw outOfMemory;
		}
		interval = block_[voidBlockIndex_ - 1]->allocateVector<Type> (length, method);
		end :
		#ifdef DEBUG_HEAP_MAP
		map_.allocate (interval);
		#endif
		return interval;
	}

	template<class T>
	void
	Heap :: dispose (const Interval<T> interval)
	{
		disposed_. template dispose<T> (interval);
		#ifdef DEBUG_HEAP_MAP
		map_.dispose (interval);
		#endif
	}

	void
	Heap :: swapBlocks (const Index_ i, const Index_ j)
	{
		unit :: Block* b = block_ [i];
		block_[i] = block_ [j];
		block_[j] = b;
	}
}
}
}

#endif /*NSTD_MEMORY_UNIT_HEAP_CPP_*/
