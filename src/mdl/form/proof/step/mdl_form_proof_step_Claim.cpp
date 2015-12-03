/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_step_Claim.cpp                            */
/* Description:     step with claim inference                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_PROOF_STEP_CLAIM_CPP_
#define MDL_FORM_PROOF_STEP_CLAIM_CPP_

namespace mdl {
namespace form {
namespace proof {
namespace step {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Claim :: Claim
	(
		mdl :: proof :: Line* line,
		const Location& location,
		const mdl :: Comments* comments,
		index :: Step index,
		mdl :: Identificator* type,
		mdl :: proof :: Link* link,
		array :: Expression* expression,
		mdl :: Proof* proof,
		mdl :: Theory* theory
	) :
	Ancestor_
	(
		line,
		location,
		comments,
		index,
		type,
		expression,
		theory
	),
	link_ (link),
	downSteps_ (INITIAL_DOWN_STEPS_CAPACITY),
	proof_ (proof),
	node_ (NULL),
	scope_ (NULL) {
	}
	inline
	Claim :: Claim
	(
		mdl :: proof :: Step* question,
		index :: Step proofLength
	) :
	Ancestor_ (question),
	link_ (new form :: proof :: Link (Ancestor_ :: location_, Token :: CLAIM, NULL)
	),
	downSteps_ (INITIAL_DOWN_STEPS_CAPACITY),
	proof_ (new proof :: Proof (question, proofLength)),
	node_ (NULL),
	scope_ (new scope :: Claim (Ancestor_ :: scope_, this)) {
		proof_->buildScope (scope_);
	}
	Claim :: ~ Claim()
	{
		deleteAggregateObject (proof_);
		deleteAggregateObject (link_);
		deleteAggregateObject (scope_);
	}

	// proof :: Claim implementation
	void
	Claim :: addStep (mdl :: proof :: Step* step) {
		proof_->addStep (step);
	}
	void
	Claim :: addVariable (const Symbol& symbol)
	{
		const object :: Typing* typing =
			(proof_->getLast() == NULL) ?
			proof_->getScope()->getVariables() :
			proof_->getLast()->getScope()->getVariables();

		if (typing->getType (symbol.getLiteral()) == NULL) {
			mdl :: proof :: Line* last = proof_->getLast();
			Location location =
				(last == NULL) ?
				Ancestor_ :: location_ :
				last->getLocation();
			if (last == NULL) {
				location.indent().incTabs();
			}
			mdl :: proof :: Variable*
				variable = new form :: proof :: Variable
				(
					last,
					location,
					NULL,
					new form :: header :: Variable (symbol),
					proof_->getTheory()
				);
			proof_->addVariable (variable);
		}
	}
	mdl :: Proof*
	Claim :: getProof() {
		return proof_;
	}
	const mdl :: Proof*
	Claim :: getProof() const {
		return proof_;
	}

	// proof :: Provable implementation
	void
	Claim :: setProof (mdl :: proof :: Node* node) {
		node_ = node;
	}

	// proof :: Step implementation
	mdl :: proof :: Step :: Class
	Claim :: getClass() const {
		return mdl :: proof :: Step :: CLAIM;
	}
	void
	Claim :: addReference (mdl :: proof :: Reference* reference) {
		link_->getReferences()->add (reference);
	}
	void
	Claim :: addDown (mdl :: proof :: Step* step) {
		downSteps_.add (step);
	}
	index :: Arity
	Claim :: getUpArity() const {
		return link_->getReferences()->getArity();
	}
	index :: Arity
	Claim :: getDownArity() const {
		return downSteps_.getSize();
	}
	mdl :: proof :: Link*
	Claim :: getLink()  {
		return link_;
	}
	mdl :: proof :: Node*
	Claim :: getUp (const index :: Arity i) {
		return link_->getReferences()->get (i)->getNode();
	}
	mdl :: proof :: Step*
	Claim :: getDown (const index :: Arity i) {
		return downSteps_.getValue (i);
	}
	const mdl :: proof :: Link*
	Claim :: getLink() const {
		return link_;
	}
	const mdl :: proof :: Node*
	Claim :: getUp (const index :: Arity i) const {
		return link_->getReferences()->get (i)->getNode();
	}
	const mdl :: proof :: Step*
	Claim :: getDown (const index :: Arity i) const {
		return downSteps_.getValue (i);
	}

using manipulator :: endLine;
using manipulator :: space;

	// proof :: Node implementation
	void
	Claim :: replicateReference (String& string) const {
		string << Token :: step_  << space << index_;
	}
	void
	Claim :: translateReference (String& string) const {
	}

	// object :: Scoping implementation
	mdl :: proof :: Scope*
	Claim :: buildScope (mdl :: proof :: Scope* scope)
	{
		Ancestor_ :: buildScope (scope);
		try {
			link_->buildScope (scope);

			for (index :: Arity i = 0; i < getUpArity(); ++ i) {
				mdl :: proof :: Node* node = getUp (i);
				if (node->getKind() != mdl :: proof :: Node :: STEP) {
					continue;
				}
				mdl :: proof :: Step*
					step = dynamic_cast<mdl :: proof :: Step* >(node);
				step->addDown (this);
			}

			scope_ = new scope :: Claim (scope, this);
			proof_->buildScope (scope_);
		} catch (Error* error) {
			error->add (location_);
			throw error;
		}
		return scope;
	}

	// object :: Verifiable implementation
	void
	Claim :: check() {
		proof_->check();
	}
	void
	Claim :: compress() {
		proof_->compress();
	}
	void
	Claim :: prove() {
		try {
			proof_->prove();
		} catch (Error* error) {
			error->add (location_);
			error->message() << "claim proof failed." << endLine;
			throw error;
		}
	}

	// object :: Buildable implementation
	void
	Claim :: build() {
		Ancestor_ :: build();
		proof_->build();
	}

	// object :: Writable implementation
	void
	Claim :: translate (String& string) const {
		node_->translate (string);
	}
	void
	Claim :: replicate (String& string) const
	{
		if (!Config :: removeComments() && (Ancestor_ :: comments_ != NULL)) {
			string << Ancestor_ :: location_.getIndent();
			Ancestor_ :: comments_->replicate (string);
			string << endLine;
		}
		string << Ancestor_ :: location_.getIndent() << Token :: step_ << space;
		string << (index_ + 1) << space << Token :: colon_ << space;

		Ancestor_ :: type_->replicateName (string); string << space;
		string << Token :: equality_ << space;

		link_->replicate (string);
		string << space << Token :: turnstile_ << space;

		Ancestor_ :: expression_->write (string); string << space;
		string << Token :: semicolon_ << space;
		string << Token :: proof_ << space;
		proof_->replicate (string);
	}
	bool
	Claim :: lookup() const
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return true;
		}
		return proof_->lookup();
	}
	object :: Writable*
	Claim :: find()
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return this;
		}
		object :: Writable*
			object = proof_->find();
		if (object != NULL) {
			return object;
		} else {
			return proof :: Step :: find();
		}
	}
	const object :: Writable*
	Claim :: find() const
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return this;
		}
		const object :: Writable*
			object = proof_->find();
		if (object != NULL) {
			return object;
		} else {
			return proof :: Step :: find();
		}
	}

	// object :: Object implementation
	void
	Claim :: commitSuicide() {
		delete this;
	}
	Size_t
	Claim :: getVolume() const
	{
		Size_t volume = 0;
		volume += Ancestor_ :: getVolume();
		volume += downSteps_.getVolume();
		volume += getAggregateVolume (proof_);
		volume += getAggregateVolume (link_);
		volume += getAggregateVolume (scope_);
		return volume;
	}
	Size_t
	Claim :: getSizeOf() const {
		return sizeof (Claim);
	}
}
}
}
}

#endif /*MDL_FORM_PROOF_STEP_CLAIM_CPP_*/
