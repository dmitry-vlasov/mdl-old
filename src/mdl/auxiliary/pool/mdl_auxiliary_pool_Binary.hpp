/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_pool_Binary.hpp                            */
/* Description:     pool for cloning pairs of dependent classes              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_AUXILIARY_POOL_BINARY_HPP_
#define MDL_AUXILIARY_POOL_BINARY_HPP_

#include "mdl/auxiliary/pool/mdl_auxiliary_pool_Unit.hpp"

namespace mdl {
namespace auxiliary {
namespace pool {

template
<
	class T_1,
	class T_2,
	class A_1 = allocator :: Heap,
	class A_2 = allocator :: Stack
>
class Binary : public Scalar<Binary<T_1, T_2, A_1, A_2>, A_2> {
private :
	enum { INITIAL_POOL_CAPACITY = 256 };
public :
	typedef T_1 Type_1_;
	typedef T_2 Type_2_;
	typedef A_1 CloneAllocator_;
	typedef A_2 PoolAllocator_;

	Binary (const Size_t = INITIAL_POOL_CAPACITY);
	virtual ~ Binary();

	Type_1_* clone (Type_1_*);
	Type_2_* clone (Type_2_*);
	template<class T_3>
	T_3* clone (T_3*);

	void add (Type_1_*, Type_1_* = NULL);
	void add (Type_2_*, Type_2_* = NULL);

private :
	typedef
		Unit<Type_1_, CloneAllocator_, PoolAllocator_, Binary>
		Unit_1_;
	typedef
		Unit<Type_2_, CloneAllocator_, PoolAllocator_, Binary>
		Unit_2_;

	Unit_1_ unit_1_;
	Unit_2_ unit_2_;
};

}
}
}

#include "mdl/auxiliary/pool/mdl_auxiliary_pool_Binary.ipp"

#endif /*MDL_AUXILIARY_POOL_BINARY_HPP_*/
