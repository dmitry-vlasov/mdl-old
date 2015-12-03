/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_unit_Map.hpp                                 */
/* Description:     memory allocation map                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_MEMORY_UNIT_MAP_HPP_
#define NSTD_MEMORY_UNIT_MAP_HPP_

namespace nstd {
namespace memory {
namespace unit {

class Map {
public :
	Map();

	void create (const bool isOn);
	void destroy();
	void clear();

	void switchOn();
	void switchOff();

	template<class T>
	bool allocate (const Interval<T>&);
	template<class T>
	bool dispose (const Interval<T>&);

	Size_t getSize() const;
	Size_t calculateAllocated() const;

	Size_t getVolume() const;
	Size_t getSizeOf() const;
	template<class S>
	void show (S&, const bool = false) const;
	template<class S>
	void show (S&, const Interval<>&) const;
	template<class S>
	void showNeighborhood
	(
		S&,
		const void* pointer,
		const int diameter = 5
	) const;

private :
	enum {
		INITIAL_MAP_CAPACITY = size :: MEGABYTE,
		INITIAL_NAME_TABLE_CAPACITY = size :: KILOBYTE * 4,
		BUFFER_CAPACITY = size :: KILOBYTE,
		SHOW_THRESHOLD = 32
	};
	typedef int Type_id;
	typedef
		map :: Scalar
		<
			Interval<>,
			Type_id,
			allocator :: Direct
		>
		Map_;
	typedef
		NameTable
		<
			Type_id,
			allocator :: Direct
		>
		NameTable_;

	const char* demangle (const char*);
	void verifyMap() const;
	bool intersectsWith (const int, const Interval<>) const;

	bool isInitiallyOn_;
	bool isOn_;
	Map_* map_;
	NameTable_* nameTable_;

	// Type demangling fields
	char buffer_ [BUFFER_CAPACITY];
	Size_t size_;
	int status_;
	const char* name_;
};

}
}
}

#endif /*NSTD_MEMORY_UNIT_MAP_HPP_*/
