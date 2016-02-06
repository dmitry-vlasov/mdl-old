/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_pool_Unit.hpp                              */
/* Description:     utility class pool for cloning classes                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/types/mdl_types.hpp"

namespace mdl {
namespace auxiliary {
namespace pool {

template<class T, class A_1, class A_2, class P>
class Unit : public Scalar<Unit<T, A_1, A_2, P>, A_2> {
private :
	enum { INITIAL_UNIT_CAPACITY = 256 };
public :
	typedef T Type_;
	typedef A_1 CloneAllocator_;
	typedef A_2 PoolAllocator_;
	typedef P Pool_;

	Unit (const Size_t = INITIAL_UNIT_CAPACITY);
	virtual ~ Unit();

	Type_* clone (Type_*, Pool_*);
	void add (Type_*, Type_* = NULL);

	template<class N>
	N* clone (N*, Pool_*);
	template<class N>
	void add (N*, N* = NULL);

private :
	typedef
		typename map :: Scalar
		<Type_*, Type_*, PoolAllocator_>
		Map_;

	Map_ map_;
};

}
}
}

#include "mdl/auxiliary/pool/mdl_auxiliary_pool_Unit.ipp"


