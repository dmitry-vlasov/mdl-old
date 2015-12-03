/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_container_Vector.cpp                                */
/* Description:     vector (mutable in size) container                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_CONTAINER_VECTOR_CPP_
#define NSTD_CONTAINER_VECTOR_CPP_

namespace nstd {
namespace container {

	/****************************
	 *		Public members
	 ****************************/

	template<class T, template<class> class H, class A>
	Vector<T, H, A> :: Vector() :
	Ancestor_() {
	}
	template<class T, template<class> class H, class A>
	Vector<T, H, A> :: Vector (const Index_ initialCapacity) :
	Ancestor_ (initialCapacity) {
	}
	template<class T, template<class> class H, class A>
	Vector<T, H, A> :: Vector (const Vector& array) :
	Ancestor_ (array) {
	}
	template<class T, template<class> class H, class A>
	template<class T1, template<class> class H1>
	Vector<T, H, A> :: Vector (const typename continual :: Collection<T1, H1>& array) :
	Ancestor_ (array) {
	}
	template<class T, template<class> class H, class A>
	Vector<T, H, A> :: Vector
	(
		const Type_* const array,
		const Index_ size
	) :
	Ancestor_ (array, size) {
	}
	template<class T, template<class> class H, class A>
	Vector<T, H, A> :: ~ Vector() {
	}

	template<class T, template<class> class H, class A>
	typename Vector<T, H, A> :: Index_
	Vector<T, H, A> :: add (Argument_ value)
	{
		const bool reallocated = Ancestor_ :: ensureOneMoreElement();
		const Index_ index = Ancestor_ :: size_;
		Ancestor_ :: getReference (Ancestor_ :: size_ ++) = value;
		if (reallocated) {
			Ancestor_ :: undefineTail();
		}
		return index;
	}
	template<class T, template<class> class H, class A>
	void
	Vector<T, H, A> :: insert (Argument_ value, const Index_ index)
	{
		const bool reallocated = Ancestor_ :: ensureOneMoreElement();
		for (Index_ i = Ancestor_ :: size_; i > index; i --) {
			const Value_
				value = Ancestor_ :: getValue (i - 1);
			Ancestor_ :: getReference (i) = value;
		}
		Ancestor_ :: size_ ++;
		Ancestor_ :: getReference (index) = value;
		if (reallocated) {
			Ancestor_ :: undefineTail();
		}
	}
	template<class T, template<class> class H, class A>
	void
	Vector<T, H, A> :: insertNextTo (Argument_ value, const Argument_ sibling)
	{
		const Index_ index = Ancestor_ :: find (sibling);
		if (index == Undefined<Index_> :: getValue()) {
			add (value);
		} else {
			insert (value, index + 1);
		}
	}
	template<class T, template<class> class H, class A>
	void
	Vector<T, H, A> :: insertPreviousTo (Argument_ value, const Argument_ sibling)
	{
		const Index_ index = Ancestor_ :: find (sibling);
		if (index == Undefined<Index_> :: getValue()) {
			add (value);
		} else {
			insert (value, index);
		}
	}
	template<class T, template<class> class H, class A>
	void
	Vector<T, H, A> :: shiftToEnd (const Index_ i)
	{
		if (i == Ancestor_ :: size_ - 1) {
			return;
		}
		const Value_ value = Ancestor_ :: getValue (i);
		Ancestor_ :: memMove
		(
			Ancestor_ :: data_ + i,
			Ancestor_ :: data_ + i + 1,
			Ancestor_ :: size_ - i - 1
		);
		Ancestor_ :: getLastReference() = value;
	}

	template<class T, template<class> class H, class A>
	inline typename Vector<T, H, A> :: Reference_
	Vector<T, H, A> :: pushRaw()
	{
		const bool reallocated = Ancestor_ :: ensureOneMoreElement();
		Reference_
			result = Ancestor_ :: getReference (Ancestor_ :: size_ ++);
		if (reallocated) {
			Ancestor_ :: undefineTail();
		}
		return result;
	}
	template<class T, template<class> class H, class A>
	inline typename Vector<T, H, A> :: Reference_
	Vector<T, H, A> :: push() {
		return pushLast();
	}
	template<class T, template<class> class H, class A>
	inline typename Vector<T, H, A> :: Reference_
	Vector<T, H, A> :: pushLast()
	{
		const bool reallocated = Ancestor_ :: ensureOneMoreElement();
		Storage_&
			storage = Ancestor_ :: data_ [Ancestor_ :: size_ ++];
		storage.init();
		if (reallocated) {
			Ancestor_ :: undefineTail();
		}
		return storage.getReference();
	}
	template<class T, template<class> class H, class A>
	inline typename Vector<T, H, A> :: Reference_
	Vector<T, H, A> :: pushFirst()
	{
		const bool reallocated = Ancestor_ :: ensureOneMoreElement();
		if (Ancestor_ :: size_ > 0) {
			Ancestor_ :: memMove
			(
				Ancestor_ :: data_ + Ancestor_ :: size_,
				Ancestor_ :: data_ + Ancestor_ :: size_ - 1,
				Ancestor_ :: size_,
				true
			);
		}
		++ Ancestor_ :: size_;
		Storage_&
			storage = Ancestor_ :: data_ [0];
		storage.undefine();
		storage.init();
		if (reallocated) {
			Ancestor_ :: undefineTail();
		}
		return storage.getReference();
	}
	template<class T, template<class> class H, class A>
	inline typename Vector<T, H, A> :: Value_
	Vector<T, H, A> :: popLast()
	{
		Value_ result = Ancestor_ :: getLastValue();
		Ancestor_ :: removeLast();
		return result;
	}
	template<class T, template<class> class H, class A>
	inline typename Vector<T, H, A> :: Value_
	Vector<T, H, A> :: popFirst()
	{
		Value_ result = Ancestor_ :: getFirstValue();
		Ancestor_ :: removeFirst();
		return result;
	}

	template<class T, template<class> class H, class A>
	inline typename Vector<T, H, A> :: Reference_
	Vector<T, H, A> :: pop()
	{
		Reference_ result = Ancestor_ :: getReference (-- Ancestor_ :: size_);
		//Ancestor_ :: data_ [Ancestor_ :: size_].undefine();
		return result;
	}
	template<class T, template<class> class H, class A>
	inline typename Vector<T, H, A> :: const_Reference_
	Vector<T, H, A> :: pop() const
	{
		const_Reference_ result = Ancestor_ :: getReference (-- Ancestor_ :: size_);
		//Ancestor_ :: data_ [Ancestor_ :: size_].undefine();
		return result;
	}

	template<class T, template<class> class H, class A>
	inline void
	Vector<T, H, A> :: operator = (const Vector& vector) {
		Ancestor_ :: copy (vector);
	}
	template<class T, template<class> class H, class A>
	template<class T1, template<class> class H1>
	inline void
	Vector<T, H, A> :: operator = (const typename continual :: Collection<T1, H1>& collection) {
		Ancestor_ :: copy (collection);
	}
	template<class T, template<class> class H, class A>
	template<class T1, template<class> class H1>
	inline Vector<T, H, A>&
	Vector<T, H, A> :: operator << (const typename continual :: Collection<T1, H1>& array)
	{
		append (array);
		return *this;
	}
	template<class T, template<class> class H, class A>
	inline Vector<T, H, A>&
	Vector<T, H, A> :: operator << (Vector& (*manip)(Vector&) ) {
		return manip (*this);
	}
	template<class T, template<class> class H, class A>
	template<class T1, template<class> class H1>
	void
	Vector<T, H, A> :: append (const typename continual :: Collection<T1, H1>& array)
	{
		const Index_ startPoint = Ancestor_ :: size_;
		Ancestor_ :: size_ += array.getSize();
		const bool reallocated = Ancestor_ :: ensureCapacityNotLess (Ancestor_ :: size_ + 1);
		Ancestor_ :: template memMove<typename continual :: Collection<T1, H1> :: Storage_>
			(
				Ancestor_ :: data_ + startPoint,
				array.getData(),
				array.getSize()
			);
		Ancestor_ :: data_ [Ancestor_ :: size_].undefine();
		if (reallocated) {
			Ancestor_ :: undefineTail();
		}
	}
	template<class T, template<class> class H, class A>
	void
	Vector<T, H, A> :: append
	(
		const Type_* const array,
		const Index_ size
	)
	{
		const Index_ startPoint = Ancestor_ :: size_;
		Ancestor_ :: size_ += size;
		const bool reallocated = Ancestor_ :: ensureCapacityNotLess (Ancestor_ :: size_ + 1);
		Ancestor_ :: memMove
			(
				Ancestor_ :: data_ + startPoint,
				array,
				size
			);
		Ancestor_ :: data_ [Ancestor_ :: size_].undefine();
		if (reallocated) {
			Ancestor_ :: undefineTail();
		}
	}

	// nstd :: Object implementation
	template<class T, template<class> class H, class A>
	inline void
	Vector<T, H, A> :: commitSuicide() {
		delete this;
	}
	template<class T, template<class> class H, class A>
	inline Size_t
	Vector<T, H, A> :: getVolume() const {
		return Ancestor_ :: getVolume();
	}
	template<class T, template<class> class H, class A>
	inline Size_t
	Vector<T, H, A> :: getRawVolume () const {
		return Ancestor_ :: getRawVolume();
	}
	template<class T, template<class> class H, class A>
	inline Size_t
	Vector<T, H, A> :: getSizeOf() const {
		return sizeof (Vector);
	}
}
}

#endif /*NSTD_CONTAINER_VECTOR_CPP_*/
