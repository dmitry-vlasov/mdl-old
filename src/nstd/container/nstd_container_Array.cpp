/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_container_Array.cpp                                 */
/* Description:     array (immutable in size) container                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_CONTAINER_ARRAY_CPP_
#define NSTD_CONTAINER_ARRAY_CPP_

namespace nstd {
namespace container {

	/****************************
	 *		Public members
	 ****************************/

	template<class T, template<class> class H, class A>
	inline
	Array<T, H, A> :: Array (const Index_ size) :
	Ancestor_ ()
	{
		Ancestor_ :: size_ = size;
		const memory :: Interval<Storage_>
			interval = Memory_ :: allocateArray (size + 1);
		Ancestor_ :: data_ = interval.beg();
		Ancestor_ :: undefineArray();
	}
	template<class T, template<class> class H, class A>
	Array<T, H, A> :: Array (const Ancestor_& array) :
	Ancestor_ (array)
	{
		const memory :: Interval<Storage_>
			interval = Memory_ :: allocateArray (Ancestor_ :: size_ + 1);
		Ancestor_ :: data_ = interval.beg();
		Ancestor_ :: copy (array);
		Ancestor_ :: data_ [Ancestor_ :: size_] = Undefined<Storage_> :: getValue();
	}
	template<class T, template<class> class H, class A>
	Array<T, H, A> :: Array (const Array& array) :
	Ancestor_ (array)
	{
		const memory :: Interval<Storage_>
			interval = Memory_ :: allocateArray (Ancestor_ :: size_ + 1);
		Ancestor_ :: data_ = interval.beg();
		Ancestor_ :: copy (array);
		Ancestor_ :: data_ [Ancestor_ :: size_] = Undefined<Storage_> :: getValue();
	}
	template<class T, template<class> class H, class A>
	inline
	Array<T, H, A> :: Array
	(
		const Type_ array [],
		const Index_ size
	) :
	Ancestor_ ()
	{
		Ancestor_ :: size_ = size;
		const memory :: Interval<Storage_>
			interval = Memory_ :: allocateArray (Ancestor_ :: size_ + 1);
		Ancestor_ :: data_ = interval.beg();
		Ancestor_ :: copy (array, size);
		Ancestor_ :: data_ [Ancestor_ :: size_] = Undefined<Storage_> :: getValue();
	}
	template<class T, template<class> class H, class A>
	Array<T, H, A> :: ~ Array()
	{
		if (Ancestor_ :: data_ == NULL) {
			return;
		}
		for (Index_ i = 0; i < Ancestor_ :: size_ + 1; ++ i) {
			Ancestor_ :: data_[Ancestor_ :: size_ - i].commitSuicide();
		}
		const memory :: Interval<Storage_>
			interval = memory :: Interval<Storage_>
			(
				Ancestor_ :: data_,
				Ancestor_ :: size_ + 1
			);
		Memory_ :: disposeArray (interval);
		Ancestor_ :: data_ = NULL;
	}

	template<class T, template<class> class H, class A>
	inline void
	Array<T, H, A> :: copy (const Array& array)
	{
		if (Ancestor_ :: size_ != array.getSize()) {
			throw std :: exception();
		}
		Ancestor_ :: copy (array);
	}

	// nstd :: Object implementation
	template<class T, template<class> class H, class A>
	inline void
	Array<T, H, A> :: commitSuicide() {
		delete this;
	}
	template<class T, template<class> class H, class A>
	inline Size_t
	Array<T, H, A> :: getVolume() const {
		return Ancestor_ :: getVolume();
	}
	template<class T, template<class> class H, class A>
	inline Size_t
	Array<T, H, A> :: getRawVolume () const {
		return Ancestor_ :: getRawVolume();
	}
	template<class T, template<class> class H, class A>
	inline Size_t
	Array<T, H, A> :: getSizeOf() const {
		return sizeof (Array);
	}
}
}

#endif /*NSTD_CONTAINER_ARRAY_CPP_*/
