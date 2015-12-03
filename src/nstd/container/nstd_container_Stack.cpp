/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_container_Stack.cpp                                 */
/* Description:     stack container                                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_CONTAINER_STACK_CPP_
#define NSTD_CONTAINER_STACK_CPP_

namespace nstd {
namespace container {

	/****************************
	 *		Public members
	 ****************************/

	template<class T, template<class> class H, class A>
	inline
	Stack<T, H, A> :: Stack () :
	vector_ () {
	}
	template<class T, template<class> class H, class A>
	inline
	Stack<T, H, A> :: Stack (const Index_ initialCapacity) :
	vector_ (initialCapacity) {
	}
	template<class T, template<class> class H, class A>
	inline
	Stack<T, H, A> :: ~ Stack() {
	}

	template<class T, template<class> class H, class A>
	typename Stack<T, H, A> :: Reference_
	Stack<T, H, A> :: pop () {
		return vector_.pop();
	}
	template<class T, template<class> class H, class A>
	typename Stack<T, H, A> :: const_Reference_
	Stack<T, H, A> :: pop () const {
		return vector_.pop();
	}
	template<class T, template<class> class H, class A>
	typename Stack<T, H, A> :: Reference_
	Stack<T, H, A> :: push () {
		return vector_.push();
	}
	template<class T, template<class> class H, class A>
	typename Stack<T, H, A> :: Reference_
	Stack<T, H, A> :: pushRaw () {
		return vector_.pushRaw();
	}
	template<class T, template<class> class H, class A>
	void
	Stack<T, H, A> :: push (const_Reference_ reference) {
		vector_.push() = reference;
	}
	template<class T, template<class> class H, class A>
	bool
	Stack<T, H, A> :: isEmpty() const {
		return vector_.isEmpty();
	}
	template<class T, template<class> class H, class A>
	const typename Stack<T, H, A> :: Vector_
	Stack<T, H, A> :: getVector() const {
		return vector_;
	}
	template<class T, template<class> class H, class A>
	inline Size_t
	Stack<T, H, A> :: getCapacity() const {
		return vector_.getCapacity();
	}


	// nstd :: Object implementation
	template<class T, template<class> class H, class A>
	inline void
	Stack<T, H, A> :: commitSuicide() {
		delete this;
	}
	template<class T, template<class> class H, class A>
	Size_t
	Stack<T, H, A> :: getVolume() const {
		return vector_.getVolume();
	}
	template<class T, template<class> class H, class A>
	Size_t
	Stack<T, H, A> :: getSizeOf() const {
		return sizeof (Stack);
	}
	template<class T, template<class> class H, class A>
	template<class S>
	void
	Stack<T, H, A> :: show (S& s) const {
		vector_.show (s);
	}

	/****************************
	 *		Operators
	 ****************************/

	template<class S, class T, template<class> class H, class A>
	S&
	operator << (S& s, const Stack<T, H, A>& stack)
	{
		stack.template show<S> (s);
		return s;
	}
}
}

#endif /* NSTD_CONTAINER_STACK_CPP_ */
