/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_evidence_Top.cpp                              */
/* Description:     top (premise) proof evidence element                     */
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
namespace evidence {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	Top<A> :: Top
	(
		Node_* node,
		Premise_* premise
	) try :
	Evidence_ (node),
	premise_ (premise),
	down_ (NULL),
	substitution_ (NULL),
	clone_ (NULL) {
		Evidence_ :: node_->getTree()->refresh ("building top evidence node");
		Evidence_ :: node_->getTree()->down().add (this);
		//#ifdef DEBUG_PROVER_DOWN
		//verifyIntegrity();
		//#endif
	} catch (Exception& exception) {
		Evidence_ :: deleteAggregateObject (substitution_);
		throw exception;
	}
	template<class A>
	Top<A> :: ~ Top() {
		Evidence_ :: deleteAggregateObject (substitution_);
	}

using manipulator :: space;
using manipulator :: tab;
using manipulator :: endLine;
using manipulator :: iterate;

	// prover :: Evidence implementation
	template<class A>
	bool
	Top<A> :: growDown()
	{
		Node_* node = Evidence_ :: node_->getDown();
		return node->growDown (this);
	}
	template<class A>
	void
	Top<A> :: setDown (Evidence_* down) {
		down_ = down;
	}
	template<class A>
	value :: Integer
	Top<A> :: getUpForking() const {
		return 0;
	}
	template<class A>
	value :: Integer
	Top<A> :: getDownForking() const {
		return (down_ == NULL) ? 0 : 1;
	}
	template<class A>
	typename Top<A> :: Evidence_*
	Top<A> :: getUp (const value :: Integer) {
		return NULL;
	}
	template<class A>
	typename Top<A> :: Evidence_*
	Top<A> :: getDown (const value :: Integer i) {
		return (i == 0) ? down_ : NULL;
	}
	template<class A>
	const typename Top<A> :: Evidence_*
	Top<A> :: getUp (const value :: Integer) const {
		return NULL;
	}
	template<class A>
	const typename Top<A> :: Evidence_*
	Top<A> :: getDown (const value :: Integer i) const {
		return (i == 0) ? down_ : NULL;
	}
	template<class A>
	void
	Top<A> :: verifyIntegrity() const
	{
		Memory :: stack().push();
		stack :: Expression* const
			expression = new stack :: Expression (Evidence_ :: node_->getExpression());
		expression->execute (getSubstitution());
		const stack :: Expression* const
			premise = new stack :: Expression (premise_->getExpression());

		/*Expression_* const
			expression = new Expression_ (Evidence_ :: node_->getExpression());
		expression->execute (getSubstitution());
		const Expression_* const
			premise = new Expression_ (premise_->getExpression());*/

		if (*expression != *premise) {
			Error* error = new Error (Error :: SEMANTIC);
			expression :: Mode mode;
			mode << expression :: Mode :: SHOW_REPLACEABILITY;
			error->message() << mode << "premise unification fail" << endLine;
			error->message() << *expression << " != " << *premise << endLine;
			error->message() << "substitution = " << *getSubstitution() << endLine;
			showVerification (error->message());
			Memory :: stack().pop();
			throw error;
		}
		//premise->commitSuicide();
		Memory :: stack().pop();
	}
	template<class A>
	typename Top<A> :: Substitution_*
	Top<A> :: getSubstitution() {
		return (down_ == NULL) ? substitution_ : down_->getSubstitution();
	}
	template<class A>
	const typename Top<A> :: Substitution_*
	Top<A> :: getSubstitution() const {
		return (down_ == NULL) ? substitution_ : down_->getSubstitution();
	}
	template<class A>
	index :: Step
	Top<A> :: getDepth() const {
		return 0;
	}
	template<class A>
	value :: Integer
	Top<A> :: getCardinality() const {
		return 0;
	}
	template<class A>
	typename Top<A> :: Proof_*
	Top<A> :: constructProof (const Substitution_*) {
		return new proof :: Top<Allocator_> (this);
	}
	template<class A>
	bool
	Top<A> :: givesSameProof (const Evidence_* evidence) const
	{
		const Top* top = dynamic_cast<const Top*>(evidence);
		if (top == NULL) {
			return false;
		} else {
			return (premise_ == top->premise_);
		}
	}

	// object :: Cloneable implementation
	template<class A>
	typename Top<A> :: Evidence_*
	Top<A> :: clone() const
	{
		if (clone_ != NULL) {
			return clone_;
		}
		clone_ = new Top (*this);
		return clone_;
	}

