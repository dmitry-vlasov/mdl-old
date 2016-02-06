/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_model_node_positive_Pair.cpp                         */
/* Description:     a positive node - pair of concepts                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/interface/del_interface.hpp"

namespace del {
namespace model {
namespace node {
namespace positive {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	Pair<A> :: Pair () :
	Positive_ (NULL, 0),
	variable_1_ (),
	variable_2_ () {
	}
	template<class A>
	inline
	Pair<A> :: Pair
	(
		Model* model,
		const Symbol variable_1,
		const Symbol variable_2,
		const value :: Integer size
	) :
	Positive_ (model, size),
	variable_1_ (variable_1),
	variable_2_ (variable_2)
	{
		if (model != NULL) {
			model->registerNode (this);
		}
	}
	template<class A>
	inline
	Pair<A> :: Pair
	(
		Model* model,
		const Symbol variable_1,
		const Symbol variable_2,
		const Node* node,
		const Formula* formula
	) :
	Positive_ (model, node, formula),
	variable_1_ (variable_1),
	variable_2_ (variable_2)
	{
		if (node != NULL) {
			const Node* n = Positive_ :: createNode (node, formula);
			Positive_ :: nodeVector_.add (n);
		}
		if (model != NULL) {
			model->registerNode (this);
		}
	}
	template<class A>
	template<class A1>
	Pair<A> :: Pair (const Pair<A1>& pair, Model* model) :
	Positive_ (pair, model),
	variable_1_ (pair.variable_1_),
	variable_2_ (pair.variable_2_)
	{
		if (model != NULL) {
			model->registerNode (this);
		}
	}
	template<class A>
	Pair<A> :: ~ Pair () {
	}

	template<class A>
	inline bool
	Pair<A> :: isEqual
	(
		const Symbol variable_1,
		const Symbol variable_2
	) const {
		return (variable_1_ == variable_1) && (variable_2_ == variable_2);
	}
	template<class A>
	template<class A1>
	inline void
	Pair<A> :: operator = (const Pair<A1>& pair)
	{
		variable_1_ = pair.variable_1_;
		variable_2_ = pair.variable_2_;
		Positive_ :: operator = (pair);
	}

	template<class A>
	inline bool
	Pair<A> :: operator == (const Pair& pair) const
	{
		return
			(variable_1_ == pair.variable_1_) &&
			(variable_2_ == pair.variable_2_);
	}
	template<class A>
	inline bool
	Pair<A> :: operator != (const Pair& pair) const {
		return !operator == (pair);
	}
	template<class A>
	inline bool
	Pair<A> :: operator < (const Pair& pair) const
	{
		return
			(variable_1_ < pair.variable_1_) ||
			(
				(variable_1_ == pair.variable_1_) &&
				(variable_2_ < pair.variable_2_)
			);
	}
	template<class A>
	inline bool
	Pair<A> :: operator > (const Pair& pair) const {
		return pair.operator < (*this);
	}

	template<class A>
	inline Symbol
	Pair<A> :: getFirst() const {
		return variable_1_;
	}
	template<class A>
	inline Symbol
	Pair<A> :: getSecond() const {
		return variable_2_;
	}

	template<class A>
	inline void
	Pair<A> :: setFirst (const Symbol variable_1) {
		variable_1_ = variable_1;
	}
	template<class A>
	inline void
	Pair<A> :: setSecond (const Symbol variable_2) {
		variable_2_ = variable_2;
	}

	// del :: model :: Positive interface
	template<class A>
	Symbol
	Pair<A> :: getVariable() const {
		return Undefined<Symbol> :: getValue();
	}
	template<class A>
	pair :: Symbol
	Pair<A> :: getPair() const {
		return pair :: Symbol (variable_1_, variable_2_);
	}

	// del :: model :: Node implementation
	template<class A>
	bool
	Pair<A> :: isEqual (const Node* node, const Formula* formula) const {
		return Positive_ :: isEqual (node, formula);
	}
	template<class A>
	bool
	Pair<A> :: isEqual
	(
		const Node* nodes[],
		const value :: Integer size,
		const Formula* formula
	) const {
		return Positive_ :: isEqual (nodes, size, formula);
	}
	template<class A>
	bool
	Pair<A> :: fitsUntheory (const del :: set :: Formula* untheory) const {
		return Positive_ :: fitsUntheory (untheory);
	}
	template<class A>
	void
	Pair<A> :: showSuccessBranch (set :: Node* visitedNodes) const
	{
		std :: cout << "$$$ PAIR = " << (void*)this;
		std :: cout << (Node :: isTrue() ? " TRUE" : "FALSE") << " [";
		std :: cout << "(" << variable_1_ << ", " << variable_2_ << ")";
		std :: cout << " -> ";
		if (visitedNodes->contains (this)) {
			std :: cout << " --FINAL-- ]" << std :: endl;
		} else {
			visitedNodes->add (this);
			for (value :: Integer i = 0; i < Positive_ :: nodeVector_.getSize(); ++ i) {
				const Node* node = Positive_ :: nodeVector_.getValue (i);
				std :: cout << " node: " << (void*)node;
				if (node->isTrue()) {
					std :: cout << "(+)";
				}
				if (i < Positive_ :: nodeVector_.getSize() - 1) {
					std :: cout << ", ";
				} else {
					std :: cout << "] " << std :: endl;
				}
			}
			for (value :: Integer i = 0; i < Positive_ :: nodeVector_.getSize(); ++ i) {
				const Node* node = Positive_ :: nodeVector_.getValue (i);
				if (node->isTrue()) {
					node->showSuccessBranch (visitedNodes);
					break;
				}
			}
		}
	}
	template<class A>
	const Term*
	Pair<A> :: evalInterpolant (const Signature* delta) const {
		return NULL;
	}
	template<class A>
	model :: Node*
	Pair<A> :: clone (model :: Model* model) const
	{
		if (Node :: clone_ == NULL) {
			Node :: clone_ = new Pair
			(
				model,
				variable_1_,
				variable_2_,
				Positive_ :: nodeVector_.getSize()
			);
			Positive_ :: cloneNodeVector (model);
		}
		return Node :: clone_;
	}
	template<class A>
	bool
	Pair<A> :: isEqual (const Node* node, const bool show) const
	{
		if (!Node :: isVisited()) {
			Node :: setTrue();
			if (Positive_ :: isEqual (node, show)) {
				const Pair* pair = dynamic_cast<const Pair*>(node);
				if (pair == NULL) {
					if (show) {
						std :: cout << "Inequality in <node :: positive :: Pair> class." << std :: endl;
						std :: cout << "-----------------------------------------------" << std :: endl;
						std :: cout << "Node: " << (void*)node << "does not cast to <Pair>" << std :: endl;
						std :: cout << " -- node 1 = " << *this << std :: endl;
						std :: cout << " -- node 2 = " << *node << std :: endl;
					}
					Node :: setFalse();
				} else {
					if ((variable_1_ != pair->variable_1_) ||
						(variable_2_ != pair->variable_2_)) {
						if (show) {
							std :: cout << "Inequality in <node :: positive :: Pair> class." << std :: endl;
							std :: cout << "-----------------------------------------------" << std :: endl;
							std :: cout << "Pairs do not coincide:" << std :: endl;
							std :: cout << " -- pair 1 = (" << variable_1_ << ", " << variable_1_ << ")" << std :: endl;
							std :: cout << " -- pair 2 = (" << pair->variable_1_ << ", " << pair->variable_1_ << ")" << std :: endl;
							std :: cout << std :: endl;
							std :: cout << " -- node 1 = " << *this << std :: endl;
							std :: cout << " -- node 2 = " << *node << std :: endl;
						}
						Node :: setFalse();
					}
				}
			}
			Node :: setVisited();
		}
		return Node :: isTrue();
	}

	// del :: Object implementation
	template<class A>
	void
	Pair<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Pair<A> :: getSizeOf() const {
		return sizeof (Pair);
	}
	template<class A>
	Size_t
	Pair<A> :: getVolume() const {
		return Positive_ :: getVolume();
	}
	template<class A>
	void
	Pair<A> :: show (String& string) const
	{
		Mode mode (string);
		if (mode.getValue (Mode :: SHOW_NODES)) {
			string << "pair (+) = " << (void*)this << " [ ";
			string << "(" << variable_1_ << ", " << variable_2_ << ")";
			string << " -> ";
			Positive_ :: show (string);
			string << "]";
		} else {
			string << "(" << variable_1_ << ", " << variable_2_ << ")";
		}
	}
}
}
}
}


