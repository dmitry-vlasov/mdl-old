/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_allocator_Boxed.hpp                          */
/* Description:     allocator to the boxed memory                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_MEMORY_ALLOCATOR_BOXED_HPP_
#define NSTD_MEMORY_ALLOCATOR_BOXED_HPP_

#include "memory/allocator/nstd_memory_allocator_Control.hpp"

namespace nstd {
namespace memory {
namespace allocator {

class Boxed {
public :
	template<class T>
	static const Interval<T> allocateScalar (const Size_t);
	template<class T>
	static const Interval<T> allocateVector (const Size_t, const Method = DEFAULT);
	template<class T>
	static void dispose (const Interval<T>&);
	static void setControl (const void*, const Size_t);

private :
	static pthread_mutex_t mutex_;
	static Control control_;
};

}
}
}

#endif /*NSTD_MEMORY_ALLOCATOR_BOXED_HPP_*/
