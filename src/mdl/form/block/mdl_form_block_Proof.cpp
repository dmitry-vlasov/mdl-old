/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_block_Proof.cpp                                 */
/* Description:     proof class                                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_BLOCK_PROOF_CPP_
#define MDL_FORM_BLOCK_PROOF_CPP_

namespace mdl {
namespace form {
namespace block {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Proof :: Proof
	(
		const Location& location,
		const mdl :: Comments* comments,
		value :: Name name,
		mdl :: Identificator* theoremId,
		proof :: Proof* proof,
		mdl :: Theory* theory
	) :
	form :: Identifiable (location, comments, name, theory),
	theoremId_ (theoremId),
	theory_ (theory),
	theorem_ (NULL),
	proof_ (proof),
	scope_ (NULL)
	{
		Math :: proofs()->add (this);
		if (Config :: localParsing()) {
			return;
		}
		const index :: Assertion
			index = theory_->getIndex (theoremId_);
		if (index == index :: undefined :: FORM) {
			throw new Error (location_, Error :: SEMANTIC, "reference to undefined assertion");
		}
		theorem_ = Math :: assertions()->get (index);
		if (Config :: shallowParsing() && !location_.isTop()) {
			return;
		}
		mdl :: form :: Theorem* theorem =
			dynamic_cast<mdl :: form :: Theorem*>(theorem_);
		theorem->addProof (this);
	}
	inline
	Proof :: Proof (mdl :: Assertion* problem) :
	form :: Identifiable
	(
		problem->getLocation(),
		new Comments ("Automatically generated proof."),
		Table :: defaultName(),
		problem->getTheory()
	),
	theoremId_ (new Identificator (problem->getIdentificator())),
	theory_ (problem->getTheory()),
	theorem_ (problem),
	proof_ (new proof :: Proof (problem)),
	scope_ (NULL)
	{
		build();
		Math :: proofs()->add (this);
		for (index :: Arity i = 0; i < problem->getPropArity(); ++ i) {
			mdl :: Proposition* proposition = problem->getProposition (i);
			mdl :: proof :: Step* step = new proof :: step :: Question (proposition);
			proof_->addStep (step);
			mdl :: proof :: Qed* qed = new proof :: Qed (proposition);
			proof_->addQed (qed);
		}
	}
	Proof :: ~ Proof()
	{
		deleteAggregateObject (comments_);
		deleteAggregateObject (theoremId_);
		deleteAggregateObject (proof_);
		deleteAggregateObject (scope_);
	}

	void
	Proof :: verifyStructure() const {
		proof_->verifyStructure();
	}

	// mdl :: Proof implementation
	bool
	Proof :: isCompressed() const {
		return proof_->isCompressed();
	}
	index :: Step
	Proof :: getLength() const {
		return proof_->getLength();
	}
	index :: Arity
	Proof :: getQedArity() const {
		return proof_->getQedArity();
	}
	void
	Proof :: addStep (mdl :: proof :: Step* step) {
		proof_->addStep (step);
	}
	void
	Proof :: addVariable (mdl :: proof :: Variable* variable) {
		proof_->addVariable (variable);
	}
	void
	Proof :: addQed (mdl :: proof :: Qed* qed) {
		proof_->addQed (qed);
	}
	mdl :: proof :: Step*
	Proof :: getStep (const index :: Step index) {
		return proof_->getStep (index);
	}
	mdl :: proof :: Qed*
	Proof :: getQed (const index :: Arity i) {
		return proof_->getQed (i);
	}
	mdl :: proof :: Line*
	Proof :: getFirst() {
		return proof_->getFirst();
	}
	mdl :: proof :: Line*
	Proof :: getLast() {
		return proof_->getLast();
	}
	const mdl :: proof :: Step*
	Proof :: getStep (const index :: Step index) const {
		return proof_->getStep (index);
	}
	const mdl :: proof :: Qed*
	Proof :: getQed (const index :: Arity i) const {
		return proof_->getQed (i);
	}
	const mdl :: proof :: Line*
	Proof :: getFirst() const {
		return proof_->getFirst();
	}
	const mdl :: proof :: Line*
	Proof :: getLast() const {
		return proof_->getLast();
	}

	// object :: Scoping implementation
	mdl :: proof :: Scope*
	Proof :: buildScope (mdl :: proof :: Scope* scope)
	{
		scope_ = new proof :: scope :: Proof (scope, this);
		return proof_->buildScope (scope_);
	}
	void
	Proof :: setScope (mdl :: proof :: Scope* scope) {
		proof_->setScope (scope);
	}
	mdl :: proof :: Scope*
	Proof :: getScope() {
		return proof_->getScope();
	}
	const mdl :: proof :: Scope*
	Proof :: getScope() const {
		return proof_->getScope();
	}

	// object :: Identifiable interface
	const Location&
	Proof :: getLocation() const {
		return Identifiable :: getLocation();
	}
	value :: Name
	Proof :: getName() const {
		return Identifiable :: getName();
	}
	void
	Proof :: translateName (String& string, const index :: Arity i) const {
		Identifiable :: translateName (string, i);
	}
	void
	Proof :: replicateName (String& string) const {
		Identifiable :: replicateName (string);
	}
	mdl :: Theory*
	Proof :: getTheory() {
		return Identifiable :: getTheory();
	}
	mdl :: Identificator*
	Proof :: getIdentificator() {
		return Identifiable :: getIdentificator();
	}
	const mdl :: Theory*
	Proof :: getTheory() const {
		return Identifiable :: getTheory();
	}
	const mdl :: Identificator*
	Proof :: getIdentificator() const {
		return Identifiable :: getIdentificator();
	}

	// object :: Verifiable implementation
	void
	Proof :: check()
	{
		if (theorem_->getKind() == mdl :: Assertion :: THEOREM) {
			proof_->check();
		}
	}
	void
	Proof :: compress() {
		proof_->compress();
	}
	void
	Proof :: reprove()
	{
		Time timeLimit = Config :: getTimeLimit();
		mdl :: proof :: Step*
			step = getQed(0)->getStep();
		bool isReproved = Prover :: get()->reprove (timeLimit, step);
		if (!isReproved) {
			Error* error = new Error (location_, Error :: PROVER, "proof is not reproved");
			throw error;
		}
	}
	void
	Proof :: prove()
	{
		proof_->prove();
		dynamic_cast<mdl :: form :: Theorem*>(theorem_)->isProved_ = isVerified();
	}
	bool
	Proof :: isVerified() const {
		if (theorem_->getKind() == mdl :: Assertion :: PROBLEM) {
			return false;
		} else {
			return proof_->isVerified();
		}
	}
	void
	Proof :: mine (String& string) const
	{
		const value :: Integer depth =
			Config :: getMiningOptions().getValue (Config :: MINE_THEORIES) ?
			getTheoryDepth() :
			1;
		string << iterate << depth << tab << "<proof ";
		string << "name=\"" << *theoremId_ << "\" ";
		if (theory_ != NULL) {
			string << "identifier=\"";
			string << *theory_->getPath() << "." << *theoremId_ << "\" ";
		}
		location_.showAttributes (string);
		string << "/>" << endLine;
	}

	// object :: Buildable implementation
	void
	Proof :: build()
	{
		proof_->build();
		buildScope (dynamic_cast<mdl :: form :: Theorem*>(theorem_)->getScope());
	}

using nstd :: manipulator :: endLine;

	// object :: Writable implementation
	void
	Proof :: translate (String&) const {
	}
	void
	Proof :: replicate (String& string) const
	{
		if (!Config :: removeComments() && (comments_ != NULL)) {
			comments_->replicate (string);
		}
		string << location_.getIndent() << mdl :: Token :: proof_ << space;
		if (name_ != Table :: defaultName()) {
			string << Table :: names()->get (name_) << space;
		}
		string << mdl :: Token :: of_ << space;
		theoremId_->replicate (string);
		string << space;
		proof_->replicate (string);
		string << endLine;
	}
	bool
	Proof :: lookup() const
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return true;
		}
		if (theoremId_->lookup()) {
			if (Config :: lookupDefinition()) {
				std :: cout << *theorem_;
			} else {
				std :: cout << theorem_->getLocation();
			}
			return true;
		} else {
			return proof_->lookup();
		}
	}
	object :: Writable*
	Proof :: find()
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return this;
		}
		if (theoremId_->lookup()) {
			return this;
		} else {
			return proof_->find();
		}
	}
	const object :: Writable*
	Proof :: find() const
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return this;
		}
		if (theoremId_->lookup()) {
			return this;
		} else {
			return proof_->find();
		}
	}

	// object :: Object implementation
	void
	Proof :: commitSuicide() {
		delete this;
	}
	Size_t
	Proof :: getSizeOf() const  {
		return sizeof (Proof);
	}
	Size_t
	Proof :: getVolume() const
	{
		Size_t volume = 0;
		volume += Identifiable :: getVolume();
		volume += getAggregateVolume (comments_);
		volume += getAggregateVolume (theoremId_);
		volume += getAggregateVolume (proof_);
		volume += getAggregateVolume (scope_);
		return volume;
	}

	/****************************
	 *		Private members
	 ****************************/

	value :: Integer
	Proof :: getTheoryDepth() const
	{
		value :: Integer depth = 0;
		const mdl :: Theory* theory = theory_;
		while (theory != NULL) {
			++ depth;
			theory = theory->getTheory();
		}
		return depth;
	}
}
}
}

#endif /*MDL_FORM_BLOCK_PROOF_CPP_*/
