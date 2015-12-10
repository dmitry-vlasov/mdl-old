/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_strategy_Scheduler.hpp                        */
/* Description:     strategy scheduler                                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_STRATEGY_SCHEDULER_HPP_
#define MDL_PROVER_STRATEGY_SCHEDULER_HPP_

namespace mdl {
namespace prover {
namespace strategy {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	Scheduler<A> :: Scheduler (Tree_* tree) :
	tree_(tree), timers_(), strategies_()
	{
		strategies_[DIRECTED]      = new Directed_ (tree_);
		strategies_[BEST_IN_ALL]   = new BestInAll_ (tree_);
		strategies_[BEST_IN_LEVEL] = new BestInLevel_(tree_);
	}

	template<class A>
	inline
	Scheduler<A> :: ~ Scheduler()
	{
		for (int i = 0; i < STRATEGY_NUM; ++ i) {
			if (strategies_[i] != NULL) {
				delete strategies_[i];
				strategies_[i] = NULL;
			}
		}
		tree_ = NULL;
	}

	// prover :: Strategy implementation
	template<class A>
	void
	Scheduler<A> :: use (const Time limit) {
		strategies_ [BEST_IN_LEVEL]->use (limit);
	}

	// object :: Object implementation
	template<class A>
	void
	Scheduler<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Scheduler<A> :: getVolume() const
	{
		Size_t volume = 0;
		for (int i = 0; i < STRATEGY_NUM; ++ i) {
			if (strategies_[i] != NULL) {
				volume += getAggregateVolume (strategies_[i]);
			}
		}
		return volume;
	}
	template<class A>
	Size_t
	Scheduler<A> :: getSizeOf() const {
		return sizeof (Scheduler);
	}
	template<class A>
	void
	Scheduler<A> :: show (String&) const {
	}
}
}
}


#endif /*MDL_PROVER_STRATEGY_SCHEDULER_HPP_*/
