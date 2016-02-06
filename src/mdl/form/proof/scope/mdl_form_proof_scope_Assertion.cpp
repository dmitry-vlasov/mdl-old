/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_scope_Assertion.cpp                       */
/* Description:     scope which contains assertion                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/form/mdl_form.hpp"

namespace mdl {
namespace form {
namespace proof {
namespace scope {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Assertion :: Assertion (mdl :: Assertion* assertion) :
	Ancestor (NULL),
	assertion_ (assertion) {
	}
	Assertion :: ~ Assertion() {
	}

	// proof :: Scope implementation
	mdl :: Assertion*
	Assertion :: getAssertion () {
		return assertion_;
	}
	mdl :: Proof*
	Assertion :: getProof() {
		return NULL;
	}
	mdl :: proof :: Claim*
	Assertion :: getClaim() {
		return NULL;
	}
	mdl :: proof :: Node*
	Assertion :: getHypothesis (const index :: Arity index)
	{
		if (index >= assertion_->getHypArity()) {
			return NULL;
		}
		return assertion_->getHypothesis (index)->getProofNode();
	}
	mdl :: proof :: Node*
	Assertion :: getProposition (const index :: Arity index)
	{
		if (index >= assertion_->getPropArity()) {
			return NULL;
		}
		return assertion_->getProposition (index)->getProofNode();
	}
	object :: Typing*
	Assertion :: getVariables () {
		return assertion_->getVariables();
	}
	mdl :: proof :: Notation*
	Assertion :: getNotation (const value :: Literal) {
		return NULL;
	}
	mdl :: proof :: Step*
	Assertion :: getStep (const index :: Step) {
		return NULL;
	}

	const mdl :: Assertion*
	Assertion :: getAssertion () const {
		return assertion_;
	}
	const mdl :: Proof*
	Assertion :: getProof() const {
		return NULL;
	}
	const mdl :: proof :: Claim*
	Assertion :: getClaim() const {
		return NULL;
	}
	const mdl :: proof :: Node*
	Assertion :: getHypothesis (const index :: Arity index) const {
		return assertion_->getHypothesis (index)->getProofNode();
	}
	const mdl :: proof :: Node*
	Assertion :: getProposition (const index :: Arity index) const {
		return assertion_->getProposition (index)->getProofNode();
	}
	const object :: Typing*
	Assertion :: getVariables () const {
		return assertion_->getVariables();
	}
	const mdl :: proof :: Notation*
	Assertion :: getNotation (const value :: Literal) const {
		return NULL;
	}
	const mdl :: proof :: Step*
	Assertion :: getStep (const index :: Step) const {
		return NULL;
	}

	// object :: Object implementation
	void
	Assertion :: commitSuicide() {
		delete this;
	}
	Size_t
	Assertion :: getVolume() const {
		return 0;
	}
	Size_t
	Assertion :: getSizeOf() const {
		return sizeof (Assertion);
	}
}
}
}
}


