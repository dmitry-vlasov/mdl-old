/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_strategy_BestInLevel.hpp                        */
/* Description:     directed strategy                                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_STRATEGY_BEST_IN_LEVEL_HPP_
#define MDL_PROVER_STRATEGY_BEST_IN_LEVEL_HPP_

namespace mdl {
namespace prover {
namespace strategy {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	BestInLevel<A> :: BestInLevel (Tree_* tree) :
	tree_(tree) {
	}

	template<class A>
	inline
	BestInLevel<A> :: ~ BestInLevel() {
		tree_ = NULL;
	}

	// prover :: Strategy implementation
	template<class A>
	void
	BestInLevel<A> :: use (const Time limit) {


	}

	// object :: Object implementation
	template<class A>
	void
	BestInLevel<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	BestInLevel<A> :: getVolume() const {
		return 0;
	}
	template<class A>
	Size_t
	BestInLevel<A> :: getSizeOf() const {
		return sizeof (BestInLevel);
	}
	template<class A>
	void
	BestInLevel<A> :: show (String&) const {
	}
}
}
}


#endif /*MDL_PROVER_STRATEGY_BEST_IN_LEVEL_HPP_*/
