/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_Link.cpp                                  */
/* Description:     proof link class                                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_PROOF_LINK_CPP_
#define MDL_FORM_PROOF_LINK_CPP_

namespace mdl {
namespace form {
namespace proof {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Link :: Link
	(
		const Location& location,
		value :: Kind kind,
		mdl :: Identificator* identificator,
		index :: Arity proposition,
		mdl :: proof :: References* references,
		mdl :: Theory* theory
	) :
	location_ (location),
	theory_ (theory),
	kind_ (kind),
	identificator_ (identificator),
	proposition_ (proposition - 1),
	references_ (references),
	assertion_ (NULL)
	{
		if (Config :: localParsing() || (kind_ == Token :: CLAIM)) {
			return;
		}
		const index :: Assertion
			index = theory_->getIndex (identificator_);
		if (index == index :: undefined :: FORM) {
			Error* error = new Error (location_, Error :: SEMANTIC, "reference to undefined assertion");
			error->message() << "identificator: " << *identificator_ << manipulator :: endLine;
			throw error;
		}
		assertion_ = Math :: assertions()->get (index);
		switch (assertion_->getKind()) {
		case mdl :: Assertion :: THEOREM :
			if (kind_ != Token :: THEOREM) {
				throw new Error (location_, Error :: SEMANTIC, "wrong assertion kind");
			} break;
		case mdl :: Assertion :: PROBLEM :
			if ((kind_ != Token :: THEOREM) && (kind_ != Token :: PROBLEM)) {
				throw new Error (location_, Error :: SEMANTIC, "wrong assertion kind");
			} break;
		case mdl :: Assertion :: AXIOM :
			if (kind_ != Token :: AXIOM) {
				throw new Error (location_, Error :: SEMANTIC, "wrong assertion kind");
			} break;
		case mdl :: Assertion :: DEFINITION :
			if (kind_ != Token :: DEFINITION) {
				throw new Error (location_, Error :: SEMANTIC, "wrong assertion kind");
			}
		}
	}
	inline
	Link :: Link
	(
		const Location& location,
		value :: Kind kind,
		mdl :: Theory* theory
	) :
	location_ (location),
	theory_ (theory),
	kind_ (kind),
	identificator_ (NULL),
	proposition_ (index :: undefined :: ARITY),
	references_ (new form :: proof :: References()),
	assertion_ (NULL)
	{
		if (Config :: localParsing() || (kind_ == Token :: CLAIM)) {
			return;
		}
		const index :: Assertion
			index = theory_->getIndex (identificator_);
		if (index == index :: undefined :: FORM) {
			Error* error = new Error (location_, Error :: SEMANTIC, "reference to undefined assertion");
			error->message() << "identificator: " << *identificator_ << manipulator :: endLine;
			throw error;
		}
		assertion_ = Math :: assertions()->get (index);
		switch (assertion_->getKind()) {
		case mdl :: Assertion :: THEOREM :
			if (kind_ != Token :: THEOREM) {
				throw new Error (location_, Error :: SEMANTIC, "wrong assertion kind");
			} break;
		case mdl :: Assertion :: PROBLEM :
			if ((kind_ != Token :: THEOREM) && (kind_ != Token :: PROBLEM)) {
				throw new Error (location_, Error :: SEMANTIC, "wrong assertion kind");
			} break;
		case mdl :: Assertion :: AXIOM :
			if (kind_ != Token :: AXIOM) {
				throw new Error (location_, Error :: SEMANTIC, "wrong assertion kind");
			} break;
		case mdl :: Assertion :: DEFINITION :
			if (kind_ != Token :: DEFINITION) {
				throw new Error (location_, Error :: SEMANTIC, "wrong assertion kind");
			}
		}
	}
	Link :: Link
	(
		const Location& location,
		mdl :: Proposition* proposition,
		mdl :: proof :: References* references,
		mdl :: Theory* theory
	) :
	location_ (location),
	theory_ (theory),
	kind_ (),
	identificator_ (NULL),
	proposition_ (proposition->getIndex()),
	references_ (references),
	assertion_ (proposition->getAssertion())
	{
		switch (proposition->getAssertion()->getKind()) {
		case mdl :: Assertion :: THEOREM :
			kind_ = Token :: THEOREM; break;
		case mdl :: Assertion :: PROBLEM :
			kind_ = Token :: PROBLEM; break;
		case mdl :: Assertion :: AXIOM :
			kind_ = Token :: AXIOM;   break;
		case mdl :: Assertion :: DEFINITION :
			kind_ = Token :: DEFINITION;
		}
	}
	Link :: ~ Link()
	{
		deleteAggregateObject (identificator_);
		deleteAggregateObject (references_);
	}

using manipulator :: space;

	// mdl :: proof :: Link implementation
	void
	Link :: buildScope (mdl :: proof :: Scope* scope) {
		references_->build (scope);
	}
	index :: Arity
	Link :: getPropositionIndex() const {
		return proposition_;
	}
	mdl :: Assertion*
	Link :: getAssertion() {
		return assertion_;
	}
	mdl :: Proposition*
	Link :: getProposition() {
		return assertion_->getProposition (proposition_);
	}
	mdl :: proof :: References*
	Link :: getReferences() {
		return references_;
	}
	const mdl :: Assertion*
	Link :: getAssertion() const {
		return assertion_;
	}
	const mdl :: Proposition*
	Link :: getProposition() const {
		return assertion_->getProposition (proposition_);
	}
	const mdl :: proof :: References*
	Link :: getReferences() const {
		return references_;
	}

	void
	Link :: translateReferences (String& string) const {
		references_->translate (string);
	}
	void
	Link :: translateAssertion (String& string) const
	{
		assertion_->translateName (string, proposition_);
		string << space;
	}

	// object :: Buildable implementation
	void
	Link :: build() {
	}

using manipulator :: underline;

	// object :: Writable implementation
	void
	Link :: translate (String& string) const
	{
		references_->translate (string);
		assertion_->translateName (string);
		string << space;
	}
	void
	Link :: replicate (String& string) const
	{
		switch (kind_) {
		case Token :: AXIOM :
			string << Token :: axiom_ << space;
			break;
		case Token :: THEOREM :
		case Token :: PROBLEM :
			string << Token :: theorem_ << space;
			break;
		case Token :: DEFINITION :
			string << Token :: definition_ << space;
			break;
		case Token :: CLAIM :
			string << Token :: claim_ << space;
			break;
		}
		if (identificator_ != NULL) {
			identificator_->replicate (string);
			string << space;
		} else if (kind_ != Token :: CLAIM) {
			assertion_->replicateName (string);
			string << space;
		}
		if ((kind_ != Token :: CLAIM) && (proposition_ != 0)) {
			string << space << Token :: colon_;
			string << space << proposition_ + 1;
			string << space;
		}
		references_->replicate (string);
	}
	bool
	Link :: lookup() const
	{
		if (identificator_->lookup()) {
			if (Config :: lookupDefinition()) {
				std :: cout << *assertion_;
			} else {
				std :: cout << assertion_->getLocation();
			}
			return true;
		}
		return references_->lookup();
	}
	const object :: Writable*
	Link :: find() const
	{
		if (identificator_->lookup()) {
			return assertion_;
		} else {
			return NULL;
		}
	}

	// object :: Object implementation
	void
	Link :: commitSuicide() {
		delete this;
	}
	Size_t
	Link :: getVolume() const {
		Size_t volume = 0;
		volume += getAggregateVolume (identificator_);
		volume += getAggregateVolume (references_);
		return volume;
	}
	Size_t
	Link :: getSizeOf() const {
		return sizeof (Link);
	}
}
}
}

#endif /*MDL_FORM_PROOF_LINK_CPP_*/
