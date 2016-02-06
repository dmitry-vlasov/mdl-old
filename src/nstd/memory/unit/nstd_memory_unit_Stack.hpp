/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_unit_Stack.hpp                               */
/* Description:     stack memory                                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "memory/unit/nstd_memory_unit_Tank.hpp"
#include "memory/unit/nstd_memory_unit_PointerStack.hpp"

namespace nstd {
namespace memory {
namespace unit {

class Stack : public Tank {
public :
	typedef PointerStack :: Index_ Index_;

	Stack ();

	void create (const Size_t);
 	void destroy();
 	bool isCreated() const;

	void push();
	void pop();
	void clear (const bool wipe);
	bool isEmpty() const;

	void memorizeState();
	void recallState();

	Size_t getMaxVolume();
	Index_ getMaxDepth() const;
	Index_ getDepth() const;

	Size_t getUsedVolume() const;
	Size_t getOverallVolume() const;
	Size_t getAllocatedVolume() const;
	Size_t getFreeVolume() const;

	template<class S>
	void show (S&, const int indent = 0) const;

private :
	friend class allocator :: Stack;

	template<class T>
	const Interval<T> allocateScalar (const Size_t);
	template<class T>
	const Interval<T> allocateVector (const Size_t);

	PointerStack stack_;
	Size_t maxVolume_;
};

}
}
}


