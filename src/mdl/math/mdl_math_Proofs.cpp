/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_math_Proofs.cpp                                      */
/* Description:     global container for proofs                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_MATH_PROOFS_CPP_
#define MDL_MATH_PROOFS_CPP_

namespace mdl {
namespace math {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Proofs :: Proofs () :
	proofVector_ (INITIAL_PROOF_VECTOR_CAPACITY),
	mutex_ () {
		pthread_mutex_init (&mutex_, NULL);
	}
	Proofs :: ~ Proofs () {
	}

	inline index :: Assertion
	Proofs :: getSize() const {
		return proofVector_.getSize();
	}
	inline mdl :: Proof*
	Proofs :: get (const index :: Assertion index) {
		return proofVector_.getValue (index);
	}
	inline void
	Proofs :: add (mdl :: Proof* proof)
	{
		pthread_mutex_lock (&mutex_);
		proofVector_.add (proof);
		pthread_mutex_unlock (&mutex_);
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;
	
	// object :: Object implementation
	void
	Proofs :: commitSuicide() {
		delete this;
	}
	Size_t
	Proofs :: getVolume() const
	{
		Size_t volume = 0;
		volume += proofVector_.getVolume();
		return volume;
	}
	Size_t
	Proofs :: getSizeOf() const {
		return sizeof (Proofs);
	}
	void
	Proofs :: show (String& string) const {
		string << tab << "proofs:    " << tab << proofVector_.getSize() << endLine;
	}
}
}

#endif /*MDL_MATH_PROOFS_CPP_*/
