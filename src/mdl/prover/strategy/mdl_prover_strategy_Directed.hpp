/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_strategy_Directed.hpp                         */
/* Description:     directed strategy                                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_STRATEGY_DIRECTED_HPP_
#define MDL_PROVER_STRATEGY_DIRECTED_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/prover/mdl_prover.dpp"

namespace mdl {
namespace prover {
namespace strategy {

template<class A>
class Directed :
	public Strategy<A>,
	public Scalar<Directed<A>, A>{
public :
	typedef A Allocator_;
	typedef
		typename tree :: Timers<Allocator_>
		Timers_;
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

	Directed (Tree* tree);
	virtual ~ Directed();

	// prover :: Strategy interface
	virtual void use (const Time limit);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	Tree* tree_;
};

}
}
}

#endif /*MDL_PROVER_STRATEGY_DIRECTED_HPP_*/
