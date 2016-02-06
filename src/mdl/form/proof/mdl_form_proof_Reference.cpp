/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_Reference.cpp                             */
/* Description:     reference to the proof node                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace form {
namespace proof {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Reference :: Reference
	(
		const Location& location,
		value :: Kind kind,
		index :: Step index,
		mdl :: proof :: Node* node,
		mdl :: Theory*
	) :
	location_ (location),
	kind_ (kind),
	index_ (index),
	node_ (node) {
	}
	inline
	Reference :: Reference (const Reference& reference) :
	location_ (reference.location_),
	kind_ (reference.kind_),
	index_ (reference.index_),
	node_ (reference.node_) {
	}
	Reference :: Reference (const mdl :: proof :: Reference* reference) :
	location_ (dynamic_cast<const Reference*>(reference)->location_),
	kind_ (dynamic_cast<const Reference*>(reference)->kind_),
	index_ (dynamic_cast<const Reference*>(reference)->index_),
	node_ (dynamic_cast<const Reference*>(reference)->node_) {
	}
	Reference :: ~ Reference() {
	}

using nstd :: manipulator :: space;
using nstd :: manipulator :: endLine;
using nstd :: manipulator :: tab;

	// mdl :: proof :: Reference implementation
	value :: Kind
	Reference :: getKind() const {
		return kind_;
	}
	index :: Step
	Reference :: getIndex() const {
		return index_;
	}
	void
	Reference :: build (mdl :: proof :: Scope* scope)
	{
		try {
			switch (kind_) {
			case Token :: HYP :
				node_ = scope->getHypothesis (index_);
				break;
			case Token :: PROP :
				node_ = scope->getProposition (index_);
				break;
			case Token :: STEP :
				node_ = scope->getStep (index_);
				break;
			}
		} catch (Error* error) {
			error->add (location_);
			throw error;
		}
		if (node_ == NULL) {
			node_ = scope->getHypothesis (index_);
			Error* error = new Error (location_, Error :: SEMANTIC);
			error->message() << "undefined reference ";
			error->message() << *this << " in proof" << endLine;
			throw error;
		}
	}
	mdl :: proof :: Node*
	Reference :: getNode() {
		return node_;
	}
	const mdl :: proof :: Node*
	Reference :: getNode() const {
		return node_;
	}

	// object :: Writable implementation
	void
	Reference :: replicate (String& string) const
	{
		switch (kind_) {
		case Token :: HYP :   string << Token :: hyp_;  break;
		case Token :: PROP :  string << Token :: prop_; break;
		case Token :: STEP :  string << Token :: step_; break;
		}
		string << space;
		string << (index_ + 1);
	}
	void
	Reference :: translate (String& string) const {
		node_->translate (string);
	}
	bool
	Reference :: lookup() const
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			if (Config :: lookupDefinition()) {
				std :: cout << *node_;
			}
			return true;
		}
		return false;
	}

	// object :: Object implementation
	void
	Reference :: commitSuicide() {
		delete this;
	}
	Size_t
	Reference :: getVolume () const {
		return location_.getVolume();
	}
	Size_t
	Reference :: getSizeOf () const {
		return sizeof (Reference);
	}
}
}
}


