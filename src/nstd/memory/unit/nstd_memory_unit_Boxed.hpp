/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_unit_Boxed.hpp                               */
/* Description:     boxed memory manager                                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_MEMORY_UNIT_BOXED_HPP_
#define NSTD_MEMORY_UNIT_BOXED_HPP_

#include "memory/unit/nstd_memory_unit_Disposed.hpp"
#include "memory/unit/nstd_memory_unit_Map.hpp"
#include "memory/unit/nstd_memory_unit_Tank.hpp"

namespace nstd {
namespace memory {
namespace unit {

class Boxed {
public :
	Boxed ();

	void create (const Size_t, const Size_t);
 	void clear (const bool wipe = false);
 	void destroy();
 	bool isCreated() const;
 	bool isFast() const;
 	void setFast (bool);

 	Map& map();
 	const Tank getMain() const;
	const Tank getReserve() const;

	bool contains (const void* pointer) const;
	bool containsInFree (const void* pointer) const;
	bool containsInUsed (const void* pointer) const;

 	Size_t getUsedVolume() const;
	Size_t getOverallVolume () const;
	Size_t getAllocatedVolume () const;
	Size_t getDisposedVolume () const;
	Size_t getFreeVolume () const;

	Size_t getReserveVolume() const;
	Size_t getMainVolume() const;
	Size_t getMaxVolume () const;

	void verifyDisposed();

	template<class S>
	void show (S&) const;

private :
	friend class allocator :: Boxed;

	template<class T>
	const Interval<T> allocateScalar (const Size_t);
	template<class T>
	const Interval<T> allocateVector
	(
		const Size_t,
		const allocator :: Method = allocator :: DEFAULT
	);
	template<class T>
	void dispose (const Interval<T>&);

	Map map_;
	Disposed disposed_;
	Tank main_;
	Tank reserve_;
	Tank* current_;
	Size_t maxVolume_;
	bool isFast_; //< Do not track disposed memory but waste it instead
};

}
}
}

#endif /*NSTD_MEMORY_UNIT_BOXED_HPP_*/
