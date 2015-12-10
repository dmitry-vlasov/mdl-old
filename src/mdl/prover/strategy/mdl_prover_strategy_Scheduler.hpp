/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_strategy_Scheduler.hpp                        */
/* Description:     general strategy scheduler                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_STRATEGY_SCHEDULER_HPP_
#define MDL_PROVER_STRATEGY_SCHEDULER_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/prover/mdl_prover.dpp"
#include "mdl/prover/mdl_prover_Timers.hpp"

namespace mdl {
namespace prover {
namespace strategy {

template<class A>
class Scheduler :
	public object :: Object,
	public Scalar<Scheduler<A>, A>{
public :
	typedef A Allocator_;
	typedef
		Types<Allocator_> Types_;
	typedef
		Strategy<Allocator_> Strategy_;
	typedef
		typename Types_ :: Tree_
		Tree_;
	typedef
		typename Types_ :: Node_
		Node_;
	typedef
		typename Types_ :: Evidence_
		Evidence_;
	typedef
		typename Types_ :: PremiseTree_
		PremiseTree_;
	typedef
		typename Types_ :: PremiseVector_
		PremiseVector_;
	typedef
		typename Types_ :: ExpressionTree_
		ExpressionTree_;
	typedef
		typename Types_ :: Expression_
		Expression_;

	Scheduler (Tree_* tree);
	virtual ~ Scheduler();

	void run (const Time limit);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	enum {
		DIRECTED       = 0,
		BEST_IN_ALL    = 1,
		BEST_IN_LEVEL  = 2,
		STRATEGY_NUM   = 3
	};

	typedef Directed<Allocator_>    Directed_;
	typedef BestInAll<Allocator_>   BestInAll_;
	typedef BestInLevel<Allocator_> BestInLevel_;

	Strategy_* chooseStrategy();

	Tree_*     tree_;
	Timers     timers_;
	Strategy_* strategies_ [STRATEGY_NUM];
};

}
}
}

#endif /*MDL_PROVER_STRATEGY_SCHEDULER_HPP_*/
