/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_pool_Universal.hpp                         */
/* Description:     pool for cloning arbitrary classes                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_AUXILIARY_POOL_UNIVERSAL_HPP_
#define MDL_AUXILIARY_POOL_UNIVERSAL_HPP_

#include "mdl/auxiliary/pool/mdl_auxiliary_pool_Unit.hpp"

namespace mdl {
namespace auxiliary {
namespace pool {

template
<
	class A_1 = allocator :: Heap,
	class A_2 = allocator :: Stack
>
class Universal : public Scalar<Universal<A_1, A_2>, A_2> {
private :
	enum { INITIAL_POOL_CAPACITY = 256 };
public :
	typedef A_1 CloneAllocator_;
	typedef A_2 PoolAllocator_;

	Universal (const Size_t = INITIAL_POOL_CAPACITY);
	virtual ~ Universal();

	template<class T>
	T* clone (T*);
	template<class T>
	void add (T*, T* = NULL);

private :
	typedef
		Unit<void, CloneAllocator_, PoolAllocator_, Universal>
		Unit_;
	Unit_ unit_;
};

}
}
}

#include "mdl/auxiliary/pool/mdl_auxiliary_pool_Universal.ipp"

#endif /*MDL_AUXILIARY_POOL_UNIVERSAL_HPP_*/
