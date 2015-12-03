/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_scope_Variable.cpp                        */
/* Description:     scope which contains variable declaration                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_PROOF_SCOPE_VARIABLE_CPP_
#define MDL_FORM_PROOF_SCOPE_VARIABLE_CPP_

#include "mdl/form/mdl_form.hpp"

namespace mdl {
namespace form {
namespace proof {
namespace scope {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Variable :: Variable (mdl :: proof :: Scope* scope, mdl :: proof :: Variable* variable) :
	Ancestor (scope),
	variable_ (variable) {
	}
	Variable :: ~ Variable() {
	}

	// proof :: Scope implementation
	mdl :: Assertion*
	Variable :: getAssertion () {
		return scope_->getAssertion();
	}
	mdl :: Proof*
	Variable :: getProof() {
		return scope_->getProof();
	}
	mdl :: proof :: Claim*
	Variable :: getClaim() {
		return scope_->getClaim();
	}
	mdl :: proof :: Node*
	Variable :: getHypothesis (index :: Arity index) {
		return scope_->getHypothesis (index);
	}
	mdl :: proof :: Node*
	Variable :: getProposition (index :: Arity index) {
		return scope_->getProposition (index);
	}
	object :: Typing*
	Variable :: getVariables() {
		return variable_;
	}
	mdl :: proof :: Notation*
	Variable :: getNotation (value :: Literal literal) {
		return scope_->getNotation (literal);
	}
	mdl :: proof :: Step*
	Variable :: getStep (index :: Step index) {
		return scope_->getStep (index);
	}

	const mdl :: Assertion*
	Variable :: getAssertion () const {
		return scope_->getAssertion();
	}
	const mdl :: Proof*
	Variable :: getProof() const {
		return scope_->getProof();
	}
	const mdl :: proof :: Claim*
	Variable :: getClaim() const {
		return scope_->getClaim();
	}
	const mdl :: proof :: Node*
	Variable :: getHypothesis (const index :: Arity index) const {
		return scope_->getHypothesis (index);
	}
	const mdl :: proof :: Node*
	Variable :: getProposition (const index :: Arity index) const {
		return scope_->getProposition (index);
	}
	const object :: Typing*
	Variable :: getVariables() const {
		return variable_;
	}
	const mdl :: proof :: Notation*
	Variable :: getNotation (const value :: Literal literal) const {
		return scope_->getNotation (literal);
	}
	const mdl :: proof :: Step*
	Variable :: getStep (const index :: Step index) const {
		return scope_->getStep (index);
	}

	// object :: Object implementation
	void
	Variable :: commitSuicide() {
		delete this;
	}
	Size_t
	Variable :: getVolume() const {
		return 0;
	}
	Size_t
	Variable :: getSizeOf() const {
		return sizeof (Variable);
	}
}
}
}
}

#endif /*MDL_FORM_PROOF_SCOPE_VARIABLE_CPP_*/
