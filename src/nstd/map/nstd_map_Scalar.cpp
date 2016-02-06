/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_map_Scalar.ipp                                      */
/* Description:     scalar mapping                                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace nstd {
namespace map {

	/****************************
	 *		Public members
	 ****************************/

	template <class K, class T, class A>
	inline
	Scalar<K, T, A> :: Scalar () :
	keyContainer_ (),
	valueContainer_ () {
	}
	template <class K, class T, class A>
	inline
	Scalar<K, T, A> :: Scalar (const Index_ capacity) :
	keyContainer_ (capacity),
	valueContainer_ (capacity) {
	}
	template <class K, class T, class A>
	Scalar<K, T, A> :: ~ Scalar() {
	}

	template <class K, class T, class A>
	inline void
	Scalar<K, T, A> :: add (const Key_ key, const Value_ value)
	{
		const Index_ index = keyContainer_.add (key);
		if (index == Undefined<Index_> :: getValue()) {
			const Index_ index_1 = keyContainer_.find (key);
			std :: cout << "key " << key << " duplicate at add." << std :: endl;
			/*std :: cout << "keys  = ";
			for (Index_ i = 0; i < keyContainer_.getSize(); ++ i) {
				std :: cout << keyContainer_.getValue (i) << ", ";
			}*/
			std :: cout << std :: endl;
			throw std :: exception();
		}
		valueContainer_.insert (value, index);
	}

	template <class K, class T, class A>
	inline void
	Scalar<K, T, A> :: set (const Key_ key, const Value_ value)
	{
		const Index_ index = keyContainer_.find (key);
		if (index == Undefined<Index_> :: getValue()) {
			std :: cout << "key " << key << " not found at set." << std :: endl;
			std :: cout << "keys  = ";
			for (Index_ i = 0; i < keyContainer_.getSize(); ++ i) {
				std :: cout << keyContainer_.getValue (i) << ", ";
			}
			throw std :: exception();
		}
		valueContainer_.getReference (index) = value;
	}
	template <class K, class T, class A>
	inline void
	Scalar<K, T, A> :: remove (const Key_ key)
	{
		const Index_ index = keyContainer_.find (key);
		if (index == Undefined<Index_> :: getValue()) {
			std :: cout << "key " << key << " not found at remove." << std :: endl;
			std :: cout << "keys  = ";
			for (Index_ i = 0; i < keyContainer_.getSize(); ++ i) {
				std :: cout << keyContainer_.getValue (i) << ", ";
			}
			throw std :: exception();
		}
		keyContainer_.remove (index);
		valueContainer_.remove (index);
	}
	template <class K, class T, class A>
	inline void
	Scalar<K, T, A> :: removeDec (const Key_ key, const Value_ value)
	{
		const Index_ index = keyContainer_.find (key);
		if (index == Undefined<Index_> :: getValue()) {
			std :: cout << "key " << key << " not found at remove." << std :: endl;
			throw std :: exception();
		}
		if (value != valueContainer_.getValue (index)) {
			std :: cout << "value " << value << " does not fit map." << std :: endl;
			throw std :: exception();
		}
		keyContainer_.remove (index);
		valueContainer_.remove (index);
		decValue (value);
	}
	template <class K, class T, class A>
	inline void
	Scalar<K, T, A> :: replaceKey (const Key_ keyOld, const Key_ keyNew)
	{
		const Index_ index = keyContainer_.find (keyOld);
		if (index == Undefined<Index_> :: getValue()) {
			std :: cout << "key " << keyOld << " not found at replace key." << std :: endl;
			std :: cout << "keys  = ";
			for (Index_ i = 0; i < keyContainer_.getSize(); ++ i) {
				std :: cout << keyContainer_.getValue (i) << ", ";
			}
			throw std :: exception();
		}
		const Value_ value = valueContainer_.getValue (index);
		remove (keyOld);
		add (keyNew, value);
	}
	template <class K, class T, class A>
	inline void
	Scalar<K, T, A> :: replaceValue (const Value_ valueOld, const Value_ valueNew)
	{
		for (Index_ i = 0; i < valueContainer_.getSize(); ++ i) {
			if (valueContainer_.getValue (i) == valueOld) {
				valueContainer_.getReference (i) == valueNew;
			}
		}
	}
	template <class K, class T, class A>
	inline void
	Scalar<K, T, A> :: decValue (const Value_ value)
	{
		for (Index_ i = 0; i < valueContainer_.getSize(); ++ i) {
			if (valueContainer_.getValue (i) > value) {
				-- valueContainer_.getReference (i);
			}
		}
	}
	template <class K, class T, class A>
	inline typename Scalar<K, T, A> :: Value_
	Scalar<K, T, A> :: find (const Key_ key) const
	{
		const Index_ index = keyContainer_.find (key);
		if (index == Undefined<Index_> :: getValue()) {
			return Undefined<Value_> :: getValue();
		} else {
			return valueContainer_.getValue (index);
		}
	}
	template <class K, class T, class A>
	inline typename Scalar<K, T, A> :: Value_
	Scalar<K, T, A> :: addFind (const Key_ key, const Value_ value)
	{
		const Index_ index = keyContainer_.find (key);
		if (index == Undefined<Index_> :: getValue()) {
			add (key, value);
			return value;
		} else {
			return valueContainer_.getValue (index);
		}
	}
	template <class K, class T, class A>
	inline typename Scalar<K, T, A> :: Index_
	Scalar<K, T, A> :: findIndex (const Key_ key) const {
		return keyContainer_.find (key);
	}
	template <class K, class T, class A>
	inline typename Scalar<K, T, A> :: Index_
	Scalar<K, T, A> :: findPlace (const Key_ key) const {
		return keyContainer_.findPlace (key);
	}
	template <class K, class T, class A>
	inline typename Scalar<K, T, A> :: Index_
	Scalar<K, T, A> :: getSize() const {
		return keyContainer_.getSize();
	}
	template <class K, class T, class A>
	inline bool
	Scalar<K, T, A> :: containsKey (const Key_ key) const
	{
		const Index_ index = keyContainer_.find (key);
		return (index != Undefined<Index_> :: getValue());
	}

	template <class K, class T, class A>
	inline typename Scalar<K, T, A> :: Key_
	Scalar<K, T, A> :: getKey (const Index_ index) const {
		return keyContainer_.getValue (index);
	}
	template <class K, class T, class A>
	inline typename Scalar<K, T, A> :: Value_
	Scalar<K, T, A> :: getValue (const Index_ index) const {
		return valueContainer_.getValue (index);
	}
	template <class K, class T, class A>
	inline typename Scalar<K, T, A> :: Key_
	Scalar<K, T, A> :: getFirstKey() const {
		return keyContainer_.getFirstValue();
	}
	template <class K, class T, class A>
	inline typename Scalar<K, T, A> :: Value_
	Scalar<K, T, A> :: getFirstValue() const {
		return valueContainer_.getFirstValue();
	}
	template <class K, class T, class A>
	inline typename Scalar<K, T, A> :: Key_
	Scalar<K, T, A> :: getLastKey() const {
		return keyContainer_.getLastValue();
	}
	template <class K, class T, class A>
	inline typename Scalar<K, T, A> :: Value_
	Scalar<K, T, A> :: getLastValue() const {
		return valueContainer_.getLastValue();
	}
	template <class K, class T, class A>
	inline typename Scalar<K, T, A> :: Key_&
	Scalar<K, T, A> :: key (const Index_ index) {
		return keyContainer_.getReference (index);
	}
	template <class K, class T, class A>
	inline typename Scalar<K, T, A> :: Value_&
	Scalar<K, T, A> :: value (const Index_ index) {
		return valueContainer_.getReference (index);
	}
	template <class K, class T, class A>
	inline typename Scalar<K, T, A> :: Key_&
	Scalar<K, T, A> :: firstKey() {
		return keyContainer_.firstValue();
	}
	template <class K, class T, class A>
	inline typename Scalar<K, T, A> :: Value_&
	Scalar<K, T, A> :: firstValue() {
		return valueContainer_.firstValue();
	}
	template <class K, class T, class A>
	inline typename Scalar<K, T, A> :: Key_&
	Scalar<K, T, A> :: lastKey() {
		return keyContainer_.lastValue();
	}
	template <class K, class T, class A>
	inline typename Scalar<K, T, A> :: Value_&
	Scalar<K, T, A> :: lastValue() {
		return valueContainer_.lastValue();
	}

	template <class K, class T, class A>
	inline void
	Scalar<K, T, A> :: clear()
	{
		keyContainer_.clear();
		valueContainer_.clear();
	}
	template <class K, class T, class A>
	inline void
	Scalar<K, T, A> :: init()
	{
		keyContainer_.init (INITIAL_CAPACITY);
		valueContainer_.init (INITIAL_CAPACITY);
	}

	// nstd :: Object implementation
	template <class K, class T, class A>
	inline void
	Scalar<K, T, A> :: commitSuicide() {
		delete this;
	}
	template <class K, class T, class A>
	inline Size_t
	Scalar<K, T, A> :: getVolume() const
	{
		Size_t result = 0;
		result += keyContainer_.getVolume();
		result += valueContainer_.getVolume();
		return result;
	}
	template <class K, class T, class A>
	inline Size_t
	Scalar<K, T, A> :: getSizeOf() const {
		return sizeof (Scalar);
	}
	template <class K, class T, class A>
	template<class S>
	inline void
	Scalar<K, T, A> :: show (S& s) const
	{
		s << "size:" << keyContainer_.getSize() << chars :: NEW_LINE;
		s << "capacity:" << keyContainer_.getCapacity() << chars :: NEW_LINE;
		for (Index_ i = 0; i < keyContainer_.getSize(); ++ i) {
			const Key_ key = keyContainer_.getValue (i);
			const Value_ value = valueContainer_.getValue (i);
			s << chars :: TAB << key << " -----> ";
			s << value << chars :: NEW_LINE;
		}
	}

	/********************************
	 *		Overloaded operators
	 ********************************/

	template<class K, class T, class A, class S>
	inline S&
	operator << (S& s, const Scalar<K, T, A>& map)
	{
		map.show (s);
		return s;
	}
}
}



