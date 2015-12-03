/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_scope_Notation.cpp                        */
/* Description:     scope which contains notation                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_PROOF_SCOPE_NOTATION_CPP_
#define MDL_FORM_PROOF_SCOPE_NOTATION_CPP_

#include "mdl/form/mdl_form.hpp"

namespace mdl {
namespace form {
namespace proof {
namespace scope {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Notation :: Notation (mdl :: proof :: Scope* scope, mdl :: proof :: Notation* notation) :
	Ancestor (scope),
	notation_ (notation) {
	}
	Notation :: ~ Notation() {
	}

	// proof :: Scope implementation
	mdl :: Assertion*
	Notation :: getAssertion () {
		return scope_->getAssertion();
	}
	mdl :: Proof*
	Notation :: getProof() {
		return scope_->getProof();
	}
	mdl :: proof :: Claim*
	Notation :: getClaim() {
		return scope_->getClaim();
	}
	mdl :: proof :: Node*
	Notation :: getHypothesis (const index :: Arity index) {
		return scope_->getHypothesis (index);
	}
	mdl :: proof :: Node*
	Notation :: getProposition (const index :: Arity index) {
		return scope_->getProposition (index);
	}
	object :: Typing*
	Notation :: getVariables() {
		return scope_->getVariables();
	}
	mdl :: proof :: Notation*
	Notation :: getNotation (const value :: Literal literal)
	{
		if (notation_->getLiteral() == literal) {
			return notation_;
		}
		return scope_->getNotation (literal);
	}
	mdl :: proof :: Step*
	Notation :: getStep (const index :: Step index) {
		return scope_->getStep (index);
	}

	const mdl :: Assertion*
	Notation :: getAssertion () const {
		return scope_->getAssertion();
	}
	const mdl :: Proof*
	Notation :: getProof() const {
		return scope_->getProof();
	}
	const mdl :: proof :: Claim*
	Notation :: getClaim() const {
		return scope_->getClaim();
	}
	const mdl :: proof :: Node*
	Notation :: getHypothesis (const index :: Arity index) const {
		return scope_->getHypothesis (index);
	}
	const mdl :: proof :: Node*
	Notation :: getProposition (const index :: Arity index) const {
		return scope_->getProposition (index);
	}
	const object :: Typing*
	Notation :: getVariables() const {
		return scope_->getVariables();
	}
	const mdl :: proof :: Notation*
	Notation :: getNotation (const value :: Literal literal) const
	{
		if (notation_->getLiteral() == literal) {
			return notation_;
		}
		return scope_->getNotation (literal);
	}
	const mdl :: proof :: Step*
	Notation :: getStep (const index :: Step index) const {
		return scope_->getStep (index);
	}

	// object :: Object implementation
	void
	Notation :: commitSuicide() {
		delete this;
	}
	Size_t
	Notation :: getVolume() const {
		return 0;
	}
	Size_t
	Notation :: getSizeOf() const {
		return sizeof (Notation);
	}
}
}
}
}

#endif /*MDL_FORM_PROOF_SCOPE_NOTATION_CPP_*/
