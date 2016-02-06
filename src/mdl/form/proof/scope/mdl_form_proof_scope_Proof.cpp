/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_scope_Proof.cpp                           */
/* Description:     scope which contains proof                               */
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
	Proof :: Proof (mdl :: proof :: Scope* scope, mdl :: Proof* proof) :
	Ancestor (scope),
	proof_ (proof) {
	}
	Proof :: ~ Proof() {
	}

	// proof :: Scope implementation
	mdl :: Assertion*
	Proof :: getAssertion () {
		return scope_->getAssertion();
	}
	mdl :: Proof*
	Proof :: getProof () {
		return proof_;
	}
	mdl :: proof :: Claim*
	Proof :: getClaim() {
		return scope_->getClaim();
	}
	mdl :: proof :: Node*
	Proof :: getHypothesis (const index :: Arity index) {
		return scope_->getHypothesis (index);
	}
	mdl :: proof :: Node*
	Proof :: getProposition (const index :: Arity index) {
		return scope_->getProposition (index);
	}
	object :: Typing*
	Proof :: getVariables() {
		return scope_->getVariables();
	}
	mdl :: proof :: Notation*
	Proof :: getNotation (const value :: Literal literal) {
		return scope_->getNotation (literal);
	}
	mdl :: proof :: Step*
	Proof :: getStep (const index :: Step index) {
		return scope_->getStep (index);
	}

	const mdl :: Assertion*
	Proof :: getAssertion() const {
		return scope_->getAssertion();
	}
	const mdl :: Proof*
	Proof :: getProof() const {
		return proof_;
	}
	const mdl :: proof :: Claim*
	Proof :: getClaim() const {
		return scope_->getClaim();
	}
	const mdl :: proof :: Node*
	Proof :: getHypothesis (const index :: Arity index) const {
		return scope_->getHypothesis (index);
	}
	const mdl :: proof :: Node*
	Proof :: getProposition (const index :: Arity index) const {
		return scope_->getProposition (index);
	}
	const object :: Typing*
	Proof :: getVariables() const {
		return scope_->getVariables();
	}
	const mdl :: proof :: Notation*
	Proof :: getNotation (const value :: Literal literal) const {
		return scope_->getNotation (literal);
	}
	const mdl :: proof :: Step*
	Proof :: getStep (const index :: Step index) const {
		return scope_->getStep (index);
	}

	// object :: Object implementation
	void
	Proof :: commitSuicide() {
		delete this;
	}
	Size_t
	Proof :: getVolume() const {
		return 0;
	}
	Size_t
	Proof :: getSizeOf() const {
		return sizeof (Proof);
	}
}
}
}
}


