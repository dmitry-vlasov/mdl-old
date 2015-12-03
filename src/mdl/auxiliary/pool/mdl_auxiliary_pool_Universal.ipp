/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_pool_Universal.ipp                         */
/* Description:     pool for cloning arbitrary classes                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_AUXILIARY_POOL_UNIVERSAL_IPP_
#define MDL_AUXILIARY_POOL_UNIVERSAL_IPP_

namespace mdl {
namespace auxiliary {
namespace pool {

	/****************************
	 *		Public members
	 ****************************/

	template<class A_1, class A_2>
	inline
	Universal<A_1, A_2> :: Universal (const Size_t InitialCapacity) :
	unit_ (InitialCapacity) {
	}
	template<class A_1, class A_2>
	Universal<A_1, A_2> :: ~ Universal() {
	}

	template<class A_1, class A_2>
	template<class T>
	inline T*
	Universal<A_1, A_2> :: clone (T* object) {
		return unit_.template clone<T> (object, this);
	}
	template<class A_1, class A_2>
	template<class T>
	void
	Universal<A_1, A_2> :: add (T* object, T* clone) {
		unit_.add (object, clone);
	}
}
}
}

#endif /*MDL_AUXILIARY_POOL_UNIVERSAL_IPP_*/
