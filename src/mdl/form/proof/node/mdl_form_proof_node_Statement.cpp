/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_node_Statement.cpp                        */
/* Description:     statement as a base class for proof node                 */
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
namespace node {

	/****************************
	 *		Public members
	 ****************************/

	Statement :: Statement
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
	Statement :: ~ Statement() {
		deleteAggregateObject (expression_);
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;
using manipulator :: underline;

	// mdl :: proof :: Node implementation
	index :: Step
	Statement :: getIndex() const {
		return index_;
	}
	void
	Statement :: replicateReference (String& string) const
	{
		string << Token :: prop_;
		if (assertion_->getPropArity() > 1) {
			string << space << (index_ + 1) << space;
		} else {
			string << space;
		}
	}
	void
	Statement :: translateReference (String& string) const {
		assertion_->translateName (string, index_);
	}

	// object :: Scoping implementation
	mdl :: proof :: Scope*
	Statement :: buildScope (mdl :: proof :: Scope* scope) {
		return scope;
	}
	void
	Statement :: setScope (mdl :: proof :: Scope* scope) {
		scope_ = scope;
	}
	mdl :: proof :: Scope*
	Statement :: getScope() {
		return scope_;
	}
	const mdl :: proof :: Scope*
	Statement :: getScope() const {
		return scope_;
	}

	// object :: Expressive interface
	array :: Expression*
	Statement :: getExpression() {
		return expression_;
	}
	mdl :: Type*
	Statement :: getType() {
		return assertion_->getProposition (index_ - 1)->getType();
	}
	const array :: Expression*
	Statement :: getExpression() const {
		return expression_;
	}
	const mdl :: Type*
	Statement :: getType() const {
		return assertion_->getProposition (index_ - 1)->getType();
	}

	// object :: Writable interface
	void
	Statement :: translate (String& string) const {
		translateReference (string);
	}
	void
	Statement :: replicate (String& string) const {
		replicateReference (string);
	}

	// object :: Object interface
	Size_t
	Statement :: getVolume() const {
		return getAggregateVolume (expression_);
	}
	Size_t
	Statement :: getSizeOf() const {
		return sizeof (Statement);
	}
}
}
}
}


