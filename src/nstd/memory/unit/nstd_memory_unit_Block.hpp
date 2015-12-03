/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_unit_Block.hpp                               */
/* Description:     a chunk of memory                                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_MEMORY_UNIT_BLOCK_HPP_
#define NSTD_MEMORY_UNIT_BLOCK_HPP_

namespace nstd {
namespace memory {
namespace unit {

class Block {
public :
	template<class T>
	static Block* create();
	template<class T>
	static Block* create (const Size_t);
	virtual ~ Block();

	template<class T>
	const Interval<T> allocateScalar (const Size_t);
	template<class T>
	const Interval<T> allocateVector
	(
		const Size_t,
		const allocator :: Method = allocator :: DEFAULT
	);

	bool isFilled() const;
	void clear();

	bool contains (const void* pointer) const;
	bool containsInFree (const void* pointer) const;
	bool containsInUsed (const void* pointer) const;

	Size_t getOverallVolume() const;
	Size_t getAllocatedVolume() const;
	Size_t getFreeVolume() const;

private :
	Block (const Size_t);

	const Interval<> block_;
	Interval<> free_;
};

}
}
}

#endif /*NSTD_MEMORY_UNIT_BLOCK_HPP_*/
