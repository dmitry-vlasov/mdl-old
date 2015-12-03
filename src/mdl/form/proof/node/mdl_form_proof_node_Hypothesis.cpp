/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_node_Hypothesis.cpp                       */
/* Description:     hypothesis as a proof node                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_PROOF_NODE_HYPOTHESIS_CPP_
#define MDL_FORM_PROOF_NODE_HYPOTHESIS_CPP_

#include "mdl/form/mdl_form.hpp"

namespace mdl {
namespace form {
namespace proof {
namespace node {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Hypothesis :: Hypothesis
	(
		mdl :: Assertion* assertion,
		index :: Arity index,
		const array :: Expression* expression
	) :
	assertion_ (assertion),
	index_ (index),
	expression_ (new array :: Expression (*expression, false)),
	scope_ (NULL) {
	}
	Hypothesis :: ~ Hypothesis() {
		deleteAggregateObject (expression_);
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;
using manipulator :: underline;

	// mdl :: proof :: Node implementation
	Hypothesis :: Kind
	Hypothesis :: getKind() const {
		return HYP;
	}
	index :: Step
	Hypothesis :: getIndex() const {
		return index_;
	}
	void
	Hypothesis :: replicateReference (String& string) const {
		string << Token :: hyp_ << space <<  (index_ + 1) << space;
	}
	void
	Hypothesis :: translateReference (String& string) const {
		string << :: smm :: Token :: prefix_e_ << index_ << space;
	}

	// object :: Scoping implementation
	mdl :: proof :: Scope*
	Hypothesis :: buildScope (mdl :: proof :: Scope* scope) {
		return scope;
	}
	void
	Hypothesis :: setScope (mdl :: proof :: Scope* scope) {
		scope_ = scope;
	}
	mdl :: proof :: Scope*
	Hypothesis :: getScope() {
		return scope_;
	}
	const mdl :: proof :: Scope*
	Hypothesis :: getScope() const {
		return scope_;
	}

	// object :: Expressive interface
	array :: Expression*
	Hypothesis :: getExpression() {
		return expression_;
	}
	mdl :: Type*
	Hypothesis :: getType() {
		return assertion_->getHypothesis (index_ - 1)->getType();
	}
	const array :: Expression*
	Hypothesis :: getExpression() const {
		return expression_;
	}
	const mdl :: Type*
	Hypothesis :: getType() const {
		return assertion_->getHypothesis (index_ - 1)->getType();
	}

	// object :: Writable interface
	void
	Hypothesis :: translate (String& string) const {
		translateReference (string);
	}
	void
	Hypothesis :: replicate (String& string) const {
		replicateReference (string);
	}

	// object :: Object interface
	void
	Hypothesis :: commitSuicide() {
		delete this;
	}
	Size_t
	Hypothesis :: getVolume() const {
		return getAggregateVolume (expression_);
	}
	Size_t
	Hypothesis :: getSizeOf() const {
		return sizeof (Hypothesis);
	}
}
}
}
}

#endif /*MDL_FORM_PROOF_NODE_HYPOTHESIS_CPP_*/
