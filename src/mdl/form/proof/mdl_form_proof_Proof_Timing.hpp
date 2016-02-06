/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_Proof_Timing.hpp                          */
/* Description:     timer for proof compression                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/form/proof/mdl_form_proof.dpp"

namespace mdl {
namespace form {
namespace proof {

class Proof :: Timing :
	public object :: Object,
	public Scalar<Proof :: Timing, allocator :: Heap> {
public :
	Timing (const mdl :: Proof*);
	virtual ~ Timing();

	Time calculateTimeLimit (const bool exactAssertion);
	void incrementProveActs();

	mdl :: Timer& timer();
	const mdl :: Timer& getTimer() const;

	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	value :: Long estimateProveActsLeft (const bool exactAssertion);
	index :: Step estimateProveActs ();
	index :: Step estimateProveActs (const mdl :: Assertion* const);
	Time estimateClocksPerProveAct (value :: Long proveActsLeft);

	const mdl :: Proof* proof_;
	Timer timer_;

	// prove time estimation attributes
	static value :: Long proveActsTotal_;
	static value :: Long proveActsDone_;
	static Time averageClocksForProve_;
};

}
}
}


