/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_scope_Claim.cpp                           */
/* Description:     scope which contains claim                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_PROOF_SCOPE_CLAIM_CPP_
#define MDL_FORM_PROOF_SCOPE_CLAIM_CPP_

#include "mdl/form/mdl_form.hpp"

namespace mdl {
namespace form {
namespace proof {
namespace scope {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Claim :: Claim (mdl :: proof :: Scope* scope, mdl :: proof :: Claim* claim ) :
	Ancestor (scope),
	claim_ (claim) {
	}
	Claim :: ~ Claim() {
	}

	// proof :: Scope implementation
	mdl :: Assertion*
	Claim :: getAssertion () {
		return scope_->getAssertion();
	}
	mdl :: Proof*
	Claim :: getProof() {
		return scope_->getProof();
	}
	mdl :: proof :: Claim*
	Claim :: getClaim() {
		return claim_;
	}
	mdl :: proof :: Node*
	Claim :: getHypothesis (const index :: Arity index)
	{
		mdl :: proof :: Link*
			link = claim_->getLink();
		mdl :: proof :: References*
			references = link->getReferences();
		mdl :: proof :: Reference*
			reference = references->get (index);
		mdl :: proof :: Node*
			node = reference->getNode();
		return node;
	}
	mdl :: proof :: Node*
	Claim :: getProposition (const index :: Arity index) {
		return scope_->getProposition (index);
	}
	object :: Typing*
	Claim :: getVariables() {
		return scope_->getVariables ();
	}
	mdl :: proof :: Notation*
	Claim :: getNotation (const value :: Literal literal) {
		return scope_->getNotation (literal);
	}
	mdl :: proof :: Step*
	Claim :: getStep (const index :: Step index) {
		return scope_->getStep (index);
	}

	const mdl :: Assertion*
	Claim :: getAssertion () const {
		return scope_->getAssertion();
	}
	const mdl :: Proof*
	Claim :: getProof() const {
		return scope_->getProof();
	}
	const mdl :: proof :: Claim*
	Claim :: getClaim() const {
		return claim_;
	}
	const mdl :: proof :: Node*
	Claim :: getHypothesis (const index :: Arity index) const
	{
		const mdl :: proof :: Link*
			link = claim_->getLink();
		const mdl :: proof :: References*
			references = link->getReferences();
		const mdl :: proof :: Reference*
			reference = references->get (index);
		const mdl :: proof :: Node*
			node = reference->getNode();
		return node;
	}
	const mdl :: proof :: Node*
	Claim :: getProposition (const index :: Arity index) const {
		return scope_->getProposition (index);
	}
	const object :: Typing*
	Claim :: getVariables() const {
		return scope_->getVariables ();
	}
	const mdl :: proof :: Notation*
	Claim :: getNotation (const value :: Literal literal) const {
		return scope_->getNotation (literal);
	}
	const mdl :: proof :: Step*
	Claim :: getStep (const index :: Step index) const {
		return scope_->getStep (index);
	}

	// object :: Object implementation
	void
	Claim :: commitSuicide() {
		delete this;
	}
	Size_t
	Claim :: getVolume() const {
		return 0;
	}
	Size_t
	Claim :: getSizeOf() const {
		return sizeof (Claim);
	}
}
}
}
}

#endif /*MDL_FORM_PROOF_SCOPE_CLAIM_CPP_*/
