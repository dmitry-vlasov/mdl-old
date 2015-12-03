/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_proof_Prop.cpp                                */
/* Description:     prop proof element                                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_PROOF_PROP_CPP_
#define MDL_PROVER_PROOF_PROP_CPP_

namespace mdl {
namespace prover {
namespace proof {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	Prop<A> :: Prop (const Prop& prop) try :
	evidence_ (prop.evidence_),
	substitution_ (Substitution_ :: create (prop.substitution_)),
	arity_ (prop.arity_),
	up_ (prop.up_.getSize()),
	depth_ (prop.depth_),
	cardinality_ (prop.cardinality_),
	isValid_ (prop.isValid_),
	step_ (NULL)
	{
		for (index :: Arity i = 0; i < prop.up_.getSize(); ++ i) {
			Proof_* upProof = prop.up_.getValue (i);
			Proof_* upCopy = upProof->makeCopy();
			up_.getReference (i) = upCopy;
		}
		evidence_->getNode()->getTree()->root().add (this);
	} catch (Exception& exception) {
		Proof_ :: deleteAggregateObject (substitution_);
		if (!up_.isNull()) {
			for (index :: Arity i = 0; i < up_.getSize(); ++ i) {
				Proof_ :: deleteObject (up_ [i]);
				up_ [i] = NULL;
			}
		}
		throw exception;
	}
	template<class A>
	inline
	Prop<A> :: Prop
	(
		Evidence_* evidence,
		const Substitution_* substitution,
		index :: Arity arity,
		Proof_* up[]
	) try :
	evidence_ (evidence),
	substitution_ (Substitution_ :: create (substitution)),
	arity_ (arity),
	up_ (arity),
	depth_ (1),
	cardinality_ (1),
	isValid_ (false),
	step_ (NULL)
	{
		for (index :: Arity i = 0; i < arity; ++ i) {
			up_.getReference (i) = up [i];
			const index :: Step
				proofDepth = up[i]->getDepth();
			depth_ =
				(proofDepth + 1 > depth_) ?
				proofDepth + 1 :
				depth_;
			cardinality_ += up[i]->getCardinality();
		}
		checkDisjointeds();
		evidence_->getNode()->getTree()->root().add (this);
	} catch (Exception& exception) {
		Proof_ :: deleteAggregateObject (substitution_);
		if (!up_.isNull()) {
			for (index :: Arity i = 0; i < up_.getSize(); ++ i) {
				Proof_ :: deleteObject (up_ [i]);
				up_ [i] = NULL;
			}
		}
		throw exception;
	}
	template<class A>
	Prop<A> :: ~ Prop() {
		Proof_ :: deleteAggregateObject (substitution_);
	}

using manipulator :: space;
using manipulator :: tab;
using manipulator :: endLine;

	// prover :: Proof implementation
	template<class A>
	index :: Arity
	Prop<A> :: getUpArity() const {
		return arity_;
	}
	template<class A>
	typename Prop<A> :: Proof_*
	Prop<A> :: getUp (const index :: Arity i) {
		return up_.getValue (i);
	}
	template<class A>
	const typename Prop<A> :: Proof_*
	Prop<A> :: getUp (const index :: Arity i) const {
		return up_.getValue (i);
	}
	template<class A>
	void
	Prop<A> :: checkValidity()
	{
		for (index :: Arity i = 0; i < up_.getSize(); ++ i) {
			Proof_* upProof = up_.getValue (i);
			upProof->checkValidity();
		}
		checkDisjointeds();
	}
	template<class A>
	typename Prop<A> :: Proof_*
	Prop<A> :: makeCopy() const {
		return new Prop (*this);
	}
	template<class A>
	typename Prop<A> :: Proof_ :: Kind
	Prop<A> :: getKind() const {
		return Proof_ :: PROP;
	}
	template<class A>
	bool
	Prop<A> :: isIdentical (const Proof_* proof) const
	{
		if (proof->getKind() != Proof_ :: PROP) {
			return false;
		}
		const Prop* prop = dynamic_cast<const Prop*>(proof);
		if (evidence_->getNode()->getProposition() !=
			prop->evidence_->getNode()->getProposition()) {
			return false;
		}
		/*if (evidence_ != prop->evidence_) {
			return false;
		}*/
		/*if (!substitution_->isIdentical (prop->substitution_)) {
			return false;
		}*/
		if (up_.getSize() != prop->up_.getSize()) {
			return false;
		}
		for (index :: Arity i = 0; i < up_.getSize(); ++ i) {
			const Proof_* const
				proof_1 = up_.getValue (i);
			const Proof_* const
				proof_2 = prop->up_.getValue (i);
			if (!proof_1->isIdentical (proof_2)) {
				return false;
			}
		}
		return true;
	}
	template<class A>
	bool
	Prop<A> :: isValid() const
	{
		if (!isValid_) {
			return false;
		}
		for (index :: Arity i = 0; i < up_.getSize(); ++ i) {
			const Proof_* const
				proof = up_.getValue (i);
			if (!proof->isValid()) {
				return false;
			}
		}
		return true;
	}
	template<class A>
	void
	Prop<A> :: resetCompilation()
	{
		step_ = NULL;
		for (index :: Arity i = 0; i < up_.getSize(); ++ i) {
			Proof_* proof = up_.getValue (i);
			proof->resetCompilation();
		}
	}
	template<class A>
	void
	Prop<A> :: verifyIntegrity()
	{
		mdl :: proof :: Step* claim =
			(getCardinality() > 1) ?
			compileClaim() :
			compileStep();
		//std :: cout << *claim << std :: endl;
		try {
			claim->check();
		} catch (Error* error) {
			typename Error :: Type_ errorType = error->getType();
			delete error;
			if (errorType == Error :: DISJOINTEDS) {
				Proof_ :: deleteObject (claim);
				return;
			} else {
				Proof_ :: deleteObject (claim);
				throw error;
			}
			/*
			//claim->getScope()->getProof()->check();
			evidence_->verifyIntegrity();
			Counter :: set();
			Config :: miscOption (Config :: EXPR_WITH_TYPES).value() = true;
			Config :: miscOption (Config :: EXPR_MULTYLINE).value() = true;
			try {
				claim->check();
			} catch (Error* e) {
				error = e;
			}
			//std :: cout << "substitutuon = " << *substitution_ << std :: endl;
			//std :: cout << "evidence_->substitutuon = " << *evidence_->getSubstitution() << std :: endl;
			std :: cout << "prop proof verification error:" << std :: endl;
			std :: cout << *getEvidence()->getNode()->getTree()->getProblem() << std :: endl;
			std :: cout << "claim:" << std :: endl;
			std :: cout << *claim << std :: endl << std :: endl << std :: endl;
			std :: cout << "prop node:" << std :: endl;
			std :: cout << *getEvidence()->getNode() << std :: endl << std :: endl << std :: endl;
			std :: cout << "hyp node (down):" << std :: endl;
			std :: cout << *getEvidence()->getNode()->getDown(0) << std :: endl;

			mdl :: Assertion* ass = Math :: assertions()->get ("math.funssres");


			for (int i = 0; i < evidence_->getNode()->getTree()->up().getSize(); ++ i) {
				const Node_* node = evidence_->getNode()->getTree()->up().getNode (i);
				if (node->getProposition() != NULL &&
					node->getProposition()->getAssertion() == ass) {

					std :: cout << std :: endl << "SSSSSSS -- NODE -- SSSSSSS" << std :: endl << std :: endl;
					//node->dump();
					node->dumpTree();
					std :: cout << std :: endl << "SSSSSSS -- DONW -- SSSSSSSS" << std :: endl << std :: endl;
					std :: cout << "global index = " << node->getDown(0)->getGlobalIndex() << std :: endl;
					node->getDown(0)->dump();
					node->dumpEvidences();
					std :: cout << std :: endl << "DDDDDDDDDDDDDDD" << std :: endl << std :: endl;


					const Prop_* prop = dynamic_cast<const Prop_*>(node);
					std :: cout << std :: endl << "DDDDDDD -- node->substitutionInt_->dump() -- DDDDDDDD" << std :: endl << std :: endl;
					prop->substitutionInt_->dump();

					std :: cout << std :: endl << "DDDDDDD -- node->substitutionExt_->dump() -- DDDDDDDD" << std :: endl << std :: endl;
					prop->substitutionExt_->dump();
				}
			}

			std :: cout << *ass;

			std :: cout << *error << std :: endl;
			std :: cout << *this << std :: endl;

			Config :: miscOption (Config :: EXPR_WITH_TYPES).value() = false;
			Config :: miscOption (Config :: EXPR_MULTYLINE).value() = false;

			Proof_ :: deleteObject (error);*/
		}
		const_cast<Node_*>(getEvidence()->getNode())->getTree()->getQuestion()->clear();
		Proof_ :: deleteObject (claim);
		resetCompilation();
	}
	template<class A>
	const typename Prop<A> :: Evidence_*
	Prop<A> :: getEvidence() const {
		return evidence_;
	}
	template<class A>
	index :: Step
	Prop<A> :: getDepth() const {
		return depth_;
	}
	template<class A>
	value :: Integer
	Prop<A> :: getCardinality() const {
		return cardinality_;
	}
	template<class A>
	mdl :: proof :: Step*
	Prop<A> :: compileStep (mdl :: proof :: Question* question)
	{
		compileStepUp (question);
		createStep
		(
			question,
			question->getIndex()
		);
		return step_;
	}
	template<class A>
	void
	Prop<A> :: compileClaim (mdl :: proof :: Claim* claim)
	{
		compileClaimUp (claim);
		if (step_ != NULL) {
			return;
		}
		createStep
		(
			claim,
			claim->getProof()->getLength()
		);
		const_cast<Location&>(step_->getLocation()).indent().incTabs();
		addVariables (claim);
		//subtypeVariables (claim);
		claim->addStep (step_);
	}
	template<class A>
	mdl :: proof :: Reference*
	Prop<A> :: getReference() {
		return NULL;
	}
	template<class A>
	mdl :: proof :: Step*
	Prop<A> :: getStep() {
		return step_;
	}
	template<class A>
	const mdl :: proof :: Reference*
	Prop<A> :: getReference() const {
		return NULL;
	}
	template<class A>
	const mdl :: proof :: Step*
	Prop<A> :: getStep() const {
		return step_;
	}
	template<class A>
	void
	Prop<A> :: showAsTerm(String& string) const
	{
		const mdl :: Proposition*
			proposition = evidence_->getNode()->getProposition();
		const mdl :: Assertion*
			assertion = proposition->getAssertion();
		const index :: Arity
			index = proposition->getIndex();
		assertion->replicateName (string);
		if (index > 0) {
			string << ":" << index;
		}
		string << "(";
		for (index :: Arity i = 0; i < arity_; ++ i) {
			const Proof_* hyp = up_.getValue (i);
			hyp->showAsTerm (string);
			if (i + 1 < arity_) {
				string << ", ";
			}
		}
		string << ")";
	}

	// object :: Object interface
	template<class A>
	void
	Prop<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Prop<A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += Proof_ :: getAggregateVolume (substitution_);
		return volume;
	}
	template<class A>
	Size_t
	Prop<A> :: getSizeOf() const {
		return sizeof (Prop);
	}
	template<class A>
	void
	Prop<A> :: show (String& string) const
	{
		string << "PROOF_PROP: ";
		evidence_->getNode()->getProposition()->getAssertion()->replicateName (string);
		string << ", ";
		if (substitution_ == NULL) {
			string << "{ }";
		} else {
			string << *substitution_;
		}
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class A>
	void
	Prop<A> :: checkDisjointeds()
	{
		const Node_* const
			node = evidence_->getNode();
		const Prop_*
			prop = dynamic_cast<const Prop_*>(node);
		const mdl :: Proposition* const
			proposition = node->getProposition();
		const mdl :: Assertion* const
			assertion = proposition->getAssertion();
		const mdl :: Disjointeds* const
			disjointeds = assertion->getDisjointeds();
		const mdl :: Variables* const
			variables = assertion->getVariables();
		const mdl :: Assertion*
			theorem = getEvidence()->getNode()->getTree()->getProblem();

		Memory :: stack().push(); {
			stack :: Substitution*
				outer = stack :: Substitution :: create (prop->substitutionExt_);
			stack :: Substitution*
				ext = stack :: Substitution :: create (substitution_);
			outer = outer->compose (ext, false);
			for (index :: Arity i = 0; i < variables->getSize(); ++ i) {
				const mdl :: header :: Variable* const
					variable = variables->getVariable (i);
				const Symbol& symbol = variable->getSymbol();
				if (outer->find (symbol) == NULL) {
					const stack :: Substitution :: Term_*
						term = stack :: Expression :: createSingleton (symbol);
					const stack :: Substitution*
						delta = new stack :: Substitution (symbol, term);
					outer = outer->join (delta);
				}
			}
			isValid_ = disjointeds->check
			(
				outer->castAway<allocator :: Heap>(),
				theorem
			);
		}
		Memory :: stack().pop();
	}
	template<class A>
	void
	Prop<A> :: compileStepUp (mdl :: proof :: Question* question)
	{
		for (index :: Arity i = 0; i < up_.getSize(); ++ i) {
			Proof_* proof = up_.getValue (i);
			proof->compileStep (question);
		}
	}
	template<class A>
	void
	Prop<A> :: compileClaimUp (mdl :: proof :: Claim* claim)
	{
		for (index :: Arity i = 0; i < up_.getSize(); ++ i) {
			Proof_* proof = up_.getValue (i);
			proof->compileClaim (claim);
		}
	}
	template<class A>
	void
	Prop<A> :: createStep
	(
		mdl :: proof :: Step* step,
		const index :: Step index
	)
	{
		mdl :: proof :: References* references = createReferences();

		mdl :: proof :: Link*
			link = new form :: proof :: Link
			(
				step->getLocation(),
				evidence_->getNode()->getProposition(),
				references
			);

		array :: Expression* expression = NULL;
		Memory :: stack().push(); {
			stack :: Expression* const
				exp = new stack :: Expression (evidence_->getNode()->getExpression());
			exp->execute (substitution_);
			expression = new array :: Expression (exp);
		}
		Memory :: stack().pop();
		step_ = new form :: proof :: step :: Assertion
		(
			step,
			index,
			link,
			expression
		);
	}
	template<class A>
	mdl :: proof :: References*
	Prop<A> :: createReferences()
	{
		mdl :: proof :: References*
			references = new form :: proof :: References (up_.getSize());
		for (index :: Arity i = 0; i < up_.getSize(); ++ i) {
			Proof_* proof = up_.getValue (i);
			mdl :: proof :: Reference* reference = proof->getReference();
			references->add (reference);
		}
		return references;
	}
	template<class A>
	void
	Prop<A> :: addVariables (mdl :: proof :: Claim* claim)
	{
		array :: Expression*
			expression = step_->getExpression();
		for (index :: Literal i = 0; i < expression->getSize(); ++ i) {
			const Symbol& symbol = expression->getSymbol (i);
			if (symbol.isVariable()) {
				claim->addVariable (symbol);
			}
		}
	}

	template<class A>
	mdl :: proof :: Step*
	Prop<A> :: compileClaim()
	{
		resetCompilation();
		mdl :: proof :: Claim*
			claim = new form :: proof :: step :: Claim
			(
				evidence_->getNode()->getTree()->getQuestion(),
				getCardinality()
			);
		compileClaim (claim);
		return claim;
	}
	template<class A>
	mdl :: proof :: Step*
	Prop<A> :: compileStep()
	{
		resetCompilation();
		mdl :: proof :: Question*
			question = const_cast<mdl :: proof :: Question*>
				(getEvidence()->getNode()->getTree()->getQuestion());
		return compileStep (question);
	}
}
}
}

#endif /*MDL_PROVER_PROOF_PROP_CPP_*/
