/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_pool_Binary.ipp                            */
/* Description:     pool for cloning pairs of dependent classes              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_AUXILIARY_POOL_BINARY_IPP_
#define MDL_AUXILIARY_POOL_BINARY_IPP_

namespace mdl {
namespace auxiliary {
namespace pool {

	/****************************
	 *		Public members
	 ****************************/

	template<class T_1, class T_2, class A_1, class A_2>
	inline
	Binary<T_1, T_2, A_1, A_2> :: Binary (const Size_t initialCapacity) :
	unit_1_ (initialCapacity),
	unit_2_ (initialCapacity) {
	}
	template<class T_1, class T_2, class A_1, class A_2>
	Binary<T_1, T_2, A_1, A_2> :: ~ Binary() {
	}

	template<class T_1, class T_2, class A_1, class A_2>
	inline typename Binary<T_1, T_2, A_1, A_2> :: Type_1_*
	Binary<T_1, T_2, A_1, A_2> :: clone (Type_1_* object) {
		return unit_1_.clone (object, this);
	}
	template<class T_1, class T_2, class A_1, class A_2>
	inline typename Binary<T_1, T_2, A_1, A_2> :: Type_2_*
	Binary<T_1, T_2, A_1, A_2> :: clone (Type_2_* object) {
		return unit_2_.clone (object, this);
	}
	template<class T_1, class T_2, class A_1, class A_2>
	template<class T_3>
	inline T_3*
	Binary<T_1, T_2, A_1, A_2> :: clone (T_3* object) {
		return object;
	}

	template<class T_1, class T_2, class A_1, class A_2>
	void
	Binary<T_1, T_2, A_1, A_2> :: add (Type_1_* object, Type_1_* clone) {
		unit_1_.add (object, clone);
	}
	template<class T_1, class T_2, class A_1, class A_2>
	void
	Binary<T_1, T_2, A_1, A_2> :: add (Type_2_* object, Type_2_* clone) {
		unit_2_.add (object, clone);
	}
}
}
}

#endif /*MDL_AUXILIARY_POOL_BINARY_IPP_*/
