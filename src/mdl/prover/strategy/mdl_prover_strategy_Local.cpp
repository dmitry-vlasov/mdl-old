/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_strategy_Local.hpp                            */
/* Description:     local strategy                                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_STRATEGY_LOCAL_HPP_
#define MDL_PROVER_STRATEGY_LOCAL_HPP_

namespace mdl {
namespace prover {
namespace strategy {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	Local<A> :: Local (Tree_* tree) : tree_(tree) { }

	template<class A>
	inline
	Local<A> :: ~ Local() {
		tree_ = NULL;
	}

	// prover :: Strategy implementation
	template<class A>
	void
	Local<A> :: use (const Time limit) {

	}

	// object :: Object implementation
	template<class A>
	void
	Local<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Local<A> :: getVolume() const {
		return 0;
	}
	template<class A>
	Size_t
	Local<A> :: getSizeOf() const {
		return sizeof (Directed);
	}
	template<class A>
	void
	Local<A> :: show (String&) const {
	}
}
}
}


#endif /*MDL_PROVER_STRATEGY_LOCAL_HPP_*/
