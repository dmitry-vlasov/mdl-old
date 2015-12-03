/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_container_discrete_Unidirectional.hpp               */
/* Description:     unidirectional connectivity policy for lists             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_CONTAINER_DISCRETE_UNIDIRECTIONAL_HPP_
#define NSTD_CONTAINER_DISCRETE_UNIDIRECTIONAL_HPP_

#include "container/discrete/nstd_container_discrete_Direction.hpp"

namespace nstd {
namespace container {
namespace discrete {

template
<
	class S,
	class A,
	class N
>
class Unidirectional :
	public S,
	public memory :: storage :: Scalar
	<
		Unidirectional<S, A, N>,
		A
	> {
public :
	typedef N Node_;
	typedef S Storage_;
	typedef typename Storage_ :: Type_ Type_;
	typedef typename Storage_ :: Argument_ Argument_;
	typedef typename Storage_ :: Value_ Value_;
	typedef typename Storage_ :: Reference_ Reference_;
	typedef typename Storage_ :: const_Reference_ const_Reference_;

	Unidirectional ();
	Unidirectional (const Argument_ , const Direction, const Node_*  = NULL);
	virtual ~ Unidirectional();

	Value_ getValue() const;
	Reference_ getReference();
	const_Reference_ getReference() const;

	const Node_* getNext() const;
	void setNext (const Node_* const) const;

	static void remove
	(
		const Node_* prev,
		const Node_* node,
		const Node_* next
	);

	// nstd :: Object interface
	void commitSuicide();
	Size_t getVolume () const;
	Size_t getSizeOf() const;
	template<class T>
	void show (T&) const;

protected :
	mutable const Node_* next_;
};

}
}
}

#endif /* NSTD_CONTAINER_DISCRETE_UNIDIRECTIONAL_HPP_ */
