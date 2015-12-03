/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_types_allocator.hpp                                  */
/* Description:     basic types for memory management                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_TYPES_ALLOCATOR_HPP_
#define DEL_TYPES_ALLOCATOR_HPP_

namespace del {
namespace allocator {
	typedef
		nstd :: memory :: allocator :: Standard
		Standard;
	typedef
		nstd :: memory :: allocator :: Heap
		Heap;
	typedef
		nstd :: memory :: allocator :: Stack
		Stack;
}
namespace memory {

	using nstd :: memory :: UsageMessage;
	using namespace nstd :: memory :: exception;
}
	template<class T, class A = allocator :: Heap>
	class Scalar : public nstd :: memory :: storage :: Scalar<T, A> {
	};
}

#endif /*DEL_TYPES_ALLOCATOR_HPP_*/
