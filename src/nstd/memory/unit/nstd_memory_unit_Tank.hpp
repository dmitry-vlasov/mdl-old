/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_unit_Tank.hpp                                */
/* Description:     base class for memory managers                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_MEMORY_UNIT_TANK_HPP_
#define NSTD_MEMORY_UNIT_TANK_HPP_

namespace nstd {
namespace memory {
namespace unit {

class Tank {
public :
	Tank();

	void create (const Size_t);
	void clear (const bool wipe = true);
	void destroy();

	bool isRegular() const;
	bool isEmpty() const;
	bool isFull() const;

	bool contains (const void* pointer) const;
	bool containsInFree (const void* pointer) const;
	bool containsInUsed (const void* pointer) const;

	template<class T>
	const Interval<T> allocateScalar (const Size_t);
	template<class T>
	const Interval<T> allocateVector (const Size_t);

	Size_t getOverallVolume() const;
	Size_t getAllocatedVolume() const;
	Size_t getFreeVolume() const;

	template<class S>
	void show (S&, const char[], const int indent = 0) const;

protected :
	const Interval<> space_;
	Interval<> free_;
};

}
}
}

#endif /*NSTD_MEMORY_UNIT_TANK_HPP_*/
