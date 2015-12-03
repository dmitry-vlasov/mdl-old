/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_types_allocator.hpp                                  */
/* Description:     basic types for memory management                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_TYPES_ALLOCATOR_HPP_
#define MDL_TYPES_ALLOCATOR_HPP_

namespace mdl {
namespace allocator {
	typedef
		nstd :: memory :: allocator :: Standard
		Standard;

#ifndef USE_STANDARD_HEAP
	typedef
		nstd :: memory :: allocator :: Heap
		Heap;
#else
	typedef
		nstd :: memory :: allocator :: Standard
		Heap;
#endif

	typedef
		nstd :: memory :: allocator :: Stack
		Stack;

	typedef
		nstd :: memory :: allocator :: Boxed
		Boxed;
}

namespace memory {

	using nstd :: memory :: UsageMessage;
	using namespace nstd :: memory :: exception;
}
	template<class T, class A = allocator :: Heap>
	class Scalar : public nstd :: memory :: storage :: Scalar<T, A> {
	};

	template<class C, class A = allocator :: Heap>
	class Factory : public nstd :: memory :: Factory<C, A> {
	};
}

#endif /*MDL_TYPES_ALLOCATOR_HPP_*/
