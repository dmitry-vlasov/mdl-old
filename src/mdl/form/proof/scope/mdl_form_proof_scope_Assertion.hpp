/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_scope_Assertion.hpp                       */
/* Description:     scope which contains assertion                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/form/proof/scope/mdl_form_proof_scope_Scope.hpp"

namespace mdl {
namespace form {
namespace proof {
namespace scope {

class Assertion :
	public Scope,
	public Scalar<Assertion> {
	typedef Scope Ancestor;
public :
	Assertion (mdl :: Assertion*);
	virtual ~ Assertion();

	// proof :: Scope interface
	virtual mdl :: Assertion* getAssertion ();
	virtual mdl :: Proof* getProof();
	virtual mdl :: proof :: Claim* getClaim();
	virtual mdl :: proof :: Node* getHypothesis (const index :: Arity);
	virtual mdl :: proof :: Node* getProposition (const index :: Arity);
	virtual object :: Typing* getVariables();
	virtual mdl :: proof :: Notation* getNotation (const value :: Literal);
	virtual mdl :: proof :: Step* getStep (const index :: Step);

	virtual const mdl :: Assertion* getAssertion() const;
	virtual const mdl :: Proof* getProof() const;
	virtual const mdl :: proof :: Claim* getClaim() const;
	virtual const mdl :: proof :: Node* getHypothesis (const index :: Arity) const;
	virtual const mdl :: proof :: Node* getProposition (const index :: Arity) const;
	virtual const object :: Typing* getVariables() const;
	virtual const mdl :: proof :: Notation* getNotation (const value :: Literal) const;
	virtual const mdl :: proof :: Step* getStep (const index :: Step) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	mdl :: Assertion* assertion_;
};

}
}
}
}


