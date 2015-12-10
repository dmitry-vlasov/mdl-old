/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_strategy_BestInAll.hpp                        */
/* Description:     directed strategy                                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_STRATEGY_BEST_IN_ALL_CPP_
#define MDL_PROVER_STRATEGY_BEST_IN_ALL_CPP_

namespace mdl {
namespace prover {
namespace strategy {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	BestInAll<A> :: BestInAll (Tree_* tree) :
	tree_(tree) {
	}

	template<class A>
	inline
	BestInAll<A> :: ~ BestInAll() {
		tree_ = NULL;
	}

	// prover :: Strategy implementation
	template<class A>
	bool
	BestInAll<A> :: use() {


	}

	// object :: Object implementation
	template<class A>
	void
	BestInAll<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	BestInAll<A> :: getVolume() const {
		return 0;
	}
	template<class A>
	Size_t
	BestInAll<A> :: getSizeOf() const {
		return sizeof (BestInAll);
	}
	template<class A>
	void
	BestInAll<A> :: show (String&) const {
	}
}
}
}


#endif /*MDL_PROVER_STRATEGY_BEST_IN_ALL_CPP_*/
