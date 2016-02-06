/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_node_Ref.cpp                                  */
/* Description:     reference node in proof variant tree                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

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
	Ref<A> :: Ref
	(
		Tree_* tree,
		Substitution_* replacement,
		Node_* down,
		Node_* up,
		const mdl :: proof :: Node* hint
	) try :
	Node_ (tree),
	minHeight_ (down->getMinHeight()),
	replacement_ (replacement),
	up_ (up),
	down_ (down),
	clone_ (NULL),
	evidences_ (this),
	hint_ (hint),
	xx_ (static_cast<value :: Real>(down_->getXCoord() + up_->getXCoord()) / 2),
	yy_ (static_cast<value :: Real>(down_->getYCoord() + up_->getYCoord()) / 2)
	{
		Node_ :: forking_ = down->getForking();
		if (hint_ != NULL) {
			up_->markHint (hint_);
		}
		if (yy_ == down_->getYCoord()) {
			yy_ -= 0.2;
		}
		Node_ :: tree_->refresh ("building ref node");
		Node_ :: tree_->up().add (this);
		const_cast<Node_*>(up_)->addDown (this);
	} catch (Exception& exception) {
		Node_ :: deleteAggregateObject (replacement_);
		throw exception;
	}
	template<class A>
	Ref<A> :: ~ Ref() {
		Node_ :: deleteAggregateObject (replacement_);
	}

	// prover :: Node implementation
	template<class A>
	const mdl :: proof :: Node*
	Ref<A> :: getHint() const {
		return down_->getHint();
	}
	template<class A>
	void
	Ref<A> :: markHint (const mdl :: proof :: Node* node)
	{
		hint_ = node;
		up_->markHint (node);
	}
	template<class A>
	value :: Integer
	Ref<A> :: getUpArity() const {
		return 1;
	}
	template<class A>
	value :: Integer
	Ref<A> :: getDownArity() const {
		return 1;
	}
	template<class A>
	typename Ref<A> :: Node_*
	Ref<A> :: getUp (const value :: Integer i) {
		return (i == 0) ? up_ : NULL;
	}
	template<class A>
	typename Ref<A> :: Node_*
	Ref<A> :: getDown (const value :: Integer i) {
		return (i == 0) ? down_ : NULL;
	}
	template<class A>
	const typename Ref<A> :: Node_*
	Ref<A> :: getUp (const value :: Integer i) const {
		return (i == 0) ? up_ : NULL;
	}
	template<class A>
	const typename Ref<A> :: Node_*
	Ref<A> :: getDown (const value :: Integer i) const {
		return (i == 0) ? down_ : NULL;
	}

	template<class A>
	void
	Ref<A> :: growUp() {
	}
	template<class A>
	bool
	Ref<A> :: growDown (Evidence_* evidence)
	{
		pthread_mutex_t mutex;
		pthread_mutex_init (&mutex, NULL);
		pthread_mutex_lock (&mutex);
		bool result = addEvidence (evidence);
		pthread_mutex_unlock (&mutex);
		return result;
	}

	template<class A>
	typename Ref<A> :: Expression_*
	Ref<A> :: getExpression() {
		return down_->getExpression();
	}
	template<class A>
	mdl :: Proposition*
	Ref<A> :: getProposition() {
		return NULL;
	}
	template<class A>
	const typename Ref<A> :: Expression_*
	Ref<A> :: getExpression() const {
		return down_->getExpression();
	}
	template<class A>
	const mdl :: Proposition*
	Ref<A> :: getProposition() const {
		return NULL;
	}
	template<class A>
	typename Ref<A> :: Evidences_&
	Ref<A> :: getEvidences() {
		return evidences_;
	}
	template<class A>
	const typename Ref<A> :: Evidences_&
	Ref<A> :: getEvidences() const {
		return evidences_;
	}
	template<class A>
	value :: Integer
	Ref<A> :: getMaxHeight() const {
		return down_->getMaxHeight();
	}
	template<class A>
	value :: Integer
	Ref<A> :: getMinHeight() const {
		return minHeight_;
	}
	template<class A>
	value :: Real
	Ref<A> :: getWeight() const {
		return down_->getWeight();
	}
	template<class A>
	bool
	Ref<A> :: isProved() const {
		return (evidences_.getSize() > 0);
	}
	template<class A>
	bool
	Ref<A> :: isRoot() const {
		return false;
	}
	template<class A>
	bool
	Ref<A> :: mayGrowUp() const {
		return false;
	}
	template<class A>
	void
	Ref<A> :: addDown (Node_*) {
	}
	template<class A>
	bool
	Ref<A> :: liesDown (const Node_* node) const
	{
		if (node == this) {
			return true;
		}
		return down_->liesDown (node);
	}
	template<class A>
	void
	Ref<A> :: showBack (String& string) const
	{
		down_->showBack (string);
		string << "ref: " << *replacement_ << space;
	}
	template<class A>
	void
	Ref<A> :: showTreeBriefly (String& string) const {
		//up_->showTreeBriefly (string);
	}
	template<class A>
	value :: Integer
	Ref<A> :: getForking() const {
		return down_->getForking();
	}
	template<class A>
	void
	Ref<A> :: showInfo (String& string, const int indent) const
	{
		if (Config :: infoTree (Config :: SHOW_TREE_NODE)) {
			showInfoNode (string, indent);
		} else {
			showInfoTree (string, indent);
		}
	}

	// object :: Cloneable implementation
	template<class A>
	typename Ref<A> :: Node_*
	Ref<A> :: clone () const {
		return clone_;
	}

	// object :: Object implementation
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
		volume += evidences_.getVolume();
		volume += Node_ :: getAggregateVolume (replacement_);
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
			Node_ :: showGraphInGML (string);
		} else if (mode.getValue (Mode :: SHOW_IN_GML)) {
			showNodeInGML (string);
		} else {
			showNodePlain (string);
		}
	}

	/****************************
	 *		Protected members
	 ****************************/

	template<class A>
	int
	Ref<A> :: getXGraphCoord() const
	{
		xx_ = static_cast<value :: Real>(down_->getXGraphCoord() + up_->getXGraphCoord()) / 2;
		return xx_;
	}
	template<class A>
	int
	Ref<A> :: getYGraphCoord() const
	{
		const value :: Real y_1 = static_cast<value :: Real>(down_->getYGraphCoord());
		const value :: Real y_2 = static_cast<value :: Real>(up_->getYGraphCoord());
		yy_ = static_cast<value :: Real>(down_->getYGraphCoord() + up_->getYGraphCoord()) / 2;
		yy_ -= 500;
		return yy_ ;
	}

	/****************************
	 *		Private members
	 ****************************/

	// weight routines
	template<class A>
	void
	Ref<A> :: calculateWeight() const
	{
		/*localWeight_ += Config :: getProofFactor() * evidences_.getSize();
		globalWeight_ = down_->getWeight();
		globalWeight_ += localWeight_;*/
	}

	// build down routines
	template<class A>
	bool
	Ref<A> :: addEvidence (Evidence_* upEvidence)
	{
		typedef
			typename evidence :: Ref<Allocator_>
			Ref_;

		Substitution_*
			upSubstitution = upEvidence->getSubstitution();
		Substitution_*
			replacement = Substitution_ :: create (replacement_);

		Ref_* evidenceRef = new Ref_ (this, replacement, upEvidence);
		Memory :: stack().push(); {
			stack :: Substitution*
				sub = stack :: Substitution :: create (replacement_);
			stack :: Substitution*
				upSub = stack :: Substitution :: create (upSubstitution);
			sub = sub->compose (upSub, false);
			evidences_.add (sub, evidenceRef);
		}
		Memory :: stack().pop();
		return true;
	}

	template<class A>
	inline void
	Ref<A> :: verify() const {
	}

