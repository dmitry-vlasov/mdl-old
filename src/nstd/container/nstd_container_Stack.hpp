/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_container_Stack.hpp                                 */
/* Description:     stack container                                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_CONTAINER_STACK_HPP_
#define NSTD_CONTAINER_STACK_HPP_

#include "container/nstd_container_Vector.hpp"

namespace nstd {
namespace container {

template
<
	class T,                 ///< stored type
	template<class> class H, ///< storage policy (by value, by pointer, etc.)
	class A                  ///< allocator
>
class Stack :
	public memory :: storage :: Scalar
	<
		Stack<T, H, A>,
		A
	> {
public :
	typedef Vector<T, H, A> Vector_;
	typedef typename Vector_ :: Index_ Index_;
	typedef typename Vector_ :: Reference_ Reference_;
	typedef typename Vector_ :: const_Reference_ const_Reference_;

	Stack ();
	Stack (const Index_);
	virtual ~ Stack();

	Reference_ pop();
	const_Reference_ pop() const;
	Reference_ push();
	Reference_ pushRaw();
	void push (const_Reference_);
	bool isEmpty() const;
	const Vector_ getVector() const;
	Size_t getCapacity() const;

	// nstd :: Object interface
	void commitSuicide();
	Size_t getVolume() const;
	Size_t getSizeOf() const;
	template<class S>
	void show (S&) const;

private :
	Vector_ vector_;
};

	template<class S, class T, template<class> class H, class A>
	S&
	operator << (S&, const Stack<T, H, A>&);
}
}

#endif /* NSTD_CONTAINER_STACK_HPP_ */
