/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_container_storage_ByWeakPointer.cpp                 */
/* Description:     storage policy by not owning pointer for containers      */
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
namespace storage {

	/****************************
	 *		Public members
	 ****************************/

	template<class T>
	inline
	ByWeakPointer<T> :: ByWeakPointer() :
	Ancestor_ (NULL) {
	}
	template<class T>
	inline
	ByWeakPointer<T> :: ByWeakPointer (typename Ancestor_ :: Argument_ data) :
	Ancestor_ (data) {
	}
	template<class T>
	inline
	ByWeakPointer<T> :: ByWeakPointer (const ByWeakPointer& storage) :
	Ancestor_ (storage) {
	}
	template<class T>
	inline
	ByWeakPointer<T> :: ~ ByWeakPointer() {
		Ancestor_ :: data_ = NULL;
	}

	template<class T>
	inline void
	ByWeakPointer<T> :: clear() {
		Ancestor_ :: data_ = NULL;
	}
	template<class T>
	void
	ByWeakPointer<T> :: erase() {
		Ancestor_ :: data_ = NULL;
	}
	template<class T>
	inline void
	ByWeakPointer<T> :: init() {
	}

	// operators with Argument_ implementation
	template<class T>
	inline bool
	ByWeakPointer<T> :: operator == (Argument_ data) const {
		return (*Ancestor_ :: data_ == *data);
	}
	template<class T>
	inline bool
	ByWeakPointer<T> :: operator != (Argument_ data) const {
		return !(operator == (data));
	}
	template<class T>
	inline bool
	ByWeakPointer<T> :: operator < (Argument_ data) const {
		return (*Ancestor_ :: data_ < *data);
	}
	template<class T>
	inline bool
	ByWeakPointer<T> :: operator <= (Argument_ data) const {
		return (*Ancestor_ :: data_ <= *data);
	}
	template<class T>
	inline bool
	ByWeakPointer<T> :: operator > (Argument_ data) const {
		return (*Ancestor_ :: data_ > *data);
	}
	template<class T>
	inline bool
	ByWeakPointer<T> :: operator >= (Argument_ data) const {
		return (*Ancestor_ :: data_ >= *data);
	}
	template<class T>
	inline void
	ByWeakPointer<T> :: operator = (Argument_ data) {
		Ancestor_ :: data_ = data;
	}

	// operators with ByValue<Type_> implementation
	template<class T>
	inline bool
	ByWeakPointer<T> :: operator == (const ByValue<Type_>& storage) const {
		return (Ancestor_ :: data_ == storage.getValue());
	}
	template<class T>
	inline bool
	ByWeakPointer<T> :: operator != (const ByValue<Type_>& storage) const {
		return !(operator == (storage));
	}
	template<class T>
	inline bool
	ByWeakPointer<T> :: operator < (const ByValue<Type_>& storage) const {
		return (*Ancestor_ :: data_ < storage.getReference());
	}
	template<class T>
	inline bool
	ByWeakPointer<T> :: operator <= (const ByValue<Type_>& storage) const {
		return (*Ancestor_ :: data_ <= storage.getReferenece());
	}
	template<class T>
	inline bool
	ByWeakPointer<T> :: operator > (const ByValue<Type_>& storage) const {
		return (*Ancestor_ :: data_ > storage.getReference());
	}
	template<class T>
	inline bool
	ByWeakPointer<T> :: operator >= (const ByValue<Type_>& storage) const {
		return (*Ancestor_ :: data_ >= storage.getReference());
	}
	template<class T>
	inline void
	ByWeakPointer<T> :: operator = (const ByValue<Type_>& storage) {
		Ancestor_ :: data_ = storage.getValue();
	}

	// operators with ByWeakPointer implementation
	template<class T>
	inline bool
	ByWeakPointer<T> :: operator == (const ByWeakPointer& storage) const {
		return (Ancestor_ :: data_ == storage.getValue());
	}
	template<class T>
	inline bool
	ByWeakPointer<T> :: operator != (const ByWeakPointer& storage) const {
		return !(operator == (storage));
	}
	template<class T>
	inline bool
	ByWeakPointer<T> :: operator < (const ByWeakPointer& storage) const {
		return (*Ancestor_ :: data_ < *storage.data_);
	}
	template<class T>
	inline bool
	ByWeakPointer<T> :: operator <= (const ByWeakPointer& storage) const {
		return (*Ancestor_ :: data_ <= *storage.data_);
	}
	template<class T>
	inline bool
	ByWeakPointer<T> :: operator > (const ByWeakPointer& storage) const {
		return (*Ancestor_ :: data_ > *storage.data_);
	}
	template<class T>
	inline bool
	ByWeakPointer<T> :: operator >= (const ByWeakPointer& storage) const {
		return (*Ancestor_ :: data_ >= *storage.data_);
	}
	template<class T>
	inline void
	ByWeakPointer<T> :: operator = (const ByWeakPointer& storage) {
		Ancestor_ :: data_ = storage.getValue();
	}

	// nstd :: Object implementation
	template<class T>
	inline void
	ByWeakPointer<T> :: commitSuicide() {
		Ancestor_ :: data_ = NULL;
	}
	template<class T>
	inline Size_t
	ByWeakPointer<T> :: getVolume() const {
		return 0;
	}
	template<class T>
	inline Size_t
	ByWeakPointer<T> :: getSizeOf() const {
		return sizeof (ByWeakPointer);
	}
	template<class T>
	template<class S>
	void
	ByWeakPointer<T> :: show (S& string) const
	{
		if (Ancestor_ :: data_ != NULL) {
			Ancestor_ :: data_->show (string);
		}
	}

	/****************************
	 *	Overloaded operators
	 ****************************/

	template<class T, class S>
	S&
	operator << (S& s, const ByWeakPointer<T>& storage)
	{
		storage.show (s);
		return s;
	}
}
}
}


