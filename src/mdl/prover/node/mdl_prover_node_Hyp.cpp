/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_node_Hyp.cpp                                  */
/* Description:     hypothesis node in proof variant tree                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_NODE_HYP_CPP_
#define MDL_PROVER_NODE_HYP_CPP_

#include "mdl/prover/node/mdl_prover_node.hpp"

namespace mdl {
namespace prover {
namespace node {

	/****************************
	 *		Public members
	 ****************************/

using manipulator :: space;
using manipulator :: tab;
using manipulator :: endLine;
using manipulator :: iterate;

	template<class A>
	Hyp<A> :: Hyp
	(
		Tree_* tree,
		Expression_* expression,
		const mdl :: proof :: Node* hint,
		Node_* down,
		index :: Arity index
	) try :
	Node_ (tree),
	index_ (index),
	minHeight_ ((down == NULL) ? 0 : down->getMinHeight() + 1),
	expression_ (expression),
	up_ (INITIAL_UP_CAPACITY),
	down_ (INITIAL_DOWN_CAPACITY),
	clone_ (NULL),
	evidences_ (this),
	hint_ (hint)
	{
		Node_ :: forking_ =
			(down == NULL) ?
			0 :
			down->getForking();
		if (down != NULL) {
			Node_ :: tree_->refresh ("building hyp node");
		}
		if (down != NULL) {
			down_.add (down);
		}
		Node_ :: tree_->up().add (this);
	} catch (Exception& exception) {
		Node_ :: deleteAggregateObject (expression_);
		throw exception;
	}
	template<class A>
	Hyp<A> :: ~ Hyp() {
		Node_ :: deleteAggregateObject (expression_);
	}

	// prover :: Node implementation
	template<class A>
	const mdl :: proof :: Node*
	Hyp<A> :: getHint() const {
		return hint_;
	}
	template<class A>
	void
	Hyp<A> :: markHint (const mdl :: proof :: Node* node)
	{
		hint_ = node;
		if (hint_ == NULL) {
			return;
		}
		const mdl :: proof :: Step*
			stepHint = dynamic_cast<const mdl :: proof :: Step*>(hint_);
		const mdl :: Proposition* hintProposition =
			(stepHint == NULL) ?
			NULL :
			stepHint->getLink()->getProposition();
		for (value :: Integer i = 0; i < up_.getSize(); ++ i) {
			Node_* up = up_.getValue (i);
			if (up->getProposition() == hintProposition) {
				up->markHint (node);
			}
		}
	}
	template<class A>
	value :: Integer
	Hyp<A> :: getUpArity() const {
		return up_.getSize();
	}
	template<class A>
	value :: Integer
	Hyp<A> :: getDownArity() const {
		return down_.getSize();
	}
	template<class A>
	typename Hyp<A> :: Node_*
	Hyp<A> :: getUp (const value :: Integer i) {
		return up_.getValue (i);
	}
	template<class A>
	typename Hyp<A> :: Node_*
	Hyp<A> :: getDown (const value :: Integer i) {
		return down_.getValue (i);
	}
	template<class A>
	const typename Hyp<A> :: Node_*
	Hyp<A> :: getUp (const value :: Integer i) const {
		return up_.getValue (i);
	}
	template<class A>
	const typename Hyp<A> :: Node_*
	Hyp<A> :: getDown (const value :: Integer i) const {
		return down_.getValue (i);
	}

	template<class A>
	void
	Hyp<A> :: growUp()
	{
		unifyPremises();
		if (Config :: growUpMode() != Config :: GROW_UP_DETERMINED) {
			if (growUpRefs()) {
				return;
			}
		}
		growUpProps();
	}
	template<class A>
	bool
	Hyp<A> :: growDown (Evidence_* evidence)
	{
		pthread_mutex_t mutex;
		pthread_mutex_init (&mutex, NULL);
		pthread_mutex_lock (&mutex);
		bool result = addEvidence (evidence);
		if (isRoot()) {
			Node_ :: tree_->root().update();
		}
		pthread_mutex_unlock (&mutex);
		return result;
	}

	template<class A>
	typename Hyp<A> :: Expression_*
	Hyp<A> :: getExpression() {
		return expression_;
	}
	template<class A>
	mdl :: Proposition*
	Hyp<A> :: getProposition() {
		return NULL;
	}
	template<class A>
	const typename Hyp<A> :: Expression_*
	Hyp<A> :: getExpression() const {
		return expression_;
	}
	template<class A>
	const mdl :: Proposition*
	Hyp<A> :: getProposition() const {
		return NULL;
	}
	template<class A>
	typename Hyp<A> :: Evidences_&
	Hyp<A> :: getEvidences() {
		return evidences_;
	}
	template<class A>
	const typename Hyp<A> :: Evidences_&
	Hyp<A> :: getEvidences() const {
		return evidences_;
	}
	template<class A>
	value :: Integer
	Hyp<A> :: getMaxHeight() const
	{
		value :: Integer maxHeight = 1;
		for (value :: Integer i = 0; i < down_.getSize(); ++ i) {
			const Node_* const
				prop = down_.getValue (i);
			if (prop->getMaxHeight() + 1 > maxHeight) {
				maxHeight = prop->getMaxHeight() + 1;
			}
		}
		return maxHeight;
	}
	template<class A>
	value :: Integer
	Hyp<A> :: getMinHeight() const {
		return minHeight_;
	}
	template<class A>
	value :: Real
	Hyp<A> :: getWeight() const
	{
		value :: Real weight = 0;
		for (value :: Integer i = 0; i < down_.getSize(); ++ i) {
			const Node_* const
				prop = down_.getValue (i);
			const value :: Real
				downWeight = prop->getWeight();
			if ((i == 0) || (downWeight > weight)) {
				weight = downWeight;
			}
		}
		return weight;
	}
	template<class A>
	bool
	Hyp<A> :: isProved() const {
		return (evidences_.getSize() > 0);
	}
	template<class A>
	bool
	Hyp<A> :: isRoot() const {
		return (down_.isEmpty());
	}
	template<class A>
	bool
	Hyp<A> :: mayGrowUp() const {
		return true;
	}
	template<class A>
	void
	Hyp<A> :: addDown (Node_* node)
	{
		down_.add (node);
		if (Node_ :: forking_ < node->getForking()) {
			Node_ :: forking_ = node->getForking();
		}
	}
	template<class A>
	bool
	Hyp<A> :: liesDown (const Node_* node) const
	{
		if (node == this) {
			return true;
		}
		for (value :: Integer i = 0; i < down_.getSize(); ++ i) {
			const Node_* const
				prop = down_.getValue (i);
			if (prop->liesDown (node)) {
				return true;
			}
		}
		return false;
	}
	template<class A>
	void
	Hyp<A> :: showBack (String& string) const
	{
		/*for (value :: Integer i = 0; i < down_.getSize(); ++ i) {
			down_.getValue (i)->showBack (string);
			if (i + 1 != down_.getSize()) {
				string << endLine;
			}
		}*/
		if (down_.getSize() > 0) {
			down_.getValue (0)->showBack (string);
		}
		string << " " << *expression_ << " ";
	}
	template<class A>
	void
	Hyp<A> :: showTreeBriefly (String& string) const
	{
		if (up_.isEmpty()) {
			showBack (string);
			string << endLine;
		} else {
			for (value :: Integer i = 0; i < up_.getSize(); ++ i) {
				const Node_* const
					prop = up_.getValue (i);
				prop->showTreeBriefly (string);
			}
		}
	}
	template<class A>
	value :: Integer
	Hyp<A> :: getForking() const
	{
		const value :: Integer upForking = up_.getSize();
		value :: Integer maxDownForking = 0;
		for (value :: Integer i = 0; i < down_.getSize(); ++ i) {
			const Node_* const
				node = down_.getValue (i);
			const value :: Integer
				downForking = node->getForking();
			if(maxDownForking < downForking) {
				maxDownForking = downForking;
			}
		}
		Node_ :: forking_ = upForking + maxDownForking;
		return Node_ :: forking_;
	}
	template<class A>
	void
	Hyp<A> :: showInfo (String& string, const int indent) const
	{
		if (Config :: infoTree (Config :: SHOW_TREE_NODE)) {
			showInfoNode (string, indent);
		} else {
			showInfoTree (string, indent);
		}
	}

	// object :: Cloneable implementation
	template<class A>
	typename Hyp<A> :: Node_*
	Hyp<A> :: clone () const
	{
		if (clone_ != NULL) {
			return clone_;
		}
		Hyp* clone = new Hyp (*this);
		clone_ = clone;
		return clone_;
	}

	// object :: Object implementation
	template<class A>
	void
	Hyp<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Hyp<A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += up_.getVolume();
		volume += down_.getVolume();
		volume += evidences_.getVolume();
		volume += Node_ :: getAggregateVolume (expression_);
		return volume;
	}
	template<class A>
	Size_t
	Hyp<A> :: getSizeOf() const {
		return sizeof (Hyp);
	}
	template<class A>
	void
	Hyp<A> :: show (String& string) const
	{
		const Mode mode (string);
		if (mode.getValue (Mode :: SHOW_IN_GML_GRAPH)) {
			Node_ :: showGraphInGML (string);
		} else if (mode.getValue (Mode :: SHOW_IN_GML)) {
			showNodeInGML (string);
		} else {
			showNodePlain (string);
		}
	}

	/****************************
	 *		Private members
	 ****************************/

	// grow up routines
	template<class A>
	bool
	Hyp<A> :: growUpRefs()
	{
		bool result = true;
		Memory :: stack().push();

		UnifiedRefs_ refs =
			Node_ :: tree_->expressionTree_->template equifyInverse<Expression_>(expression_);

		const typename UnifiedRefs_ :: Node_*
			node = refs.getFirst();
		if (node == NULL) {
			Node_ :: tree_->expressionTree_->addBranch (expression_, this);
			result = false;
		}
		while (node != NULL) {
			growUpRef (node);
			node = node->getNext();
		}
		Memory :: stack().pop();
		return result;
	}
	template<class A>
	void
	Hyp<A> :: growUpProps()
	{
		const forest :: Proposition*
			propositions = Math :: propositions()->getTree();

		const index :: Assertion
			problemIndex = Node_ :: tree_->getProblemIndex();
		const index :: Assertion
			boundary = problemIndex - 1;

		typedef
			typename mdl :: tree :: Proposition :: Data_
			Data_;
		typedef
			typename Propositions_ :: Unit_
			Unit_;
		typedef
			typename forest :: Proposition :: const_Iterator_
			Iterator_;

		Memory :: stack().push();

		/*const mdl :: Proposition* hintProposition = NULL;
		if (hint_ != NULL) {
			const mdl :: proof :: Step*
				stepHint = dynamic_cast<const mdl :: proof :: Step*>(hint_);
			if (stepHint != NULL) {
				if (stepHint->getClass() == mdl :: proof :: Step :: CLAIM) {
					const mdl :: proof ::Claim*
						claimHint = dynamic_cast<const mdl :: proof :: Claim*>(stepHint);
					const mdl :: Proof*
						proof = claimHint->getProof();
					 hintProposition = proof->getQed (0)->getStep()->getLink()->getProposition();
				} else {
					hintProposition = stepHint->getLink()->getProposition();
				}
			} AAA
		}*/

		/*if (hintProposition != NULL) {
			Expression_ expr (hintProposition->getExpression());
			const Substitution_* s = NULL;
			if (!expr.unifySymmetric (expression_, s)) {
				expr.dump();
				expression_->dump();
				std :: cout << std :: endl << std :: endl;
				Counter ::set();
				expr.unifySymmetric (expression_, s);
			}

			forest :: Proposition forest;
			forest.addBranch (hintProposition->getExpression(), hintProposition);
			Propositions_ res =	forest.unifySymmetric<Expression_>(expression_, boundary);
			if (res.isEmpty()) {
				forest.dump();
				expression_->dump();
				std :: cout << std :: endl << std :: endl;
				Counter ::set();
				res = forest.unifySymmetric<Expression_>(expression_, boundary);
			}
		}*/

		//expression_->dump();
		//propositions->dump();

		Propositions_ result =
			propositions->unifySymmetric<Expression_>
			(
				expression_,
				boundary
			);



		/*bool success = true;
		int count = 0;
		const typename Propositions_ :: Node_*
			n = result.getFirst();
		while (n != NULL) {
			const Unit_&
				unit = n->getReference();
			const Iterator_
				iterator = unit.getSource();
			const Data_&
				data = iterator->getData();
			const Data_ :: Node_*
				dataNode = data.getFirst();
			while (dataNode != NULL) {
				mdl :: Proposition*
					proposition = const_cast<mdl :: Proposition*>(dataNode->getValue());
				mdl :: Assertion*
					assertion = proposition->getAssertion();
				bool isAccessible = true;
				for (index :: Arity i = 0; i < assertion->getPropArity(); ++ i) {
					mdl :: Proposition*
						proposition = assertion->getProposition (i);
					isAccessible &= (proposition->getSourceIndex() <= boundary);
				}
				bool isHint = (proposition == hintProposition);
				if (assertion->isVerified() && isAccessible) {
					if (isHint || !Config :: removeNonHint()) {
						++ count;
						if (up_.getSize() > 0 || count > 1) {
							success = false;
						}
					}
				}
				dataNode = dataNode->getNext();
			}
			n = n->getNext();
		}
		if ((!success || count == 0) && (hintProposition != NULL)) {
			propositions->dump();
			expression_->dump();
			hintProposition->getExpression()->dump();
			std :: cout << std :: endl << std :: endl;
			std :: cout << (void*)hintProposition << std :: endl;
			std :: cout << std :: endl << std :: endl;

			Expression_ expr (hintProposition->getExpression());
			const Substitution_* s = NULL;
			expr.unifySymmetric (expression_, s);
			s->dump();
			std :: cout << std :: endl << std :: endl;


			Counter ::set();
			result =
			propositions->unifySymmetric<Expression_>
			(
				expression_,
				boundary
			);

			std :: cout << "RESULT SIZE = " << result.getSize() << std :: endl;
			int ind = 0;
			n = result.getFirst();
			while (n != NULL) {
				const Unit_&
					unit = n->getReference();
				const Iterator_
					iterator = unit.getSource();
				const Data_&
					data = iterator->getData();
				const Data_ :: Node_*
					dataNode = data.getFirst();
				while (dataNode != NULL) {
					mdl :: Proposition*
						proposition = const_cast<mdl :: Proposition*>(dataNode->getValue());
					mdl :: Assertion*
						assertion = proposition->getAssertion();
					bool isAccessible = true;
					for (index :: Arity i = 0; i < assertion->getPropArity(); ++ i) {
						mdl :: Proposition*
							proposition = assertion->getProposition (i);
						isAccessible &= (proposition->getSourceIndex() <= boundary);
					}
					bool isHint = (proposition == hintProposition);
					if (assertion->isVerified() && isAccessible) {
						if (isHint || !Config :: removeNonHint()) {
							std :: cout << "<<<< Result " << ind << " >>>>" << std :: endl;
							std :: cout << "hint prop: " << (void*)proposition << std :: endl;
							std :: cout << "UNIT: " << std :: endl;
							unit.dump();
						}
					}
					dataNode = dataNode->getNext();
				}
				n = n->getNext();
				++ ind;
			}
		}*/

		value :: Integer count; //< total number of possible up nodes

		if (Config :: growUpMode() == Config :: GROW_UP_DETERMINED) {
			const typename Propositions_ :: Node_*
				node = result.getFirst();
			while (node != NULL) {
				growUpProp (node, boundary, true, count);
				node = node->getNext();
			}
		}
		if (Config :: growUpLimit() == value :: undefined :: INTEGER ||
			Config :: growUpLimit() > 1) {
			const typename Propositions_ :: Node_*
				node = result.getFirst();
			while (node != NULL) {
				growUpProp (node, boundary, false, count);
				node = node->getNext();
			}
		}

		if (Config :: growUpMode() == Config :: GROW_UP_DETERMINED &&
			Config :: growUpLimit() == 1) {
			if (up_.getSize() != 1) {
				std :: cout << "something wrong (growing up prop)...: " << up_.getSize() << std :: endl;
				//String str;
				//this->show (str);
				//std :: cout << str << std :: endl;
				this->dumpTree (false, false);
				hint_->dump();
				std :: cout << "something wrong..." << std :: endl;
			}
		}
		Memory :: stack().pop();
	}
	template<class A>
	void
	Hyp<A> :: growUpProp
	(
		const typename Propositions_ :: Node_* node,
		const index :: Assertion boundary,
		const bool onlyHint,
		value :: Integer& count
	)
	{
		const mdl :: proof :: Step*
			stepHint = dynamic_cast<const mdl :: proof :: Step*>(hint_);
		const mdl :: Proposition* hintProposition = NULL;
		if (stepHint != NULL) {
			if (stepHint->getClass() == mdl :: proof :: Step :: CLAIM) {
				const mdl :: proof ::Claim*
					claimHint = dynamic_cast<const mdl :: proof :: Claim*>(stepHint);
				const mdl :: Proof*
					proof = claimHint->getProof();
				 hintProposition = proof->getQed (0)->getStep()->getLink()->getProposition();
			} else {
				hintProposition = stepHint->getLink()->getProposition();
			}
		}
		typedef
			typename mdl :: tree :: Proposition :: Data_
			Data_;
		typedef
			typename Propositions_ :: Unit_
			Unit_;
		typedef
			typename forest :: Proposition :: const_Iterator_
			Iterator_;

		Memory :: stack().push();

		const stack :: Substitution*
			internal = node->getReference().template getTargetSubstitution<allocator :: Stack>();
		const stack :: Substitution*
			external = node->getReference().template getSourceSubstitution<allocator :: Stack>();

		const Unit_&
			unit = node->getReference();
		const Iterator_
			iterator = unit.getSource();
		const Data_&
			data = iterator->getData(); //node->getReference().getSource()->getData();
		const Data_ :: Node_*
			dataNode = data.getFirst();
		while (dataNode != NULL) {
			mdl :: Proposition*
				proposition = const_cast<mdl :: Proposition*>(dataNode->getValue());
			mdl :: Assertion*
				assertion = proposition->getAssertion();
			bool isAccessible = true;
			for (index :: Arity i = 0; i < assertion->getPropArity(); ++ i) {
				mdl :: Proposition*
					proposition = assertion->getProposition (i);
				isAccessible &= (proposition->getSourceIndex() <= boundary);
			}
			if (assertion->isVerified() && isAccessible) {

				Substitution_* substitutionInt = NULL;
				Substitution_* substitutionExt = NULL;

				buildSubstitutions
				(
					assertion,
					proposition,
					internal,
					external,
					substitutionInt,
					substitutionExt
				);
				if (onlyHint) {
					++ count;
				}
				const bool isHint = (proposition == hintProposition);
				const bool addNode =
					(!onlyHint || (up_.getSize() == 0 && isHint)) &&
					( onlyHint || (up_.getSize() < Config :: growUpLimit() && !isHint));
				if (addNode) {
					Prop_* prop = NULL;
					try {
						prop = new Prop_
						(
							Node_:: tree_,
							proposition,
							substitutionInt,
							substitutionExt,
							this,
							(isHint ? stepHint : NULL)
						);
					} catch (Exception& exception) {
						Memory :: stack().pop();
						throw exception;
					}
					up_.add (prop);
				} else {
					substitutionInt->commitSuicide();
					substitutionExt->commitSuicide();
				}
			}
			dataNode = dataNode->getNext();
		}
		Memory :: stack().pop();
	}

