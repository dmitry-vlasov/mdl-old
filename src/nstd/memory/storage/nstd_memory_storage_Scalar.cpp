/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_storage_Scalar.cpp                           */
/* Description:     scalar memory storage                                    */
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
namespace storage {

	/*************************
	 *		Public members
	 *************************/

	template<class T, class A>
	inline void*
	Scalar<T, A> :: operator new (const Size_t size)
	{
		typedef T Type;
		const Interval<>
			interval = Allocator_ :: template allocateScalar<Type> (size);
		return interval.beg();
	}
	/* the array allocator does not work properly
	 * with the memory manager. For this reason it is
	 * switched off.
	 *
	template<class T, class A>
	inline void*
	Scalar<T, A> :: operator new[] (const Size_t size)
	{
		const Size_t
			length = (size - sizeof (Size_t)) / sizeof (T);
		const Interval<>
			interval = Allocator_ :: template allocate<Byte_t> (size);
		Size_t* initial = reinterpret_cast<Size_t*>(interval.beg());
		*initial = length;
		++ initial;
		return initial;
	}*/
	template<class T, class A>
	inline void*
	Scalar<T, A> :: operator new (const Size_t size, void* place) {
		return place;
	}
	/* the array allocator does not work properly
	 * with the memory manager. For this reason it is
	 * switched off.
	 *
	template<class T, class A>
	inline void*
	Scalar<T, A> :: operator new[] (const Size_t size, void* place) {
		return place;
	}*/
	template<class T, class A>
	inline void
	Scalar<T, A> :: operator delete (void* space)
	{
		if (space == NULL) {
			return;
		}
		Byte_t* beg = reinterpret_cast<Byte_t*>(space);
		const Size_t size = sizeof (Type_);
		Interval<> interval = Interval<>(beg, size);
		Allocator_ :: template dispose<>(interval);
	}
	/* the array allocator does not work properly
	 * with the memory manager. For this reason it is
	 * switched off.
	 *
	template<class T, class A>
	inline void
	Scalar<T, A> :: operator delete[] (void* array)
	{
		if (array == NULL) {
			return;
		}
		Size_t* space = reinterpret_cast<Size_t*>(array);
		-- space;
		const Size_t length = *space;
		const Size_t size = sizeof (Type_) * length + sizeof (Size_t);
		//destroyContents (array, length);
		destroyArray (space, size);
	}*/

	/*************************
	 *		Private members
	 *************************/

	template<class T, class A>
	inline void
	Scalar<T, A> :: destroyContents (void* array, const Size_t length)
	{
		Type_* object = reinterpret_cast<Type_*>(array) + (length - 1);
		for (Size_t i = 0; i < length; ++ i) {
			object->commitSuicide();
			-- object;
		}
	}
	template<class T, class A>
	inline void
	Scalar<T, A> :: destroyArray (void* space, const Size_t size)
	{
		Byte_t* beg = reinterpret_cast<Byte_t*>(space);
		Interval<> interval = Interval<>(beg, size);
		Allocator_ :: template dispose<>(interval);
	}
}
}
}


