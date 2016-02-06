/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_unit_Heap.hpp                                */
/* Description:     heap memory unit                                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "memory/unit/nstd_memory_unit_Disposed.hpp"
#include "memory/unit/nstd_memory_unit_Map.hpp"
#include "memory/unit/nstd_memory_unit_Block.hpp"

namespace nstd {
namespace memory {
namespace unit {

class Heap {
public :
	Heap();

	void create();
	void destroy();
	bool isEmpty() const;
	bool isCreated() const;

	Map& map();

	bool contains (const void* pointer) const;
	bool containsInFree (const void* pointer) const;
	bool containsInUsed (const void* pointer) const;

	Size_t getUsedVolume() const;
	Size_t getAllocatedVolume() const;
	Size_t getFreeVolume() const;
	Size_t getOverallVolume() const;
	Size_t getDisposedVolume() const;

	void verifyDisposed();

	template<class S>
	void show
	(
		S&,
		const bool = false, // show disposed
		const bool = false  // show fragmentation
	);

private :
	friend class allocator :: Heap;

	template<class T>
	const Interval<T>
	allocateScalar (const Size_t);
	template<class T>
	const Interval<T>
	allocateVector (const Size_t, const allocator :: Method = allocator :: DEFAULT);
	template<class T>
	void
	dispose (const Interval<T>);

	enum {
		BLOCK_ARRAY_SIZE = size :: KILOBYTE,
		DEFAULT_BLOCK_SIZE = size :: MEGABYTE  * 16
	};

	typedef long Index_;

	bool isCreated_;
	Map map_;
	Block* block_ [BLOCK_ARRAY_SIZE];
	Disposed disposed_;
	Index_ voidBlockIndex_;
	Index_ usefulBlockIndex_;

	void swapBlocks (const Index_, const Index_);
};

}
}
}


