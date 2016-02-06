/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_interface_Evidence.cpp                        */
/* Description:     interface for evidence (semiproof) in variant tree       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/mdl_interface.dpp"
#include "mdl/prover/evidence/mdl_prover_evidence.hpp"

namespace mdl {
namespace prover {
namespace interface {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	Evidence<A> :: Evidence(Node_* node) :
	mapped_ (false),
	node_ (node),
	complexity_ (0 /*getSubstitution()->getComplexity()*/),
	globalIndex_ (0),
	levelIndex_ (0) {
	}
	template<class A>
	inline
	Evidence<A> :: Evidence(const Evidence_& evidence) :
	mapped_ (evidence.mapped_),
	node_ (evidence.node_) {
	}

	template<class A>
	inline typename Evidence<A> :: Node_*
	Evidence<A> :: getNode() {
		return node_;
	}
	template<class A>
	inline const typename Evidence<A> :: Node_*
	Evidence<A> :: getNode() const {
		return node_;
	}
	template<class A>
	inline index :: Step
	Evidence<A> :: getMaxHeight() const {
		return node_->getMaxHeight();
	}
	template<class A>
	inline index :: Step
	Evidence<A> :: getMinHeight() const {
		return node_->getMinHeight();
	}
	template<class A>
	inline value :: Integer
	Evidence<A> :: getComplexity() const {
		return complexity_;
	}

