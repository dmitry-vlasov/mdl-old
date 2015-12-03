/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_types_allocator.hpp                                   */
/* Description:     basic types for memory management                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_TYPES_ALLOCATOR_HPP_
#define MM_TYPES_ALLOCATOR_HPP_

namespace mm {
namespace allocator {

	typedef
		nstd :: memory :: allocator :: Heap
		Heap;
	typedef
		nstd :: memory :: allocator :: Standard
		Standard;
}
namespace memory {

	using nstd :: memory :: UsageMessage;
	using namespace nstd :: memory :: exception;
}
	template<class T>
	class Scalar : public nstd :: memory :: storage :: Scalar<T, allocator :: Heap> {
	};
}

#endif /*MM_TYPES_ALLOCATOR_HPP_*/