	// object :: Object implementation
	template<class A>
	void
	Top<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Top<A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += Evidence_ :: getAggregateVolume (substitution_);
		return volume;
	}
	template<class A>
	Size_t
	Top<A> :: getSizeOf() const {
		return sizeof (Top);
	}
	template<class A>
	void
	Top<A> :: show (String& string) const
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
	void
	Top<A> :: showVerification (String& string) const
	{
		stack :: Expression* const
			expression = new stack :: Expression (Evidence_ :: node_->getExpression());
		expression->execute (getSubstitution());
		const stack :: Expression* const
			premise = new stack :: Expression (premise_->getExpression());

		string << "************* VERIFICATION *************" << endLine;
		string << "Evidence_ :: node_ = " << endLine;
		string << *Evidence_ :: node_ << endLine;
		string << endLine;
		string << "expression_ = " << *(Evidence_ :: node_->getExpression()) << endLine;
		string << "expression_->execute (substitution_) = " << *expression << endLine;
		string << "premise_ = " << *premise << endLine;
		string << endLine;
		//string << "proof_ = " << endLine;
		//string << *this;
	}

	template<class A>
	void
	Top<A> :: showNodeInGML (String& string) const
	{
		if (Evidence_ :: mapped_) {
			return;
		}
		Mode mode (string);
		if (!mode.getValue (Mode :: SHOW_IN_GML_EVIDENCE)) {
			return;
		}
		if (mode.getValue (Mode :: SHOW_ONLY_HINT) && (Evidence_ :: node_->getHint() == NULL)) {
			return;
		}
		string << tab << "node [" << endLine;
		string << tab << tab << "id " << Evidence_ :: shrinkTo (reinterpret_cast<Size_t>(this), _digits_) << endLine;
		string << tab << tab;
			string << "label \"" ;
			string << *premise_ << ", " << endLine;
			string << tab << tab << tab;
			//if (!mode.getValue (Mode :: SHOW_ONLY_HINT) && (Evidence_ :: node_->getHint() != NULL)) {
			//	string << "<HINT> ";
			//}
			if (mode.getValue (Mode :: SHOW_IN_GML_EXPRESSION)) {
				string << *premise_->getExpression() << ", " << endLine;
			}
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

		string << tab << tab << "premise \"" << *premise_ << "\"" << endLine;
		if (substitution_ == NULL) {
			string << tab << tab << "substitution \"NULL\"" << endLine;
		} else {
			string << tab << tab << "substitution \"" << *substitution_<< "\"" << endLine;
		}
		string << tab << tab << "expression \"" << *Evidence_ :: node_->getExpression() << "\"" << endLine;
		string << tab << tab << "type \"top\"" << endLine;

		string << tab << tab << "graphics [" << endLine;
		//string << tab << tab << tab << "x " << getXGraphCoord() << endLine;
		//string << tab << tab << tab << "y " << getYGraphCoord() << endLine;
		string << tab << tab << tab << "w " << :: fmax (120, 30 * premise_->getExpression()->getLength()) << endLine;
		//string << tab << tab << tab << "width 1" << endLine;
		string << tab << tab << tab << "type \"ellipse\"" << endLine;
		//string << tab << tab << tab << "style \"dotted\"" << endLine;
		string << tab << tab << tab << "fill \"#FF23F4\"" << endLine;
		string << tab << tab << tab << "targetArrow \"standard\"" << endLine;
		string << tab << tab << "]" << endLine;

		string << tab << "edge [" << endLine;
		string << tab << tab << "source " << Evidence_ :: shrinkTo (reinterpret_cast<Size_t>(this), _digits_) << endLine;
		string << tab << tab << "target " << Evidence_ :: shrinkTo (reinterpret_cast<Size_t>(Evidence_ :: node_), _digits_) << endLine;
		string << tab << "]" << endLine;
		string << tab << "]" << endLine;
		Evidence_ :: mapped_ = true;
	}
	template<class A>
	void
	Top<A> :: showNodePlain (String& string) const
	{
		string << "TOP ";
		if (Evidence_ :: isHint()) {
			string << "(hint) ";
		}
#ifdef DEBUG_POINTERS
		string << (void*)this << " ";
#endif
		string << *premise_ << " ";
#ifdef DEBUG_POINTERS
		string << "node: " << (void*)(Evidence_ :: node_);
#endif
	}
}
}
}