using manipulator :: mode;
using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: iterate;

	template<class A>
	bool
	Evidence<A> :: hasSameSubstitution (const Evidence_* evidence) const
	{
		const Substitution_* const
			substutution_1 = this->getSubstitution();
		const Substitution_* const
			substutution_2 = evidence->getSubstitution();
		return substutution_1->isIdentical (substutution_2);
	}
	template<class A>
	void
	Evidence<A> :: showInfo (String& string, const int indent) const
	{
		string << iterate << indent << tab << "<evidence" << endLine;
			showKind    (string, indent + 1);
			showHint    (string, indent + 1);
			showProof   (string, indent + 1);
			showTypes   (string, indent + 1);
			showScalars (string, indent + 1);
		string << iterate << indent << tab << ">" << endLine;
			showExpression   (string, indent + 1);
			showSubstitution (string, indent + 1);
		string << iterate << indent << tab << "</evidence>" << endLine;
	}
	template<class A>
	void
	Evidence<A> :: showTree (String& string, const int indent) const
	{
		string << iterate << indent << tab;
		this->show (string);
		if (getUpForking() == 0) {
			string << "()" << endLine;
		} else {
			string << iterate << indent << tab;
			string << "(" << endLine;
			for (value :: Integer i = 0; i < getUpForking(); ++ i) {
				const Evidence* upEvidence = getUp (i);
				upEvidence->showTree (string, indent + 1);
				if (i + 1 < getUpForking()) {
					string << ", ";
				}
				string << endLine;
			}
			string << iterate << indent << tab;
			string << ")" << endLine;
		}
	}
	template<class A>
	void
	Evidence<A> :: dumpInfo () const
	{
		std :: cout << std :: endl;
		String string (1024);
		showInfo (string);
		std :: cout << string << std :: endl;
	}
	template<class A>
	void
	Evidence<A> :: dumpTree () const
	{
		std :: cout << std :: endl;
		String string (1024);
		showTree (string);
		std :: cout << string << std :: endl;
	}
	template<class A>
	void
	Evidence<A> :: dumpProof() const
	{
		std :: cout << std :: endl;
		String string (1024);
		showProof (string);
		std :: cout << string; // << std :: endl;
	}
	template<class A>
	void
	Evidence<A> :: dumpIndex() const
	{
		std :: cout << std :: endl;
		std :: cout << "index = " << globalIndex_ << std :: endl;
	}

	template<class A>
	void
	Evidence<A> :: setMapped (const bool value) const
	{
		mapped_ = value;
		for (value :: Integer i = 0; i < getUpForking(); ++ i) {
			const Evidence_* evidence = getUp (i);
			evidence->setMapped (value);
		}
	}

	template<class A>
	inline bool
	Evidence<A> :: isHint() const
	{
		if (!node_->isHint()) {
			return false;
		}
		for (value :: Integer i = 0; i < getUpForking(); ++ i) {
			const Evidence_* evidence = getUp (i);
			if (!evidence->isHint()) {
				return false;
			}
		}
		return true;
	}

	template<class A>
	bool
	Evidence<A> :: containsUpGlobalIndex (value :: Integer index) const
	{
		if (globalIndex_ == index) {
			return true;
		}
		for (value :: Integer i = 0; i < getUpForking(); ++ i) {
			const Evidence_* evidence = getUp (i);
			if (evidence->containsUpGlobalIndex (index)) {
				return true;
			}
		}
		return false;
	}

	template<class A>
	inline value :: Integer
	Evidence<A> :: getGlobalIndex() const {
		return globalIndex_;
	}
	template<class A>
	inline value :: Integer
	Evidence<A> :: getLevelIndex() const {
		return levelIndex_;
	}
	template<class A>
	inline void
	Evidence<A> :: setGlobalIndex (const value :: Integer globalIndex) {
		globalIndex_ = globalIndex;
	}
	template<class A>
	inline void
	Evidence<A> :: setLevelIndex (const value :: Integer levelIndex) {
		levelIndex_ = levelIndex;
	}

	/****************************
	 *		Protected members
	 ****************************/

	template<class A>
	void
	Evidence<A> :: showGraphInGML
	(
		String& string,
		const value :: Integer index,
		const char* label
	) const
	{
		setMapped (false);
		string << "graph [" << endLine;
		//string << tab << "comment \" ... \"";
		string << tab << "directed 1" << endLine;
		string << tab << "id " << index << endLine;
		string << tab << "label \"" << label << "\"" << endLine;
		string << endLine;
		const Mode mOld (string);
		Mode mNew (mOld);
		mNew.setValue (Mode :: SHOW_IN_GML_GRAPH, false);
		mNew.setValue (Mode :: SHOW_IN_GML, true);
		string << mode << mNew;
		this->show (string);
		string << mode << mOld;
		string << "]" << endLine;
		string << endLine;
		setMapped (false);
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class A>
	void
	Evidence<A> :: showProof (String& string, const int indent) const
	{
		string << iterate << indent << tab;
		string << "proof=\"";
		node_->getTree()->root().block();
		Proof_* proof = const_cast<Evidence_*>(this)->constructProof();
		proof->showAsTerm (string);
		node_->getTree()->root().unblock();
		string << "\" " << endLine;
	}
	template<class A>
	void
	Evidence<A> :: showTypes (String& string, const int indent) const
	{
		string << iterate << indent << tab;
		string << "types=\"";
		Memory :: stack().push(); {
			stack :: Expression* const
				expression = new stack :: Expression (node_->getExpression());
			expression->execute (getSubstitution());
			expression->showTypes (string);
		}
		Memory :: stack().pop();
		string << "\" " << endLine;
	}
	template<class A>
	void
	Evidence<A> :: showScalars (String& string, const int indent) const
	{
		string << iterate << indent << tab;
		string << "node_index=\"" << node_->getGlobalIndex() << "\" " << endLine;
		string << iterate << indent << tab;
		string << "min_height=\"" << getMinHeight() << "\" " << endLine;
		string << iterate << indent << tab;
		string << "cardinality=\"" << getCardinality() << "\" " << endLine;
		string << iterate << indent << tab;
		string << "complexity=\"" << getComplexity() << "\" " << endLine;
	}
	template<class A>
	void
	Evidence<A> :: showKind (String& string, const int indent) const
	{
		string << iterate << indent << tab;
		string << "kind=\"";
		if (dynamic_cast<const evidence :: Hyp<A>*>(this) != NULL) {
			string << "hyp";
		} else if (dynamic_cast<const evidence :: Prop<A>*>(this) != NULL) {
			string << "prop";
		} else if (dynamic_cast<const evidence :: Ref<A>*>(this) != NULL) {
			string << "ref";
		} else if (dynamic_cast<const evidence :: Sub<A>*>(this) != NULL) {
			string << "sub";
		} else if (dynamic_cast<const evidence :: Top<A>*>(this) != NULL) {
			string << "top";
		}
		string << "\"" << endLine;
	}
	template<class A>
	inline void
	Evidence<A> :: showHint (String& string, const int indent) const
	{
		string << iterate << indent << tab;
		string << "hint=\"" << (this->isHint() ? "-" : "+");
		string <<"\" " << endLine;
	}

	template<class A>
	void
	Evidence<A> :: showExpression (String& string, const int indent) const
	{
		string << iterate << indent << tab;
		string << "<expression>";
		string << "<![CDATA[";
		Memory :: stack().push(); {
			stack :: Expression* const
				expression = new stack :: Expression (node_->getExpression());
			expression->execute (getSubstitution());
			string << *expression;
		}
		Memory :: stack().pop();
		string << "]]>";
		string << "</expression>" << endLine;
	}
	template<class A>
	void
	Evidence<A> :: showSubstitution (String& string, const int indent) const
	{
		string << iterate << indent << tab;
		string << "<substitution>";
		string << "<![CDATA[";
		getSubstitution()->show (string);
		string << "]]>";
		string << "</substitution>" << endLine;
	}

	/*********************************
	 *		Overloaded operators
	 *********************************/

	template<class A>
	bool
	operator < (const Evidence<A>& evidence_1, const Evidence<A>& evidence_2)
	{
		const value :: Integer minHeight_1 = evidence_1.getMinHeight();
		const value :: Integer minHeight_2 = evidence_2.getMinHeight();
		if (minHeight_1 < minHeight_2) {
			return true;
		}
		if (minHeight_1 > minHeight_2) {
			return false;
		}
		const value :: Integer cardinality_1 = evidence_1.getCardinality();
		const value :: Integer cardinality_2 = evidence_2.getCardinality();
		if (cardinality_1 < cardinality_2) {
			return true;
		} if (cardinality_1 > cardinality_2) {
			return false;
		}
		const value :: Integer complexity_1 = evidence_1.getComplexity();
		const value :: Integer complexity_2 = evidence_2.getComplexity();
		if (complexity_1 < complexity_2) {
			return true;
		}
		if (complexity_1 > complexity_2) {
			return false;
		}
		return (&evidence_1 < &evidence_2);
	}
	template<class A>
	inline bool
	operator <= (const Evidence<A>& evidence_1, const Evidence<A>& evidence_2) {
		return
			(evidence_1 < evidence_2) ||
			(&evidence_1 == &evidence_2);
	}
	template<class A>
	inline bool
	operator > (const Evidence<A>& evidence_1, const Evidence<A>& evidence_2) {
		return operator < (evidence_2, evidence_1);
	}
	template<class A>
	inline bool
	operator >= (const Evidence<A>& evidence_1, const Evidence<A>& evidence_2) {
		return operator <= (evidence_2, evidence_1);
	}
	template<class A>
	inline bool
	operator == (const Evidence<A>& evidence_1, const Evidence<A>& evidence_2) {
		return (&evidence_1 == &evidence_2);
	}
}
}
}