using manipulator :: mode;

	template<class A>
	void
	Ref<A> :: showNodeInGML (String& string) const
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
		string << *up_;
		string << tab << "node [" << endLine;
		string << tab << tab << "id " << Node_ :: shrinkTo (reinterpret_cast<Size_t>(this), _digits_) << endLine;
		string << tab << tab;
			string << "label \"" << *replacement_ << ", " << endLine;
			if (mode.getValue (Mode :: SHOW_IN_GML_WEIGHT)) {
				string << "w = " << getWeight() << ", ";
			}
			if (mode.getValue (Mode :: SHOW_IN_GML_HEIGHT_MAX)) {
				string << "max h = " << getMaxHeight() << ", ";
			}
			if (mode.getValue (Mode :: SHOW_IN_GML_HEIGHT_MIN)) {
				string << "min h = " << getMinHeight(); // << ", ";
			}
			string << "\"" << endLine;

		if (replacement_ == NULL) {
			string << tab << tab << "replacement \"NULL\"" << endLine;
		} else {
			string << tab << tab << "replacement \"" << *replacement_ << "\"" << endLine;
		}
		string << tab << tab << "type \"ref\"" << endLine;
		string << tab << tab << "graphics [" << endLine;
		string << tab << tab << tab << "x " << getXGraphCoord() << endLine;
		string << tab << tab << tab << "y " << getYGraphCoord() << endLine;
		string << tab << tab << tab << "w " << :: fmax (120, 30 * replacement_->getSymbolVolume()) << endLine;
		string << tab << tab << tab << "h " << 30 << endLine;
		string << tab << tab << tab << "type \"roundrectangle\"" << endLine;
		string << tab << tab << tab << "fill \"#00FF00\"" << endLine;
		string << tab << tab << tab << "outline \"#000000\"" << endLine;
		string << tab << tab << "]" << endLine;
		string << tab << "]" << endLine;
		string << tab << "edge [" << endLine;
		string << tab << tab << "source " << Node_ :: shrinkTo (reinterpret_cast<Size_t>(this), _digits_) << endLine;
		string << tab << tab << "target " << Node_ :: shrinkTo (reinterpret_cast<Size_t>(up_), _digits_) << endLine;
		string << tab << tab << "graphics [" << endLine;
		string << tab << tab << tab << "width 2" << endLine;
		string << tab << tab << tab << "style \"dashed\"" << endLine;
		string << tab << tab << tab << "fill \"#000000\"" << endLine;
		string << tab << tab << tab << "targetArrow \"standard\"" << endLine;
		string << tab << tab << "]" << endLine;
		string << tab << "]" << endLine;
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
	Ref<A> :: showNodePlain (String& string) const {
		string << "ref ";
#ifdef DEBUG_POINTERS
		string << (void*)this << ": ";
#endif
		string << *replacement_;
	}
	template<class A>
	void
	Ref<A> :: showInfoHeader (String& string, const int indent) const
	{
		string << iterate << indent << tab;
		string << "<ref ";
		string << "index=\"" << Node_ :: getGlobalIndex() <<"\" ";
		string << "types=\"";
		getExpression()->showTypes (string);
		string << "\" ";
		string << "hint=\"" << ((hint_ == NULL) ? "-" : "+")  <<"\" ";
		string << ">" << endLine;
	}
	template<class A>
	void
	Ref<A> :: showInfoTree (String& string, const int indent) const
	{
		showInfoHeader (string, indent);
		showInfoExpression (string, indent + 1);
		for (index :: Arity i = 0; i < getDownArity(); ++ i) {
			const Node_* node = getDown(i);
			string << iterate << indent << tab;
			string << "<down index=\"" << node->getGlobalIndex() << "\"/>" << endLine;
		}
		for (index :: Arity i = 0; i < getUpArity(); ++ i) {
			const Node_* node = getUp(i);
			string << iterate << indent << tab;
			string << "<up index=\"" << node->getGlobalIndex() << "\"/>" << endLine;
		}
		Tree_ :: writeEnding (string, "ref", indent);
	}
	template<class A>
	void
	Ref<A> :: showInfoNode (String& string, const int indent) const
	{
		showInfoHeader (string, indent);
		showInfoExpression (string, indent + 1);
		evidences_.showInfo (string, indent + 1);
		Tree_ :: writeEnding (string, "ref", indent);
	}
	template<class A>
	void
	Ref<A> :: showInfoExpression (String& string, const int indent) const
	{
		string << iterate << indent << tab;
		string << "<expression>";
		string << "<![CDATA[";
		string << *getExpression();
		string << "]]>";
		string <<"</expression>" << endLine;
	}
}
}
}


