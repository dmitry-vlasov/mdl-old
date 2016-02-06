/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_evidence_Hyp.cpp                              */
/* Description:     hyp evidence element                                     */
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
	Hyp<A> :: Hyp
	(
		Node_* node,
		Evidence_* up,
		Substitution_* substitution
	) try :
	Evidence_ (node),
	substitution_ (substitution),
	up_ (up),
	down_ (NULL),
	depth_ (up_->getDepth() + 1),
	cardinality_ (up_->getCardinality()),
	clone_ (NULL) {
		up_->setDown (this);
		Evidence_ :: node_->getTree()->refresh ("building hyp evidence node");
		Evidence_ :: node_->getTree()->down().add (this);
	} catch (Exception& exception) {
		Evidence_ :: deleteAggregateObject (substitution_);
		throw exception;
	}
	template<class A>
	Hyp<A> :: ~ Hyp() {
		Evidence_ :: deleteAggregateObject (substitution_);
	}

	// prover :: Evidence implementation
	template<class A>
	bool
	Hyp<A> :: growDown()
	{
		bool result = true;
		for (value :: Integer i = 0; i < Evidence_ :: node_->getDownArity(); ++ i) {
			Node_* node = Evidence_ :: node_->getDown (i);
			if (!node->growDown (this)) {
				result = false;
			}
		}
		return result;
	}
	template<class A>
	void
	Hyp<A> :: setDown (Evidence_* down) {
		down_ = down;
	}
	template<class A>
	value :: Integer
	Hyp<A> :: getUpForking() const {
		return 1;
	}
	template<class A>
	value :: Integer
	Hyp<A> :: getDownForking() const {
		return (down_ == NULL) ? 0 : 1;
	}
	template<class A>
	typename Hyp<A> :: Evidence_*
	Hyp<A> :: getUp (const value :: Integer i) {
		return (i == 0) ? up_ : NULL;
	}
	template<class A>
	typename Hyp<A> :: Evidence_*
	Hyp<A> :: getDown (const value :: Integer i) {
		return (i == 0) ? down_ : NULL;
	}
	template<class A>
	const typename Hyp<A> :: Evidence_*
	Hyp<A> :: getUp (const value :: Integer i) const {
		return (i == 0) ? up_ : NULL;
	}
	template<class A>
	const typename Hyp<A> :: Evidence_*
	Hyp<A> :: getDown (const value :: Integer i) const {
		return (i == 0) ? down_ : NULL;
	}

using manipulator :: space;
using manipulator :: tab;
using manipulator :: endLine;
using manipulator :: iterate;

	template<class A>
	inline void
	Hyp<A> :: verifyIntegrity() const {
		up_->verifyIntegrity();
	}
	template<class A>
	typename Hyp<A> :: Substitution_*
	Hyp<A> :: getSubstitution() {
		return (down_ == NULL) ? substitution_ : down_->getSubstitution();
	}
	template<class A>
	const typename Hyp<A> :: Substitution_*
	Hyp<A> :: getSubstitution() const {
		return (down_ == NULL) ? substitution_ : down_->getSubstitution();
	}
	template<class A>
	inline index :: Step
	Hyp<A> :: getDepth() const {
		return depth_;
	}
	template<class A>
	inline value :: Integer
	Hyp<A> :: getCardinality() const {
		return cardinality_;
	}
	template<class A>
	typename Hyp<A> :: Proof_*
	Hyp<A> :: constructProof (const Substitution_* substutition)
	{
		Proof_* upProof = up_->constructProof (substutition);
		return new proof :: Hyp<Allocator_> (this, upProof);
	}
	template<class A>
	bool
	Hyp<A> :: givesSameProof (const Evidence_* evidence) const
	{
		const Hyp* hyp = dynamic_cast<const Hyp*>(evidence);
		if (hyp == NULL) {
			return false;
		} else {
			return up_->givesSameProof (hyp->up_);
		}
	}

	// object :: Cloneable implementation
	template<class A>
	typename Hyp<A> :: Evidence_*
	Hyp<A> :: clone() const
	{
		if (clone_ != NULL) {
			return clone_;
		}
		Hyp* clone = new Hyp (*this);
		clone_ = clone;
		clone->node_ = Evidence_ :: node_->clone();
		clone->up_ = up_->clone();
		return clone_;
	}

	// object :: Object interface
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
		volume += Evidence_ :: getAggregateVolume (substitution_);
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
	Hyp<A> :: showNodeInGML (String& string) const
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
			string << "label \"";
			if (mode.getValue (Mode :: SHOW_IN_GML_EXPRESSION)) {
				string << *(Evidence_ :: node_->getExpression()) << endLine;
				string << tab << tab << tab;
			}
			if (!mode.getValue (Mode :: SHOW_ONLY_HINT) && (Evidence_ :: node_->getHint() != NULL)) {
				string << "<HINT> ";
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

		string << tab << tab << "expression \"" << *(Evidence_ :: node_->getExpression()) << "\"" << endLine;
		string << tab << tab << "depth " << depth_ << endLine;
		string << tab << tab << "type \"hyp\"" << endLine;

		string << tab << tab << "graphics [" << endLine;
		//string << tab << tab << tab << "x " << getXGraphCoord() << endLine;
		//string << tab << tab << tab << "y " << getYGraphCoord() << endLine;
		string << tab << tab << tab << "w " << :: fmax (120, 20 * (Evidence_ :: node_->getExpression()->getLength())) << endLine;
		string << tab << tab << tab << "type \"rectangle\"" << endLine;
		if (Evidence_ :: node_->isRoot()) {
			string << tab << tab << tab << "fill \"#3366FF\"" << endLine;
		} else if (!mode.getValue (Mode :: SHOW_ONLY_HINT) && (Evidence_ :: node_->getHint() != NULL)) {
			string << tab << tab << tab << "fill \"#FF0000\"" << endLine;
		} else {
			string << tab << tab << tab << "fill \"#3CFF06\"" << endLine;
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
	Hyp<A> :: showNodePlain (String& string) const
	{
		string << "HYP ";
		if (Evidence_ :: isHint()) {
			string << "(hint) ";
		}
#ifdef DEBUG_POINTERS
		string << (void*)this << " ";
#endif
		string << *Evidence_ :: node_->getExpression() << " ";
#ifdef DEBUG_POINTERS
		string << "node: " << (void*)(Evidence_ :: node_) << " ";
#endif
	}
}
}
}


