/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_storage_Array.hpp                            */
/* Description:     array memory storage                                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_MEMORY_STORAGE_ARRAY_HPP_
#define NSTD_MEMORY_STORAGE_ARRAY_HPP_

#include "memory/storage/nstd_memory_storage_Scalar.hpp"

namespace nstd {
namespace memory {
namespace storage {

template<class T, class E, class A>
class Array : public Scalar<T, A> {
public :
	typedef
		typename Scalar<T, A> :: Allocator_
		Allocator_;
	typedef T Type_;
	typedef E Element_;

protected :
	const Interval<Element_> allocateArray (const Size_t);
	void disposeArray (const Interval<Element_>);
};

}
}
}

#endif /*NSTD_MEMORY_STORAGE_ARRAY_HPP_*/
