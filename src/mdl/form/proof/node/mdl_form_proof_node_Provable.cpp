/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_node_Provable.cpp                         */
/* Description:     provable proof node                                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_PROOF_NODE_PROVABLE_CPP_
#define MDL_FORM_PROOF_NODE_PROVABLE_CPP_

#include "mdl/form/mdl_form.hpp"

namespace mdl {
namespace form {
namespace proof {
namespace node {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Provable :: Provable
	(
		mdl :: Assertion* assertion,
		index :: Arity index,
		const array :: Expression* expression
	) :
	Statement (assertion, index, expression),
	proof_ (NULL) {
	}
	Provable :: ~ Provable() {
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;
using manipulator :: underline;

	// proof :: Provable interface
	void
	Provable :: setProof (mdl :: proof :: Node* proof) {
		proof_ = proof;
	}

	// proof :: Node implementation
	Provable :: Kind
	Provable :: getKind() const {
		return PROP;
	}
	index :: Step
	Provable :: getIndex() const {
		return Statement :: getIndex();
	}
	void
	Provable :: replicateReference (String& string) const {
		Statement :: replicateReference (string);
	}
	void
	Provable :: translateReference (String& string) const {
		Statement :: translateReference (string);
	}

	// object :: Scoping implementation
	mdl :: proof :: Scope*
	Provable :: buildScope (mdl :: proof :: Scope* scope) {
		return scope;
	}
	void
	Provable :: setScope (mdl :: proof :: Scope* scope) {
		Statement :: setScope (scope);
	}
	mdl :: proof :: Scope*
	Provable :: getScope() {
		return Statement :: getScope();
	}
	const mdl :: proof :: Scope*
	Provable :: getScope() const {
		return Statement :: getScope();
	}

	// object :: Expressive interface
	const array :: Expression*
	Provable :: getExpression() const {
		return Statement :: getExpression();
	}
	const mdl :: Type*
	Provable :: getType() const {
		return Statement :: getType();
	}

	// object :: Writable interface
	void
	Provable :: translate (String& string) const {
		proof_->translate (string);
	}
	void
	Provable :: replicate (String& string) const {
		Statement :: replicateReference (string);
	}

	// object :: Object interface
	void
	Provable :: commitSuicide() {
		delete this;
	}
	Size_t
	Provable :: getVolume() const {
		return Statement :: getVolume();
	}
	Size_t
	Provable :: getSizeOf() const {
		return sizeof (Provable);
	}
}
}
}
}

#endif /*MDL_FORM_PROOF_NODE_PROVABLE_CPP_*/
