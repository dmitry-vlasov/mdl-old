/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_container_storage_ByPointer.cpp                     */
/* Description:     storage policy by pointer for containers                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_CONTAINER_STORAGE_BY_POINTER_CPP_
#define NSTD_CONTAINER_STORAGE_BY_POINTER_CPP_

namespace nstd {
namespace container {
namespace storage {

	/****************************
	 *		Public members
	 ****************************/

	template<class T>
	inline
	ByPointer<T> :: ByPointer() :
	Ancestor_ (NULL) {
	}
	template<class T>
	inline
	ByPointer<T> :: ByPointer (typename Ancestor_ :: Argument_ data) :
	Ancestor_ (data) {
	}
	template<class T>
	inline
	ByPointer<T> :: ByPointer (const ByPointer& storage) :
	Ancestor_ (storage) {
	}
	template<class T>
	inline
	ByPointer<T> :: ~ ByPointer() {
		erase();
	}

	template<class T>
	inline void
	ByPointer<T> :: clear() {
		Ancestor_ :: data_->clear();
	}
	template<class T>
	void
	ByPointer<T> :: erase()
	{
		if (Ancestor_ :: data_ == NULL) {
			return;
		}
		typedef
			typename type :: Unconst<T> :: Result_
			Unconst;
		const_cast<Unconst*>(Ancestor_ :: data_)->commitSuicide();
		Ancestor_ :: data_ = NULL;
	}
	template<class T>
	inline void
	ByPointer<T> :: init()
	{
		if (Ancestor_ :: data_ == NULL) {
			Ancestor_ :: data_ = new T();
			Ancestor_ :: data_->init();
		}
	}

	// operators with Argument_ implementation
	template<class T>
	inline bool
	ByPointer<T> :: operator == (Argument_ data) const {
		return (*Ancestor_ :: data_ == *data);
	}
	template<class T>
	inline bool
	ByPointer<T> :: operator != (Argument_ data) const {
		return !(operator == (data));
	}
	template<class T>
	inline bool
	ByPointer<T> :: operator < (Argument_ data) const {
		return (*Ancestor_ :: data_ < *data);
	}
	template<class T>
	inline bool
	ByPointer<T> :: operator <= (Argument_ data) const {
		return (*Ancestor_ :: data_ <= *data);
	}
	template<class T>
	inline bool
	ByPointer<T> :: operator > (Argument_ data) const {
		return (*Ancestor_ :: data_ > *data);
	}
	template<class T>
	inline bool
	ByPointer<T> :: operator >= (Argument_ data) const {
		return (*Ancestor_ :: data_ >= *data);
	}
	template<class T>
	inline void
	ByPointer<T> :: operator = (Argument_ data) {
		Ancestor_ :: data_ = data;
	}

	// operators with ByValue<Type_> implementation
	template<class T>
	inline bool
	ByPointer<T> :: operator == (const ByValue<Type_>& storage) const {
		return (Ancestor_ :: data_ == storage.getValue());
	}
	template<class T>
	inline bool
	ByPointer<T> :: operator != (const ByValue<Type_>& storage) const {
		return !(operator == (storage));
	}
	template<class T>
	inline bool
	ByPointer<T> :: operator < (const ByValue<Type_>& storage) const {
		return (*Ancestor_ :: data_ < storage.getReference());
	}
	template<class T>
	inline bool
	ByPointer<T> :: operator <= (const ByValue<Type_>& storage) const {
		return (*Ancestor_ :: data_ <= storage.getReferenece());
	}
	template<class T>
	inline bool
	ByPointer<T> :: operator > (const ByValue<Type_>& storage) const {
		return (*Ancestor_ :: data_ > storage.getReference());
	}
	template<class T>
	inline bool
	ByPointer<T> :: operator >= (const ByValue<Type_>& storage) const {
		return (*Ancestor_ :: data_ >= storage.getReference());
	}
	template<class T>
	inline void
	ByPointer<T> :: operator = (const ByValue<Type_>& storage) {
		throw std :: exception();
	}

	// operators with ByPointer implementation
	template<class T>
	inline bool
	ByPointer<T> :: operator == (const ByPointer& storage) const {
		return (Ancestor_ :: data_ == storage.getValue());
	}
	template<class T>
	inline bool
	ByPointer<T> :: operator != (const ByPointer& storage) const {
		return !(operator == (storage));
	}
	template<class T>
	inline bool
	ByPointer<T> :: operator < (const ByPointer& storage) const {
		return (*Ancestor_ :: data_ < *storage.data_);
	}
	template<class T>
	inline bool
	ByPointer<T> :: operator <= (const ByPointer& storage) const {
		return (*Ancestor_ :: data_ <= *storage.data_);
	}
	template<class T>
	inline bool
	ByPointer<T> :: operator > (const ByPointer& storage) const {
		return (*Ancestor_ :: data_ > *storage.data_);
	}
	template<class T>
	inline bool
	ByPointer<T> :: operator >= (const ByPointer& storage) const {
		return (*Ancestor_ :: data_ >= *storage.data_);
	}
	template<class T>
	inline void
	ByPointer<T> :: operator = (const ByPointer& storage) {
		Ancestor_ :: data_ = storage.getValue();
	}

	// nstd :: Object implementation
	template<class T>
	inline void
	ByPointer<T> :: commitSuicide() {
		erase();
	}
	template<class T>
	inline Size_t
	ByPointer<T> :: getVolume() const
	{
		Size_t volume = 0;
		if (Ancestor_ :: data_ != NULL) {
			volume += Ancestor_ :: data_->getVolume();
			volume += Ancestor_ :: data_->getSizeOf();
		}
		return volume;
	}
	template<class T>
	inline Size_t
	ByPointer<T> :: getSizeOf() const {
		return sizeof (ByPointer);
	}
	template<class T>
	template<class S>
	void
	ByPointer<T> :: show (S& string) const
	{
		if (Ancestor_ :: data_ != NULL) {
			Ancestor_ :: data_->show (string);
		}
	}

	/****************************
	 *		Overloaded operators
	 ****************************/

	template<class T, class S>
	S&
	operator << (S& s, const ByPointer<T>& storage)
	{
		storage.show (s);
		return s;
	}
}
}
}

#endif /*NSTD_CONTAINER_STORAGE_BY_POINTER_CPP_*/
