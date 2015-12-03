/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_unit_Map.cpp                                 */
/* Description:     memory allocation map                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_MEMORY_UNIT_MAP_CPP_
#define NSTD_MEMORY_UNIT_MAP_CPP_

#include <cxxabi.h>

namespace nstd {
namespace memory {
namespace unit {

	/****************************
	 *		Public members
	 ****************************/

	Map :: Map () :
	isInitiallyOn_ (false),
	isOn_(false),
	map_ (NULL),
	nameTable_ (NULL),
	buffer_ (),
	size_ (BUFFER_CAPACITY),
	status_ (0),
	name_ (NULL) {
	}

	void
	Map :: create (const bool isOn)
	{
		isOn_ = isOn;
		if (isOn_) {
			isInitiallyOn_ = true;
		}
		#ifdef DEBUG_SOME_MAP
		map_ = new Map_ (INITIAL_MAP_CAPACITY);
		nameTable_ = new NameTable_ (INITIAL_NAME_TABLE_CAPACITY);
		#endif
	}
	void
	Map :: destroy()
	{
		if (map_ != NULL) {
			map_->commitSuicide();
			map_ = NULL;
		}
		if (nameTable_ != NULL) {
			nameTable_->commitSuicide();
			nameTable_ = NULL;
		}
	}
	void
	Map :: clear()
	{
		if (nameTable_ != NULL) {
			nameTable_->clear();
		}
		if (map_ != NULL) {
			map_->clear();
		}
	}

	inline void
	Map :: switchOn() {
		isOn_ = true;
	}
	inline void
	Map :: switchOff() {
		isOn_ = false;
	}

	template<class T>
	bool
	Map :: allocate (const Interval<T>& interval)
	{
		if (!isOn_) {
			return true;
		}
		typedef T Type;
		demangle (typeid (Type).name());
		const Type_id type_id = nameTable_->add (name_);
		Interval<> byteInterval = interval.byteRepresentation();

		const Size_t index = map_->findPlace (byteInterval);
		bool result = true;
		if (intersectsWith (index - 1, byteInterval)) {
			result = false;
		}
		if (intersectsWith (index, byteInterval)) {
			result = false;
		}
		if (intersectsWith (index + 1, byteInterval)) {
			result = false;
		}
		if (result) {
			map_->add (byteInterval, type_id);
		} else {
			std :: cout << std ::endl;
			std :: cout << "incorrect allocation of interval" << std :: endl;
			std :: cout << "--------------------------------" << std :: endl;
			std :: cout << "interval = " << byteInterval << std :: endl;
			std :: cout << "of type  = " << name_ << std :: endl;
		}
		return result;
	}
	template<class T>
	bool
	Map :: dispose (const Interval<T>& interval)
	{
		if (!isOn_) {
			return true;
		}
		if (interval.isNull()) {
			return true;
		}
		const_cast<Interval<T>& >(interval).clear();

		typedef T Type;
		demangle (typeid (Type).name());
		Interval<> byteInterval = interval.byteRepresentation();

		const Size_t index = map_->findPlace (byteInterval);

		if (map_->getKey (index) == byteInterval) {
			map_->remove (byteInterval);
			return true;
		} if ((index > 0) && (map_->getKey (index - 1) == byteInterval)) {
			map_->remove (byteInterval);
			return true;
		} if ((index + 1 < map_->getSize()) && (map_->getKey (index + 1) == byteInterval)) {
			map_->remove (byteInterval);
			return true;
		} else if (isInitiallyOn_) {
			std :: cout << std ::endl;
			std :: cout << "disposal of unallocated" << std :: endl;
			std :: cout << "-----------------------" << std :: endl;
			std :: cout << "interval = " << byteInterval << std :: endl;
			std :: cout << "of type: " << name_ << std :: endl;
			std :: cout << "nearest allocated intervals:" << std :: endl;
			if (index > 0) {
				std :: cout << "interval [" << (index - 1) << "] = " << map_->getKey (index - 1) << std :: endl;
				std :: cout << "of type: " << nameTable_->get (map_->getValue (index - 1)) << std :: endl;
			}
			std :: cout << "interval [" << index << "] = " << map_->getKey (index) << std :: endl;
			std :: cout << "of type: " << nameTable_->get (map_->getValue (index)) << std :: endl;
			if (index + 1 < map_->getSize()) {
				std :: cout << "interval [" << (index + 1) << "] = " << map_->getKey (index + 1) << std :: endl;
				std :: cout << "of type: " << nameTable_->get (map_->getValue (index + 1)) << std :: endl;
			}
			return false;
		} else {
			bool result = true;
			if (intersectsWith (index - 1, byteInterval)) {
				result = false;
			}
			if (intersectsWith (index, byteInterval)) {
				result = false;
			}
			if (intersectsWith (index + 1, byteInterval)) {
				result = false;
			}
			if (!result) {
				std :: cout << std ::endl;
				std :: cout << "incorrect disposal of interval" << std :: endl;
				std :: cout << "--------------------------------" << std :: endl;
				std :: cout << "interval = " << byteInterval << std :: endl;
				std :: cout << "of type = " << name_ << std :: endl;
			}
			return result;
		}
	}

	inline Size_t
	Map :: getSize() const {
		return (map_ == NULL) ? 0 : map_->getSize();
	}
	Size_t
	Map :: calculateAllocated() const
	{
		Size_t volume = 0;
		if (map_ != NULL) {
			for (int i = 0; i < map_->getSize(); ++ i) {
				Interval<> interval = map_->getKey (i);
				volume += interval.getVolume();
			}
		}
		return volume;
	}

	Size_t
	Map :: getVolume() const {
		return 0;
	}
	Size_t
	Map :: getSizeOf() const {
		return sizeof (Map);
	}
	template<class S>
	void
	Map :: show (S& string, const bool thorough) const
	{
		const Size_t allocatedVolume = calculateAllocated();
		if (allocatedVolume == 0) {
			return;
		}
		string << "allocated memory (in map): ";
		Unit :: show (string, allocatedVolume);
		string << " (" << allocatedVolume << ")" << chars :: NEW_LINE;
		if (map_->getSize() > 0) {
			string << "-----------------------------" << chars :: NEW_LINE;
			for (int i = 0; i < map_->getSize(); ++ i) {
				const Interval<> interval = map_->getKey (i);
				const Type_id type_id = map_->getValue (i);
				const NameTable_ :: NameString_& typeName = nameTable_->get (type_id);
				string << interval << " ----> " << typeName << chars :: NEW_LINE;
				if (!thorough && (i > SHOW_THRESHOLD)) {
					break;
				}
			}
		}
	}
	template<class S>
	void
	Map :: show (S& string, const Interval<>& interval) const
	{
		const Type_id type_id = map_->find (interval);
		if (type_id == Undefined<Type_id> :: getValue()) {
			string << "<unknown> <---- " << interval;
		} else {
			string << nameTable_->get (type_id) << " <---- " << interval;
		}
	}
	template<class S>
	void
	Map :: showNeighborhood (S& string, const void* pointer, const int diameter) const
	{
		void* ptr = const_cast<void*>(pointer);
		const Interval<> interval (static_cast<Byte_t*>(ptr), 16);
		const Size_t index = map_->findPlace (interval);
		string << chars :: NEW_LINE;
		string << "neighborhood of pointer" << pointer << chars :: NEW_LINE;
		string << "-----------------------" << chars :: NEW_LINE;
		for (int i = index - diameter; i <= index + diameter; ++ i) {
			if ((0 <= i) && (i < map_->getSize())) {
				const Interval<> interval = map_->getKey (i);
				const Type_id type_id = map_->getValue (i);
				const NameTable_ :: NameString_& typeName = nameTable_->get (type_id);
				string << interval << " ----> " << typeName << chars :: NEW_LINE;
			}
		}
	}

	/****************************
	 *		Private members
	 ****************************/
	#ifdef _CXXABI_H
	const char*
	Map :: demangle (const char* name)
	{
		size_ = BUFFER_CAPACITY;
		name_ = abi :: __cxa_demangle (name, buffer_, &size_, &status_);
		return name_;
	  }
	#else
	const char*
	Map :: demangle (const char* name)
	{
		name_ = name;
		return name_;
	}
	#endif

	void
	Map :: verifyMap() const
	{
		const int size = map_->getSize();
		if (size < 2) {
			return;
		}
		for (int i = 0; i < size - 1; ++ i) {
			const Interval<> interval_1 = map_->getKey (i);
			const Interval<> interval_2 = map_->getKey (i + 1);
			interval_1.verify();
			interval_2.verify();
			if (!(interval_1 < interval_2)) {
				std :: cout << "interval_1 = " << interval_1 << std :: endl;
				std :: cout << "interval_2 = " << interval_2 << std :: endl;
				std :: cout << std :: endl;
				show (std :: cout, true);
				throw exception :: Exception ("invalid memory map");
			}
		}
	}
	bool
	Map :: intersectsWith (const int index, const Interval<> int_0) const
	{
		if ((index < 0) || (index >= map_->getSize())) {
			return false;
		} else {
			const Interval<> int_1 = map_->getKey (index);
			if (int_1.intersectsWith (int_0)) {
				std :: cout << std :: endl;
				std :: cout << "allocation error" << std :: endl;
				std :: cout << "----------------" << std :: endl;
				std :: cout << "already allocated" << std :: endl;
				show (std :: cout, int_0); std :: cout << std :: endl;
				std :: cout << "intersects with newly allocated" << std :: endl;
				show (std :: cout, int_1); std :: cout << std :: endl;
				return true;
			} else {
				return false;
			}
		}
	}
}
}
}

#endif /*NSTD_MEMORY_UNIT_MAP_CPP_*/
