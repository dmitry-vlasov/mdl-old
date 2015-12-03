/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_pool_Unary.ipp                             */
/* Description:     pool for cloning single classes                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_AUXILIARY_POOL_UNARY_IPP_
#define MDL_AUXILIARY_POOL_UNARY_IPP_

namespace mdl {
namespace auxiliary {
namespace pool {

	/****************************
	 *		Public members
	 ****************************/

	template<class T, class A_1, class A_2>
	inline
	Unary<T, A_1, A_2> :: Unary (const Size_t InitialCapacity) :
	unit_ (InitialCapacity) {
	}
	template<class T, class A_1, class A_2>
	Unary<T, A_1, A_2> :: ~ Unary() {
	}

	template<class T, class A_1, class A_2>
	inline typename Unary<T, A_1, A_2> :: Type_*
	Unary<T, A_1, A_2> :: clone (Type_* object) {
		return unit_.clone (object, this);
	}
	template<class T, class A_1, class A_2>
	template<class T_1>
	inline T_1*
	Unary<T, A_1, A_2> :: clone (T_1* object) {
		return object;
	}

	template<class T, class A_1, class A_2>
	void
	Unary<T, A_1, A_2> :: add (Type_* object, Type_* clone) {
		unit_.add (object, clone);
	}
}
}
}

#endif /*MDL_AUXILIARY_POOL_UNARY_IPP_*/
