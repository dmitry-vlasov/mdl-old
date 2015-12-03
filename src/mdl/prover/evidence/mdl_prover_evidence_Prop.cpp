/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_evidence_Prop.cpp                             */
/* Description:     prop proof evidence element                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_EVIDENCE_PROP_CPP_
#define MDL_PROVER_EVIDENCE_PROP_CPP_

namespace mdl {
namespace prover {
namespace evidence {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	Prop<A> :: Prop
	(
		Node_* node,
		const index :: Arity arity,
		Evidence_* up[],
		Substitution_* substitution
	) try :
	Evidence_ (node),
	substitution_ (substitution),
	up_ (arity),
	down_ (NULL),
	depth_ (0),
	cardinality_ (1),
	clone_ (NULL)
	{
		for (index :: Arity i = 0; i < arity; ++ i) {
			Evidence_* evidence = up [i];
			evidence->setDown (this);
			up_.getReference (i) = evidence;
			const index :: Step
				upDepth = evidence->getDepth();
			const_cast<index :: Step&>(depth_) =
				(upDepth + 1 > depth_) ?
				upDepth + 1 :
				depth_;
			const_cast<value :: Integer&>(cardinality_) += evidence->getCardinality();
		}
		Evidence_ :: node_->getTree()->refresh ("building prop evidence node");
		Evidence_ :: node_->getTree()->down().add (this);
	} catch (Exception& exception) {
		Evidence_ :: deleteAggregateObject (substitution_);
		throw exception;
	}
	template<class A>
	Prop<A> :: ~ Prop() {
		Evidence_ :: deleteAggregateObject (substitution_);
	}

	template<class A>
	inline index :: Arity
	Prop<A> :: getArity() const {
		return up_.getSize();
	}

using manipulator :: space;
using manipulator :: tab;
using manipulator :: endLine;
using manipulator :: iterate;

	// prover :: Evidence implementation
	template<class A>
	bool
	Prop<A> :: growDown()
	{
		this->dumpTree();
		Node_* node = Evidence_ :: node_->getDown();
		return node->growDown (this);
	}
	template<class A>
	void
	Prop<A> :: setDown (Evidence_* down) {
		down_ = down;
	}
	template<class A>
	value :: Integer
	Prop<A> :: getUpForking() const {
		return up_.getSize();
	}
	template<class A>
	value :: Integer
	Prop<A> :: getDownForking() const {
		return (down_ == NULL) ? 0 : 1;
	}
	template<class A>
	typename Prop<A> :: Evidence_*
	Prop<A> :: getUp (const value :: Integer i) {
		return up_.getValue (i);
	}
	template<class A>
	typename Prop<A> :: Evidence_*
	Prop<A> :: getDown (const value :: Integer i) {
		return (i == 0) ? down_ : NULL;
	}
	template<class A>
	const typename Prop<A> :: Evidence_*
	Prop<A> :: getUp (const value :: Integer i) const {
		return up_.getValue (i);
	}
	template<class A>
	const typename Prop<A> :: Evidence_*
	Prop<A> :: getDown (const value :: Integer i) const {
		return (i == 0) ? down_ : NULL;
	}
	template<class A>
	inline void
	Prop<A> :: verifyIntegrity() const
	{
		Memory :: stack().push();
		verifySubstitutions();

		expression :: Mode mode;
		mode << expression :: Mode :: SHOW_REPLACEABILITY;
		verifyUp();

		const Prop_*
			prop = dynamic_cast<const Prop_*>(Evidence_ :: node_);
		const stack :: Substitution* const
			substitutionExt = stack :: Substitution :: create (prop->substitutionExt_);

		stack :: Expression* const
			proposition_1 = new stack :: Expression (Evidence_ :: node_->getExpression());
		proposition_1->execute (getSubstitution());
		const mdl :: Proposition* const
			proposition = Evidence_ :: node_->getProposition();
		const mdl :: Assertion* const
			assertion = proposition->getAssertion();
		stack :: Expression* const
			proposition_2 = new stack :: Expression (proposition->getExpression());
		proposition_2->execute (substitutionExt);
		proposition_2->execute (getSubstitution());
		if (*proposition_1 != *proposition_2) {
			Error* error = new Error (Error :: SEMANTIC);
			error->message() << mode << "debug proposition ";
			assertion->replicateName (error->message());
			error->message() << " verification fail" << endLine;
			error->message() << *proposition_1 << " != " << *proposition_2 << endLine;
			showVerification (error->message());
			Memory :: stack().pop();
			throw error;
		}

		if (assertion->getHypArity() != up_.getSize()) {
			Error* error = new Error (Error :: SEMANTIC);
			error->message() << mode  << "debug proposition ";
			assertion->replicateName (error->message());
			error->message() << " verification fail: arity mismatch" << endLine;
			error->message() << assertion->getHypArity() << " != " << up_.getSize() << endLine;
			showVerification (error->message());
			Memory :: stack().pop();
			throw error;
		}

		for (index :: Arity i = 0; i < up_.getSize(); ++ i) {
			const mdl :: Hypothesis* const
				hypothesis_1 = assertion->getHypothesis (i);
			stack :: Expression* const
				hyp_1 = new stack :: Expression (hypothesis_1->getExpression());
			hyp_1->execute (substitutionExt);
			hyp_1->execute (getSubstitution());
			stack :: Expression* const
				hyp_2 = new stack :: Expression (up_.getValue (i)->Evidence_ :: getNode()->getExpression());
			hyp_2->execute (getSubstitution());
			if (*hyp_1 != *hyp_2) {
				Error* error = new Error (Error :: SEMANTIC);
				error->message() << mode  << "debug hypothesis ";
				assertion->replicateName (error->message());
				error->message() << " verification fail" << endLine;
				error->message() << *hyp_1 << " != " <<  *hyp_2 << endLine;
				showVerification (error->message());
				//show (error->message());
				Memory :: stack().pop();
				throw error;
			}
		}
		Memory :: stack().pop();
	}
	template<class A>
	typename Prop<A> :: Substitution_*
	Prop<A> :: getSubstitution() {
		return (down_ == NULL) ? substitution_ : down_->getSubstitution();
	}
	template<class A>
	const typename Prop<A> :: Substitution_*
	Prop<A> :: getSubstitution() const {
		return (down_ == NULL) ? substitution_ : down_->getSubstitution();
	}
	template<class A>
	inline index :: Step
	Prop<A> :: getDepth() const {
		return depth_;
	}
	template<class A>
	inline value :: Integer
	Prop<A> :: getCardinality() const {
		return cardinality_;
	}
	template<class A>
	typename Prop<A> :: Proof_*
	Prop<A> :: constructProof (const Substitution_* substitution)
	{
		proof :: Prop<Allocator_>* proof = NULL;
		try {
			Proof_* upProofs [up_.getSize()];
			for (index :: Arity i = 0; i < up_.getSize(); ++ i) {
				Evidence_* upEvidence = up_.getValue (i);
				upProofs [i] = upEvidence->constructProof (substitution);
			}
			proof = new proof :: Prop<Allocator_> (this, substitution, up_.getSize(), upProofs);
		} catch (Exception& exception) {
			Evidence_ :: deleteObject (proof);
			throw exception;
		}
		return proof;
	}
	template<class A>
	bool
	Prop<A> :: givesSameProof (const Evidence_* evidence) const
	{
		const Prop* prop = dynamic_cast<const Prop*>(evidence);
		if (prop == NULL) {
			return false;
		} else {
			if (Evidence_ :: node_->getProposition() != prop->Evidence_ :: node_->getProposition()) {
				return false;
			}
			if (up_.getSize() != prop->up_.getSize()) {
				return false;
			}
			for (index :: Arity i = 0; i < up_.getSize(); ++ i) {
				if (!up_[i]->givesSameProof (prop->up_[i])) {
					return false;
				}
			}
			return true;
		}
	}

	// object :: Cloneable implementation
	template<class A>
	typename Prop<A> :: Evidence_*
	Prop<A> :: clone() const
	{
		if (clone_ != NULL) {
			return clone_;
		}
		Prop* clone = new Prop (*this);
		clone_ = clone;
		clone->node_ = Evidence_ :: node_->clone();
		for (index :: Arity i = 0; i < up_.getSize(); ++ i) {
			const Evidence_*
				evidence = up_.getValue (i);
			clone->up_.getReference (i) = evidence->clone();
		}
		return clone_;
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
		volume += Evidence_ :: getAggregateVolume (substitution_);
		volume += up_.getVolume();
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
		const Mode mode (string);
		if (mode.getValue (Mode :: SHOW_IN_GML_GRAPH)) {
			Evidence_ :: showGraphInGML (string);
		} else if (mode.getValue (Mode :: SHOW_IN_GML)) {
			showNodeInGML (string);
		} else {
			showNodePlain (string);
		}
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class A>
	inline void
	Prop<A> :: verifyUp() const
	{
		for (index :: Arity i = 0; i < up_.getSize(); ++ i) {
			Evidence_* up = up_.getValue (i);
			up_.getValue (i)->verifyIntegrity();
		}
	}
	template<class A>
	void
	Prop<A> :: verifySubstitutions() const {
		getSubstitution()->verifyIntegrity();
	}
	template<class A>
	void
	Prop<A> :: verifyVariables (const Substitution_* substitution) const
	{
		while (substitution != NULL) {
			const Symbol& variable = substitution->getVariable();
			verifyVariable (variable, substitution);
			substitution = substitution->getNext();
		}
	}
	template<class A>
	void
	Prop<A> :: verifyVariable
	(
		const Symbol& variable,
		const Substitution_* substitution
	) const
	{
		if (Evidence_ :: node_->getExpression()->getTerm()->contains(variable)) {
			return;
		}
		for (index :: Arity i = 0; i < up_.getSize(); ++ i) {
			const Evidence_* const
				hyp = up_.getValue (i);
			if (hyp->Evidence_ :: getNode()->getExpression()->getTerm()->contains(variable)) {
				return;
			}
		}
		expression :: Mode mode;
		mode << expression :: Mode :: SHOW_REPLACEABILITY;
		Error* error = new Error (Error :: SEMANTIC);
		error->message() << mode  << "dumb variable in substitution" << endLine;
		error->message() << tab << "substitution = " << *substitution;
		error->message() << tab << "variable = " << variable << endLine;
		error->message() << endLine;
		error->message() << endLine;
		show (error->message());
		std :: cout << error->message() << std :: endl;
		throw error;
	}
	template<class A>
	inline void
	Prop<A> :: showVerification (String& string) const
	{
		Memory :: stack().push();
		expression :: Mode mode;
		//mode << expression :: Mode :: SHOW_REPLACEABILITY;
		string << mode;

		const mdl :: Proposition* const
			proposition = Evidence_ :: node_->getProposition();
		const mdl :: Assertion* const
			assertion = proposition->getAssertion();
		string << "************* VERIFICATION *************" << endLine;
		string << mode << "assertion ";
		assertion->replicateName (string);
		string << endLine;
		string << "=============================================" << endLine;

		const Prop_*
			prop = dynamic_cast<const Prop_*>(Evidence_ :: node_);
		const stack :: Substitution* const
			substitutionInt = stack :: Substitution :: create (prop->substitutionInt_);
		const stack :: Substitution* const
			substitutionExt = stack :: Substitution :: create (prop->substitutionExt_);

		string << "substitution_ = " << *getSubstitution() << endLine;
		string << endLine;
		string << "substitution ext = " << *substitutionExt << endLine;
		string << "substitution int = " << *substitutionInt << endLine;

		stack :: Expression* const
			proposition_1 = new stack :: Expression (Evidence_ :: node_->getExpression());
		proposition_1->execute (getSubstitution());

		stack :: Expression* const
			proposition_2 = new stack :: Expression (proposition->getExpression());
		proposition_2->execute (substitutionExt);
		proposition_2->execute (getSubstitution());

		string << "proposition_1 = " << *proposition_1 << endLine;
		string << "proposition_2 = " << *proposition_2 << endLine;

		string << endLine;
		string << "Evidence_ :: node_ = " << Evidence_ :: node_ << endLine;
		string << "Evidence_ :: node_->getExpression() = " << *(Evidence_ :: node_->getExpression()) << endLine;
		string << "proposition->getExpression() = " << *(proposition->getExpression()) << endLine;
		string << endLine;


		for (index :: Arity i = 0; i < up_.getSize(); ++ i) {
			const mdl :: Hypothesis* const
				hypothesis_1 = assertion->getHypothesis (i);
			stack :: Expression* const
				hyp_1 = new stack :: Expression (hypothesis_1->getExpression());
			hyp_1->execute (substitutionExt);
			hyp_1->execute (getSubstitution());


			stack :: Expression* const
				hyp_2 = new stack :: Expression (up_.getValue (i)->Evidence_ :: getNode()->getExpression());
			hyp_2->execute (getSubstitution());

			string << "hypothesis " << i << endLine;
			string << "--------------------------------------" << endLine;
			string << "hyp_1 = " << *hyp_1 << endLine;
			string << "hyp_2 = " << *hyp_2 << endLine;

			string << endLine;
			string << "hypothesis_1->getExpression() = " << *(hypothesis_1->getExpression()) << endLine;
			string << "up_.getAll (i)->getExpression() = " << *(up_.getValue (i)->getNode()->getExpression()) << endLine;
			string << endLine;
		}
		string << "=============================================" << endLine;
		string << endLine << endLine;
		Memory :: stack().pop();
	}

	template<class A>
	void
	Prop<A> :: showNodeInGML (String& string) const
	{
		if (Evidence_ :: mapped_) {
			return;
		}
		Mode mode (string);
		if (!mode.getValue (Mode :: SHOW_IN_GML_EVIDENCE)) {
			return;
		}
		for (index :: Arity i = 0; i < up_.getSize(); ++ i) {
			up_.getValue (i)->show (string);
		}
		if (mode.getValue (Mode :: SHOW_ONLY_HINT) && (Evidence_ :: node_->getHint() == NULL)) {
			return;
		}
		string << tab << "node [" << endLine;
		string << tab << tab << "id " << Evidence_ :: shrinkTo (reinterpret_cast<Size_t>(this), _digits_) << endLine;
		string << tab << tab;
			string << "label \"";
			if (mode.getValue (Mode :: SHOW_IN_GML_ASSERTION)) {
				Evidence_ :: node_->getProposition()->getAssertion()->replicateName (string); string << ", ";
			}
			//if (!mode.getValue (Mode :: SHOW_ONLY_HINT) && (Evidence_ :: node_->getHint() != NULL)) {
			//	string << "<HINT> ";
			//}
			if (mode.getValue (Mode:: SHOW_IN_GML_ADDRESS)) {
				string << (void*)this << ", ";
			}
			if (mode.getValue (Mode :: SHOW_IN_GML_DEPTH)) {
				string << "d = " << getDepth() << ", ";
			}
			if (mode.getValue (Mode :: SHOW_IN_GML_HEIGHT_MAX)) {
				string << "max h = " << Evidence_ :: getMaxHeight() << ", ";
			}
			if (mode.getValue (Mode :: SHOW_IN_GML_HEIGHT_MIN)) {
				string << "min h = " << Evidence_ :: getMinHeight(); //<< ", ";
			}
			string << "\"" << endLine;

		string << tab << tab << "expression \"" << *(Evidence_ :: node_->getExpression()) << "\"" << endLine;
		string << tab << tab << "depth " << depth_ << endLine;
		string << tab << tab << "assertion \"";
		Evidence_ :: node_->getProposition()->getAssertion()->replicateName (string);
		string << "\"" << endLine;
		string << tab << tab << "type \"prop\"" << endLine;

		string << tab << tab << "graphics [" << endLine;
		//string << tab << tab << tab << "x " << getXGraphCoord() << endLine;
		//string << tab << tab << tab << "y " << getYGraphCoord() << endLine;
		string << tab << tab << tab << "w " << 120 << endLine;
		string << tab << tab << tab << "h " << 30 << endLine;
		string << tab << tab << tab << "type \"ellipse\"" << endLine;
		if (!mode.getValue (Mode :: SHOW_ONLY_HINT) && (Evidence_ :: node_->getHint() != NULL)) {
			string << tab << tab << tab << "fill \"#FF0000\"" << endLine;
		} else {
			string << tab << tab << tab << "fill \"#FFFF00\"" << endLine;
		}
		string << tab << tab << tab << "outline \"#000000\"" << endLine;
		string << tab << tab << "]" << endLine;
		string << tab << "]" << endLine;

		for (index :: Arity i = 0; i < up_.getSize(); ++ i) {
			string << tab << "edge [" << endLine;
			string << tab << tab << "source " << Evidence_ :: shrinkTo (reinterpret_cast<Size_t>(this), _digits_) << endLine;
			string << tab << tab << "target " << Evidence_ :: shrinkTo (reinterpret_cast<Size_t>(up_.getValue (i)), _digits_) << endLine;
			string << tab << "]" << endLine;
		}
		string << tab << "edge [" << endLine;
		string << tab << tab << "source " << Evidence_ :: shrinkTo (reinterpret_cast<Size_t>(this), _digits_) << endLine;
		string << tab << tab << "target " << Evidence_ :: shrinkTo (reinterpret_cast<Size_t>(Evidence_ :: node_), _digits_) << endLine;
		string << tab << tab << "graphics [" << endLine;
		string << tab << tab << tab << "width 1" << endLine;
		string << tab << tab << tab << "style \"dotted\"" << endLine;
		string << tab << tab << tab << "fill \"#000000\"" << endLine;
		string << tab << tab << tab << "targetArrow \"standard\"" << endLine;
		string << tab << tab << "]" << endLine;
		string << tab << "]" << endLine;
		Evidence_ :: mapped_ = true;
	}
	template<class A>
	void
	Prop<A> :: showNodePlain (String& string) const
	{
		string << "PROP ";
		if (Evidence_ :: isHint()) {
			string << "(hint) ";
		}
#ifdef DEBUG_POINTERS
		string << (void*)this << " ";
#endif
		Evidence_ :: node_->getProposition()->getAssertion()->replicateName (string);
#ifdef DEBUG_POINTERS
		string << " node: " << (void*)(Evidence_ :: node_);
#endif
	}
}
}
}

#endif /*MDL_PROVER_EVIDENCE_PROP_CPP_*/
