/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_pool_Unit.ipp                              */
/* Description:     utility class pool for cloning classes                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_AUXILIARY_POOL_UNIT_IPP_
#define MDL_AUXILIARY_POOL_UNIT_IPP_

namespace mdl {
namespace auxiliary {
namespace pool {

	/****************************
	 *		Public members
	 ****************************/

	template<class T, class A_1, class A_2, class P>
	inline
	Unit<T, A_1, A_2, P> :: Unit (const Size_t InitialCapacity) :
	map_ (InitialCapacity) {
	}
	template<class T, class A_1, class A_2, class P>
	Unit<T, A_1, A_2, P> :: ~ Unit() {
	}

	template<class T, class A_1, class A_2, class P>
	typename Unit<T, A_1, A_2, P> :: Type_*
	Unit<T, A_1, A_2, P> :: clone (Type_* object, Pool_* pool)
	{
		if (object == NULL) {
			return NULL;
		}
		Type_* clone = map_.find (object);
		if (clone != NULL) {
			return clone;
		}
		clone = object->template cloneSelf<CloneAllocator_>();
		map_.add (object, clone);
		clone->cloneContents (pool);
		return clone;
	}

	template<class T, class A_1, class A_2, class P>
	void
	Unit<T, A_1, A_2, P> :: add (Type_* object, Type_* clone)
	{
		if (clone == NULL) {
			map_.add (object, object);
		} else {
			map_.add (object, clone);
		}
	}

	template<class T, class A_1, class A_2, class P>
	template<class N>
	N*
	Unit<T, A_1, A_2, P> :: clone (N* object, Pool_* pool)
	{
		if (object == NULL) {
			return NULL;
		}
		N* clone = reinterpret_cast<N*>(map_.find (object));
		if (clone != NULL) {
			return clone;
		}
		clone = object->template cloneSelf<CloneAllocator_>();
		map_.add (object, clone);
		clone->cloneContents (pool);
		return clone;
	}

	template<class T, class A_1, class A_2, class P>
	template<class N>
	void
	Unit<T, A_1, A_2, P> :: add (N* object, N* clone)
	{
		if (clone == NULL) {
			map_.add (object, object);
		} else {
			map_.add (object, clone);
		}
	}
}
}
}

#endif /*MDL_AUXILIARY_POOL_UNIT_IPP_*/
