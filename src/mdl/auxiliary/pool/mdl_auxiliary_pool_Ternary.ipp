/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_pool_Ternary.ipp                           */
/* Description:     pool for cloning triples of dependent classes            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace auxiliary {
namespace pool {

	/****************************
	 *		Public members
	 ****************************/

	template<class T_1, class T_2, class T_3, class A_1, class A_2>
	inline
	Ternary<T_1, T_2, T_3, A_1, A_2> :: Ternary (const Size_t initialCapacity) :
	unit_1_ (initialCapacity),
	unit_2_ (initialCapacity),
	unit_3_ (initialCapacity) {
	}
	template<class T_1, class T_2, class T_3, class A_1, class A_2>
	Ternary<T_1, T_2, T_3, A_1, A_2> :: ~ Ternary() {
	}

	template<class T_1, class T_2, class T_3, class A_1, class A_2>
	inline typename Ternary<T_1, T_2, T_3, A_1, A_2> :: Type_1_*
	Ternary<T_1, T_2, T_3, A_1, A_2> :: clone (Type_1_* object) {
		return unit_1_.clone (object, this);
	}
	template<class T_1, class T_2, class T_3, class A_1, class A_2>
	inline typename Ternary<T_1, T_2, T_3, A_1, A_2> :: Type_2_*
	Ternary<T_1, T_2, T_3, A_1, A_2> :: clone (Type_2_* object) {
		return unit_2_.clone (object, this);
	}
	template<class T_1, class T_2, class T_3, class A_1, class A_2>
	inline typename Ternary<T_1, T_2, T_3, A_1, A_2> :: Type_3_*
	Ternary<T_1, T_2, T_3, A_1, A_2> :: clone (Type_3_* object) {
		return unit_3_.clone (object, this);
	}
	template<class T_1, class T_2, class T_3, class A_1, class A_2>
	template<class T_4>
	inline T_4*
	Ternary<T_1, T_2, T_3, A_1, A_2> :: clone (T_4* object) {
		return object;
	}

	template<class T_1, class T_2, class T_3, class A_1, class A_2>
	void
	Ternary<T_1, T_2, T_3, A_1, A_2> :: add (Type_1_* object, Type_1_* clone) {
		unit_1_.add (object, clone);
	}
	template<class T_1, class T_2, class T_3, class A_1, class A_2>
	void
	Ternary<T_1, T_2, T_3, A_1, A_2> :: add (Type_2_* object, Type_2_* clone) {
		unit_2_.add (object, clone);
	}
	template<class T_1, class T_2, class T_3, class A_1, class A_2>
	void
	Ternary<T_1, T_2, T_3, A_1, A_2> :: add (Type_3_* object, Type_3_* clone) {
		unit_3_.add (object, clone);
	}
}
}
}


