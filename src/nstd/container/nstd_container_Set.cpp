/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_container_Set.cpp                                   */
/* Description:     set container                                            */
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

	/****************************
	 *		Public members
	 ****************************/

	template<class T, template<class> class H, class A>
	inline
	Set<T, H, A> :: Set () :
	Ancestor_() {
	}
	template<class T, template<class> class H, class A>
	inline
	Set<T, H, A> :: Set (const Index_ initialCapacity) :
	Ancestor_ (initialCapacity) {
	}
	template<class T, template<class> class H, class A>
	inline
	Set<T, H, A> :: Set (const Set& array) :
	Ancestor_ (array) {
	}
	template<class T, template<class> class H, class A>
	template<class T1, template<class> class H1>
	inline
	Set<T, H, A> :: Set (const typename continual :: Collection<T1, H1>& array) :
	Ancestor_ (array.getSize()) {
		unite (array);
	}
	template<class T, template<class> class H, class A>
	inline
	Set<T, H, A> :: Set (const Type_* const array, const Index_ size) :
	Ancestor_ (size) {
		unite (array, size);
	}
	template<class T, template<class> class H, class A>
	inline
	Set<T, H, A> :: ~ Set() {
	}

	template<class T, template<class> class H, class A>
	inline typename Set<T, H, A> :: Index_
	Set<T, H, A> :: add (Argument_ value)
	{
		if (find (value) != Undefined<Index_> :: getValue()) {
			return Undefined<Index_> :: getValue();
		}
		const bool reallocated = Ancestor_ :: ensureOneMoreElement();
		const Index_ index = findPlace (value);
		insert (value, index);
		if (reallocated) {
			Ancestor_ :: undefineTail();
		}
		return index;
	}
	template<class T, template<class> class H, class A>
	typename Set<T, H, A> :: Index_
	Set<T, H, A> :: find (Argument_ value) const
	{
		if (Ancestor_ :: isEmpty()) {
			return Undefined<Index_> :: getValue();
		}
		if (Ancestor_ :: size_ < LINEAR_SEARCH_THRESHOLD) {
			return Ancestor_ :: find (value);
		}
		int lowerBound = 0;
		int upperBound = Ancestor_ :: getSize() - 1;
		while (true) {
			//const int medium = static_cast<int> (round ((lowerBound + upperBound)/2));
			const int medium = static_cast<int> ((lowerBound + upperBound)/2 + 0.5);
			if (Ancestor_ :: data_ [medium] > value) {
				upperBound = medium - 1;
			} else if (Ancestor_ :: data_ [medium] < value) {
				lowerBound = medium + 1;
			} else {
				if (Ancestor_ :: data_ [medium] == value) {
					return medium;
				} else {
					return Undefined<Index_> :: getValue();
				}
			}
			if ((lowerBound > upperBound) || (upperBound < 0)) {
				return Undefined<Index_> :: getValue();
			}
		}
	}
	template<class T, template<class> class H, class A>
	typename Set<T, H, A> :: Index_
	Set<T, H, A> :: findPlace (Argument_ value) const
	{
		if (Ancestor_ :: isEmpty()) {
			return 0;
		} else if (Ancestor_ :: getSize() == 1) {
			if (Ancestor_ :: data_ [0] == value) {
				return 0; //Undefined<Index_> :: getValue();
			} else if (Ancestor_ :: data_ [0] < value) {
				return 1;
			} else {
				return 0;
			}
		}
		int lowerBound = 0;
		int upperBound = Ancestor_ :: getSize() - 1;
		if (Ancestor_ :: data_ [lowerBound] > value) {
			return 0;
		} else if (Ancestor_ :: data_ [upperBound] < value) {
			return Ancestor_ :: getSize();
		}
		while (true) {
			switch (upperBound - lowerBound) {
				case 1 :
					return upperBound;
				case 2 :
					if (Ancestor_ :: data_ [lowerBound + 1] < value) {
						return upperBound;
					} else {
						return upperBound - 1;
					}
			}
			//const int medium = static_cast<int> (round ((lowerBound + upperBound)/2));
			const int medium = static_cast<int> ((lowerBound + upperBound)/2 + 0.5);
			if (Ancestor_ :: data_ [medium] > value) {
				upperBound = medium;
			} else if (Ancestor_ :: data_ [medium + 1] < value) {
				lowerBound = medium + 1;
			} else {
				return medium + 1; //Undefined<Index_> :: getValue();
			}
		}
	}
	template<class T, template<class> class H, class A>
	inline bool
	Set<T, H, A> :: contains (Argument_ value) const
	{
		const Index_ index = find (value);
		return (index != Undefined<Index_> :: getValue());
	}
	template<class T, template<class> class H, class A>
	inline typename Set<T, H, A> :: Index_
	Set<T, H, A> :: addValue (Argument_ value) {
		return add (value);
	}
	template<class T, template<class> class H, class A>
	void
	Set<T, H, A> :: removeValue (Argument_ value)
	{
		const Index_ index = find (value);
		if (index != Undefined<Index_> :: getValue()) {
			Ancestor_ :: remove (index);
		}
	}
	template<class T, template<class> class H, class A>
	inline void
	Set<T, H, A> :: sort()
	{
		if (Ancestor_ :: getSize() > LINEAR_SEARCH_THRESHOLD) {
			qSort();
		} else {
			combSort();
		}
	}
	template<class T, template<class> class H, class A>
	inline void
	Set<T, H, A> :: qSort()
	{
		if (Ancestor_ :: getSize() == 0) {
			return;
		}
		quickSort (0, Ancestor_ :: getSize() - 1);
		#ifdef VERIFY_QUICK_SORT
		verify (true);
		#endif
	}
	template<class T, template<class> class H, class A>
	inline void
	Set<T, H, A> :: qSort (int (*compare) (Type_, Type_))
	{
		if (Ancestor_ :: getSize() == 0) {
			return;
		}
		quickSort (0, Ancestor_ :: getSize() - 1, compare);
		#ifdef VERIFY_QUICK_SORT
		verify (true);
		#endif
	}
	template<class T, template<class> class H, class A>
	inline void
	Set<T, H, A> :: combSort()
	{
		if (Ancestor_ :: getSize() == 0) {
			return;
		}
		// empirical optimal factor
		const double factor = 1.24733;

		const Index_ size = Ancestor_ :: getSize();
		Index_ jump = size;
        bool swapped = true;
        while ((jump > 1) || swapped) {
            if (jump > 1) {
                jump /= factor;
            }
            swapped = false;
            for (Index_ i = 0; i + jump < size; ++ i) {
                if (Ancestor_ :: data_ [i + jump] > Ancestor_ :: getValue (i)) {
                    Ancestor_ :: swap(i, i + jump);
                    swapped = true;
                }
            }
        }
		#ifdef VERIFY_SORT
		verify (true);
		#endif
	}

	template<class T, template<class> class H, class A>
	template<class T1, template<class> class H1>
	void
	Set<T, H, A> :: unite (const typename continual :: Collection<T1, H1>& array)
	{
		for (Index_ i = 0; i < array.getSize(); ++ i) {
			const Value_ value = array.getValue(i);
			add (value);
		}
	}
	template<class T, template<class> class H, class A>
	void
	Set<T, H, A> :: unite (const Type_* const array, const Index_ size)
	{
		for (Index_ i = 0; i < array.getSize(); ++ i) {
			const Value_ value = array [i];
			add (value);
		}
	}

	template<class T, template<class> class H, class A>
	template<class T1, template<class> class H1>
	inline void
	Set<T, H, A> :: intersect (const typename continual :: Collection<T1, H1>& collection) {
		intersectDirected<T1, H1, true> (collection);
	}
	template<class T, template<class> class H, class A>
	inline void
	Set<T, H, A> :: intersect (const Type_* const array, const Index_ size) {
		intersectDirected<true> (array, size);
	}
	template<class T, template<class> class H, class A>
	inline void
	Set<T, H, A> :: intersect (const Set& set)
	{
		if ((Ancestor_ :: size_ < INTERSECT_THRESHOLD)||
			(Ancestor_ :: size_ < set.getSize() * INTERSECT_FACTOR)) {
			intersectDirected<true> (set);
		} else {
			Set setCopy (set);
			setCopy.intersectDirected<true> (*this);
			Ancestor_ :: copy (setCopy);
		}
	}

	template<class T, template<class> class H, class A>
	template<class T1, template<class> class H1>
	void
	Set<T, H, A> :: subtract (const typename continual :: Collection<T1, H1>& collection)
	{
		for (Index_ i = 0; i < collection.getSize(); ++ i) {
			const Value_ value = collection [i];
			removeValue (value);
		}
	}
	template<class T, template<class> class H, class A>
	void
	Set<T, H, A> :: subtract (const Type_* const array, const Index_ size)
	{
		for (Index_ i = 0; i < size; ++ i) {
			const Value_ value = array [i];
			removeValue (value);
		}
	}
	template<class T, template<class> class H, class A>
	inline void
	Set<T, H, A> :: subtract (const Set& set) {
		intersectDirected<false> (set);
	}

	template<class T, template<class> class H, class A>
	void
	Set<T, H, A> :: insert (Argument_ value, const Index_ index) {
		Ancestor_ :: insert (value, index);
	}
	template<class T, template<class> class H, class A>
	inline bool
	Set<T, H, A> :: isDisjointed (const Set& set) const
	{
		if ((Ancestor_ :: size_ < INTERSECT_THRESHOLD)||
			(Ancestor_ :: size_ < set.getSize() * INTERSECT_FACTOR)) {
			return isDisjointedDirected (set);
		} else {
			return set.isDisjointedDirected (*this);
		}
	}

	template<class T, template<class> class H, class A>
	inline bool
	Set<T, H, A> :: verify (const bool strict) const
	{
		for (Index_ i = 0; i + 1 < Ancestor_ :: size_; ++ i) {
			const Value_ value_1 = Ancestor_ :: getValue (i);
			const Value_ value_2 = Ancestor_ :: getValue (i + 1);
			if (strict) {
				if (!(Ancestor_ :: data_ [i] < value_2)) {
					return false;
				}
			} else {
				if (!(Ancestor_ :: data_ [i] <= value_2)) {
					return false;
				}
			}
		}
		return true;
	}

	// nstd :: Object implementation
	template<class T, template<class> class H, class A>
	inline void
	Set<T, H, A> :: commitSuicide() {
		delete this;
	}
	template<class T, template<class> class H, class A>
	inline Size_t
	Set<T, H, A> :: getVolume() const {
		return Ancestor_ :: getVolume();
	}
	template<class T, template<class> class H, class A>
	inline Size_t
	Set<T, H, A> :: getRawVolume () const {
		return Ancestor_ :: getRawVolume();
	}
	template<class T, template<class> class H, class A>
	inline Size_t
	Set<T, H, A> :: getSizeOf() const {
		return sizeof (Set);
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class T, template<class> class H, class A>
	template<class T1, template<class> class H1, bool sign>
	void
	Set<T, H, A> :: intersectDirected (const typename continual :: Collection<T1, H1>& collection)
	{
		Index_ i = 0;
		while (i < Ancestor_ :: size_) {
			const Value_ value = Ancestor_ :: getValue (i);
			if (collection.contains (value) == sign) {
				++ i;
			} else {
				Ancestor_ :: remove (i);
			}
		}
	}
	template<class T, template<class> class H, class A>
	template<bool sign>
	void
	Set<T, H, A> :: intersectDirected (const Type_* const array, const Index_ size)
	{
		Index_ i = 0;
		while (i < Ancestor_ :: size_) {
			const Value_ value = Ancestor_ :: getValue (i);
			bool belongsToBoth = false;
			for (Index_ j = 0; j < size; ++ j) {
				if (value == array [j]) {
					++ i;
					belongsToBoth = true;
					break;
				}
			}
			if (belongsToBoth == sign) {
				++ i;
			} else {
				Ancestor_ :: remove (i);
			}
		}
	}
	template<class T, template<class> class H, class A>
	template<bool sign>
	void
	Set<T, H, A> :: intersectDirected (const Set& set)
	{
		Index_ i = 0;
		while (i < Ancestor_ :: size_) {
			const Value_ value = Ancestor_ :: getValue (i);
			if (set.contains (value) == sign) {
				++ i;
			} else {
				Ancestor_ :: remove (i);
			}
		}
	}

	template<class T, template<class> class H, class A>
	template<class T1, template<class> class H1>
	bool
	Set<T, H, A> :: isDisjointedDirected (const typename continual :: Collection<T1, H1>& collection) const
	{
		for (Index_ i = 0; i < Ancestor_ :: size_; ++ i) {
			const Value_ value = Ancestor_ :: getValue (i);
			if (collection.contains (value)) {
				return false;
			}
		}
		return true;
	}
	template<class T, template<class> class H, class A>
	bool
	Set<T, H, A> :: isDisjointedDirected (const Type_* const array, const Index_ size) const
	{
		for (Index_ i = 0; i < Ancestor_ :: size_; ++ i) {
			const Value_ value = Ancestor_ :: getValue (i);
			bool belongsToBoth = false;
			for (Index_ j = 0; j < size; ++ j) {
				if (value == array [j]) {
					++ i;
					belongsToBoth = true;
					break;
				}
			}
			if (belongsToBoth) {
				return false;
			}
		}
		return true;
	}
	template<class T, template<class> class H, class A>
	bool
	Set<T, H, A> :: isDisjointedDirected (const Set& set) const
	{
		for (Index_ i = 0; i < Ancestor_ :: size_; ++ i) {
			const Value_ value = Ancestor_ :: getValue (i);
			if (set.contains (value)) {
				return false;
			}
		}
		return true;
	}

	template<class T, template<class> class H, class A>
	void
	Set<T, H, A> :: quickSort (const int low, const int high)
	{
		if (low == high) {
			return;
		}
		int i = low;
		int j = high;
		const int mid = (low + high)/2;

		const Value_ valueLow = Ancestor_ :: getValue (low);
		const Value_ valueHigh = Ancestor_ :: getValue (high);
		const Value_ valueMid = Ancestor_ :: getValue (mid);

		// pivot element
		const Value_ mediana = valueMid;
		/*const Value_ mediana =
		 (Ancestor_ :: data_ [mid] < valueHigh) ?
			(
				(Ancestor_ :: data_ [low] < valueMid) ?
				valueMid :
				(
					(Ancestor_ :: data_ [high] < valueLow) ?
					valueHigh :
					valueLow
				)
			)
		:
			(
				(Ancestor_ :: data_ [mid] < valueLow) ?
				valueMid :
				(
					(Ancestor_ :: data_ [low] < valueHigh) ?
					valueHigh :
					valueLow
				)
			)
		;*/

		do {
			while (Ancestor_ :: data_ [i] < mediana) {
				++ i;
			}
			while (Ancestor_ :: data_ [j] > mediana) {
				-- j;
			}
			if (i <= j) {
				Ancestor_ :: swap (i, j);
				++ i;
				-- j;
			}
		} while (i < j);

		if (low < j) {
			quickSort (low, j);
		}
		if (i < high) {
			quickSort (i, high);
		}
	}
	template<class T, template<class> class H, class A>
	void
	Set<T, H, A> :: quickSort
	(
		const int low,
		const int high,
		int (*compare) (Type_, Type_)
	)
	{
		if (low == high) {
			return;
		}
		int i = low;
		int j = high;
		const int mid = (low + high)/2;

		// pivot element
		const Value_ mediana = Ancestor_ :: getValue (mid);
		do {
			while (compare (mediana , Ancestor_ :: getValue (i)) > 0) {
				++ i;
			}
			while (compare (mediana, Ancestor_ :: getValue (j)) < 0) {
				-- j;
			}
			if (i <= j) {
				Ancestor_ :: swap (i, j);
				++ i;
				-- j;
			}
		} while (i < j);

		if (low < j) {
			quickSort (low, j, compare);
		}
		if (i < high) {
			quickSort (i, high, compare);
		}
	}
}
}


