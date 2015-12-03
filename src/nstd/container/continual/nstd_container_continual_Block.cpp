/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_container_continual_Block.cpp                       */
/* Description:     array container for long vector                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_CONTAINER_CONTINUAL_BLOCK_CPP_
#define NSTD_CONTAINER_CONTINUAL_BLOCK_CPP_

namespace nstd {
namespace container {
namespace continual {

	/****************************
	 *		Public members
	 ****************************/

	template<class T, template<class> class H, class A, Size_t C>
	inline
	Block<T, H, A, C> :: Block () :
	Ancestor_ () {
	}
	template<class T, template<class> class H, class A, Size_t C>
	inline
	Block<T, H, A, C> :: Block (const Block& block) :
	Ancestor_ (block)
	{
		init();
		copy (block);
	}
	template<class T, template<class> class H, class A, Size_t C>
	Block<T, H, A, C> :: ~Block ()
	{
		const memory :: Interval<Storage_>
			interval = memory :: Interval<Storage_>
			(
				Ancestor_ :: data_,
				Ancestor_ :: size_
			);
		Memory_ :: disposeArray (interval);
	}

	template<class T, template<class> class H, class A, Size_t C>
	void
	Block<T, H, A, C> :: init ()
	{
		if (Ancestor_ :: data_ != NULL) {
			std :: cout << "double initialization of continual block container" << std :: endl;
			throw std :: exception();
		}
		const memory :: Interval<Storage_>
			interval = Memory_ :: allocateArray (CAPACITY);
		Ancestor_ :: data_ = interval.beg();
		undefineBlock();
	}

	template<class T, template<class> class H, class A, Size_t C>
	inline void
	Block<T, H, A, C> :: operator = (const Block& block)
	{
		init();
		copy (block);
	}

	template<class T, template<class> class H, class A, Size_t C>
	inline void
	Block<T, H, A, C> :: add (Argument_ value)  {
		Ancestor_ :: data_ [Ancestor_ :: size_ ++] = value;
	}

	template<class T, template<class> class H, class A, Size_t C>
	inline typename Block<T, H, A, C> :: Reference_
	Block<T, H, A, C> :: pushRaw () {
		return Ancestor_ :: data_ [Ancestor_ :: size_ ++].getReference();
	}
	template<class T, template<class> class H, class A, Size_t C>
	inline typename Block<T, H, A, C> :: Reference_
	Block<T, H, A, C> :: push ()
	{
		Storage_&
			storage = Ancestor_ :: data_ [Ancestor_ :: size_ ++];
		storage.init();
		return storage.getReference();
	}

	template<class T, template<class> class H, class A, Size_t C>
	inline typename Block<T, H, A, C> :: Storage_&
	Block<T, H, A, C> :: pushRawNode ()  {
		return Ancestor_ :: data_ [Ancestor_ :: size_ ++];
	}
	template<class T, template<class> class H, class A, Size_t C>
	inline typename Block<T, H, A, C> :: Storage_&
	Block<T, H, A, C> :: pushNode ()
	{
		typename Ancestor_ :: NodeReference_
			node = Ancestor_ :: data_ [Ancestor_ :: size_ ++];
		node.init();
		return node;
	}

	template<class T, template<class> class H, class A, Size_t C>
	inline typename Block<T, H, A, C> :: Index_
	Block<T, H, A, C> :: getCapacity() const {
		return CAPACITY;
	}

	template<class T, template<class> class H, class A, Size_t C>
	inline bool
	Block<T, H, A, C> :: isFull () const {
		return (CAPACITY == Ancestor_ :: size_);
	}

	// nstd :: Object implementation
	template<class T, template<class> class H, class A, Size_t C>
	inline void
	Block<T, H, A, C> :: commitSuicide() {
		delete this;
	}
	template<class T, template<class> class H, class A, Size_t C>
	Size_t
	Block<T, H, A, C> :: getVolume() const
	{
		Size_t volume = 0;
		volume += getRawVolume ();
		for (Index_ i = 0; i < CAPACITY; i++) {
			volume += Ancestor_ :: data_[i].getVolume();
		}
		return volume;
	}
	template<class T, template<class> class H, class A, Size_t C>
	Size_t
	Block<T, H, A, C> :: getRawVolume () const {
		return CAPACITY * sizeof (Storage_);
	}
	template<class T, template<class> class H, class A, Size_t C>
	Size_t
	Block<T, H, A, C> :: getSizeOf() const {
		return sizeof (Block);
	}

	/****************************
	 *		Protected members
	 ****************************/

	template<class T, template<class> class H, class A, Size_t C>
	void
	Block<T, H, A, C> :: undefineBlock()
	{
		// Duff's device
		Storage_*
			data = Ancestor_ :: data_;
		long count = CAPACITY;
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

#endif /*NSTD_CONTAINER_CONTINUAL_BLOCK_CPP_*/
