/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_container_continual_Collection.cpp                  */
/* Description:     base class for all array-based containers                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "nstd_Undefined.hpp"

namespace nstd {
namespace container {
namespace continual {

	/****************************
	 *		Public members
	 ****************************/

	template<class T, template<class> class H>
	inline
	Collection<T, H> :: Collection () :
	size_ (0),
	data_ (NULL) {
	}
	template<class T, template<class> class H>
	template<class T1, template<class> class H1>
	inline
	Collection<T, H> :: Collection (const Collection<T1, H1>& array) :
	size_ (array.getSize()),
	data_ (NULL) {
	}

	template<class T, template<class> class H>
	inline bool
	Collection<T, H> :: contains (Argument_ value) const
	{
		const Index_ ind = find (value);
		return (ind != Undefined<Index_> :: getValue());
	}

	template<class T, template<class> class H>
	typename Collection<T, H> :: Index_
	Collection<T, H> :: find (Argument_ value) const
	{
		if (size_ == 0) {
			return Undefined<Index_> :: getValue();
		}
		const Storage_* d = data_;
		long c = size_;
		switch (c % 8) { // c > 0 assumed
			case 0 : do { if (*d++ == value) return (d - data_ - 1);
			case 7 :      if (*d++ == value) return (d - data_ - 1);
			case 6 :      if (*d++ == value) return (d - data_ - 1);
			case 5 :      if (*d++ == value) return (d - data_ - 1);
			case 4 :      if (*d++ == value) return (d - data_ - 1);
			case 3 :      if (*d++ == value) return (d - data_ - 1);
			case 2 :      if (*d++ == value) return (d - data_ - 1);
			case 1 :      if (*d++ == value) return (d - data_ - 1);
			            } while ((c -= 8) > 0);
		}
		return Undefined<Index_> :: getValue();
	}

	template<class T, template<class> class H>
	inline typename Collection<T, H> :: Reference_
	Collection<T, H> :: operator [] (const Index_ ind) {
		return data_ [ind].getReference();
	}
	template<class T, template<class> class H>
	inline typename Collection<T, H> :: const_Reference_
	Collection<T, H> :: operator [] (const Index_ ind) const {
		return data_ [ind].getReference();
	}

	template<class T, template<class> class H>
	inline typename Collection<T, H> :: Value_
	Collection<T, H> :: getValue (const Index_ ind) const {
		return data_ [ind].getValue();
	}
	template<class T, template<class> class H>
	inline typename Collection<T, H> :: Reference_
	Collection<T, H> :: getReference (const Index_ ind) {
		return data_ [ind].getReference();
	}
	template<class T, template<class> class H>
	inline typename Collection<T, H> :: const_Reference_
	Collection<T, H> :: getReference (const Index_ ind) const {
		return data_ [ind].getReference();
	}

	template<class T, template<class> class H>
	inline typename Collection<T, H> :: Value_
	Collection<T, H> :: getLastValue() const {
		return data_ [size_ - 1].getValue();
	}
	template<class T, template<class> class H>
	inline typename Collection<T, H> :: Value_
	Collection<T, H> :: getFirstValue() const {
		return data_ [0].getValue();
	}
	template<class T, template<class> class H>
	inline typename Collection<T, H> :: Reference_
	Collection<T, H> :: getLastReference() {
		return data_ [size_ - 1].getReference();
	}
	template<class T, template<class> class H>
	inline typename Collection<T, H> :: Reference_
	Collection<T, H> :: getFirstReference() {
		return data_ [0].getReference();
	}
	template<class T, template<class> class H>
	inline typename Collection<T, H> :: const_Reference_
	Collection<T, H> :: getLastReference() const {
		return data_ [size_ - 1].getReference();
	}
	template<class T, template<class> class H>
	inline typename Collection<T, H> :: const_Reference_
	Collection<T, H> :: getFirstReference() const {
		return data_ [0].getReference();
	}

	template<class T, template<class> class H>
	inline void
	Collection<T, H> :: set (const Index_ index, Argument_ value) {
		data_ [index].getReference() = value;
	}

	template<class T, template<class> class H>
	template<class T1, template<class> class H1>
	inline bool
	Collection<T, H> :: operator == (const Collection<T1, H1>& array) const {
		return isEqual (array);
	}
	template<class T, template<class> class H>
	template<class T1, template<class> class H1>
	inline bool
	Collection<T, H> :: operator != (const Collection<T1, H1>& array) const {
		return !isEqual (array);
	}
	template<class T, template<class> class H>
	template<class T1, template<class> class H1>
	bool
	Collection<T, H> :: isEqual (const Collection<T1, H1>& array) const
	{
		if (size_ != array.getSize()) {
			return false;
		}
		for (Index_ i = 0; i < size_; ++ i) {
			if (getValue (i) != array.getValue (i)) {
				return false;
			}
		}
		return true;
	}
	template<class T, template<class> class H>
	bool
	Collection<T, H> :: isEqual (const Type_* array, const Index_ size) const
	{
		if (size_ != size) {
			return false;
		}
		for (Index_ i = 0; i < size_; ++ i) {
			if (getValue (i) != array [i]) {
				return false;
			}
		}
		return true;
	}

	template<class T, template<class> class H>
	inline void
	Collection<T, H> :: swap (const Index_ i, const Index_ j) {
		Storage_ :: swap (data_ [i], data_ [j]);
	}

	template<class T, template<class> class H>
	inline bool
	Collection<T, H> :: isNull() const {
		return (data_ == NULL);
	}
	template<class T, template<class> class H>
	inline bool
	Collection<T, H> :: isEmpty() const {
		return (size_ == 0);
	}
	template<class T, template<class> class H>
	inline bool
	Collection<T, H> :: isSingleton() const {
		return (size_ == 1);
	}

	template<class T, template<class> class H>
	inline void
	Collection<T, H> :: clear() {
		size_ = 0;
	}
	template<class T, template<class> class H>
	void
	Collection<T, H> :: erase()
	{
		if (size_ == 0) {
			return;
		}
		const Storage_* d = data_;
		long c = size_;
		switch (c % 8) { // c > 0 assumed
			case 0 : do { const_cast<Storage_*>(d++)->erase();
			case 7 :      const_cast<Storage_*>(d++)->erase();
			case 6 :      const_cast<Storage_*>(d++)->erase();
			case 5 :      const_cast<Storage_*>(d++)->erase();
			case 4 :      const_cast<Storage_*>(d++)->erase();
			case 3 :      const_cast<Storage_*>(d++)->erase();
			case 2 :      const_cast<Storage_*>(d++)->erase();
			case 1 :      const_cast<Storage_*>(d++)->erase();
			            } while ((c -= 8) > 0);
		}
		size_ = 0;
	}
	template<class T, template<class> class H>
	void
	Collection<T, H> :: reverse()
	{
		for (Size_t i = 0; i < floor (size_ / 2); ++ i) {
			const Size_t j = size_ - i - 1;
			swap (i, j);
		}
	}

	template<class T, template<class> class H>
	inline typename Collection<T, H> :: Index_
	Collection<T, H> :: getSize() const {
		return size_;
	}
	template<class T, template<class> class H>
	inline Size_t
	Collection<T, H> :: getRawVolume() const {
		return (size_ + 1) * sizeof (Storage_);
	}

	template<class T, template<class> class H>
	Size_t
	Collection<T, H> :: getVolume() const
	{
		Size_t volume = 0;
		volume += getRawVolume ();
		for (Index_ i = 0; i < size_; ++ i) {
			volume += data_[i].getVolume();
		}
		return volume;
	}
	template<class T, template<class> class H>
	inline Size_t
	Collection<T, H> :: getSizeOf() const {
		return sizeof (Collection);
	}
}
}
}

