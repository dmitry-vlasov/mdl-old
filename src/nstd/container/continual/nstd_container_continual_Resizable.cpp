/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_container_continual_Resizable.cpp                   */
/* Description:     base class for resizable array-based containers          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace nstd {
namespace container {
namespace continual {

	/****************************
	 *		Public members
	 ****************************/

	template<class T, template<class> class H, class A>
	inline
	Resizable<T, H, A> :: Resizable() :
	Ancestor_ (),
	capacity_ (0) {
	}
	template<class T, template<class> class H, class A>
	inline
	Resizable<T, H, A> :: Resizable (const Index_ initialCapacity) :
	Ancestor_ (),
	capacity_ (initialCapacity + 1)
	{
		if (capacity_ < 2) {
			capacity_ = 2;
		}
		const memory :: Interval<Storage_>
			interval = Memory_ :: allocateVector (capacity_);
		Ancestor_ :: data_ = interval.beg();
		undefineTail();
	}
	template<class T, template<class> class H, class A>
	inline
	Resizable<T, H, A> :: Resizable (const Resizable& array) :
	Ancestor_ (array),
	capacity_ (array.getSize() + 1)
	{
		const memory :: Interval<Storage_>
			interval = Memory_ :: allocateVector (capacity_);
		Ancestor_ :: data_ = interval.beg();
		Ancestor_ :: copy (array);
		undefineTail();
	}
	template<class T, template<class> class H, class A>
	template<class T1, template<class> class H1>
	inline
	Resizable<T, H, A> :: Resizable (const Collection<T1, H1>& array) :
	Ancestor_ (array),
	capacity_ (array.getSize() + 1)
	{
		const memory :: Interval<Storage_>
			interval = Memory_ :: allocateVector (capacity_);
		Ancestor_ :: data_ = interval.beg();
		Ancestor_ :: copy (array);
		undefineTail();
	}
	template<class T, template<class> class H, class A>
	inline
	Resizable<T, H, A> :: Resizable
	(
		const Type_* const array,
		const Index_ size
	) :
	Ancestor_ (),
	capacity_ (size + 1)
	{
		const memory :: Interval<Storage_>
			interval = Memory_ :: allocateVector (capacity_);
		Ancestor_ :: data_ = interval.beg();
		Ancestor_ :: copy (array, size);
		undefineTail();
	}
	template<class T, template<class> class H, class A>
	Resizable<T, H, A> :: ~ Resizable()
	{
		if (Ancestor_ :: data_ == NULL) {
			return;
		}
		for (Index_ i = 0; i < capacity_; ++ i) {
			Ancestor_ :: data_[capacity_ - i - 1].commitSuicide();
		}
		const memory :: Interval<Storage_>
			interval = memory :: Interval<Storage_>
			(
				Ancestor_ :: data_,
				capacity_
			);
		Memory_ :: disposeVector (interval);
		Ancestor_ :: data_ = NULL;
	}

	template<class T, template<class> class H, class A>
	void
	Resizable<T, H, A> :: init (const Index_ initialCapacity)
	{
		if (Ancestor_ :: data_ != NULL) {
			std :: cout << "double initialization of container" << std :: endl;
			throw std :: exception();
		}
		capacity_  = initialCapacity;
		if (capacity_ < 2) {
			capacity_ = 2;
		}
		const memory :: Interval<Storage_>
			interval = Memory_ :: allocateVector (capacity_);
		Ancestor_ :: data_ = interval.beg();
		undefineTail();
	}

	template<class T, template<class> class H, class A>
	template<class T1, template<class> class H1>
	void
	Resizable<T, H, A> :: copy (const Collection<T1, H1>& array)
	{
		const bool reallocated = ensureCapacity (array.getSize() + 1, false);
		const bool becomingSmaller = (Ancestor_ :: size_ > array.getSize());

		Ancestor_ :: size_ = array.getSize();
		Ancestor_ :: template memMove<Storage_>
			(
				Ancestor_ :: data_,
				array.getData(),
				Ancestor_ :: size_
			);

		if (reallocated || becomingSmaller) {
			undefineTail();
		}
	}
	template<class T, template<class> class H, class A>
	inline void
	Resizable<T, H, A> :: copy
	(
		const Type_* const array,
		const Index_ size
	) {
		const bool reallocated = ensureCapacity (size + 1, false);
		const bool becomingSmaller = (Ancestor_ :: size_ > size);

		Ancestor_ :: size_ = size;
		Ancestor_ :: memMove
			(
				Ancestor_ :: data_,
				array,
				Ancestor_ :: size_
			);

		if (reallocated || becomingSmaller) {
			undefineTail();
		}
	}

	template<class T, template<class> class H, class A>
	inline typename Resizable<T, H, A> :: Index_
	Resizable<T, H, A> :: getCapacity() const {
		return capacity_;
	}
	template<class T, template<class> class H, class A>
	inline void
	Resizable<T, H, A> :: remove (const Index_ i)
	{
		Ancestor_ :: memMove
		(
			Ancestor_ :: data_ + i,
			Ancestor_ :: data_ + i + 1,
			-- Ancestor_ :: size_ - i
		);
		Ancestor_ :: data_ [Ancestor_ :: size_].undefine();
	}
	template<class T, template<class> class H, class A>
	inline void
	Resizable<T, H, A> :: insert (Argument_ value, const Index_ i)
	{
		const bool reallocated = ensureOneMoreElement();
		if (Ancestor_ :: size_ > 0) {
			Ancestor_ :: memMove
			(
				Ancestor_ :: data_ + Ancestor_ :: size_,
				Ancestor_ :: data_ + Ancestor_ :: size_ - 1,
				Ancestor_ :: size_ - i,
				true
			);
		}
		++ Ancestor_ :: size_;
		Ancestor_ :: data_ [i] = value;
		if (reallocated) {
			undefineTail();
		}
	}
	template<class T, template<class> class H, class A>
	inline void
	Resizable<T, H, A> :: removeLast()
	{
		-- Ancestor_ :: size_;
		Ancestor_ :: data_ [Ancestor_ :: size_].undefine();
	}
	template<class T, template<class> class H, class A>
	inline void
	Resizable<T, H, A> :: removeFirst() {
		remove (0);
	}

	template<class T, template<class> class H, class A>
	inline bool
	Resizable<T, H, A> :: ensureSize
	(
		const Index_ newSize,
		const bool keepInfo
	)
	{
		const bool reallocated = ensureCapacity (newSize + 1, keepInfo);
		if (reallocated) {
			undefineTail();
		}
		return reallocated;
	}
	template<class T, template<class> class H, class A>
	inline bool
	Resizable<T, H, A> :: ensureCapacity
	(
		const Index_ newCapacity,
		const bool keepInfo
	)
	{
		if (capacity_ < newCapacity) {
			const memory :: Interval<Storage_>
				interval = Memory_ :: resizeVector
					(
						Ancestor_ :: data_,
						capacity_,
						newCapacity,
						keepInfo
					);

			Ancestor_ :: data_ = interval.beg();
			capacity_ = interval.getLength();
			return true;
		}
		return false;
	}
	template<class T, template<class> class H, class A>
	bool
	Resizable<T, H, A> :: ensureCapacityNotLess
	(
		const Index_ newCapacity2,
		const bool keepInfo
	)
	{
		if (capacity_ < newCapacity2)
		{
			Index_ newCapacity1 =
				(capacity_ < LINEAR_GROWTH_POLICY_THRESHOLD) ?
				capacity_ * 2 :
				capacity_ + LINEAR_GROWTH_POLICY_THRESHOLD;

			Index_ newCapacity =
				(newCapacity1 > newCapacity2) ?
				newCapacity1 :
				newCapacity2;

			newCapacity =
				(capacity_ == 0) ?
				newCapacity :
				((newCapacity / capacity_) + 1) * capacity_;

			const memory :: Interval<Storage_>
				interval = Memory_ :: resizeVector
					(
						Ancestor_ :: data_,
						capacity_,
						newCapacity,
						keepInfo
					);

			Ancestor_ :: data_ = interval.beg();
			capacity_ = interval.getLength();
			return true;
		}
		return false;
	}
	template<class T, template<class> class H, class A>
	bool
	Resizable<T, H, A> :: ensureOneMoreElement (const bool keepInfo)
	{
		if (capacity_ <= Ancestor_ :: size_ + 1) {
			Index_ newCapacity = 0;

			if (capacity_ == 0) {
				newCapacity = 2;
			} else if (capacity_ < LINEAR_GROWTH_POLICY_THRESHOLD) {
				newCapacity = capacity_ * 2;
			} else {
				newCapacity = capacity_ + LINEAR_GROWTH_POLICY_THRESHOLD;
			}

			const memory :: Interval<Storage_>
				interval = Memory_ :: resizeVector
					(
						Ancestor_ :: data_,
						capacity_,
						newCapacity,
						keepInfo
					);

			Ancestor_ :: data_ = interval.beg();
			capacity_ = interval.getLength();
			return true;
		}
		return false;
	}

	// nstd :: Object implementation
	template<class T, template<class> class H, class A>
	inline void
	Resizable<T, H, A> :: commitSuicide() {
		delete this;
	}
	template<class T, template<class> class H, class A>
	inline Size_t
	Resizable<T, H, A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += getRawVolume ();
		for (Index_ i = 0; i < capacity_; ++ i) {
			volume += Ancestor_ :: data_[i].getVolume();
		}
		return volume;
	}
	template<class T, template<class> class H, class A>
	inline Size_t
	Resizable<T, H, A> :: getRawVolume() const {
		return capacity_ * sizeof (Storage_);
	}
	template<class T, template<class> class H, class A>
	inline Size_t
	Resizable<T, H, A> :: getSizeOf() const {
		return sizeof (Resizable);
	}

	/****************************
	 *		Protected members
	 ****************************/

	template<class T, template<class> class H, class A>
	void
	Resizable<T, H, A> :: undefineTail()
	{
		// Duff's device
		Storage_*
			data = Ancestor_ :: data_ + Ancestor_ :: size_;
		long count = capacity_ - Ancestor_ :: size_;

		if (count <= 0) {
			return;
		}
		switch (count % 8)  // count > 0 assumed
		{
			case 0 : do { (data++)->undefine();
			case 7 :      (data++)->undefine();
			case 6 :      (data++)->undefine();
			case 5 :      (data++)->undefine();
			case 4 :      (data++)->undefine();
			case 3 :      (data++)->undefine();
			case 2 :      (data++)->undefine();
			case 1 :      (data++)->undefine();
			            } while ((count -= 8) > 0);
		}
	}

}
}
}


