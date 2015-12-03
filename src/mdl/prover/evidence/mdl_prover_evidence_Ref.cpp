/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_evidence_Ref.cpp                              */
/* Description:     reference proof evidence element                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_EVIDENCE_REF_CPP_
#define MDL_PROVER_EVIDENCE_REF_CPP_

namespace mdl {
namespace prover {
namespace evidence {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	Ref<A> :: Ref
	(
		Node_* node,
		Substitution_* replacement,
		Evidence_* up
	) try :
	Evidence_ (node),
	replacement_ (replacement),
	substitution_ (NULL),
	up_ (up),
	down_ (NULL),
	depth_ (up_->getDepth()),
	cardinality_ (up_->getCardinality()),
	clone_ (NULL) {
		up_->setDown (this);
		Evidence_ :: node_->getTree()->refresh ("building ref evidence node");
		Evidence_ :: node_->getTree()->down().add (this);
	} catch (Exception& exception) {
		Evidence_ :: deleteAggregateObject (substitution_);
		Evidence_ :: deleteAggregateObject (replacement_);
		throw exception;
	}
	template<class A>
	Ref<A> :: ~ Ref()
	{
		Evidence_ :: deleteAggregateObject (substitution_);
		Evidence_ :: deleteAggregateObject (replacement_);
	}

	// prover :: Evidence implementation
	template<class A>
	bool
	Ref<A> :: growDown()
	{
		Node_* node = Evidence_ :: node_->getDown();
		return node->growDown (this);
	}
	template<class A>
	void
	Ref<A> :: setDown (Evidence_* down) {
		down_ = down;
	}
	template<class A>
	value :: Integer
	Ref<A> :: getUpForking() const {
		return 1;
	}
	template<class A>
	value :: Integer
	Ref<A> :: getDownForking() const {
		return (down_ == NULL) ? 0 : 1;
	}
	template<class A>
	typename Ref<A> :: Evidence_*
	Ref<A> :: getUp (const value :: Integer i) {
		return (i == 0) ? up_ : NULL;
	}
	template<class A>
	typename Ref<A> :: Evidence_*
	Ref<A> :: getDown (const value :: Integer i) {
		return (i == 0) ? down_ : NULL;
	}
	template<class A>
	const typename Ref<A> :: Evidence_*
	Ref<A> :: getUp (const value :: Integer i) const {
		return (i == 0) ? up_ : NULL;
	}
	template<class A>
	const typename Ref<A> :: Evidence_*
	Ref<A> :: getDown (const value :: Integer i) const {
		return (i == 0) ? down_ : NULL;
	}

using manipulator :: space;
using manipulator :: tab;
using manipulator :: endLine;
using manipulator :: iterate;

	template<class A>
	inline void
	Ref<A> :: verifyIntegrity() const
	{
		up_->verifyIntegrity();
		Memory :: stack().push();
		stack :: Expression* const
			expressionUp = new stack :: Expression (up_->Evidence_ :: getNode()->getExpression());
		stack :: Expression* const
			expressionDown = new stack :: Expression (Evidence_ :: node_->getExpression());
		expressionDown->execute (replacement_);
		if (*expressionUp != *expressionDown) {
			Error* error = new Error (Error :: SEMANTIC);
			expression :: Mode mode;
			mode << expression :: Mode :: SHOW_REPLACEABILITY;
			error->message() << mode << "reference unification fail" << endLine;
			error->message() << *expressionUp << " != " << *expressionDown << endLine;
			error->message() << "replacement = " << *replacement_ << endLine;
			showVerification (error->message());
			throw error;
		}
		Memory :: stack().pop();
	}
	template<class A>
	typename Ref<A> :: Substitution_*
	Ref<A> :: getSubstitution() {
		return (down_ == NULL) ? substitution_ : down_->getSubstitution();
	}
	template<class A>
	const typename Ref<A> :: Substitution_*
	Ref<A> :: getSubstitution() const {
		return (down_ == NULL) ? substitution_ : down_->getSubstitution();
	}
	template<class A>
	inline index :: Step
	Ref<A> :: getDepth() const {
		return depth_;
	}
	template<class A>
	inline value :: Integer
	Ref<A> :: getCardinality() const {
		return cardinality_;
	}
	template<class A>
	typename Ref<A> :: Proof_*
	Ref<A> :: constructProof (const Substitution_* substitution)
	{
		Substitution_*
			global = Substitution_ :: create (replacement_);
		global->inverse();
		global = global->compose (substitution);

		Proof_* proof = NULL;
		try {
			Proof_* upProof = up_->constructProof (global);
			proof = new proof :: Ref<Allocator_> (this, global, upProof);
		} catch (Exception& exception) {
			Evidence_ :: deleteObject (global);
			throw exception;
		}
		Evidence_ :: deleteObject (global);
		return proof;
	}
	template<class A>
	bool
	Ref<A> :: givesSameProof (const Evidence_* evidence) const
	{
		const Ref* ref = dynamic_cast<const Ref*>(evidence);
		if (ref == NULL) {
			return false;
		} else {
			return up_->givesSameProof (ref->up_);
		}
	}

	// object :: Cloneable implementation
	template<class A>
	typename Ref<A> :: Evidence_*
	Ref<A> :: clone() const
	{
		if (clone_ != NULL) {
			return clone_;
		}
		return clone_;
	}

	// object :: Object interface
	template<class A>
	void
	Ref<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Ref<A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += Evidence_ :: getAggregateVolume (replacement_);
		volume += Evidence_ :: getAggregateVolume (substitution_);
		return volume;
	}
	template<class A>
	Size_t
	Ref<A> :: getSizeOf() const {
		return sizeof (Ref);
	}
	template<class A>
	void
	Ref<A> :: show (String& string) const
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
	Ref<A> :: showVerification (String& string) const
	{
		Expression_* const
			expressionUp = new Expression_ (up_->getNode()->getExpression());
		Expression_* const
			expressionDown = new Expression_ (Evidence_ :: node_->getExpression());
		expressionDown->execute (replacement_);

		string << "************* VERIFICATION *************" << endLine;
		string << "Evidence_ :: node_: " << endLine;
		string << *Evidence_ :: node_ << endLine;
		string << endLine;
		string << "expressionUp = " << *expressionUp << endLine;
		string << "expressionDown->execute (replacement_) = " << *expressionDown << endLine;
		string << "expressionDown = " << *(Evidence_ :: node_->getExpression()) << endLine;
		string << endLine;
		//string << "proof_ = " << endLine;
		//string << *this;
	}

	template<class A>
	void
	Ref<A> :: showNodeInGML (String& string) const
	{
		if (Evidence_ :: mapped_) {
			return;
		}
		Mode mode (string);
		if (!mode.getValue (Mode :: SHOW_IN_GML_EVIDENCE)) {
			return;
		}
		up_->show (string);
		if (mode.getValue (Mode :: SHOW_ONLY_HINT) && (Evidence_ :: node_->getHint() == NULL)) {
			return;
		}
		string << tab << "node [" << endLine;
		string << tab << tab << "id " << Evidence_ :: shrinkTo (reinterpret_cast<Size_t>(this), _digits_) << endLine;
		string << tab << tab;
			string << "label \"ref ";
			if (replacement_ != NULL) {
				string << *replacement_ << endLine;
				string << tab << tab << tab;
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
				string << "min h = " << Evidence_ :: getMinHeight(); // << ", ";
			}
			string << "\"" << endLine;

		string << tab << tab << "depth " << depth_ << endLine;
		if (replacement_ == NULL) {
			string << tab << tab << "replacement \"NULL\"" << endLine;
		} else {
			string << tab << tab << "replacement \"" << *replacement_ << "\"" << endLine;
		}
		if (substitution_ == NULL) {
			string << tab << tab << "substitution \"NULL\"" << endLine;
		} else {
			string << tab << tab << "substitution \"" << *substitution_<< "\"" << endLine;
		}
		string << tab << tab << "type \"ref\"" << endLine;
		string << tab << tab << "graphics [" << endLine;
		//string << tab << tab << tab << "x " << getXGraphCoord() << endLine;
		//string << tab << tab << tab << "y " << getYGraphCoord() << endLine;
		string << tab << tab << tab << "w " << :: fmax (120, 20 + 30 * replacement_->getSymbolVolume()) << endLine;
		string << tab << tab << tab << "type \"roundrectangle\"" << endLine;
		if (!mode.getValue (Mode :: SHOW_ONLY_HINT) && (Evidence_ :: node_->getHint() != NULL)) {
			string << tab << tab << tab << "fill \"#FF0000\"" << endLine;
		} else {
			string << tab << tab << tab << "fill \"#00FF00\"" << endLine;
		}
		string << tab << tab << tab << "outline \"#000000\"" << endLine;
		string << tab << tab << "]" << endLine;
		string << tab << "]" << endLine;

		string << tab << "edge [" << endLine;
		string << tab << tab << "source " << Evidence_ :: shrinkTo (reinterpret_cast<Size_t>(this), _digits_) << endLine;
		string << tab << tab << "target " << Evidence_ :: shrinkTo (reinterpret_cast<Size_t>(up_), _digits_) << endLine;
		string << tab << "]" << endLine;
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
	Ref<A> :: showNodePlain (String& string) const
	{
		string << "REF ";
		if (Evidence_ :: isHint()) {
			string << "(hint) ";
		}
#ifdef DEBUG_POINTERS
		string << (void*)this << " ";
#endif
		if (replacement_ == NULL) {
			string << "{ } ";
		} else {
			string << *replacement_ << " ";
		}
#ifdef DEBUG_POINTERS
		string << "node: " << (void*)(Evidence_ :: node_);
#endif
	}
}
}
}

#endif /*MDL_PROVER_EVIDENCE_REF_CPP_*/
