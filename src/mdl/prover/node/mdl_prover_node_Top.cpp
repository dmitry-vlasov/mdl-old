/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_node_Top.cpp                                  */
/* Description:     reference node in proof variant tree                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_NODE_TOP_CPP_
#define MDL_PROVER_NODE_TOP_CPP_

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
	Top<A> :: Top
	(
		Tree_* tree,
		Node_* down,
		Premise_* premise,
		Substitution_* substitution,
		const mdl :: proof :: Node* hint
	) try :
	Node_ (tree),
	minHeight_ (down->getMinHeight() + 1),
	substitution_ (substitution),
	expression_ (new Expression_ (premise->getExpression())),
	premise_ (premise),
	down_ (down),
	clone_ (NULL),
	evidences_ (this),
	hint_ (hint),
	xx_ (0 /*static_cast<value :: Real>(down_->getXCoord() + premise_->getXCoord()) / 2*/),
	yy_ (0 /*static_cast<value :: Real>(down_->getYCoord() + premise_->getYCoord()) / 2*/)
	{
		Node_ :: forking_ = down->getForking();
		if (yy_ == down_->getYCoord()) {
			yy_ -= 0.2;
		}
		Node_ :: tree_->refresh ("building top node");
		Node_ :: tree_->up().add (this);
	} catch (Exception& exception) {
		Node_ :: deleteAggregateObject (substitution_);
		Node_ :: deleteAggregateObject (expression_);
		throw exception;
	}
	template<class A>
	Top<A> :: ~ Top() {
		Node_ :: deleteAggregateObject (substitution_);
		Node_ :: deleteAggregateObject (expression_);
	}

	// prover :: Node implementation
	template<class A>
	const mdl :: proof :: Node*
	Top<A> :: getHint() const {
		return down_->getHint();
	}
	template<class A>
	void
	Top<A> :: markHint (const mdl :: proof :: Node* node) {
		hint_ = node;
	}
	template<class A>
	value :: Integer
	Top<A> :: getUpArity() const {
		return 0;
	}
	template<class A>
	value :: Integer
	Top<A> :: getDownArity() const {
		return 1;
	}
	template<class A>
	typename Top<A> :: Node_*
	Top<A> :: getUp (const value :: Integer i) {
		return NULL;
	}
	template<class A>
	typename Top<A> :: Node_*
	Top<A> :: getDown (const value :: Integer i) {
		return (i == 0) ? down_ : NULL;
	}
	template<class A>
	const typename Top<A> :: Node_*
	Top<A> :: getUp (const value :: Integer i) const {
		return NULL;
	}
	template<class A>
	const typename Top<A> :: Node_*
	Top<A> :: getDown (const value :: Integer i) const {
		return (i == 0) ? down_ : NULL;
	}

	template<class A>
	void
	Top<A> :: growUp() {
	}
	template<class A>
	bool
	Top<A> :: growDown (Evidence_*) {
		addEvidence();
	}

	template<class A>
	typename Top<A> :: Expression_*
	Top<A> :: getExpression() {
		return down_->getExpression();
	}
	template<class A>
	mdl :: Proposition*
	Top<A> :: getProposition() {
		return NULL;
	}
	template<class A>
	const typename Top<A> :: Expression_*
	Top<A> :: getExpression() const {
		return expression_;
	}
	template<class A>
	const mdl :: Proposition*
	Top<A> :: getProposition() const {
		return NULL;
	}
	template<class A>
	typename Top<A> :: Evidences_&
	Top<A> :: getEvidences() {
		return evidences_;
	}
	template<class A>
	const typename Top<A> :: Evidences_&
	Top<A> :: getEvidences() const {
		return evidences_;
	}
	template<class A>
	value :: Integer
	Top<A> :: getMaxHeight() const {
		return down_->getMaxHeight() + 1;
	}
	template<class A>
	value :: Integer
	Top<A> :: getMinHeight() const {
		return minHeight_;
	}
	template<class A>
	value :: Real
	Top<A> :: getWeight() const {
		return down_->getWeight();
	}
	template<class A>
	bool
	Top<A> :: isProved() const {
		return true;
	}
	template<class A>
	bool
	Top<A> :: isRoot() const {
		return false;
	}
	template<class A>
	bool
	Top<A> :: mayGrowUp() const {
		return false;
	}
	template<class A>
	void
	Top<A> :: addDown (Node_*) {
	}
	template<class A>
	bool
	Top<A> :: liesDown (const Node_* node) const
	{
		if (node == this) {
			return true;
		}
		return down_->liesDown (node);
	}
	template<class A>
	void
	Top<A> :: showBack (String& string) const
	{
		down_->showBack (string);
		string << "top: " << *premise_->getExpression() << space;
	}
	template<class A>
	void
	Top<A> :: showTreeBriefly (String& string) const {
		//premise_->showTreeBriefly (string);
	}
	template<class A>
	value :: Integer
	Top<A> :: getForking() const {
		return down_->getForking();
	}
	template<class A>
	void
	Top<A> :: showInfo (String& string, const int indent) const
	{
		if (Config :: infoTree (Config :: SHOW_TREE_NODE)) {
			showInfoNode (string, indent);
		} else {
			showInfoTree (string, indent);
		}
	}

	// object :: Cloneable implementation
	template<class A>
	typename Top<A> :: Node_*
	Top<A> :: clone () const {
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
		volume += evidences_.getVolume();
		volume += Node_ :: getAggregateVolume (expression_);
		volume += Node_ :: getAggregateVolume (substitution_);
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
	Top<A> :: getXGraphCoord() const
	{
		//xx_ = static_cast<value :: Real>(down_->getXGraphCoord() + premise_->getXGraphCoord()) / 2;
		return xx_;
	}
	template<class A>
	int
	Top<A> :: getYGraphCoord() const
	{
		//const value :: Real y_1 = static_cast<value :: Real>(down_->getYGraphCoord());
		//const value :: Real y_2 = static_cast<value :: Real>(premise_->getYGraphCoord());
		//yy_ = static_cast<value :: Real>(down_->getYGraphCoord() + premise_->getYGraphCoord()) / 2;
		//yy_ -= 500;
		return yy_ ;
	}

	/****************************
	 *		Private members
	 ****************************/

	// weight routines
	template<class A>
	void
	Top<A> :: calculateWeight() const
	{
		/*localWeight_ += Config :: getProofFactor() * evidences_.getSize();
		globalWeight_ = down_->getWeight();
		globalWeight_ += localWeight_;*/
	}

	// build down routines
	template<class A>
	bool
	Top<A> :: addEvidence()
	{
		typedef
			typename evidence :: Top<Allocator_>
			Top_;
		typedef
			typename evidence :: Sub<Allocator_>
			Sub_;
		Evidence_* evidenceTop = new Top_ (this, premise_);

		Memory :: stack().push(); {
			const stack :: Substitution*
				sub = stack :: Substitution :: create (substitution_);
			evidences_.add (sub, evidenceTop);
		}
		Memory :: stack().pop();
		return true;
	}

	template<class A>
	inline void
	Top<A> :: verify() const {

	}

using manipulator :: mode;

	template<class A>
	void
	Top<A> :: showNodeInGML (String& string) const
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
		string << *premise_;
		string << tab << "node [" << endLine;
		string << tab << tab << "id " << Node_ :: shrinkTo (reinterpret_cast<Size_t>(this), _digits_) << endLine;
		string << tab << tab;
			string << "label \"" << *substitution_ << ", " << endLine;
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

		if (substitution_ == NULL) {
			string << tab << tab << "replacement \"NULL\"" << endLine;
		} else {
			string << tab << tab << "replacement \"" << *substitution_ << "\"" << endLine;
		}
		string << tab << tab << "type \"ref\"" << endLine;
		string << tab << tab << "graphics [" << endLine;
		string << tab << tab << tab << "x " << getXGraphCoord() << endLine;
		string << tab << tab << tab << "y " << getYGraphCoord() << endLine;
		string << tab << tab << tab << "w " << :: fmax (120, 30 * substitution_->getSymbolVolume()) << endLine;
		string << tab << tab << tab << "h " << 30 << endLine;
		string << tab << tab << tab << "type \"roundrectangle\"" << endLine;
		string << tab << tab << tab << "fill \"#00FF00\"" << endLine;
		string << tab << tab << tab << "outline \"#000000\"" << endLine;
		string << tab << tab << "]" << endLine;
		string << tab << "]" << endLine;
		string << tab << "edge [" << endLine;
		string << tab << tab << "source " << Node_ :: shrinkTo (reinterpret_cast<Size_t>(this), _digits_) << endLine;
		string << tab << tab << "target " << Node_ :: shrinkTo (reinterpret_cast<Size_t>(premise_), _digits_) << endLine;
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
	Top<A> :: showNodePlain (String& string) const {
		string << "top";
		if (hint_ != NULL) {
			string << " (hint)";
			//string << " (" << *hint_ << ")";
		}
		string << ": ";
#ifdef DEBUG_POINTERS
		string << (void*)this << " ";
#endif
		string << *premise_;
	}
	template<class A>
	void
	Top<A> :: showInfoHeader (String& string, const int indent) const
	{
		string << iterate << indent << tab;
		string << "<top ";
		string << "index=\"" << Node_ :: getGlobalIndex() <<"\" ";
		string << "types=\"";
		getExpression()->showTypes (string);
		string << "\" ";
		string << "reference=\"";
		premise_->replicateReference (string);
		string << "\" ";
		string << "hint=\"" << ((hint_ == NULL) ? "-" : "+")  <<"\" ";
		string << "down=\"" << down_->getGlobalIndex() << "\" ";
		string << ">" << endLine;
	}
	template<class A>
	void
	Top<A> :: showInfoTree (String& string, const int indent) const
	{
		showInfoHeader (string, indent);
		showInfoExpression (string, indent + 1);
		Tree_ :: writeEnding (string, "top", indent);
	}
	template<class A>
	void
	Top<A> :: showInfoNode (String& string, const int indent) const
	{
		showInfoHeader (string, indent);
		showInfoExpression (string, indent + 1);
		evidences_.showInfo (string, indent + 1);
		Tree_ :: writeEnding (string, "top", indent);
	}
	template<class A>
	void
	Top<A> :: showInfoExpression (String& string, const int indent) const
	{
		string << iterate << indent << tab;
		string << "<expression>";
		string << "<![CDATA[";
		string << *getExpression();
		string << "]]>";
		string << "</expression>" << endLine;
	}
}
}
}

#endif /*MDL_PROVER_NODE_TOP_CPP_*/
