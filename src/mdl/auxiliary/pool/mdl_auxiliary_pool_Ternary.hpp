/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_pool_Ternary.hpp                           */
/* Description:     pool for cloning triples of dependent classes            */
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
	class T_1,
	class T_2,
	class T_3,
	class A_1 = allocator :: Heap,
	class A_2 = allocator :: Stack
>
class Ternary : public Scalar<Ternary<T_1, T_2, T_3, A_1, A_2>, A_2> {
private :
	enum { INITIAL_POOL_CAPACITY = 256 };
public :
	typedef T_1 Type_1_;
	typedef T_2 Type_2_;
	typedef T_3 Type_3_;
	typedef A_1 CloneAllocator_;
	typedef A_2 PoolAllocator_;

	Ternary (const Size_t = INITIAL_POOL_CAPACITY);
	virtual ~ Ternary();

	Type_1_* clone (Type_1_*);
	Type_2_* clone (Type_2_*);
	Type_3_* clone (Type_3_*);
	template<class T_4>
	T_4* clone (T_4*);

	void add (Type_1_*, Type_1_* = NULL);
	void add (Type_2_*, Type_2_* = NULL);
	void add (Type_3_*, Type_3_* = NULL);

private :
	typedef
		Unit<Type_1_, CloneAllocator_, PoolAllocator_, Ternary>
		Unit_1_;
	typedef
		Unit<Type_2_, CloneAllocator_, PoolAllocator_, Ternary>
		Unit_2_;
	typedef
		Unit<Type_3_, CloneAllocator_, PoolAllocator_, Ternary>
		Unit_3_;

	Unit_1_ unit_1_;
	Unit_2_ unit_2_;
	Unit_3_ unit_3_;
};

}
}
}

#include "mdl/auxiliary/pool/mdl_auxiliary_pool_Ternary.ipp"


