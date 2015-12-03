/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_Pool.hpp                                   */
/* Description:     pool of pointers for cloning classes                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_AUXILIARY_POOL_HPP_
#define MDL_AUXILIARY_POOL_HPP_

#include "mdl/types/mdl_types.hpp"

namespace mdl {
namespace auxiliary {

template
<
	class A_1 = allocator :: Heap,
	class A_2 = allocator :: Stack,
	template<class, class, class> class M = map :: Scalar
>
class Pool : public Scalar<Pool<A_1, A_2, M>, A_2> {
private :
	enum { INITIAL_CAPACITY = 256 };
public :
	typedef A_1 CloneAllocator_;
	typedef A_2 PoolAllocator_;
	typedef
		M<void*, void*, PoolAllocator_>
		Map_;

	Pool (const Size_t = INITIAL_CAPACITY);
	virtual ~ Pool();

	// safe cloning
	template<class T>
	T* clone (T*);
	template<class T>
	const T* clone (const T*);
	template<class T>
	void add (T*, T* = NULL);

	// safe transforming
	template<class T1, class T2>
	T1* transform (T2*);
	template<class T1, class T2>
	const T1* transform (const T2*);
	template<class T1, class T2>
	void add (T2*, T1* = NULL);

private :
	Map_ map_;
};

}
}

#include "mdl/auxiliary/mdl_auxiliary_Pool.ipp"

#endif /*MDL_AUXILIARY_POOL_HPP_*/
