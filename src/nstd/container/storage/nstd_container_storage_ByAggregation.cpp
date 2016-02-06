/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_container_storage_ByAggregation.cpp                 */
/* Description:     aggregation storage policy for containers                */
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
namespace storage {

	/****************************
	 *		Public members
	 ****************************/

	template<class T>
	ByAggregation<T> :: ByAggregation() :
	data_() {
	}
	template<class T>
	ByAggregation<T> :: ByAggregation (Argument_ data) :
	data_ (data) {
	}
	template<class T>
	ByAggregation<T> :: ByAggregation (const ByAggregation& storage) :
	data_ (storage.data_) {
	}

	template<class T>
	inline typename ByAggregation<T> :: Value_
	ByAggregation<T> :: getValue() const {
		return data_;
	}
	template<class T>
	inline typename ByAggregation<T> :: Reference_
	ByAggregation<T> :: getReference() {
		return data_;
	}
	template<class T>
	inline typename ByAggregation<T> :: const_Reference_
	ByAggregation<T> :: getReference() const {
		return data_;
	}

	template<class T>
	inline bool
	ByAggregation<T> :: operator == (Argument_ data) const {
		return (data_ == data);
	}
	template<class T>
	inline bool
	ByAggregation<T> :: operator != (Argument_ data) const {
		return !(operator == (data_));
	}
	template<class T>
	inline bool
	ByAggregation<T> :: operator < (Argument_ data) const {
		return (data_ < data);
	}
	template<class T>
	inline bool
	ByAggregation<T> :: operator <= (Argument_ data) const {
		return (data_ <= data);
	}
	template<class T>
	inline bool
	ByAggregation<T> :: operator > (Argument_ data) const {
		return (data_ > data);
	}
	template<class T>
	inline bool
	ByAggregation<T> :: operator >= (Argument_ data) const {
		return (data_ >= data);
	}
	template<class T>
	inline void
	ByAggregation<T> :: operator = (Argument_ data) {
		data_ = data;
	}

	template<class T>
	inline bool
	ByAggregation<T> :: operator == (const ByAggregation& storage) const {
		return (data_ == storage.data_);
	}
	template<class T>
	inline bool
	ByAggregation<T> :: operator != (const ByAggregation& storage) const {
		return ! (operator == (storage));
	}
	template<class T>
	inline bool
	ByAggregation<T> :: operator < (const ByAggregation& storage) const {
		return (data_ < storage.data_);
	}
	template<class T>
	inline bool
	ByAggregation<T> :: operator <= (const ByAggregation& storage) const {
		return (data_ <= storage.data_);
	}
	template<class T>
	inline bool
	ByAggregation<T> :: operator > (const ByAggregation& storage) const {
		return (data_ > storage.data_);
	}
	template<class T>
	inline bool
	ByAggregation<T> :: operator >= (const ByAggregation& storage) const {
		return (data_ >= storage.data_);
	}
	template<class T>
	inline void
	ByAggregation<T> :: operator = (const ByAggregation& storage) {
		data_ = storage.data_;
	}

	template<class T>
	inline void
	ByAggregation<T> :: undefine() {
		data_ = Undefined<T> :: getValue();
	}

	template<class T>
	inline void
	ByAggregation<T> :: swap (ByAggregation& storage_1, ByAggregation& storage_2)
	{
		const Type_ data_1 = storage_1.data_;
		storage_1.data_ = storage_2.data_;
		storage_2.data_ = data_1;
	}

	template<class T>
	inline Size_t
	ByAggregation<T> :: getVolume() const {
		return 0;
	}
	template<class T>
	inline Size_t
	ByAggregation<T> :: getSizeOf() const {
		return sizeof (ByAggregation);
	}
}
}
}


