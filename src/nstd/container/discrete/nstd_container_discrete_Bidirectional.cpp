/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_container_discrete_Bidirectional.cpp                */
/* Description:     bidirectional connectivity policy for lists              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_CONTAINER_DISCRETE_BIDIRECTIONAL_CPP_
#define NSTD_CONTAINER_DISCRETE_BIDIRECTIONAL_CPP_

namespace nstd {
namespace container {
namespace discrete {

	/****************************
	 *		Public members
	 ****************************/

	template<class S, class A, class N>
	inline
	Bidirectional<S, A, N> :: Bidirectional
	(
		const Argument_ value,
		const Direction direction,
		const Node_* node
	) :
	Unidirectional_ (value, node),
	previous_ (direction == LEFT ? node : NULL)
	{
		if (direction == RIGHT && node != NULL) {
				node->previous_ = static_cast<const Node_*>(this);
		}
	}
	template<class S, class A, class N>
	Bidirectional<S, A, N> :: ~ Bidirectional() {
	}

	template<class S, class A, class N>
	inline const typename Bidirectional<S, A, N> :: Node_*
	Bidirectional<S, A, N> :: getPrevious() const {
		return previous_;
	}
	template<class S, class A, class N>
	inline void
	Bidirectional<S, A, N> :: setNext (const Node_* const next) const
	{
		Unidirectional_ :: setNext (next);
		if (Unidirectional_ :: next_ != NULL) {
			Unidirectional_ :: next_->previous_ = this;
		}
	}
	template<class S, class A, class N>
	inline void
	Bidirectional<S, A, N> :: setPrev (const Node_* const prev) const
	{
		previous_ = prev;
		if (prev != NULL) {
			prev->setNext (this);
		}
	}

	template<class S, class A, class N>
	inline void
	Bidirectional<S, A, N> :: remove
	(
		const Node_* prev,
		const Node_* node,
		const Node_* next
	)
	{
		Unidirectional_ :: remove (prev, node, next);
		if (next != NULL) {
			next->setPrev (prev);
		}
		node->netPrev (NULL);
	}

	// nstd :: Object implementation
	template<class S, class A, class N>
	inline void
	Bidirectional<S, A, N> :: commitSuicide() {
		delete this;
	}
	template<class S, class A, class N>
	inline Size_t
	Bidirectional<S, A, N> :: getVolume () const {
		return Unidirectional_ :: getVolume();
	}
	template<class S, class A, class N>
	inline Size_t
	Bidirectional<S, A, N> :: getSizeOf() const {
		return sizeof (Bidirectional);
	}
	template<class S, class A, class N>
	template<class T>
	void
	Bidirectional<S, A, N> :: show (T& s) const {
		Unidirectional_ :: show (s);
	}
}
}
}

#endif /* NSTD_CONTAINER_DISCRETE_BIDIRECTIONAL_CPP_ */
