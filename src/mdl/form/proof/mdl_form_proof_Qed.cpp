/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_Qed.cpp                                   */
/* Description:     proof q.e.d. class                                       */
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

	Qed :: Qed
	(
		mdl :: proof :: Line* prev,
		const Location& location,
		const mdl :: Comments* comments,
		const value :: Kind kind,
		const index :: Arity indexProp,
		const index :: Step indexStep,
		mdl :: Theory* theory
	) :
	location_ (location),
	comments_ (comments),
	kind_ (kind),
	indexProp_ (indexProp),
	indexStep_ (indexStep),
	next_ (NULL),
	prev_ (prev),
	prop_ (NULL),
	step_ (NULL),
	scope_ (NULL),
	isVerified_ (false)
	{
		if (prev != NULL) {
			prev->setNext (this);
		}
	}
	Qed :: Qed
	(
		mdl :: proof :: Provable* claim,
		mdl :: proof :: Step* step
	) :
	location_ (step->getLocation()),
	comments_ (NULL),
	kind_ (CLAIM),
	indexProp_ (0),
	indexStep_ (step->getIndex()),
	next_ (NULL),
	prev_ (NULL),
	prop_ (claim),
	step_ (step),
	scope_ (step->getScope()),
	isVerified_ (false) {
	}
	Qed :: Qed
	(
		const index :: Arity indexProp,
		const index :: Step indexStep,
		const value :: Kind kind
	) :
	location_ (),
	comments_ (NULL),
	kind_ (kind),
	indexProp_ (indexProp),
	indexStep_ (indexStep),
	next_ (NULL),
	prev_ (NULL),
	prop_ (NULL),
	step_ (NULL),
	scope_ (NULL),
	isVerified_ (false) {
	}
	Qed :: Qed (const mdl :: Proposition* proposition) :
	location_ (proposition->getLocation()),
	comments_ (NULL),
	kind_ (PROP),
	indexProp_ (proposition->getIndex()),
	indexStep_ (proposition->getIndex()),
	next_ (NULL),
	prev_ (NULL),
	prop_ (NULL),
	step_ (NULL),
	scope_ (NULL),
	isVerified_ (false) {
	}

	Qed :: ~ Qed() {
		deleteAggregateObject (comments_);
	}

	// proof :: Qed implementation
	index :: Arity
	Qed :: getIndexProp() const {
		return indexProp_;
	}
	index :: Step
	Qed :: getIndexStep() const {
		return indexStep_;
	}
	mdl :: proof :: Provable*
	Qed :: getProp() {
		return prop_;
	}
	mdl :: proof :: Step*
	Qed :: getStep() {
		return step_;
	}
	const mdl :: proof :: Provable*
	Qed :: getProp() const {
		return prop_;
	}
	const mdl :: proof :: Step*
	Qed :: getStep() const {
		return step_;
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// proof :: Line implementation
	Qed :: Sort
	Qed :: getSort() const {
		return QED;
	}
	void
	Qed :: incIndex (const index :: Step index)
	{
		if (indexStep_ >= index) {
			++ indexStep_;
			step_ = NULL;
			buildScope (scope_);
		}
	}
	void
	Qed :: decIndex (const index :: Step index)
	{
		if (indexStep_ > index) {
			-- indexStep_;
			step_ = NULL;
			buildScope (scope_);
		}
	}
	void
	Qed :: setNext (mdl :: proof :: Line* line) {
		next_ = line;
	}
	void
	Qed :: setPrev (mdl :: proof :: Line* line) {
		prev_ = line;
	}
	mdl :: proof :: Line*
	Qed :: getNext() {
		return next_;
	}
	mdl :: proof :: Line*
	Qed :: getPrev() {
		return prev_;
	}
	const mdl :: proof :: Line*
	Qed :: getNext() const {
		return next_;
	}
	const mdl :: proof :: Line*
	Qed :: getPrev() const {
		return prev_;
	}
	const Location&
	Qed :: getLocation() const {
		return location_;
	}

	// object :: Scoping implementation
	mdl :: proof :: Scope*
	Qed :: buildScope (mdl :: proof :: Scope* scope)
	{
		try {
			scope_ = scope;
			step_ = scope_->getStep (indexStep_);
			switch (kind_) {
			case PROP : {
				mdl :: Proposition*
					statement = scope->getAssertion()->getProposition (indexProp_);
				mdl :: statement :: Provable*
					provable = dynamic_cast<mdl :: statement :: Provable*>(statement);
				prop_ = provable->getProof();
				break;
			}
			case CLAIM : {
				mdl :: proof :: Step* claim = scope->getClaim();
				prop_ = dynamic_cast<mdl :: proof :: Provable*>(claim);
				break;
			}
			}
		} catch (Error* error) {
			error->add (location_);
			throw error;
		}
		if (prop_ == NULL) {
			Error* error = new Error (location_, Error :: SEMANTIC);
			error->message() << "undefined reference to proposition ";
			error->message() << indexProp_ + 1 << " in proof." << endLine;
			throw error;
		}
		if (step_ == NULL) {
			Error* error = new Error (location_, Error :: SEMANTIC);
			error->message() << "undefined reference to step ";
			error->message() << indexStep_ + 1 << " in proof." << endLine;
			throw error;
		}
		return scope_;
	}
	void
	Qed :: setScope (mdl :: proof :: Scope* scope) {
		scope_ = scope;
	}
	mdl :: proof :: Scope*
	Qed :: getScope() {
		return scope_;
	}
	const mdl :: proof :: Scope*
	Qed :: getScope() const {
		return scope_;
	}

	// object :: Verifiable implementation
	void
	Qed :: check()
	{
		isVerified_ = false;
		const array :: Expression*
			theoremProposition = prop_->getExpression();
		if (step_ == NULL) {
			step_ = scope_->getStep (indexStep_);
		}
		const array :: Expression*
			proofProposition = step_->getExpression();
		if (*theoremProposition != *proofProposition) {
			Error* error = new Error (location_, Error :: SEMANTIC);
			error->message() << "in proof of ";
			scope_->getAssertion()->replicateName (error->message());
			error->message() << " theorem, "<< endLine;
			error->message() << "proposition does not match proof statement." << endLine;

			error->message() << tab << "proof statement: ";
			proofProposition->write (error->message());
			error->message() << endLine;
			error->message() << tab << "theorem proposition: ";
			theoremProposition->write (error->message());
			error->message() << endLine;
			throw error;
		}
		prop_->setProof (step_);
		isVerified_ = true;
	}
	bool
	Qed :: isVerified() const {
		return isVerified_;
	}

	// object :: Writable implementation
	void
	Qed :: translate (String&) const {
	}
	void
	Qed :: replicate (String& string) const
	{
		if (!Config :: removeComments() && (comments_ != NULL)) {
			string << location_.getIndent();
			comments_->replicate (string);
			string << endLine;
		}
		string << location_.getIndent() << Token :: qed_ << space;
		switch (kind_) {
		case PROP :
			string << Token :: prop_ << space;
			string << indexProp_ + 1 <<space;
			break;
		case CLAIM :
			string << Token :: claim_ << space;
			break;
		}
		string << Token :: equality_ << space;
		string << Token :: step_ << space;
		string << indexStep_ + 1 << space;
		string << Token :: semicolon_ << endLine;
	}

	// object :: Object implementation
	void
	Qed :: commitSuicide() {
		delete this;
	}
	Size_t
	Qed :: getVolume() const {
		return getAggregateVolume (comments_);
	}
	Size_t
	Qed :: getSizeOf() const {
		return sizeof (Qed);
	}
}
}
}