using manipulator :: mode;

	template<class A>
	inline void
	Hyp<A> :: growUpRef (const typename UnifiedRefs_ :: Node_* node)
	{
		Node_* up = const_cast<Node_*>(node->getValue().getSource()->getData().getValue());
		if (liesDown (up)) {
			return;
		}
		Substitution_* replacement = Substitution_ :: create
			(node->getReference().getTarget().getSubstitution());
		Ref_* ref = new Ref_ (Node_ :: tree_, replacement, this, up, hint_);
		for (value :: Integer i = 0; i < up->getEvidences().getSize(); ++ i) {
			Evidence_* upEvidence = up->getEvidences().getValue (i);
			ref->growDown (upEvidence);
		}
		up_.add (ref);
	}

	template<class A>
	inline void
	Hyp<A> :: buildSubstitutions
	(
		const mdl :: Assertion* const assertion,
		const mdl :: Proposition* const proposition,
		const stack :: Substitution* inter,
		const stack :: Substitution* exter,
		Substitution_*& substitutionInt,
		Substitution_*& substitutionExt
	)
	{
		Memory :: stack().push();
		stack :: Substitution*
			internal = stack :: Substitution :: create (inter);

		stack :: Substitution*
			external = stack :: Substitution :: create (exter);
		const stack :: Substitution*
			replacement = buildVariableReplacement (assertion, external);

		external = external->compose (replacement);
		internal = internal->compose (replacement, false);

		substitutionInt = Substitution_ :: create (internal);
		substitutionExt = Substitution_ :: create (external);
		Memory :: stack().pop();

		#ifdef DEBUG
		verifySubstitutionInt (substitutionInt);
		verifySubstitutionExt (proposition, substitutionExt);
		#endif
	}
	template<class A>
	inline const stack :: Substitution*
	Hyp<A> :: buildVariableReplacement
	(
		const mdl :: Assertion* const assertion,
		const stack :: Substitution* external
	)
	{
		const stack :: Substitution* replacement = NULL;
		const mdl :: Variables*
			variables = assertion->getVariables();
		for (index :: Arity i = 0; i < variables->getSize(); ++ i) {
			const mdl :: header :: Variable* const
				variable = variables->getVariable (i);
			const Symbol& oldSymbol = variable->getSymbol();
			if (external->find (oldSymbol) == NULL) {
				const Symbol
					newSymbol = Node_ :: tree_->createVariable (oldSymbol);
				const stack :: Expression :: Term_* const
					term = stack :: Expression :: createSingleton (newSymbol);
				replacement = new stack :: Substitution (oldSymbol, term, replacement);
			}
		}
		return replacement;
	}

	// grow down routines
	template<class A>
	void
	Hyp<A> :: unifyPremises()
	{
		const PremiseTree_*
			premiseTree = Node_ :: tree_->getPremiseTree();
		Memory :: stack().push();
		UnifiedPremises_
			result = premiseTree->template unifyInverse<Expression_>(expression_);

		value :: Integer count = 0;

		if (Config :: growUpMode() == Config :: GROW_UP_DETERMINED) {
			const typename UnifiedPremises_ :: Node_*
				node = result.getFirst();
			while (node != NULL) {
				addTop (node, true, count);
				node = node->getNext();
			}
		}
		if (Config :: growUpLimit() > 1) {
			const typename UnifiedPremises_ :: Node_*
				node = result.getFirst();
			while (node != NULL) {
				addTop (node, false, count);
				node = node->getNext();
			}
		}

		if (Config :: growUpMode() == Config :: GROW_UP_DETERMINED &&
			Config :: growUpLimit() == 1) {
			if (up_.getSize() > 1) {
				std :: cout << "something wrong (growing up premises)...: " << up_.getSize() << std :: endl;
				String str;
				this->show (str);
				std :: cout << str << std :: endl;
				std :: cout << "something wrong..." << std :: endl;
			}
		}
		Memory :: stack().pop();
	}
	template<class A>
	bool
	Hyp<A> :: addEvidence (Evidence_* upEvidence)
	{
		typedef
			typename evidence :: Hyp<Allocator_>
			Hyp_;
		const Substitution_* const
			upSubstitution = upEvidence->getSubstitution();

		Hyp_* evidenceHyp = new Hyp_ (this, upEvidence);

		Memory :: stack().push(); {
			stack :: Substitution*
				sub = stack :: Substitution :: create (upSubstitution);
			typename Expression_ :: const_Iterator_
				end = const_cast<const Expression_*>(expression_)->getTerm()->getEnd();
			sub = sub->restrictTo (end);
			evidences_.add (sub, evidenceHyp);
		}
		Memory :: stack().pop();

		evidences_.checkForDuplicateProofs();
		return true;
	}
	template<class A>
	void
	Hyp<A> :: addTop
	(
		const typename UnifiedPremises_ :: Node_* node,
		const bool onlyHint,
		value :: Integer& count
	)
	{
		typedef
			typename PremiseTree_ :: Data_
			Data_;
		const Data_&
			data = node->getReference().getSource()->getData();

		const typename Data_ :: Node_*
			dataNode = data.getFirst();
		while (dataNode != NULL) {
			Premise_* premise = dataNode->getValue();
			const typename PremiseTree_ :: Substitution_*
				premiseSubstitution = node->getReference().getTarget().getSubstitution();

			if (onlyHint) {
				++ count;
			}
			const bool isHint = (premise == hint_);
			const bool addNode =
				(!onlyHint || (up_.getSize() == 0 && isHint)) &&
				( onlyHint ||
					(
						(up_.getSize() < Config :: growUpLimit()) &&
						(Config :: growUpMode() != Config :: GROW_UP_DETERMINED) &&
						!isHint
					)
				);
			if (addNode) {
				Substitution_*
					substitution = Substitution_ :: create (premiseSubstitution);

				Top_* top = new Top_
				(
					Node_ :: tree_,
					this,
					premise,
					substitution,
					isHint ? hint_ : NULL
				);
				up_.add (top);
				top->growDown (NULL);
			}
			dataNode = dataNode->getNext();
		}
	}

	// verification routines
	template<class A>
	void
	Hyp<A> :: verifySubstitutionInt (const Substitution_* substitutionInt) const
	{
		substitutionInt->verifyIntegrity();
		while (substitutionInt != NULL) {
			const Symbol& variable = substitutionInt->getVariable();
			if (!getExpression()->getTerm()->contains(variable)) {
				expression :: Mode mode;
				mode << expression :: Mode :: SHOW_REPLACEABILITY;
				Error* error = new Error (Error :: SEMANTIC);
				error->message() << mode  << "dumb variable in substitutionInt:" << endLine;
				error->message() << tab << "substitutionInt = " << *substitutionInt;
				error->message() << tab << "variable = " << variable << endLine;
				error->message() << endLine;
				error->message() << endLine;
				show (error->message());
				std :: cout << error->message() << std :: endl;
				throw error;
			}
			substitutionInt = substitutionInt->getNext();
		}
	}
	template<class A>
	void
	Hyp<A> :: verifySubstitutionExt
	(
		const mdl :: Proposition* const proposition,
		const Substitution_* substitutionExt
	) const
	{
		substitutionExt->verifyIntegrity();
		while (substitutionExt != NULL) {
			const Symbol& variable = substitutionExt->getVariable();
			verifySubstitutionExt (variable, proposition, substitutionExt);
			substitutionExt = substitutionExt->getNext();
		}
	}
	template<class A>
	void
	Hyp<A> :: verifySubstitutionExt
	(
		const Symbol& variable,
		const mdl :: Proposition* const proposition,
		const Substitution_* substitutionExt
	) const
	{
		if (proposition->getExpression()->getTerm()->contains(variable)) {
			return;
		}
		const mdl :: Assertion* const
			assertion = proposition->getAssertion();
		for (index :: Arity i = 0; i < assertion->getHypArity(); ++ i) {
			const mdl :: Hypothesis* const
				hyp = assertion->getHypothesis (i);
			if (hyp->getExpression()->getTerm()->contains(variable)) {
				return;
			}
		}
		expression :: Mode mode;
		mode << expression :: Mode :: SHOW_REPLACEABILITY;
		Error* error = new Error (Error :: SEMANTIC);
		error->message() << mode  << "dumb variable in substitutionExt" << endLine;
		error->message() << tab << "substitutionExt = " << *substitutionExt;
		error->message() << tab << "variable = " << variable << endLine;
		error->message() << tab << "assertion = " << endLine;
		assertion->show (error->message());
		error->message() << endLine;
		error->message() << endLine;
		show (error->message());
		std :: cout << error->message() << std :: endl;
		throw error;
	}

	template<class A>
	void
	Hyp<A> :: showNodeInGML (String& string) const
	{
		if (Node_ :: mapped_) {
			return;
		}
		Mode mode (string);
		if (!mode.getValue (Mode :: SHOW_IN_GML_NODE)) {
			return;
		}
		if (mode.getValue (Mode :: SHOW_ONLY_HINT) && (hint_ == NULL)) {
			return;
		}
		for (value :: Integer i = 0; i < up_.getSize(); ++ i) {
			string << *up_.getValue (i);
		}
		string << tab << "node [" << endLine;
		string << tab << tab << "id " << Node_ :: shrinkTo (reinterpret_cast<Size_t>(this), _digits_) << endLine;
		string << tab << tab;
			string << "label \"";
			if (mode.getValue (Mode :: SHOW_IN_GML_EXPRESSION)) {
				string << *expression_ << ", " << endLine;
			}
			if (mode.getValue (Mode :: SHOW_IN_GML_WEIGHT)) {
				string << tab << tab << tab << "w = " << getWeight() << ", ";
			}
			if (mode.getValue (Mode :: SHOW_IN_GML_HEIGHT_MIN)) {
				string << tab << tab << tab << "min h = " << getMinHeight() << ", ";
			}
			if (mode.getValue (Mode :: SHOW_IN_GML_HEIGHT_MAX)) {
				string << tab << tab << tab << "max h = " << getMaxHeight(); // << ", ";
			}
			string << "\"" << endLine;

		string << tab << tab << "type \"hyp\"" << endLine;
		if (hint_ != NULL) {
			string << tab << tab << "hint 1" << endLine;
		} else {
			string << tab << tab << "hint 0" << endLine;
		}
		string << tab << tab << "graphics [" << endLine;
		string << tab << tab << tab << "x " << Node_ :: getXGraphCoord() << endLine;
		string << tab << tab << tab << "y " << Node_ :: getYGraphCoord() << endLine;
		string << tab << tab << tab << "w " << :: fmax (120, 20 * expression_->getLength()) << endLine;
		//string << tab << tab << tab << "h " << 30 << endLine;
		string << tab << tab << tab << "type \"rectangle\"" << endLine;
		if (!mode.getValue (Mode :: SHOW_ONLY_HINT) && (hint_ != NULL)) {
			string << tab << tab << tab << "fill \"#FF0000\"" << endLine;
		} else {
			string << tab << tab << tab << "fill \"#FFCC00\"" << endLine;
		}
		string << tab << tab << tab << "outline \"#000000\"" << endLine;
		string << tab << tab << "]" << endLine;
		string << tab << "]" << endLine;

		for (index :: Arity i = 0; i < up_.getSize(); ++ i) {
			string << tab << "edge [" << endLine;
			string << tab << tab << "source " << Node_ :: shrinkTo (reinterpret_cast<Size_t>(this), _digits_) << endLine;
			string << tab << tab << "target " << Node_ :: shrinkTo (reinterpret_cast<Size_t>(up_.getValue (i)), _digits_) << endLine;
			string << tab << "]" << endLine;
		}
		Node_ :: mapped_ = true;
		if (mode.getValue (Mode :: SHOW_IN_GML_EVIDENCE)) {
			for (value :: Integer i = 0; i < evidences_.getSize(); ++ i) {
				const Evidence_* evidence = evidences_.getValue (i);
				evidence->show (string);
			}
		}
	}
	template<class A>
	void
	Hyp<A> :: showNodePlain (String& string) const
	{
		if (isRoot()) {
			string << "root ";
		} else {
			string << "hyp ";
		}
		if (hint_ != NULL) {
			string << " (hint) ";
		}
#ifdef DEBUG_POINTERS
		string << (void*)this << " ";
#endif
		string << " : " << *expression_;
	}

	template<class A>
	void
	Hyp<A> :: showInfoHeader (String& string, const int indent) const
	{
		const char* header = isRoot() ? "root" : "hyp";
		string << iterate << indent << tab;
		switch (Config :: showMode()) {
		case Config :: SHOW_MODE_HUMAN :
			string <<  header << ":" << endLine; break;
		case Config :: SHOW_MODE_XML :
			string <<  "<" << header << " "; break;
		case Config :: SHOW_MODE_GML :
			// TODO: implement
			break;
		default : break;
		}
		string << "index=\"" << Node_ :: getGlobalIndex() <<"\" ";
		string << "types=\"";
		expression_->showTypes (string);
		string << "\" ";
		string << "hint=\"" << ((hint_ == NULL) ? "-" : "+")  <<"\" ";
		string << ">" << endLine;
	}
	template<class A>
	void
	Hyp<A> :: showInfoTree (String& string, const int indent) const
	{
		showInfoHeader (string, indent);
		showInfoExpression (string, indent + 1);
		for (index :: Arity i = 0; i < getDownArity(); ++ i) {
			const Node_* node = getDown(i);
			string << iterate << (indent + 1) << tab;
			string << "<down index=\"" << node->getGlobalIndex() << "\"/>" << endLine;
		}
		for (index :: Arity i = 0; i < getUpArity(); ++ i) {
			const Node_* node = getUp(i);
			string << iterate << (indent + 1) << tab;
			string << "<up index=\"" << node->getGlobalIndex() << "\"/>" << endLine;
		}
		Tree_ :: writeEnding (string, isRoot() ? "root" : "hyp", indent);
	}
	template<class A>
	void
	Hyp<A> :: showInfoNode (String& string, const int indent) const
	{
		showInfoHeader (string, indent);
		showInfoExpression (string, indent + 1);
		evidences_.showInfo (string, indent + 1);
		Tree_ :: writeEnding (string, isRoot() ? "root" : "hyp", indent);
	}
	template<class A>
	void
	Hyp<A> :: showInfoExpression (String& string, const int indent) const
	{
		string << iterate << indent << tab;
		string << "<expression>";
		string << "<![CDATA[";
		string << *expression_;
		string << "]]>";
		string <<"</expression>" << endLine;
	}
}
}
}

#endif /*MDL_PROVER_NODE_HYP_CPP_*/
