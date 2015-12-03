/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_types_allocator.hpp                                  */
/* Description:     basic types for memory management                        */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_TYPES_ALLOCATOR_HPP_
#define SMM_TYPES_ALLOCATOR_HPP_

namespace smm {
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

#endif /*SMM_TYPES_ALLOCATOR_HPP_*/
