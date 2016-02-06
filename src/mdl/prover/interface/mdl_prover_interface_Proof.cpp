/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_interface_Proof.cpp                           */
/* Description:     interface for proof in prover                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once


namespace mdl {
namespace prover {
namespace interface {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	typename  Proof<A> :: Proof*
	Proof<A> :: findInvalidProof()
	{
		if (this->isValid()) {
			return NULL;
		}
		for (index :: Arity i = 0; i  < this->getUpArity(); ++ i) {
			Proof* upProof = this->getUp (i);
			if (!upProof->isValid()) {
				return upProof->findInvalidProof();
			}
		}
		return this;
	}

	/*********************************
	 *		Overloaded operators
	 *********************************/

	template<class A>
	inline bool
	operator == (const Proof<A>& proof_1, const Proof<A>& proof_2) {
		return proof_1.isIdentical (&proof_2);
	}
}
}
}


