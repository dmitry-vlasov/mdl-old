/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_container_discrete_Unidirectional.cpp               */
/* Description:     unidirectional connectivity policy for lists             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_CONTAINER_DISCRETE_UNIDIRECTIONAL_CPP_
#define NSTD_CONTAINER_DISCRETE_UNIDIRECTIONAL_CPP_

namespace nstd {
namespace container {
namespace discrete {

	/****************************
	 *		Public members
	 ****************************/

	template<class S, class A, class N>
	inline
	Unidirectional<S, A, N> :: Unidirectional
	(
		const Argument_ value,
		const Direction direction,
		const Node_* node
	) :
	Storage_ (value),
	next_ (direction == RIGHT ? node : NULL)
	{
		if (direction == LEFT && node != NULL) {
			node->next_ = static_cast<const Node_*>(this);
		}
	}
	template<class S, class A, class N>
	Unidirectional<S, A, N> :: ~ Unidirectional() {
	}

	template<class S, class A, class N>
	inline typename Unidirectional<S, A, N> :: Value_
	Unidirectional<S, A, N> :: getValue () const {
		return Storage_ :: getValue();
	}
	template<class S, class A, class N>
	inline typename Unidirectional<S, A, N> :: Reference_
	Unidirectional<S, A, N> :: getReference () {
		return Storage_ :: getReference();
	}
	template<class S, class A, class N>
	inline typename Unidirectional<S, A, N> :: const_Reference_
	Unidirectional<S, A, N> :: getReference () const {
		return Storage_ :: getReference();
	}
	template<class S, class A, class N>
	inline const typename Unidirectional<S, A, N> :: Node_*
	Unidirectional<S, A, N> :: getNext() const {
		return next_;
	}
	template<class S, class A, class N>
	inline void
	Unidirectional<S, A, N> :: setNext (const Node_* const next) const {
		next_ = next;
	}

	template<class S, class A, class N>
	inline void
	Unidirectional<S, A, N> :: remove
	(
		const Node_* prev,
		const Node_* node,
		const Node_* next
	)
	{
		if (prev != NULL) {
			prev->setNext (next);
		}
		node->setNext (NULL);
	}

	// nstd :: Object implementation
	template<class S, class A, class N>
	inline void
	Unidirectional<S, A, N> :: commitSuicide() {
		delete this;
	}
	template<class S, class A, class N>
	inline Size_t
	Unidirectional<S, A, N> :: getVolume () const {
		return Storage_ :: getVolume();
	}
	template<class S, class A, class N>
	inline Size_t
	Unidirectional<S, A, N> :: getSizeOf() const {
		return sizeof (Unidirectional);
	}
	template<class S, class A, class N>
	template<class T>
	void
	Unidirectional<S, A, N> :: show (T& s) const {
		Storage_ :: show (s);
	}
}
}
}

#endif /* NSTD_CONTAINER_DISCRETE_UNIDIRECTIONAL_CPP_ */
