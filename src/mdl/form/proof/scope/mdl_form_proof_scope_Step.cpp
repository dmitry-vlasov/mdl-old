/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_scope_Step.cpp                            */
/* Description:     scope which contains proof steps hierarchy               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_STEP_SCOPE_STEP_CPP_
#define MDL_FORM_STEP_SCOPE_STEP_CPP_

#include "mdl/form/mdl_form.hpp"

namespace mdl {
namespace form {
namespace proof {
namespace scope {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Step :: Step (mdl :: proof :: Scope* scope, mdl :: Proof* proof) :
	Ancestor (scope),
	proof_ (proof) {
	}
	Step :: ~ Step() {
	}

	// proof :: Scope implementation
	mdl :: Assertion*
	Step :: getAssertion () {
		return scope_->getAssertion();
	}
	mdl :: Proof*
	Step :: getProof() {
		return scope_->getProof();
	}
	mdl :: proof :: Claim*
	Step :: getClaim() {
		return scope_->getClaim();
	}
	mdl :: proof :: Node*
	Step :: getHypothesis (const index :: Arity index) {
		return scope_->getHypothesis (index);
	}
	mdl :: proof :: Node*
	Step :: getProposition (const index :: Arity index) {
		return scope_->getProposition (index);
	}
	object :: Typing*
	Step :: getVariables() {
		return scope_->getVariables();
	}
	mdl :: proof :: Notation*
	Step :: getNotation (const value :: Literal literal) {
		return scope_->getNotation (literal);
	}
	mdl :: proof :: Step*
	Step :: getStep (const index :: Step index) {
		return proof_->getStep (index);
	}

	const mdl :: Assertion*
	Step :: getAssertion() const {
		return scope_->getAssertion();
	}
	const mdl :: Proof*
	Step :: getProof() const {
		return scope_->getProof();
	}
	const mdl :: proof :: Claim*
	Step :: getClaim() const {
		return scope_->getClaim();
	}
	const mdl :: proof :: Node*
	Step :: getHypothesis (const index :: Arity index) const {
		return scope_->getHypothesis (index);
	}
	const mdl :: proof :: Node*
	Step :: getProposition (const index :: Arity index) const {
		return scope_->getProposition (index);
	}
	const object :: Typing*
	Step :: getVariables() const {
		return scope_->getVariables();
	}
	const mdl :: proof :: Notation*
	Step :: getNotation (const value :: Literal literal) const {
		return scope_->getNotation (literal);
	}
	const mdl :: proof :: Step*
	Step :: getStep (const index :: Step index) const {
		return proof_->getStep (index);
	}

	// object :: Object implementation
	void
	Step :: commitSuicide() {
		delete this;
	}
	Size_t
	Step :: getVolume() const {
		return 0;
	}
	Size_t
	Step :: getSizeOf() const {
		return sizeof (Step);
	}
}
}
}
}

#endif /*MDL_FORM_STEP_SCOPE_STEP_CPP_*/
