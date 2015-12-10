/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_strategy_Constraints.hpp                      */
/* Description:     constraints on proof search tree                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_STRATEGY_CONSTRAINTS_HPP_
#define MDL_PROVER_STRATEGY_CONSTRAINTS_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/prover/mdl_prover.dpp"

namespace mdl {
namespace prover {
namespace strategy {

class Constraints :
	public object :: Object,
	public Scalar<Constraints, allocator :: Heap>{
public :
	value :: Integer maxComplexity() const;
	value :: Integer maxHeight() const;

	void setMaxComplexity();
	void setMaxComplexity(value :: Integer);
	void setMaxHeight();
	void setMaxHeight(value :: Integer);

	static Constraints& get();

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	Constraints();
	~Constraints();

	value :: Integer maxComplexity_;
	value :: Integer maxHeight_;
};

}
}
}

#endif /*MDL_PROVER_STRATEGY_CONSTRAINTS_HPP_*/