#include <typeinfo>

namespace nstd {
namespace container {
namespace continual {

	template<class T, template<class> class H>
	template<class S>
	void
	Collection<T, H> :: show (S& string) const
	{
		for (Index_ i = 0; i < size_; ++ i) {
			const Storage_ storage = data_ [i];
			storage.show (string);
		}
	}

	template<class T, template<class> class H>
	const typename Collection<T, H> :: Storage_*
	Collection<T, H> :: getData() const {
		return data_;
	}

	/****************************
	 *		Protected members
	 ****************************/

	template<class T, template<class> class H>
	template<class T1, template<class> class H1>
	inline void
	Collection<T, H> :: copy (const Collection<T1, H1>& array)
	{
		size_ = array.getSize();
		memMove<typename Collection<T1, H1> :: Storage_>(data_, array.data_, size_);
	}
	template<class T, template<class> class H>
	inline void
	Collection<T, H> :: copy (const Collection& array) {
		size_ = array.getSize();
		memMove<Storage_> (data_, array.data_, size_);
	}
	template<class T, template<class> class H>
	void
	Collection<T, H> :: copy (const Type_* const array, const Index_ size) {
		size_ = size;
		memMove (data_, array, size);
	}

	template<class T, template<class> class H>
	template<class V>
	void
	Collection<T, H> :: memMove
	(
		Storage_* destination,
		const V* const source,
		Index_ const count,
		const bool backwards
	)
	{
		if (count == 0) {
			return;
		}
		// Duff's device
		const V* s = const_cast<const V*>(source);
		Storage_* d = destination;
		long c = count; // count > 0 assumed
		if (backwards) {
			switch (c % 8) {
				case 0 :  do {  (d--)->getReference() = (s--)->getValue();
				case 7 :        (d--)->getReference() = (s--)->getValue();
				case 6 :        (d--)->getReference() = (s--)->getValue();
				case 5 :        (d--)->getReference() = (s--)->getValue();
				case 4 :        (d--)->getReference() = (s--)->getValue();
				case 3 :        (d--)->getReference() = (s--)->getValue();
				case 2 :        (d--)->getReference() = (s--)->getValue();
				case 1 :        (d--)->getReference() = (s--)->getValue();
							 } while ((c -= 8) > 0);
			}
		} else {
			switch (c % 8) {
				case 0 :  do {  (d++)->getReference() = (s++)->getValue();
				case 7 :        (d++)->getReference() = (s++)->getValue();
				case 6 :        (d++)->getReference() = (s++)->getValue();
				case 5 :        (d++)->getReference() = (s++)->getValue();
				case 4 :        (d++)->getReference() = (s++)->getValue();
				case 3 :        (d++)->getReference() = (s++)->getValue();
				case 2 :        (d++)->getReference() = (s++)->getValue();
				case 1 :        (d++)->getReference() = (s++)->getValue();
							 } while ((c -= 8) > 0);
			}
		}
	}
	template<class T, template<class> class H>
	void
	Collection<T, H> :: memMove
	(
		Storage_* destination,
		const Type_* source,
		Index_ const count,
		const bool backwards
	)
	{
		if (count == 0) {
			return;
		}
		// Duff's device
		const Type_* s = const_cast<const Type_*>(source);
		Storage_* d = destination;
		long c = count; // count > 0 assumed
		if (backwards) {
			switch (c % 8) {
				case 0 :  do { (d--)->getReference() = *s--;
				case 7 :       (d--)->getReference() = *s--;
				case 6 :       (d--)->getReference() = *s--;
				case 5 :       (d--)->getReference() = *s--;
				case 4 :       (d--)->getReference() = *s--;
				case 3 :       (d--)->getReference() = *s--;
				case 2 :       (d--)->getReference() = *s--;
				case 1 :       (d--)->getReference() = *s--;
							 } while ((c -= 8) > 0);
			}
		} else {
			switch (c % 8) {
				case 0 :  do { (d++)->getReference() = *s++;
				case 7 :       (d++)->getReference() = *s++;
				case 6 :       (d++)->getReference() = *s++;
				case 5 :       (d++)->getReference() = *s++;
				case 4 :       (d++)->getReference() = *s++;
				case 3 :       (d++)->getReference() = *s++;
				case 2 :       (d++)->getReference() = *s++;
				case 1 :       (d++)->getReference() = *s++;
							 } while ((c -= 8) > 0);
			}
		}
	}
	template<class T, template<class> class H>
	void
	Collection<T, H> :: undefineArray ()
	{
		// Duff's device
		Storage_* d = data_;
		long c = size_ + 1;

		if (c <= 0) {
			return;
		}
		switch (c % 8)  // c > 0 assumed
		{
			case 0 : do { (d++)->undefine();
			case 7 :      (d++)->undefine();
			case 6 :      (d++)->undefine();
			case 5 :      (d++)->undefine();
			case 4 :      (d++)->undefine();
			case 3 :      (d++)->undefine();
			case 2 :      (d++)->undefine();
			case 1 :      (d++)->undefine();
			            } while ((c -= 8) > 0);
		}
	}

	/********************************
	 *		Overloaded operators
	 ********************************/

	template<class S, class T, template<class> class H >
	S&
	operator << (S& s, const Collection<T, H>& array)
	{
		array.show (s);
		return s;
	}
}
}
}


