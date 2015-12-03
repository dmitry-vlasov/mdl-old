/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_container_discrete_Bidirectional.hpp                */
/* Description:     bidirectional connectivity policy for lists              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_CONTAINER_DISCRETE_BIDIRECTIONAL_HPP_
#define NSTD_CONTAINER_DISCRETE_BIDIRECTIONAL_HPP_

#include "container/discrete/nstd_container_discrete_Unidirectional.hpp"

namespace nstd {
namespace container {
namespace discrete {

template
<
	class S,
	class A,
	class N
>
class Bidirectional : public Unidirectional<S, A, N> {
public :
	typedef
		Unidirectional<S, A, N>
		Unidirectional_;
	typedef
		typename Unidirectional_ :: Argument_
		Argument_;
	typedef
		typename Unidirectional_ :: Node_
		Node_;
	typedef
		typename Unidirectional_ :: Storage_
		Storage_;

	Bidirectional ();
	Bidirectional (const Argument_ , const Direction, const Node_*  = NULL);
	virtual ~ Bidirectional();

	const Node_* getPrevious() const;
	void setNext (const Node_* const) const;
	void setPrev (const Node_* const) const;

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
	const Node_* previous_;
};

}
}
}

#endif /* NSTD_CONTAINER_DISCRETE_BIDIRECTIONAL_HPP_ */
