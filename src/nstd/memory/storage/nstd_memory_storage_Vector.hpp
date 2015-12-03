/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_storage_Vector.hpp                           */
/* Description:     vector memory storage                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_MEMORY_STORAGE_VECTOR_HPP_
#define NSTD_MEMORY_STORAGE_VECTOR_HPP_

#include "memory/storage/nstd_memory_storage_Scalar.hpp"

namespace nstd {
namespace memory {
namespace storage {

template<class T, class E, class A>
class Vector : public Scalar<T, A> {
public :
	typedef
		typename Scalar<T, A> :: Allocator_
		Allocator_;
	typedef T Type_;
	typedef E Element_;

protected :
	const Interval<Element_> allocateVector (const Size_t);
	void disposeVector (const Interval<Element_>);

	const Interval<Element_> resizeVector
	(
		Element_* array,
		const Size_t oldCapacity,
		const Size_t newCapacity,
		const bool keep
	);

private :
	void keepData
	(
		Element_* oldArray,
		Element_* newArray,
		const Size_t capacity
	);
};

}
}
}

#endif /*NSTD_MEMORY_VECTOR_STORAGE_HPP_*/
