/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_node_Rate.hpp                                 */
/* Description:     rate holder class                                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_RATE_RATE_HPP_
#define MDL_PROVER_RATE_RATE_HPP_

#include "mdl/prover/mdl_prover.dpp"

namespace mdl {
namespace prover {
namespace node {

template<class A>
class Rate :
	public object :: Object,
	public Scalar<Rate<A>, A> {
public :
	typedef A Allocator_;
	typedef Types<Allocator_> Types_;
	typedef
		typename Types_ :: Node_
		Node_;
	typedef
		mdl :: vector :: Vector
		<
			Rate,
			storage :: ByPointer,
			Allocator_
		>
		RateVector_;

	Rate (const Node_*, const evaluation :: Term*);
	virtual ~ Rate();

	value :: Real getWeight() const;
	value :: Real eval();
	bool wasChanged() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	const Node_* node_;
	const evaluation :: Term* term_;

	value :: Real weight_;
	RateVector_ subrates_;
	value :: Integer version_;
};

}
}
}

#endif /*MDL_PROVER_RATE_RATE_HPP_*/
