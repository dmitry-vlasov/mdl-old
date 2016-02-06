/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_step_Assertion.cpp                        */
/* Description:     assertion step inference                                 */
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
namespace step {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Assertion :: Assertion
	(
		mdl :: proof :: Line* line,
		const Location& location,
		const mdl :: Comments* comments,
		const index :: Step index,
		mdl :: Identificator* type,
		mdl :: proof :: Link* link,
		array :: Expression* const expression,
		mdl :: Theory* theory
	) :
	Step_
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
	substitution_ (NULL) {
	}
	Assertion :: Assertion
	(
		mdl :: proof :: Step* step,
		const index :: Step index,
		mdl :: proof :: Link* link,
		array :: Expression* expression
	) :
	Step_ (step, index, expression),
	link_ (link),
	downSteps_ (INITIAL_DOWN_STEPS_CAPACITY),
	substitution_ (NULL) {
	}
	Assertion :: ~ Assertion()
	{
		deleteAggregateObject (link_);
		deleteAggregateObject (substitution_);
	}

	// proof :: Assertion implementation
	array :: Substitution*
	Assertion :: getSubstitution() {
		return substitution_;
	}
	const array :: Substitution*
	Assertion :: getSubstitution() const {
		return substitution_;
	}
	void
	Assertion :: collectExperience()
	{
		addPositiveExperience();
		addNegativeExperience();
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;
using manipulator :: mode;

	// proof :: Step implementation
	mdl :: proof :: Step :: Class
	Assertion :: getClass() const {
		return mdl :: proof :: Step :: ASSERTION;
	}
	void
	Assertion :: addReference (mdl :: proof :: Reference* reference) {
		link_->getReferences()->add (reference);
	}
	void
	Assertion :: addDown (mdl :: proof :: Step* step) {
		downSteps_.add (step);
	}
	index :: Arity
	Assertion :: getUpArity() const {
		return link_->getReferences()->getArity();
	}
	index :: Arity
	Assertion :: getDownArity() const {
		return downSteps_.getSize();
	}

	mdl :: proof :: Link*
	Assertion :: getLink() {
		return link_;
	}
	mdl :: proof :: Node*
	Assertion :: getUp (const index :: Arity i) {
		return link_->getReferences()->get (i)->getNode();
	}
	mdl :: proof :: Step*
	Assertion :: getDown (const index :: Arity i) {
		return downSteps_.getValue (i);
	}

	const mdl :: proof :: Link*
	Assertion :: getLink() const {
		return link_;
	}
	const mdl :: proof :: Node*
	Assertion :: getUp (const index :: Arity i) const {
		return link_->getReferences()->get (i)->getNode();
	}
	const mdl :: proof :: Step*
	Assertion :: getDown (const index :: Arity i) const {
		return downSteps_.getValue (i);
	}

	// proof :: Node implementation
	void
	Assertion :: replicateReference (String& string) const {
		string << Token :: step_  << space << (index_ + 1);
	}
	void
	Assertion :: translateReference (String& string) const {
		link_->translate (string);
	}

	// proof :: Line implementation
	const mdl :: proof :: Line*
	Assertion :: getNext() const {
		return Step_ :: getNext();
	}
	const mdl :: proof :: Line*
	Assertion :: getPrev() const {
		return Step_ :: getPrev();
	}
	void
	Assertion :: incIndex (const index :: Step index) {
		Step_ :: incIndex (index);
	}
	void
	Assertion :: decIndex (const index :: Step index) {
		Step_ :: decIndex (index);
	}
	void
	Assertion :: setNext (mdl :: proof :: Line* line) {
		Step_ :: setNext (line);
	}
	void
	Assertion :: setPrev (mdl :: proof :: Line* line) {
		Step_ :: setPrev (line);
	}
	mdl :: proof :: Line*
	Assertion :: getNext() {
		return Step_ :: getNext();
	}
	mdl :: proof :: Line*
	Assertion :: getPrev() {
		return Step_ :: getPrev();
	}

	// object :: Scoping implementation
	mdl :: proof :: Scope*
	Assertion :: buildScope (mdl :: proof :: Scope* scope)
	{
		try {
			Step :: buildScope (scope);
			link_->buildScope (scope_);
			for (index :: Arity i = 0; i < getUpArity(); ++ i) {
				mdl :: proof :: Node* node = getUp (i);
				if (node->getKind() != mdl :: proof :: Node :: STEP) {
					continue;
				}
				mdl :: proof :: Step*
					step = dynamic_cast<mdl :: proof :: Step* >(node);
				step->addDown (this);
			}
			const value :: Integer expressionComplexity = expression_->getComplexity();
			Math :: statistics()->get (Statistics :: EXPRESSION_COMPLEXITY).add (expressionComplexity);
			Math :: expressions()->add (expression_, math :: Expressions :: PROOF);
			return scope_;
		} catch (Error* error) {
			error->add (location_);
			error->message() << "inference " << *this << "  build failed." << endLine;
			throw error;
		}
	}
	void
	Assertion :: setScope (mdl :: proof :: Scope* scope) {
		Step_ :: setScope (scope);
	}
	mdl :: proof :: Scope*
	Assertion :: getScope() {
		return Step_ :: getScope();
	}
	const mdl :: proof :: Scope*
	Assertion :: getScope() const {
		return Step_ :: getScope();
	}

	// object :: Expressive implementation
	const array :: Expression*
	Assertion :: getExpression() const {
		return Step_ :: getExpression();
	}
	const mdl :: Type*
	Assertion :: getType() const {
		return Step_ :: getType();
	}

	// object :: Verifiable implementation
	void
	Assertion :: check()
	{
		if (substitution_ != NULL) {
			substitution_->commitSuicide();
			substitution_ = NULL;
		}
		isVerified_ = false;
		Error* error = NULL;
		Memory :: stack().push();

		try {
			checkProposition();
			checkHypotheses();
			checkDisjoineds();
		} catch (Error* e) {
			error = e;
		}
		typedef
			pool :: Unary<const array :: Substitution>
			Pool;
		Pool* pool = new Pool();
		const array :: Substitution*
			constSub = const_cast<const array :: Substitution*>(substitution_);
		substitution_ = const_cast<array :: Substitution*>(constSub->clone<Pool> (pool));
		Memory :: stack().pop();

		const value :: Integer substitutionComplexity = substitution_->getComplexity();
		Math :: statistics()->get (Statistics :: SUBSTITUTION_COMPLEXITY).add (substitutionComplexity);

		if (error != NULL) {
			isVerified_ = false;
			throw error;
		} else {
			isVerified_ = true;
		}
	}

	// object :: Buildable implementation
	void
	Assertion :: build()
	{
		try {
			link_->build();
			Step_ :: build();
		} catch (Error* error) {
			error->add (location_);
			error->message() << "inference " << *this << "  build failed." << endLine;
			throw error;
		}
	}

	// object :: Writable implementation
	void
	Assertion :: translate (String& string) const
	{
		link_->translateReferences (string);
		translateVariables (string);
		link_->translateAssertion (string);
	}
	void
	Assertion :: replicate (String& string) const
	{
		const Indent indent = Step_ :: location_.getIndent();
		if (!Config :: removeComments() && (Step_ :: comments_ != NULL)) {
			string << indent;
			Step :: comments_->replicate (string);
			string << endLine;
		}
		string << indent << Token :: step_ << space;
		string << (index_ + 1) << space << Token :: colon_ << space;

		if (type_ != NULL) {
			Step_ :: type_->replicateName (string); string << space;
		} else {
			string << "<unknown>"<< space;
		}
		string << Token :: equality_ << space;

		link_->replicate (string);
		string << space << Token :: turnstile_ << space;

		Step :: expression_->write (string, indent); string << space;
		string << Token :: semicolon_ << endLine;
	}
	bool
	Assertion :: lookup() const
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return true;
		}
		if (link_->lookup()) {
			return true;
		}
		return Step :: lookup();
	}
	const object :: Writable*
	Assertion :: find() const
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return this;
		}
		const object :: Writable* object = link_->find();
		if (object != NULL) {
			return object;
		}
		return Step :: find();
	}

	// object :: Object implementation
	void
	Assertion :: commitSuicide() {
		delete this;
	}
	Size_t
	Assertion :: getVolume() const
	{
		Size_t volume = 0;
		volume += Step_ :: getVolume();
		volume += downSteps_.getVolume();
		volume += getAggregateVolume (link_);
		volume += getAggregateVolume (substitution_);
		return volume;
	}
	Size_t
	Assertion :: getSizeOf() const {
		return sizeof (Assertion);
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Assertion :: translateVariables (String& string) const
	{
		const mdl :: Assertion* const
			assertion = link_->getAssertion();
		const mdl :: Variables* const
			variables = assertion->getVariables();
		for (index :: Arity i = 0; i < variables->getSize(); ++ i) {
			const mdl :: header :: Variable* const
				variable = variables->getVariable (i);
			const array :: Substitution*
				substitution = substitution_->find (variable->getSymbol());

			if (substitution == NULL) {
				Error* error = new Error (location_, Error :: SEMANTIC, "unused variable");
				error->message() << endLine << *variable << endLine;
				throw error;
			} else {
				substitution->getTerm()->translate (string, variable->getType());
			}
		}
	}
	void
	Assertion :: checkProposition() const
	{
		const mdl :: Assertion* const
			assertion = link_->getAssertion();

		const index :: Assertion
			assertionIndex = assertion->getIndex();
		const index :: Assertion
			theoremIndex = scope_->getAssertion()->getIndex();

		if (assertionIndex >= theoremIndex) {
			referenceToUnverifiedError();
		}
		const mdl :: Proposition* const
			prop = link_->getProposition();
		const array :: Expression*
			proposition = prop->getExpression();

		const array :: Substitution* substitution = NULL;
		const bool
			success = proposition->unifyDirect
			(
				const_cast<array :: Expression*>(expression_),
				substitution,
				const_cast<const array :: Substitution*&>(substitution_)
			);
		if (!success || (substitution != NULL)) {
			propositionUnificationError();
		}
	}
	void
	Assertion :: checkHypotheses() const
	{
		const mdl :: Assertion* const
			assertion = link_->getAssertion();
		for (index :: Arity index = 0; index < link_->getReferences()->getArity(); ++ index) {
			const mdl :: Hypothesis* const
				hyp = assertion->getHypothesis (index);
			const array :: Expression*
				hypothesis = hyp->getExpression();
			const mdl :: proof :: Node*
				node = link_->getReferences()->get (index)->getNode();
			const array :: Expression*
				reference = node->getExpression();

			const array :: Substitution* substitution = NULL;
			array :: Substitution* s = substitution_;
			bool
				success = hypothesis->unifyDirect
				(
					reference,
					substitution,
					const_cast<const array :: Substitution*&>(substitution_)
				);
			if (!success || (substitution != NULL)) {
				hypothesisUnificationError (index);
			}
		}
	}
	void
	Assertion :: checkDisjoineds() const
	{
		const mdl :: Assertion* const
			assertion = link_->getAssertion();
		const mdl :: Disjointeds* const
			disjointeds = assertion->getDisjointeds();
		const mdl :: Assertion* const
			theorem = scope_->getAssertion();
		disjointeds->check (substitution_, theorem);
	}

	void
	Assertion :: addPositiveExperience()
	{
		mdl :: Proposition*
			proposition = link_->getProposition();
		mdl :: statement :: Experience*
			experience = proposition->getExperience();
		experience->addPositive (this);
		proposition->incRate (true);
	}
	void
	Assertion :: addNegativeExperience()
	{
		typedef
			forest :: Proposition :: Unify_<array :: Expression> :: Result_
			Unified_;
		forest :: Proposition*
			propositions = Math :: propositions()->getTree();
		Memory :: stack().push();
		mdl :: Proposition*
			firstTheoremProposition = scope_->getAssertion()->getProposition (0);

		Unified_ result =
			propositions->unifyDirect<array :: Expression>
			(
				expression_, NULL, NULL,
				firstTheoremProposition->getSourceIndex() - 1
			);
		const Unified_ :: Node_*
			node = result.getFirst();
		while (node != NULL) {
			typedef
				forest :: Proposition :: Data_
				Data_;
			const Data_&
				data = node->getReference().getSource()->getData();
			const Data_ :: Node_*
				dataNode = data.getFirst();
			while (dataNode != NULL) {
				mdl :: Proposition*
					proposition = const_cast<mdl :: Proposition*>(dataNode->getValue());
				if (proposition != link_->getProposition()) {
					proposition->getExperience()->addNegative (this);
					proposition->incRate (false);
				}
				dataNode = dataNode->getNext();
			}
			node = node->getNext();
		}
		Memory :: stack().pop();
	}

	void
	Assertion :: referenceToUnverifiedError () const
	{
		const mdl :: Assertion* const
			assertion = link_->getAssertion();

		Error* error = new Error (location_, Error :: SEMANTIC);
		error->message() << "in ";
		scope_->getAssertion()->replicateName (error->message());
		error->message() << " theorem proof"<< endLine;
		error->message() << "assertion ";
		assertion->replicateName (error->message());
		error->message() << " is not verified." << endLine;
		throw error;
	}
	void
	Assertion :: propositionUnificationError () const
	{
		const mdl :: Assertion* const
			assertion = link_->getAssertion();
		const index :: Arity
			index = link_->getPropositionIndex();
		const mdl :: Statement* const
			prop = link_->getProposition ();
		const array :: Expression*
			proposition = prop->getExpression();

		expression :: Mode mode;
		//mode << expression :: Mode :: SHOW_REPLACEABILITY;
		//mode << expression :: Mode :: SHOW_TERMS;

		Error* error = new Error (location_, Error :: UNIFICATION);
		error->message() << mode << "in ";
		scope_->getAssertion()->replicateName (error->message());
		error->message() << " theorem proof"<< endLine;
		error->message() << "assertion: " << endLine;
		error->message() << *assertion << endLine;
		error->message() << "unification " << endLine;
		error->message() << "with proof step " << (index_ + 1) << " fails." << endLine;

		error->message() << tab << "proof step expression: ";
		expression_->write (error->message());
		error->message() << endLine;
		error->message() << tab << "assertion proposition: ";
		proposition->write (error->message());
		error->message() << endLine;
		if (substitution_ != NULL) {
			error->message() << tab << "substitution: ";
			substitution_->show (error->message());
		} else {
			error->message() << tab << "substitution: NULL";
			error->message() << endLine;
		}
		throw error;
	}
	void
	Assertion :: hypothesisUnificationError (const index :: Arity index) const
	{
		const mdl :: Assertion* const
			assertion = link_->getAssertion();
		const mdl :: Hypothesis* const
			hyp = assertion->getHypothesis (index);
		const array :: Expression*
			hypothesis = hyp->getExpression();
		const array :: Expression*
			reference = link_->getReferences()->get (index)->getNode()->getExpression();

		Error* error = new Error (location_, Error :: UNIFICATION);
		error->message() << "in ";
		scope_->getAssertion()->replicateName (error->message());
		error->message() << " theorem proof"<< endLine;
		error->message() << "assertion: " << endLine;
		error->message() << *assertion << endLine;
		error->message() << "hypothesis " << (index + 1) << " unification" << endLine;
		error->message() << "with reference in step " << (index_ + 1) << " fails." << endLine;

		error->message() << tab << "reference expression: ";
		reference->write (error->message());
		error->message() << endLine;
		error->message() << tab << "assertion hypothesis: ";
		hypothesis->write (error->message());
		error->message() << endLine;
		if (substitution_ != NULL) {
			error->message() << tab << "substitution: ";
			substitution_->show (error->message());
		} else {
			error->message() << tab << "substitution: NULL";
			error->message() << endLine;
		}
		throw error;
	}
}
}
}
}


