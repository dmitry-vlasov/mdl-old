/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_block_Theorem.cpp                               */
/* Description:     theorem class                                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_BLOCK_THEOREM_CPP_
#define MDL_FORM_BLOCK_THEOREM_CPP_

namespace mdl {
namespace form {
namespace block {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Theorem :: Theorem
	(
		const Location& location,
		const mdl :: Comments* comments,
		lexer :: Indent barIndent,
		value :: Name name,
		mdl :: Variables* variables,
		mdl :: Disjointeds* disjointeds,
		const vector :: parser :: Hypothesis& hypothesisVector,
		const vector :: parser :: Provable& propositionVector,
		mdl :: Theory* theory,
		bool isProblem
	) :
	Ancestor_
	(
		location,
		comments,
		barIndent,
		name,
		variables,
		disjointeds,
		hypothesisVector,
		propositionVector,
		theory
	),
	proofVector_ (INITIAL_PROOF_VECTOR_CAPACITY),
	scope_ (NULL),
	isProved_ (false),
	isProblem_ (isProblem)
	{
		Ancestor_ :: add (this);
		if (Config :: localParsing()) {
			return;
		}
		if (!Config :: shallowParsing() || location_.isTop()) {
			scope_ = new proof :: scope :: Assertion (this);
		}
	}
	Theorem :: ~ Theorem() {
		deleteAggregateObject (scope_);
	}

	void
	Theorem :: verifyStructure() const
	{
		for (value :: Integer i = 0; i < proofVector_.getSize(); ++ i) {
			const mdl :: Proof* proof = proofVector_.getValue (i);
			dynamic_cast<const Proof*>(proof)->verifyStructure();
		}
	}

	// object :: Provable implementation
	void
	Theorem :: addProof (mdl :: Proof* proof) {
		proofVector_.add (proof);
	}
	mdl :: proof :: Scope*
	Theorem :: getScope() {
		return scope_;
	}
	vector :: Proof&
	Theorem :: getProofVector() {
		return proofVector_;
	}
	mdl :: Proof*
	Theorem :: getProof (const value :: Name name)
	{
		for (value :: Integer i = 0; i < proofVector_.getSize(); ++ i) {
			mdl :: Proof* proof = proofVector_.getValue (i);
			if (proof->getName() == name) {
				return proof;
			}
		}
		return NULL;
	}
	const mdl :: proof :: Scope*
	Theorem :: getScope() const {
		return scope_;
	}
	const vector :: Proof&
	Theorem :: getProofVector() const {
		return proofVector_;
	}
	const mdl :: Proof*
	Theorem :: getProof (const value :: Name name) const
	{
		for (value :: Integer i = 0; i < proofVector_.getSize(); ++ i) {
			const mdl :: Proof* proof = proofVector_.getValue (i);
			if (proof->getName() == name) {
				return proof;
			}
		}
		return NULL;
	}

	// mdl :: Assertion interface
	mdl :: Assertion :: Kind
	Theorem :: getKind() const {
		return isProblem_ ? mdl :: Assertion :: PROBLEM : mdl :: Assertion :: THEOREM;
	}

	// object :: Verifiable implementation
	void
	Theorem :: check()
	{
		//std :: cout << Table :: names()->get(name_) << std :: endl;
		if (proofVector_.isEmpty()) {
			Error* error = new Error (location_, Error :: SEMANTIC, "non-proved theorem occurs");
			throw error;
		}
	}
	void
	Theorem :: compress() {
		check();
	}
	void
	Theorem :: reprove() {
		prove();
	}
	void
	Theorem :: prove()
	{
		if (proofVector_.getSize() == 0) {
			mdl :: Proof* proof = new Proof (this);
			proofVector_.add (proof);
			contents_->addComponentNextTo (proof, this);
		}
	}
	bool
	Theorem :: isVerified() const
	{
		for (value :: Integer i = 0; i < proofVector_.getSize(); ++ i) {
			const mdl :: Proof* proof = proofVector_.getValue (i);
			if (!proof->isVerified()) {
				return false;
			}
		}
		isProved_ = true;
		isProblem_ = false;
		return true;
	}

using manipulator :: space;
using manipulator :: endLine;

	// object :: Buildable implementation
	void
	Theorem :: build()
	{
		try {
			Ancestor_ :: build();
			buildHypothesisNodes();
			buildPropositionNodes();
		} catch (Error* error) {
			error->add (location_);
			if (isProblem_) {
				error->message() << "in theorem ";
			} else {
				error->message() << "in problem ";
			}
			replicateName (error->message());
			error->message() << endLine;
			throw error;
		}
	}

	// object :: Writable implementation
	void
	Theorem :: translate (String& string) const {
		Ancestor_ :: translate (string);
	}
	void
	Theorem :: replicate (String& string) const
	{
		replicateHeader (string);
		Ancestor_ :: replicate (string);
		string << endLine;
	}

	// object :: Object implementation
	void
	Theorem :: commitSuicide() {
		delete this;
	}
	Size_t
	Theorem :: getSizeOf() const {
		return sizeof (Theorem);
	}
	Size_t
	Theorem :: getVolume() const
	{
		Size_t volume = 0;
		volume += Ancestor_ :: getVolume ();
		volume += proofVector_.getVolume();
		volume += getAggregateVolume (scope_);
		return volume;
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Theorem :: buildHypothesisNodes()
	{
		for (index :: Arity i = 0; i < hypothesisVector_.getSize(); ++ i) {
			mdl :: Hypothesis*
				hypothesis = hypothesisVector_.getValue (i);
			mdl :: proof :: Node*
				node = hypothesis->getProofNode();
			node->setScope (scope_);
		}
	}
	void
	Theorem :: buildPropositionNodes()
	{
		for (index :: Arity i = 0; i < propositionVector_.getSize(); ++ i) {
			mdl :: Proposition*
				proposition = propositionVector_.getValue (i);
			mdl :: proof :: Node*
				node = proposition->getProofNode();
			node->setScope (scope_);
		}
	}
	void
	Theorem :: replicateHeader (String& string) const
	{
		if (!Config :: removeComments() && (comments_ != NULL)) {
			string << location_.getIndent();
			comments_->replicate (string);
			string << endLine;
		}
		string << location_.getIndent();
		if (Config :: prove()) {
			if (isProblem_) {
				string << Token :: problem_ << space;
			} else {
				string << Token :: theorem_ << space;
			}
		} else if (Config :: shallowParsing()){
			if (isProblem_) {
				string << Token :: problem_ << space;
			} else {
				string << Token :: theorem_ << space;
			}
		} else {
			bool isCompressed = false;
			for (value :: Integer i = 0; i < proofVector_.getSize(); ++ i) {
				const mdl :: Proof* proof = proofVector_.getValue (i);
				if (proof->isCompressed()) {
					isCompressed = true;
					break;
				}
			}
			if (isProblem_) {
				string << Token :: problem_ << space;
			} else {
				string << Token :: theorem_ << space;
			}
		}
	}
}
}
}

#endif /*MDL_FORM_BLOCK_THEOREM_CPP_*/
