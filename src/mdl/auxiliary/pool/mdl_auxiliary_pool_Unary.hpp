/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_pool_Unary.hpp                             */
/* Description:     pool for cloning single classes                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/auxiliary/pool/mdl_auxiliary_pool_Unit.hpp"

namespace mdl {
namespace auxiliary {
namespace pool {

template
<
	class T,
	class A_1 = allocator :: Heap,
	class A_2 = allocator :: Stack
>
class Unary : public Scalar<Unary<T, A_1, A_2>, A_2> {
private :
	enum { INITIAL_POOL_CAPACITY = 256 };
public :
	typedef T Type_;
	typedef A_1 CloneAllocator_;
	typedef A_2 PoolAllocator_;

	Unary (const Size_t = INITIAL_POOL_CAPACITY);
	virtual ~ Unary();

	Type_* clone (Type_*);
	template<class T_1>
	T_1* clone (T_1*);
	void add (Type_*, Type_* = NULL);

private :
	typedef
		Unit<Type_, CloneAllocator_, PoolAllocator_, Unary>
		Unit_;
	Unit_ unit_;
};

}
}
}

#include "mdl/auxiliary/pool/mdl_auxiliary_pool_Unary.ipp"


