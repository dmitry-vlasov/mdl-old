/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_model_node_positive_Positive.hpp                     */
/* Description:     a positive node - concept                                */
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
	Positive<A> :: Positive
	(
		Model* model,
		const value :: Integer size
	) :
	Positive_ (),
	model_ (model),
	nodeVector_ (size) {
	}
	template<class A>
	inline
	Positive<A> :: Positive
	(
		Model* model,
		const Node* node,
		const Formula* formula
	) :
	Positive_ (),
	model_ (model),
	nodeVector_ (1) {
	}
	template<class A>
	inline
	Positive<A> :: Positive
	(
		Model* model,
		const Node* nodes[],
		const value :: Integer size,
		const Formula* formula
	) :
	Positive_ (),
	model_ (model),
	nodeVector_ ((size == 0) ? 0 : 1) {
	}
	template<class A>
	template<class A1>
	Positive<A> :: Positive (const Positive<A1>& node, Model* model) :
	Positive_ (node),
	model_ (model),
	nodeVector_ (node.nodeVector_) {
	}
	template<class A>
	Positive<A> :: ~ Positive () {
	}

	template<class A>
	inline void
	Positive<A> :: add (const Node* node) {
		nodeVector_.add (node);
	}
	template<class A>
	bool
	Positive<A> :: addNode (const Node* node, const Formula* formula) const
	{
		for (value :: Integer i = 0; i < nodeVector_.getSize(); ++ i) {
			const Node* n = nodeVector_.getValue (i);
			if (n->isEqual (node, formula)) {
				return false;
			}
		}
		const Node* n = createNode (node, formula);
		nodeVector_.add (n);
		return true;
	}
	template<class A>
	bool
	Positive<A> :: addNode
	(
		const Node* nodes[],
		const value :: Integer size,
		const Formula* formula
	) const
	{
		for (value :: Integer i = 0; i < nodeVector_.getSize(); ++ i) {
			const Node* n = nodeVector_.getValue (i);
			if (n->isEqual (nodes, size, formula)) {
				return false;
			}
		}
		const Node* n = createNode (nodes, size, formula);
		nodeVector_.add (n);
		return true;
	}

	// del :: model :: Node implementation
	template<class A>
	bool
	Positive<A> :: isEqual (const Node* node, const Formula* formula) const
	{
		for (value :: Integer i = 0; i < nodeVector_.getSize(); ++ i) {
			const Node* n = nodeVector_.getValue (i);
			if (n->isEqual (node, formula)) {
				return true;
			}
		}
		return false;
	}
	template<class A>
	bool
	Positive<A> :: isEqual
	(
		const Node* nodes[],
		const value :: Integer size,
		const Formula* formula
	) const
	{
		for (value :: Integer i = 0; i < nodeVector_.getSize(); ++ i) {
			const Node* n = nodeVector_.getValue (i);
			if (n->isEqual (nodes, size, formula)) {
				return true;
			}
		}
		return false;
	}
	template<class A>
	bool
	Positive<A> :: fitsUntheory (const del :: set :: Formula* untheory) const
	{
		Node :: setFalse();
		for (value :: Integer i = 0; i < nodeVector_.getSize(); ++ i) {
			const Node* node = nodeVector_.getValue (i);
			if (node->isVisited()) {
				if (node->isTrue()) {
					Node :: setTrue();
					break;
				} else {
					continue;
				}
			}
			if (node->fitsUntheory (untheory)) {
				Node :: setTrue();
				break;
			}
		}
		Node :: setVisited();
		return Node :: isTrue();
	}
	template<class A>
	void
	Positive<A> :: showSuccessBranch (set :: Node* visitedNodes) const
	{
		/*std :: cout << (Node :: isTrue() ? " TRUE" : "FALSE") << " [";
		if (variable_ == value :: TOP) {
			std :: cout << Token :: top_;
		} else {
			std :: cout << Table :: variables()->get (variable_);
		}
		std :: cout << " -> ";
		if (visitedNodes->contains (this)) {
			std :: cout << " --FINAL-- ";
		} else {
			visitedNodes->add (this);
			for (value :: Integer i = 0; i < nodeVector_.getSize(); ++ i) {
				const Node* node = nodeVector_.getValue (i);
				std :: cout << " node: " << (void*)node;
				if (node->isTrue()) {
					std :: cout << "(+)";
				}
				if (i < nodeVector_.getSize() - 1) {
					std :: cout << ", ";
				} else {

				}
			}
			std :: cout << "] " << std :: endl;
			for (value :: Integer i = 0; i < nodeVector_.getSize(); ++ i) {
				const Node* node = nodeVector_.getValue (i);
				if (node->isTrue()) {
					node->showSuccessBranch (visitedNodes);
				}
			}
		}*/
	}
	template<class A>
	const Term*
	Positive<A> :: evalInterpolant (const Signature* delta) const
	{
		if (Node :: isVisited()) {
			return Node :: getInterpolant();
		}
		const Term* interpolant = NULL;
		for (value :: Integer i = 0; i < nodeVector_.getSize(); ++ i) {
			const Node* node = nodeVector_.getValue (i);
			interpolant = node->evalInterpolant (delta);
			if (interpolant != NULL) {
				interpolant = interpolant->clone();
				break;
			}
		}
		Node :: setInterpolant (interpolant);
		Node :: setVisited();
		return interpolant;
	}
	template<class A>
	bool
	Positive<A> :: isEqual (const Node* node, const bool show) const
	{
		const Positive* positive = dynamic_cast<const Positive*>(node);
		if (positive == NULL) {
			if (show) {
				std :: cout << "Inequality in <node :: positive :: Positive> class." << std :: endl;
				std :: cout << "---------------------------------------------------" << std :: endl;
				std :: cout << "Node: " << (void*)node << "does not cast to <Positive>" << std :: endl;
				std :: cout << " -- node 1 = " << *this << std :: endl;
				std :: cout << " -- node 2 = " << *node << std :: endl;
			}
			Node :: setFalse();
		} else {
			if (nodeVector_.getSize() != positive->nodeVector_.getSize()) {
				if (show) {
					std :: cout << "Inequality in <node :: positive :: Positive> class." << std :: endl;
					std :: cout << "---------------------------------------------------" << std :: endl;
					std :: cout << "Node vector sizes do not coincide:" << std :: endl;
					std :: cout << " -- size 1 = " << nodeVector_.getSize() << std :: endl;
					std :: cout << " -- size 2 = " << positive->nodeVector_.getSize() << std :: endl;
					std :: cout << std :: endl;
					std :: cout << " -- node 1 = " << *this << std :: endl;
					std :: cout << " -- node 2 = " << *node << std :: endl;
				}
				Node :: setFalse();
			} else {
				for (value :: Integer i = 0; i < nodeVector_.getSize(); ++ i) {
					const Node* node_1 = nodeVector_.getValue (i);
					const Node* node_2 = positive->nodeVector_.getValue (i);
					if (!node_1->isEqual (node_2)) {
						Node :: setFalse();
					}
				}
			}
		}
		return Node :: isTrue();
	}

	// del :: Object implementation
	template<class A>
	void
	Positive<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Positive<A> :: getSizeOf() const {
		return sizeof (Positive);
	}
	template<class A>
	Size_t
	Positive<A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += Node :: getVolume();
		volume += nodeVector_.getVolume();
		return volume;
	}
	template<class A>
	void
	Positive<A> :: show (String& string) const
	{
		for (value :: Integer i = 0; i < nodeVector_.getSize(); ++ i) {
			const Node* node = nodeVector_.getValue (i);
			string << " node: " << (void*)node;
			if (i < nodeVector_.getSize() - 1) {
				string << ", ";
			}
		}
	}

	/****************************
	 *		Protected members
	 ****************************/

	template<class A>
	const Node*
	Positive<A> :: createNode (const Node* node, const Formula* formula) const
	{
		switch (formula->getKind()) {
		case Formula :: SIMPLE_SUB_KIND :
			return new Simple_ (model_, node, formula);
		case Formula :: CONJ_SUB_KIND :
			return new Conjunction_ (model_, node, formula);
		case Formula :: LEFT_SUB_KIND :
			return new ExistsLeft_ (model_, node, formula);
		case Formula :: RIGHT_SUB_KIND :
			return new ExistsRight_ (model_, node, formula);
		default :
			return NULL;
		}
	}
	template<class A>
	const Node*
	Positive<A> :: createNode
	(
		const Node* nodes[],
		const value :: Integer size,
		const Formula* formula
	) const
	{
		switch (formula->getKind()) {
		case Formula :: SIMPLE_SUB_KIND :
			return new Simple_ (model_, nodes, size, formula);
		case Formula :: CONJ_SUB_KIND :
			return new Conjunction_ (model_, nodes, size, formula);
		case Formula :: LEFT_SUB_KIND :
			return new ExistsLeft_ (model_, nodes, size, formula);
		case Formula :: RIGHT_SUB_KIND :
			return new ExistsRight_ (model_, nodes, size, formula);
		default :
			return NULL;
		}
	}

	template<class A>
	void
	Positive<A> :: cloneNodeVector (model :: Model* model) const
	{
		for (value :: Integer i = 0; i < nodeVector_.getSize(); ++ i) {
			const Node* node = nodeVector_.getValue (i);
			Node* cloned = node->clone (model);
			dynamic_cast<Positive*>(Node :: clone_)->add (cloned);
		}
	}
}
}
}
}


