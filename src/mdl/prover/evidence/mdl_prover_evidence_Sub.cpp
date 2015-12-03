/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_evidence_Sub.cpp                              */
/* Description:     common substitution proof evidence element               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_EVIDENCE_SUB_CPP_
#define MDL_PROVER_EVIDENCE_SUB_CPP_

namespace mdl {
namespace prover {
namespace evidence {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	Sub<A> :: Sub (Node_* node, Evidence_* up, Substitution_* substitution, bool confirm) try :
	Evidence_ (node),
	substitution_ (substitution),
	up_ (1),
	depth_ (up->getDepth()),
	cardinality_ (up->getCardinality()),
	clone_ (NULL),
	down_ (node->getDownArity())
	{
		Evidence_ :: node_->getTree()->refresh ("building sub evidence node");
		up_.add (up);
		for (value :: Integer i = 0; i < Evidence_ :: node_->getDownArity(); ++ i) {
			Node_* down = Evidence_ :: node_->getDown (i);
			down_.add (down);
		}
		if (confirm) {
			up->setDown (this);
			Evidence_ :: node_->getTree()->down().add (this);
			#ifdef DEBUG_PROVER_DOWN
			up->verifyIntegrity();
			#endif
		}
	} catch (Exception& exception) {
		Evidence_ :: deleteAggregateObject (substitution_);
		throw exception;
	}
	template<class A>
	Sub<A> :: ~ Sub() {
		Evidence_ :: deleteAggregateObject (substitution_);
	}

	template<class A>
	inline value :: Integer
	Sub<A> :: getSize() const {
		return up_.getSize();
	}
	template<class A>
	void
	Sub<A> :: setDown (Evidence_* down) {
	}
	template<class A>
	inline void
	Sub<A> :: addUp (Evidence_* up)
	{
		up->setDown (this);
		up_.add (up);
		#ifdef DEBUG_PROVER_DOWN
		up->verifyIntegrity();
		#endif
	}
	template<class A>
	void
	Sub<A> :: clearUp()
	{
		for (index :: Arity i = 0; i < up_.getSize(); ++ i) {
			const Evidence_*
				evidenceUp = up_.getValue (i);
			deleteObject (evidenceUp);
		}
		up_.clear();
	}
	template<class A>
	void
	Sub<A> :: confirm()
	{
		for (index :: Arity i = 0; i < up_.getSize(); ++ i) {
			Evidence_* evidenceUp = up_.getValue (i);
			evidenceUp->setDown (this);
		}
		Evidence_ :: node_->getTree()->down().add (this);
	}

using manipulator :: space;
using manipulator :: tab;
using manipulator :: endLine;
using manipulator :: iterate;

	// prover :: Evidence implementation
	template<class A>
	bool
	Sub<A> :: growDown()
	{
		const value :: Integer size = down_.getSize();
		for (value :: Integer i = 0; i < size; ++ i) {
			const value :: Integer j = size - 1 - i;
			Node_* node = down_.getValue (j);
			if (node->growDown (this)) {
				down_.remove (j);
			}
		}
		return down_.isEmpty();
	}
	template<class A>
	value :: Integer
	Sub<A> :: getUpForking() const {
		return up_.getSize();
	}
	template<class A>
	value :: Integer
	Sub<A> :: getDownForking() const {
		return 0;
	}
	template<class A>
	typename Sub<A> :: Evidence_*
	Sub<A> :: getUp (const value :: Integer i) {
		return up_.getValue (i);
	}
	template<class A>
	typename Sub<A> :: Evidence_*
	Sub<A> :: getDown (const value :: Integer i) {
		return NULL;
	}
	template<class A>
	const typename Sub<A> :: Evidence_*
	Sub<A> :: getUp (const value :: Integer i) const {
		return up_.getValue (i);
	}
	template<class A>
	const typename Sub<A> :: Evidence_*
	Sub<A> :: getDown (const value :: Integer i) const {
		return NULL;
	}
	template<class A>
	inline void
	Sub<A> :: verifyIntegrity() const
	{
		for (index :: Arity i = 0; i < up_.getSize(); ++ i) {
			up_.getValue (i)->verifyIntegrity();
		}
	}
	template<class A>
	typename Sub<A> :: Substitution_*
	Sub<A> :: getSubstitution() {
		return substitution_;
	}
	template<class A>
	const typename Sub<A> :: Substitution_*
	Sub<A> :: getSubstitution() const {
		return substitution_;
	}
	template<class A>
	inline index :: Step
	Sub<A> :: getDepth() const {
		return depth_;
	}
	template<class A>
	inline value :: Integer
	Sub<A> :: getCardinality() const {
		return cardinality_;
	}
	template<class A>
	typename Sub<A> :: Proof_*
	Sub<A> :: constructProof (const Substitution_* substitution)
	{
		Substitution_*
			global = Substitution_ :: create (substitution_);
		global = global->compose (substitution);

		Evidence_* evidence = up_.getValue (0);
		Proof_* proof = NULL;
		try {
			proof = evidence->constructProof (global);
		} catch (Exception& exception) {
			Evidence_ :: deleteObject (global);
			throw exception;
		}
		Evidence_ :: deleteObject (global);
		return proof;
	}
	template<class A>
	bool
	Sub<A> :: givesSameProof (const Evidence_* evidence) const
	{
		const Sub* sub = dynamic_cast<const Sub*>(evidence);
		if (sub == NULL) {
			return false;
		} else {
			/*if (!substitution_->isIdentical (sub->substitution_)) {
				return false;
			}*/
			for (index :: Arity i = 0; i < up_.getSize(); ++ i) {
				for (index :: Arity j = 0; j < sub->up_.getSize(); ++ j) {
					if (up_ [i]->givesSameProof (sub->up_[j])) {
						return true;
					}
				}
			}
			return false;
		}
	}

	// object :: Cloneable implementation
	template<class A>
	typename Sub<A> :: Evidence_*
	Sub<A> :: clone() const {
		return clone_;
	}

	// object :: Object interface
	template<class A>
	void
	Sub<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Sub<A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += Evidence_ :: getAggregateVolume (substitution_);
		volume += up_.getVolume();
		volume += down_.getVolume();
		return volume;
	}
	template<class A>
	Size_t
	Sub<A> :: getSizeOf() const {
		return sizeof (Sub);
	}
	template<class A>
	void
	Sub<A> :: show (String& string) const
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
	Sub<A> :: showNodeInGML (String& string) const
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
			string << "label \"sub ";
			if (substitution_ != NULL) {
				string << *substitution_ << endLine;
				string << tab << tab << tab;
			}
			//if (!mode.getValue (Mode :: SHOW_ONLY_HINT) && (Evidence_ :: node_->getHint() != NULL)) {
			//	string << "<HINT> ";
			//}
			if (mode.getValue (Mode :: SHOW_IN_GML_DEPTH)) {
				string << (void*)this << ", ";
			}
			if (mode.getValue (Mode :: SHOW_IN_GML_DEPTH)) {
				string << "d = " << getDepth() << ", ";
			}
			if (mode.getValue (Mode :: SHOW_IN_GML_HEIGHT_MAX)) {
				string << "max h = " << Evidence_ :: getMaxHeight() << ", ";
			}
			if (mode.getValue (Mode :: SHOW_IN_GML_HEIGHT_MAX)) {
				string << "min h = " << Evidence_ :: getMinHeight(); // << ", ";
			}
			string << "\"" << endLine;

		if (substitution_ == NULL) {
			string << tab << tab << "substitution \"NULL\"" << endLine;
		} else {
			string << tab << tab << "substitution \"" << *substitution_ << "\"" << endLine;
		}
		string << tab << tab << "type \"sub\"" << endLine;
		string << tab << tab << "graphics [" << endLine;
		//string << tab << tab << tab << "x " << getXGraphCoord() << endLine;
		//string << tab << tab << tab << "y " << getYGraphCoord() << endLine;
		string << tab << tab << tab << "w " << :: fmax (120, 30 * substitution_->getSymbolVolume()) << endLine;
		string << tab << tab << tab << "type \"roundrectangle\"" << endLine;
		if (!mode.getValue (Mode :: SHOW_ONLY_HINT) && (Evidence_ :: node_->getHint() != NULL)) {
			string << tab << tab << tab << "fill \"#FF0000\"" << endLine;
		} else {
			string << tab << tab << tab << "fill \"#00CCFF\"" << endLine;
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
	Sub<A> :: showNodePlain (String& string) const
	{
		string << "SUB ";
		if (Evidence_ :: isHint()) {
			string << "(hint) ";
		}
#ifdef DEBUG_POINTERS
		string << (void*)this << " ";
#endif
		if (substitution_ == NULL) {
			string << "{ } ";
		} else {
			string << *substitution_ << " ";
		}
#ifdef DEBUG_POINTERS
		string << "node: " << (void*)(Evidence_ :: node_);
#endif
	}
}
}
}

#endif /*MDL_PROVER_EVIDENCE_SUB_CPP_*/
