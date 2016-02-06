/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_Interval.cpp                                 */
/* Description:     template memory interval                                 */
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

	/****************************
	 *		Public members
	 ****************************/

	template<class T>
	inline
	Interval<T> :: Interval () :
	beg_ (NULL),
	end_ (NULL) {
	}
	template<class T>
	inline
	Interval<T> :: Interval (const Interval& interval) :
	beg_ (interval.beg_),
	end_ (interval.end_) {
	}
	template<class T>
	inline Interval<T> :: Interval (Type_* const beg, Type_* const end) :
	beg_ (beg),
	end_ (end) {
	}
	template<class T>
	inline Interval<T> :: Interval (Type_* const beg, const Size_t length)  :
	beg_ (beg),
	end_ (beg + length) {
	}

	template<class T>
	inline bool
	Interval<T> :: isClear() const
	{
		if ((beg_ == NULL) || (beg_ == end_)) {
			return true;
		}
		// Duff's device
		Byte_t* d = beg<Byte_t>();
		Ptrdiff_t c = getVolume();

		switch (c % 8)  /* c > 0 assumed */
		{
			case 0 : do { if (*d++ != '\0') return false;
			case 7 :      if (*d++ != '\0') return false;
			case 6 :      if (*d++ != '\0') return false;
			case 5 :      if (*d++ != '\0') return false;
			case 4 :      if (*d++ != '\0') return false;
			case 3 :      if (*d++ != '\0') return false;
			case 2 :      if (*d++ != '\0') return false;
			case 1 :      if (*d++ != '\0') return false;
			            } while ((c -= 8) > 0);
		}
		return true;
	}
	template<class T>
	inline bool
	Interval<T> :: isEmpty() const {
		return (beg_ == end_);
	}
	template<class T>
	inline bool
	Interval<T> :: isNull() const {
		return (beg_ == NULL) || (end_ == NULL);
	}
	template<class T>
	inline bool
	Interval<T> :: isRegular() const {
		return !isNull() && !isEmpty() && isValid();
	}
	template<class T>
	inline bool
	Interval<T> :: isValid() const {
		return (beg_ <= end_);
	}

	template<class T>
	inline bool
	Interval<T> :: operator == (const Interval& interval) const {
		return isEqual (interval);
	}
	template<class T>
	inline bool
	Interval<T> :: operator != (const Interval& interval) const {
		return !isEqual (interval);
	}
	template<class T>
	inline bool
	Interval<T> :: isEqual (const Interval& interval) const
	{
		return
			(beg_ == interval.beg()) &&
			(end_ == interval.end());
	}
	template<class T>
	inline bool
	Interval<T> :: isDisjointed (const Interval& interval) const
	{
		return
			(end_ < interval.beg()) ||
			(interval.end() < beg_);
	}
	template<class T>
	inline bool
	Interval<T> :: intersectsWith (const Interval& interval) const
	{
		const Type_* intersectionBeg = (interval.beg() < beg_ ? beg_ : interval.beg());
		const Type_* intersectionEnd = (interval.end() > end_ ? end_ : interval.end());
		return (intersectionBeg < intersectionEnd);
	}
	template<class T>
	inline bool
	Interval<T> :: contains (const Type_* pointer) const
	{
		return
			!isEmpty() &&
			(beg_ <= pointer) &&
			(pointer < end_);
	}
	template<class T>
	inline bool
	Interval<T> :: contains (const void* pointer) const {
		return contains (reinterpret_cast<const Type_*>(pointer));
	}

	template<class T>
	inline typename Interval<T> :: Type_* const
	Interval<T> :: beg() const {
		return beg_;
	}
	template<class T>
	inline typename Interval<T> :: Type_* const
	Interval<T> :: end() const {
		return end_;
	}

	template<class T>
	inline void
	Interval<T> :: operator = (const Interval& interval) {
		copy (interval);
	}
	template<class T>
	inline void
	Interval<T> :: copy (const Interval& interval)
	{
		beg_ = interval.beg();
		end_ = interval.end();
	}

	template<class T>
	inline void
	Interval<T> :: shiftBeg (const Size_t index) {
		beg_ += index;
	}
	template<class T>
	inline void
	Interval<T> :: shiftEnd (const Size_t index) {
		end_ += index;
	}

	template<class T>
	inline void
	Interval<T> :: setBeg (Type_* const beg) {
		beg_ = beg;
	}
	template<class T>
	inline void
	Interval<T> :: setEnd (Type_* const end) {
		end_ = end;
	}
	template<class T>
	inline void
	Interval<T> :: setNull ()
	{
		beg_ = NULL;
		end_ = NULL;
	}

	template<class T>
	void
	Interval<T> :: verify() const
	{
		if (!isValid()) {
			throw exception :: Exception ("invalid memory interval");
		}
	}

	template<class T>
	inline Interval<>
	Interval<T> :: byteRepresentation() const
	{
		return Interval<>
		(
			reinterpret_cast<Byte_t*> (beg_),
			reinterpret_cast<Byte_t*> (end_)
		);
	}

	// interval integer parameters
	template<class T>
	inline Size_t
	Interval<T> :: getLength() const {
		return end_ - beg_;
	}
	template<class T>
	inline Size_t
	Interval<T> :: getVolume() const {
		return sizeof (T) * getLength();
	}
	template<class T>
	inline Size_t
	Interval<T> :: getSizeOf() const {
		return sizeof (Interval);
	}

	template<class T>
	template<class S>
	inline void
	Interval<T> :: show (S& string) const
	{
		if (isNull()) {
			string << "NULL";
			return;
		}
		if (isEmpty()) {
			string << "empty ";
		}
		string << "begin = " << beg<void>() << ", ";
		string << "end = " << end<void>() << ", ";
		if (getVolume() == getLength()) {
			string << "byte volume = " << getVolume() << " ";
		} else {
			string << "byte volume = " << getVolume() << ", ";
			string << "array length = " << getLength()<< " ";
		}
	}
	template<class T>
	template<class S>
	inline void
	Interval<T> :: showContents (S& string) const
	{
		if (isNull() || isEmpty()) {
			return;
		}
		Byte_t* b = beg<Byte_t>();
		Byte_t* e = end<Byte_t>();

		while (b != e) {
			string << *b << "(";
			string << static_cast<int>(*b) << "), ";
			++ b;
		}
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class T>
	template<class T_1>
	inline
	Interval<T> :: Interval (const Interval<T_1>& interval) :
	beg_ (interval.template beg<Type_>()),
	end_ (interval.template end<Type_>())
	{
		if (getVolume() != interval.getVolume()) {
			throw exception :: Exception ("incorrect interval initialization.");
		}
	}

	template<class T>
	inline void
	Interval<T> :: allocateScalar (const Size_t size) throw (exception :: OutOfMemory)
	{
		if (beg_ != NULL) {
			throw exception :: Exception ("double interval allocation.");
		}
		beg_  = reinterpret_cast<Type_*>(new Byte_t [size]);
		end_  = (beg_ + 1);
		if ((size > 0) && (beg_ == NULL)) {
			throw exception :: OutOfMemory();
		}
		clear();
	}
	template<class T>
	inline void
	Interval<T> :: allocateVector (const Size_t length) throw (exception :: OutOfMemory)
	{
		if (beg_ != NULL) {
			throw exception :: Exception ("double interval allocation.");
		}
		beg_  = (length == 0) ? NULL : new Type_ [length];
		end_  = (length == 0) ? NULL : (beg_ + length);
		if ((length > 0) && (beg_ == NULL)) {
			throw exception :: OutOfMemory();
		}
		clear();
	}

	template<class T>
	template<class S>
	inline S* const
	Interval<T> :: beg() const {
		return reinterpret_cast<S*> (beg_);
	}
	template<class T>
	template<class S>
	inline S* const
	Interval<T> :: end() const {
		return reinterpret_cast<S*> (end_);
	}

	template<class T>
	template<class S>
	inline void
	Interval<T> :: operator = (const Interval<S>& interval) {
		copy (interval);
	}
	template<class T>
	template<class S>
	inline void
	Interval<T> :: copy (const Interval<S>& interval)
	{
		beg_ = reinterpret_cast<Type_*> (interval.beg());
		end_ = reinterpret_cast<Type_*> (interval.end());
	}

	template<class T>
	inline void
	Interval<T> :: empty() {
		end_ = beg_;
	}
	template<class T>
	void
	Interval<T> :: clear()
	{
		if ((beg_ == NULL) || (beg_ == end_)) {
			return;
		}
		// Duff's device
		Byte_t* d = beg<Byte_t>();
		Ptrdiff_t c = getVolume();

		switch (c % 8)  /* c > 0 assumed */
		{
			case 0 : do { *d++ = '\0';
			case 7 :      *d++ = '\0';
			case 6 :      *d++ = '\0';
			case 5 :      *d++ = '\0';
			case 4 :      *d++ = '\0';
			case 3 :      *d++ = '\0';
			case 2 :      *d++ = '\0';
			case 1 :      *d++ = '\0';
			            } while ((c -= 8) > 0);
		}
	}
	template<class T>
	inline void
	Interval<T> :: destroy ()
	{
		if (beg_ != NULL) {
			delete[] beg_;
			setNull();
		}
	}

	/****************************
	 *		Operators
	 ****************************/

	template<class T, class S>
	inline S&
	operator << (S& s, Interval<T> interval)
	{
		interval.show (s);
		return s;
	}

	template<class T>
	inline bool
	operator <= (const Interval<T>& interval_1, const Interval<T>& interval_2) {
		return interval_1.beg() <= interval_2.beg();
	}
	template<class T>
	inline bool
	operator < (const Interval<T>& interval_1, const Interval<T>& interval_2) {
		return interval_1.beg() < interval_2.beg();
	}
	template<class T>
	inline bool
	operator >= (const Interval<T>& interval_1, const Interval<T>& interval_2) {
		return operator <= (interval_2, interval_1);
	}
	template<class T>
	inline bool
	operator > (const Interval<T>& interval_1, const Interval<T>& interval_2) {
		return operator < (interval_2, interval_1);
	}

	/*template<class T>
	inline bool
	operator <= (const Interval<T>& interval_1, const Interval<T>& interval_2) {
		return interval_1.end() - 1 <= interval_2.beg();
	}
	template<class T>
	inline bool
	operator < (const Interval<T>& interval_1, const Interval<T>& interval_2) {
		return interval_1.end() - 1 < interval_2.beg();
	}
	template<class T>
	inline bool
	operator >= (const Interval<T>& interval_1, const Interval<T>& interval_2) {
		return operator <= (interval_2, interval_1);
	}
	template<class T>
	inline bool
	operator > (const Interval<T>& interval_1, const Interval<T>& interval_2) {
		return operator < (interval_2, interval_1);
	}*/
}
}


