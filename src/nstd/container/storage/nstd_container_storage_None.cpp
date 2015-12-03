/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_container_storage_None.cpp                          */
/* Description:     speculative storage policy                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_CONTAINER_STORAGE_NONE_CPP_
#define NSTD_CONTAINER_STORAGE_NONE_CPP_

namespace nstd {
namespace container {
namespace storage {

	/****************************
	 *		Public members
	 ****************************/

	template<class T>
	inline
	None<T> :: None() {
	}
	template<class T>
	inline
    None<T> :: None (Argument_) {
    }
	template<class T>
	inline
    None<T> :: None (const None&) {
	}
	template<class T>
	inline
    None<T> :: ~ None() {
	}

	template<class T>
    inline bool
    None<T> :: operator == (const None&) const {
		return true;
	}
	template<class T>
	inline bool
	None<T> :: operator != (const None&) const {
		return false;
	}
	template<class T>
	inline void
	None<T> :: operator = (const None&) {
	}

	template<class T>
    inline void
    None<T> :: undefine() {
	}
	template<class T>
	inline void
	None<T> :: clear() {
	}
	template<class T>
	inline void
	None<T> :: erase() {
	}
	template<class T>
	inline void
	None<T> :: init() {
	}

	// nstd :: Object implementation
	template<class T>
	inline void
	None<T> :: commitSuicide() {
	}
	template<class T>
	inline Size_t
	None<T> :: getVolume() const {
		return 0;
	}
	template<class T>
	inline Size_t
	None<T> :: getSizeOf() const {
		return sizeof (None);
	}
	template<class T>
	template<class S>
	void
	None<T> :: show (S&) const {
	}

	/****************************
	 *		Overloaded operators
	 ****************************/

	template<class T, class S>
	S&
	operator << (S& s, const None<T>& storage)
	{
		storage.show (s);
		return s;
	}
}
}
}

#endif /*NSTD_CONTAINER_STORAGE_NONE_CPP_*/
