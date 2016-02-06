/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_unit_Standard.hpp                            */
/* Description:     standard heap memory space                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "memory/unit/nstd_memory_unit_Map.hpp"

namespace nstd {
namespace memory {
namespace unit {

class Standard {
public :
	Standard();

	void create();
	void destroy();
	bool isEmpty() const;
	bool isUsed() const;
	bool isCreated() const;

	Map& map();

	Size_t getUsedVolume() const;
	Size_t getAllocatedVolume() const;
	Size_t getDisposedVolume() const;
	Size_t getOverallVolume() const;

	template<class S>
	void show (S&);

private :
	friend class allocator :: Standard;

	template<class T>
	const Interval<T> allocateScalar (const Size_t size);
	template<class T>
	const Interval<T> allocateVector (const Size_t size);

	template<class T>
	void dispose (const Interval<T>);

	Map    map_;
	Size_t allocated_;
	Size_t disposed_;
	Size_t overall_;
};

}
}
}


