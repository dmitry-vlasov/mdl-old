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

#ifndef MDL_PROVER_STRATEGY_BEST_IN_ALL_HPP_
#define MDL_PROVER_STRATEGY_BEST_IN_ALL_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/prover/mdl_prover.dpp"

namespace mdl {
namespace prover {
namespace strategy {

template<class A>
class BestInAll :
	public Strategy<A>,
	public Scalar<BestInAll<A>, A>{
public :
	typedef A Allocator_;
	typedef
		Strategy<Allocator_> Strategy_;
	typedef
		Types<Allocator_> Types_;
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

	BestInAll (Tree_* tree);
	virtual ~ BestInAll();

	// prover :: Strategy interface
	virtual bool use();

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	Tree_*     tree_;
};

}
}
}

#endif /*MDL_PROVER_STRATEGY_BEST_IN_ALL_HPP_*/
