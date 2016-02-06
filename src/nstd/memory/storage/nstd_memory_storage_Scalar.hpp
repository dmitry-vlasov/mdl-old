/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_storage_Scalar.hpp                           */
/* Description:     scalar memory storage                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace nstd {
namespace memory {
namespace storage {

template <class T, class A>
class Scalar {
public :
	typedef T Type_;
	typedef A Allocator_;

	void* operator new (const Size_t);
	void* operator new[] (const Size_t);

	void* operator new (const Size_t, void*);
	void* operator new[] (const Size_t, void*);

	void operator delete (void*);
	void operator delete[] (void*);

private :
	static void destroyContents (void*, const Size_t);
	static void destroyArray (void*, const Size_t);
};

}
}
}


