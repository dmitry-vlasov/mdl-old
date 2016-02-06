/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_Pool.ipp                                   */
/* Description:     pool of pointers for cloning classes                     */
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

	/****************************
	 *		Public members
	 ****************************/

	template<class A_1, class A_2, template<class, class, class> class M>
	inline
	Pool<A_1, A_2, M> :: Pool (const Size_t InitialCapacity) :
	map_ (InitialCapacity) {
	}
	template<class A_1, class A_2, template<class, class, class> class M>
	Pool<A_1, A_2, M> :: ~ Pool() {
	}

	// safe cloning
	template<class A_1, class A_2, template<class, class, class> class M>
	template<class T>
	inline T*
	Pool<A_1, A_2, M> :: clone (T* object)
	{
		if (object == NULL) {
			return NULL;
		}
		T* clone = static_cast<T*>(map_.find (object));
		if (clone != NULL) {
			return clone;
		}
		clone = const_cast<T*>(object->template cloneSelf<CloneAllocator_>());
		map_.add (object, clone);
		const_cast<const T*>(clone)->template cloneContents<Pool> (this);
		return clone;
	}
	template<class A_1, class A_2, template<class, class, class> class M>
	template<class T>
	inline const T*
	Pool<A_1, A_2, M> :: clone (const T* object)
	{
		T* const
			unconstObject = const_cast<T*>(object);
		T* const
			unconstClone = clone (unconstObject);
		const T*
			clone = const_cast<const T*>(unconstClone);
		return clone;
	}
	template<class A_1, class A_2, template<class, class, class> class M>
	template<class T>
	inline void
	Pool<A_1, A_2, M> :: add (T* object, T* clone)
	{
		if (clone == NULL) {
			map_.add (object, object);
		} else {
			map_.add (object, clone);
		}
	}

	// safe transforming
	template<class A_1, class A_2, template<class, class, class> class M>
	template<class T1, class T2>
	inline T1*
	Pool<A_1, A_2, M> :: transform (T2* object)
	{
		if (object == NULL) {
			return NULL;
		}
		T1* clone = static_cast<T1*>(map_.find (object));
		if (clone != NULL) {
			return clone;
		}
		clone = const_cast<T1*>(object->template transformSelf<T1>());
		map_.add (object, clone);
		const_cast<const T1*>(clone)->template transformContents<T2, Pool> (this);
		return clone;
	}
	template<class A_1, class A_2, template<class, class, class> class M>
	template<class T1, class T2>
	inline const T1*
	Pool<A_1, A_2, M> :: transform (const T2* object)
	{
		T2* const
			unconstObject = const_cast<T2*>(object);
		T1* const
			unconstClone = transform<T1, T2> (unconstObject);
		const T1*
			clone = const_cast<const T1*>(unconstClone);
		return clone;
	}
	template<class A_1, class A_2, template<class, class, class> class M>
	template<class T1, class T2>
	inline void
	Pool<A_1, A_2, M> :: add (T2* object, T1* clone)
	{
		if (clone == NULL) {
			map_.add (object, object);
		} else {
			map_.add (object, clone);
		}
	}
}
}


