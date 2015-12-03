/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_container_storage_ByValue.cpp                       */
/* Description:     storage policy by value for containers                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_CONTAINER_STORAGE_BY_VALUE_CPP_
#define NSTD_CONTAINER_STORAGE_BY_VALUE_CPP_

namespace nstd {
namespace container {
namespace storage {

	/****************************
	 *		Public members
	 ****************************/

	template<class T>
	inline
	ByValue<T> :: ByValue() :
	Ancestor_ () {
	}
	template<class T>
	inline
	ByValue<T> :: ByValue (typename Ancestor_ :: Argument_ data) :
	Ancestor_ (data) {
	}
	template<class T>
	inline
	ByValue<T> :: ByValue (const ByValue& storage) :
	Ancestor_ (storage) {
	}
	template<class T>
	inline
	ByValue<T> :: ~ByValue () {
		Ancestor_ :: data_.~ Type_();
	}

	template<class T>
	inline void
	ByValue<T> :: clear() {
		Ancestor_ :: undefine();
	}
	template<class T>
	inline void
	ByValue<T> :: erase() {
		Ancestor_ :: undefine();
	}
	template<class T>
	inline void
	ByValue<T> :: init() {
	}

	// operators with Argument_ implementation
	template<class T>
	inline bool
	ByValue<T> :: operator == (Argument_ data) const {
		return (Ancestor_ :: operator == (data));
	}
	template<class T>
	inline bool
	ByValue<T> :: operator != (Argument_ data) const {
		return !(operator == (data));
	}
	template<class T>
	inline bool
	ByValue<T> :: operator < (Argument_ data) const {
		return (Ancestor_ :: operator < (data));
	}
	template<class T>
	inline bool
	ByValue<T> :: operator <= (Argument_ data) const {
		return (Ancestor_ :: operator <= (data));
	}
	template<class T>
	inline bool
	ByValue<T> :: operator > (Argument_ data) const {
		return (Ancestor_ :: operator > (data));
	}
	template<class T>
	inline bool
	ByValue<T> :: operator >= (Argument_ data) const {
		return (Ancestor_ :: operator >= (data));
	}
	template<class T>
	inline void
	ByValue<T> :: operator = (Argument_ data) {
		Ancestor_ :: data_ = data;
	}

	// operators with ByValue implementation
	template<class T>
	inline bool
	ByValue<T> :: operator == (const ByValue& storage) const {
		return (Ancestor_ :: operator == (storage));
	}
	template<class T>
	inline bool
	ByValue<T> :: operator != (const ByValue& storage) const {
		return !(operator == (storage));
	}
	template<class T>
	inline bool
	ByValue<T> :: operator < (const ByValue& storage) const {
		return (Ancestor_ :: operator < (storage));
	}
	template<class T>
	inline bool
	ByValue<T> :: operator <= (const ByValue& storage) const {
		return (Ancestor_ :: operator <= (storage));
	}
	template<class T>
	inline bool
	ByValue<T> :: operator > (const ByValue& storage) const {
		return (Ancestor_ :: operator > (storage));
	}
	template<class T>
	inline bool
	ByValue<T> :: operator >= (const ByValue& storage) const {
		return (Ancestor_ :: operator >= (storage));
	}
	template<class T>
	inline void
	ByValue<T> :: operator = (const ByValue& storage) {
		Ancestor_ :: operator = (storage);
    }

	// nstd :: Object implementation
	template<class T>
	inline void
	ByValue<T> :: commitSuicide() {
		Ancestor_ :: data_.~ Type_();
	}
	template<class T>
	inline Size_t
	ByValue<T> :: getVolume() const {
		return 0;
	}
	template<class T>
	inline Size_t
	ByValue<T> :: getSizeOf() const {
		return sizeof (ByValue);
	}
	template<class T>
	template<class S>
	void
	ByValue<T> :: show (S& string) const {
		string << Ancestor_ :: data_;
	}

	/****************************
	 *	Overloaded operators
	 ****************************/

	template<class T, class S>
	S&
	operator << (S& s, const ByValue<T>& storage)
	{
		storage.template show<S> (s);
		return s;
	}
}
}
}

#endif /*NSTD_CONTAINER_STORAGE_BY_VALUE_CPP_*/
