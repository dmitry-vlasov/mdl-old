/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_node_Prop.cpp                                 */
/* Description:     proposition node in proof variant tree                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace prover {
namespace node {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	Prop<A> :: Prop
	(
		Tree_* tree,
		mdl :: Proposition* proposition,
		Substitution_* substitutionInt,
		Substitution_* substitutionExt,
		Node_* down,
		const mdl :: proof :: Step* hint
	) try :
	Node_ (tree),
	minHeight_ (down->getMinHeight() + 1),
	proposition_ (proposition),
	arity_ (proposition->getAssertion()->getHypArity()),
	substitutionInt_ (substitutionInt),
	substitutionExt_ (substitutionExt),
	expression_ (new Expression_ (down->getExpression())),
	up_ (arity_),
	down_ (down),
	clone_ (NULL),
	rate_ (NULL),
	evidences_ (this),
	hint_ (hint)
	#ifdef DEBUG_PROVER_MATRIX_UNIFICATION
	, evidencesOther_ (this)
	#endif
	{
		Node_ :: forking_ = arity_ + down->getForking();
		Node_ :: tree_->refresh ("building prop node");
		expression_->execute (substitutionInt_);
		#ifdef DEBUG_PROVER_UP
		verifySubstitutions();
		#endif
		const value :: Name
			evalName = Config :: experience();
		const evaluation :: Function*
			evalFunction = proposition_->getEvaluation (evalName);
		rate_ = new Rate_ (this, evalFunction->getTerm());
		if ((arity_ == 0) && (Node_ :: tree_->canGrowDown())) {
			addEvidence();
		}
		Node_ :: tree_->up().add (this);
	} catch (Exception& exception) {
		Node_ :: deleteAggregateObject (substitutionInt_);
		Node_ :: deleteAggregateObject (substitutionExt_);
		Node_ :: deleteAggregateObject (expression_);
		Node_ :: deleteAggregateObject (rate_);
		throw exception;
	}
	template<class A>
	Prop<A> :: ~ Prop()
	{
		Node_ :: deleteAggregateObject (substitutionInt_);
		Node_ :: deleteAggregateObject (substitutionExt_);
		Node_ :: deleteAggregateObject (expression_);
		Node_ :: deleteAggregateObject (rate_);
	}

	// prover :: Node implementation
	template<class A>
	const mdl :: proof :: Node*
	Prop<A> :: getHint() const {
		return hint_;
	}
	template<class A>
	void
	Prop<A> :: markHint (const mdl :: proof :: Node* node)
	{
		hint_ = dynamic_cast<const mdl :: proof :: Step*>(node);
		if (hint_ == NULL) {
			return;
		}
		for (value :: Integer i = 0; i < up_.getSize(); ++ i) {
			const mdl :: proof :: Node* hintNode =
				hint_->getLink()->getReferences()->get (i)->getNode();
			Node_* up = up_.getValue (i);
			up->markHint (hintNode);
		}
	}
	template<class A>
	value :: Integer
	Prop<A> :: getUpArity() const {
		return up_.getSize();
	}
	template<class A>
	value :: Integer
	Prop<A> :: getDownArity() const {
		return 1;
	}
	template<class A>
	typename Prop<A> :: Node_*
	Prop<A> :: getUp (const value :: Integer i) {
		return up_.getValue (i);
	}
	template<class A>
	typename Prop<A> :: Node_*
	Prop<A> :: getDown (const value :: Integer i) {
		return (i == 0) ? down_ : NULL;
	}
	template<class A>
	const typename Prop<A> :: Node_*
	Prop<A> :: getUp (const value :: Integer i) const {
		return up_.getValue (i);
	}
	template<class A>
	const typename Prop<A> :: Node_*
	Prop<A> :: getDown (const value :: Integer i) const {
		return (i == 0) ? down_ : NULL;
	}

	template<class A>
	void
	Prop<A> :: growUp ()
	{
		const mdl :: Assertion*
			assertion = proposition_->getAssertion();
		Hyp_* hypotheses [arity_];
		for (index :: Arity i = 0; i < arity_; ++ i) {
			const mdl :: Hypothesis* const
				hypothesis = assertion->getHypothesis (i);

			Memory :: stack().push();
			stack :: Expression* const
				exp = new stack :: Expression (hypothesis->getExpression());
			exp->execute (substitutionExt_);
			exp->execute (substitutionInt_);
			Expression_*
				expression = new Expression_ (exp);
			Memory :: stack().pop();

			const mdl :: proof :: Node* hintNode = NULL;
			if (hint_ != NULL) {
				if (hint_->getClass() == mdl :: proof :: Step :: CLAIM) {
					const mdl :: proof ::Claim*
						claimHint = dynamic_cast<const mdl :: proof :: Claim*>(hint_);
					const mdl :: Proof*
						proof = claimHint->getProof();
					 hintNode = proof->getQed (0)->getStep()->getLink()->getReferences()->get (i)->getNode();
				} else {
					hintNode = hint_->getLink()->getReferences()->get (i)->getNode();
				}
			}
			Hyp_* hyp = new Hyp_ (Node_ :: tree_, expression, hintNode, this, i);
			hypotheses [i] = hyp;
			up_.add (hyp);
		}
		#ifdef DEBUG_PROVER_UP
		verifySubstitutions();
		#endif
	}
	template<class A>
	bool
	Prop<A> :: growDown (Evidence_*)
	{
		if (arity_ == 0) {
			return false;
		}
		pthread_mutex_t mutex;
		pthread_mutex_init (&mutex, NULL);
		pthread_mutex_lock (&mutex);
		if (!checkUp()) {
			return false;
		}
		unifyDown();
		pthread_mutex_unlock (&mutex);
		return true;
	}

	template<class A>
	typename Prop<A> :: Expression_*
	Prop<A> :: getExpression() {
		return expression_;
	}
	template<class A>
	mdl :: Proposition*
	Prop<A> :: getProposition() {
		return proposition_;
	}
	template<class A>
	const typename Prop<A> :: Expression_*
	Prop<A> :: getExpression() const {
		return expression_;
	}
	template<class A>
	const mdl :: Proposition*
	Prop<A> :: getProposition() const {
		return proposition_;
	}
	template<class A>
	typename Prop<A> :: Evidences_&
	Prop<A> :: getEvidences() {
		return evidences_;
	}
	template<class A>
	const typename Prop<A> :: Evidences_&
	Prop<A> :: getEvidences() const {
		return evidences_;
	}
	template<class A>
	value :: Integer
	Prop<A> :: getMaxHeight() const {
		return down_->getMaxHeight() + 1;
	}
	template<class A>
	value :: Integer
	Prop<A> :: getMinHeight() const {
		return minHeight_;
	}
	template<class A>
	value :: Real
	Prop<A> :: getWeight() const {
		return rate_->eval();
	}
	template<class A>
	inline bool
	Prop<A> :: isProved() const {
		return (evidences_.getSize() > 0);
	}
	template<class A>
	bool
	Prop<A> :: isRoot() const {
		return false;
	}
	template<class A>
	bool
	Prop<A> :: mayGrowUp() const {
		return (arity_ > 0);
	}
	template<class A>
	void
	Prop<A> :: addDown (Node_*) {
	}
	template<class A>
	bool
	Prop<A> :: liesDown (const Node_* node) const
	{
		if (node == this) {
			return true;
		}
		return down_->liesDown (node);
	}

using manipulator :: space;
using manipulator :: tab;
using manipulator :: endLine;
using manipulator :: iterate;

	template<class A>
	void
	Prop<A> :: showBack (String& string) const
	{
		down_->showBack (string);
		//string << "prop: ";
		if (hint_ != NULL) {
			string << "(+) ";
		}
		proposition_->getAssertion()->replicateName(string);
		if (proposition_->getAssertion()->getPropArity() > 1) {
			string << ":" << proposition_->getIndex();
		}
		string << " (w=";
		string << getWeight();
		string << ") ";
	}
	template<class A>
	void
	Prop<A> :: showTreeBriefly (String& string) const
	{
		bool isTop = true;
		for (index :: Arity i = 0; i < up_.getSize(); ++ i) {
			const Node_* const
				hyp = up_.getValue (i);
			if (hyp != NULL) {
				hyp->showTreeBriefly (string);
				isTop = false;
			}
		}
		if (isTop) {
			showBack (string);
			string << endLine;
		}
	}
	template<class A>
	value :: Integer
	Prop<A> :: getForking() const
	{
		value :: Integer forking = up_.getSize();
		forking += down_->getForking();
		return forking;
	}
	template<class A>
	void
	Prop<A> :: showInfo (String& string, const int indent) const
	{
		if (Config :: infoTree (Config :: SHOW_TREE_NODE)) {
			showInfoNode (string, indent);
		} else {
			showInfoTree (string, indent);
		}
	}

	// object :: Cloneable implementation
	template<class A>
	typename Prop<A> :: Node_*
	Prop<A> :: clone () const
	{
		if (clone_ != NULL) {
			return clone_;
		}
		Prop* clone = new Prop (*this);
		clone_ = clone;
		return clone_;
	}

	// object :: Object implementation
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
		volume += up_.getVolume();
		volume += evidences_.getVolume();
		volume += Node_ :: getAggregateVolume (substitutionInt_);
		volume += Node_ :: getAggregateVolume (substitutionExt_);
		volume += Node_ :: getAggregateVolume (expression_);
		volume += Node_ :: getAggregateVolume (rate_);
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

	// grow down routines
	template<class A>
	bool
	Prop<A> :: checkUp() const
	{
		for (index :: Arity i = 0; i < up_.getSize(); ++ i) {
			if (!up_.getValue (i)->isProved()) {
				return false;
			}
		}
		return true;
	}
	template<class A>
	value :: Integer
	Prop<A> :: getDownVolume() const
	{
		value :: Integer volume = 1;
		Memory :: stack().push();
		Matrix_ matrix (arity_);
		fillMatrix (matrix);
		for (value :: Integer i = 0; i < arity_; ++ i) {
			const Evidences_* evidences = matrix.getValue (i);
			volume *= evidences->getSize();
		}
		Memory :: stack().pop();
		return volume;
	}
	template<class A>
	void
	Prop<A> :: unifyDown()
	{
		bool largeSearch = false;
		const value :: Integer
			volume = getDownVolume();
		for (index :: Arity i = 0 ; i < arity_; ++ i) {
			Node_* up = up_.getValue (i);
			Evidences_& evidences = up->getEvidences();
			for (value :: Integer i = 0; i < evidences.getSize(); ++ i) {
				Evidence_* e = evidences.getValue (i);
				Node_ :: tree_->down().crown()->remove (e);
			}
		}
		Timer treeTimer;
		treeTimer.start();
#ifdef DEBUG_USE_PROD_MATRIX_UNIFICATION
		unifyMatrix (evidences_, false);
#else
		unifyMatrix (evidences_, true);
#endif
		treeTimer.stop();
		Node_ :: tree_->refresh ("matrix unification");
		#ifdef DEBUG_PROVER_MATRIX_UNIFICATION
		Timer prodTimer;
		prodTimer.start();
		unifyMatrix (evidencesOther_, false);
		prodTimer.stop();
		largeSearch = false;
			//(treeTimer.getSeconds() >= 0.1) ||
			//(prodTimer.getSeconds() >= 0.1);

		if (largeSearch) {
			std :: cout << std :: endl;
			std :: cout << "tree matrix unification: " << treeTimer << std :: endl;
			std :: cout << "prod matrix unification: " << prodTimer << std :: endl;
		}
		if (!evidences_.isEqual (&evidencesOther_)) {
			Counter :: show();
			Error* error = new Error (Error :: SEMANTIC);
			error->message() << "incorrect tree matrix unification." << endLine;
			error->message() << "----------------------------------" << endLine;
			error->message() << *this << endLine;
			error->message() << "hypotheses proof substitutions:" << endLine;
			showHypEvidences (error->message());
			error->message() << endLine;
			error->message() << "product matrix unification result:" << endLine;
			evidencesOther_.showSubstitutions (error->message(), true);
			error->message() << endLine;
			error->message() << "tree matrix unification result:" << endLine;
			evidences_.showSubstitutions (error->message(), true);
			error->message() << endLine;
			evidencesOther_.showDifference (error->message(), &evidences_);
			std :: cout << error->message() << std :: endl;
			evidences_.isEqual (&evidencesOther_);
			Counter :: set (0, 1);
			Counter :: set ();
			//evidencesOther_.clear();
			//evidences_.clear();
			unifyMatrix (evidences_, true);
			unifyMatrix (evidencesOther_, false);
			//throw error;
			delete error;
		}
		#endif
	}
	template<class A>
	void
	Prop<A> :: unifyMatrix
	(
		Evidences_& evidences,
		const bool treeMode
	)
	{
		if (!treeMode) {
			Node_ :: tree_->down().block();
		}
		Memory :: stack().push();
		Matrix_ matrix (arity_);
		fillMatrix (matrix);
		if (treeMode) {
			stack :: Substitution*
				intSub = stack :: Substitution :: create (substitutionInt_);
			substitution :: tree :: template Unify<Types_> unify
			(
				arity_,
				evidences,
				intSub
			);
			unify (matrix);
		} else {
			substitution :: prod :: template Unify<Types_> unify
			(
				arity_,
				substitutionInt_,
				evidences
			);
			unify (matrix);
		}
		Memory :: stack().pop();
		if (!treeMode) {
			Node_ :: tree_->down().unblock();
		}
	}
	template<class A>
	void
	Prop<A> :: fillMatrix (Matrix_& matrix) const
	{
		for (index :: Arity i = 0; i < arity_; ++ i) {
			Node_* hyp = up_.getValue (i);
			const Evidences_&
				evidences = hyp->getEvidences();
			matrix.add (&evidences);
		}
	}
	template<class A>
	void
	Prop<A> :: addEvidence()
	{
		typedef
			typename evidence :: Prop<Allocator_>
			Prop_;

		Evidence_* evidenceProp = new Prop_ (this, 0, NULL);
		Memory :: stack().push();
		stack :: Substitution*
			subInt = stack :: Substitution :: create (substitutionInt_);
		evidences_.add
		(
			subInt,
			evidenceProp
		);
		Memory :: stack().pop();
	}

	template<class A>
	void
	Prop<A> :: showHypEvidences (String& string) const
	{
		typedef
			evidence :: Vector<Allocator_, false>
			HypEvidences;
		for (index :: Arity i = 0; i < up_.getSize(); ++ i) {
			const Node_* const
				hyp = up_.getValue (i);
			const Evidences_&
				evidences = hyp->getEvidences();
			string << "hyp " << i << " :" << endLine;
			dynamic_cast<const HypEvidences&>(evidences).showSubstitutions (string);
			string << endLine;
		}
	}
	template<class A>
	void
	Prop<A> :: verifySubstitutions() const
	{
		substitutionInt_->verifyIntegrity();
		substitutionExt_->verifyIntegrity();
		//verifyVariables (substitutionInt_);
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
		if (getExpression()->getTerm()->contains(variable)) {
			return;
		}
		for (index :: Arity i = 0; i < up_.getSize(); ++ i) {
			const Node_* const
				hyp = up_.getValue (i);
			if (hyp->getExpression()->getTerm()->contains(variable)) {
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
	void
	Prop<A> :: showNodeInGML (String& string) const
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
				if (mode.getValue (Mode :: SHOW_IN_GML_ASSERTION)) {
					proposition_->getAssertion()->replicateName (string); string << ", " << endLine;
				}
				if (mode.getValue (Mode :: SHOW_IN_GML_WEIGHT)) {
					string << "w = " << getWeight() << ", ";
				}
				if (mode.getValue (Mode :: SHOW_IN_GML_HEIGHT_MAX)) {
					string << "max h = " << getMaxHeight() << ", ";
				}
				if (mode.getValue (Mode :: SHOW_IN_GML_HEIGHT_MIN)) {
					string << "min h = " << getMinHeight(); // << ", ";
				}
				if (mode.getValue (Mode :: SHOW_IN_GML_SUBSTITUTION)) {
					if (substitutionInt_ == NULL) {
						string << tab << tab << "substitutionInt = NULL" << endLine;
					} else {
						string << tab << tab << "substitutionInt = " << *substitutionInt_<< ", ";
					}
					if (substitutionExt_ == NULL) {
						string << tab << tab << "substitutionExt = NULL" << endLine;
					} else {
						string << tab << tab << "substitutionExt = " << *substitutionExt_ ; // << ", ";
					}
				}
		string << "\"" << endLine;
		string << tab << tab << "type \"prop\"" << endLine;
		if (hint_ != NULL) {
			string << tab << tab << "hint 1" << endLine;
		} else {
			string << tab << tab << "hint 0" << endLine;
		}
		string << tab << tab << "graphics [" << endLine;
		string << tab << tab << tab << "x " << Node_ :: getXGraphCoord() << endLine;
		string << tab << tab << tab << "y " << Node_ :: getYGraphCoord() << endLine;
		string << tab << tab << tab << "w " << 120 << endLine;
		string << tab << tab << tab << "h " << 30 << endLine;
		string << tab << tab << tab << "type \"ellipse\"" << endLine;
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
	Prop<A> :: showNodePlain (String& string) const
	{
		string << "prop";
		if (hint_ != NULL) {
			string << " (hint)";
			//string << " (" << *hint_ << ")";
		}
		string << ": ";
#ifdef DEBUG_POINTERS
		string << (void*)this << " ";
#endif
		proposition_->getAssertion()->replicateName(string);
		if (proposition_->getAssertion()->getPropArity() > 1) {
			string << ":" << proposition_->getIndex();
		}
		string << "index: " << Node_ :: globalIndex_;
#ifdef DEBUG_WEIGHT
		string << ", ";
		string << "weight: " << rate_->getWeight();
#endif
	}
	template<class A>
	void
	Prop<A> :: showInfoHeader (String& string, const int indent) const
	{
		string << iterate << indent << tab;
		string << "<prop ";
		string << "index=\"" << Node_ :: getGlobalIndex() <<"\" ";

		string << "name=\"";
		proposition_->getAssertion()->replicateName(string);
		if (proposition_->getIndex() > 0) {
			string << ":";
			string << proposition_->getIndex();
		}
		string << "\" ";
		string << "hint=\"" << ((hint_ == NULL) ? "-" : "+")  <<"\" ";
		string << ">" << endLine;
	}
	template<class A>
	void
	Prop<A> :: showInfoTree (String& string, const int indent) const
	{
		showInfoHeader (string, indent);
		showInfoAssertion (string, indent + 1);
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
		Tree_ :: writeEnding (string, "prop", indent);
	}
	template<class A>
	void
	Prop<A> :: showInfoNode (String& string, const int indent) const
	{
		showInfoHeader (string, indent);
		showInfoAssertion (string, indent + 1);
		evidences_.showInfo (string, indent + 1);
		Tree_ :: writeEnding (string, "prop", indent);
	}
	template<class A>
	void
	Prop<A> :: showInfoAssertion (String& string, const int indent) const
	{
		string << iterate << indent << tab;
		string << "<assertion>";
		string << "<![CDATA[";
		proposition_->getAssertion()->replicate(string);
		string << "]]>";
		string << "</assertion>" << endLine;
	}
}
}
}


