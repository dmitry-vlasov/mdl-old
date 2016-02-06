/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_math_Proofs.hpp                                      */
/* Description:     global container for proofs                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/math/mdl_math_Container.hpp"

namespace mdl {
namespace math {

class Proofs :
	public object :: Object,
	public Scalar<Proofs> {
public :
	Proofs ();
	virtual ~ Proofs();
	
	index :: Assertion getSize() const;
	void add (mdl :: Proof*);
	mdl :: Proof* get (const index :: Assertion);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;
	
private :
	typedef
		vector :: Vector
		<
			Proof,
			storage :: ByWeakPointer,
			allocator :: Heap
		>
		ProofVector_;

	enum {
		INITIAL_PROOF_VECTOR_CAPACITY = size :: KILOBYTE * 64
	};

	ProofVector_ proofVector_;
	pthread_mutex_t mutex_;
};

}
}


