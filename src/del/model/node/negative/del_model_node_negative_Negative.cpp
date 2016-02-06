/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_model_node_negative_Negative.cpp                     */
/* Description:     a negative node container                                */
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
namespace negative {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	Negative<A> :: Negative (Model* model) :
	Negative_ (),
	formula_ (NULL),
	nodeVector_ (1) {
	}
	template<class A>
	inline
	Negative<A> :: Negative
	(
		Model* model,
		const Formula* formula,
		const value :: Integer size
	) :
	Negative_ (),
	formula_ (formula),
	nodeVector_ (size) {
	}
	template<class A>
	inline
	Negative<A> :: Negative
	(
		Model* model,
		const Node* node,
		const Formula* formula
	) :
	Negative_ (),
	formula_ (formula),
	nodeVector_ ((node == NULL) ? 0 : 1)
	{
		if (node != NULL) {
			nodeVector_.add (node);
		}
	}
	template<class A>
	inline
	Negative<A> :: Negative
	(
		Model* model,
		const Node* nodes[],
		const value :: Integer size,
		const Formula* formula
	) :
	Negative_ (),
	formula_ (formula),
	nodeVector_ (size)
	{
		for (value :: Integer i = 0; i < size; ++ i) {
			nodeVector_.add (nodes [i]);
		}
	}
	template<class A>
	template<class A1>
	Negative<A> :: Negative (const Negative<A1>& concept, Model* model) :
	Negative_ (concept),
	formula_ (concept.formula_),
	nodeVector_ (concept.nodeVector_) {
	}
	template<class A>
	Negative<A> :: ~ Negative () {
	}

	template<class A>
	inline bool
	Negative<A> :: operator == (const Negative& negative) const
	{
		return
			(formula_ == negative.formula_) &&
			(nodeVector_ == negative.nodeVector_);
	}
	template<class A>
	inline bool
	Negative<A> :: operator != (const Negative& negative) const {
		return !(operator == (negative));
	}

	template<class A>
	inline void
	Negative<A> :: add (const Node* node) {
		nodeVector_.add (node);
	}

	// del :: model :: Negative implementation
	template<class A>
	const del :: Formula*
	Negative<A> :: getFormula() const {
		return formula_;
	}

	// del :: model :: Node implementation
	template<class A>
	bool
	Negative<A> :: isEqual (const Node* node, const Formula* formula) const
	{
		return
			(nodeVector_.getSize() == 1) &&
			(formula_ == formula) &&
			(nodeVector_.getFirstValue() == node);
	}
	template<class A>
	bool
	Negative<A> :: isEqual
	(
		const Node* nodes[],
		const value :: Integer size,
		const Formula* formula
	) const
	{
		if ((size != nodeVector_.getSize()) || (formula_ != formula)) {
			return false;
		}
		for (value :: Integer i = 0; i < nodeVector_.getSize(); ++ i) {
			const Node* node = nodeVector_.getValue (i);
			if (node != nodes [i]) {
				return false;
			}
		}
		return true;
	}
	template<class A>
	bool
	Negative<A> :: fitsUntheory (const del :: set :: Formula* untheory) const
	{
		setFalse();
		setVisited();
		if (formula_ != NULL) {
			const Formula* image = formula_->getImage();
			if (formula_->isRoot() && untheory->contains (image)) {
				goto end;
			}
		}
		for (value :: Integer i = 0; i < nodeVector_.getSize(); ++ i) {
			const Node* node = nodeVector_.getValue (i);
			if (node->isVisited()) {
				if (node->isFalse()) {
					goto end;
				} else {
					continue;
				}
			}
			if (!node->fitsUntheory (untheory)) {
				goto end;
			}
		}
		setTrue();
		end :
		return isTrue();
	}
	template<class A>
	void
	Negative<A> :: showSuccessBranch (set :: Node* visitedNodes) const
	{
		std :: cout << "$$$ NODE = " << (void*)this;
		std :: cout << (isTrue() ? " TRUE" : "FALSE") << " [";
		if (formula_ != NULL) {
			std :: cout << *formula_ << " -> ";
		}
		if (visitedNodes->contains (this)) {
			std :: cout << " --FINAL-- ]" << std :: endl;
		} else {
			visitedNodes->add (this);
			if (nodeVector_.getSize() == 0) {
				std :: cout << "]" << std :: endl;
			}
			for (value :: Integer i = 0; i < nodeVector_.getSize(); ++ i) {
				const Node* node = nodeVector_.getValue (i);
				std :: cout << (void*)node << "(+)";
				if (i < nodeVector_.getSize() - 1) {
					std :: cout << ", ";
				} else {
					std :: cout << "] " << std :: endl;
				}
			}
			for (value :: Integer i = 0; i < nodeVector_.getSize(); ++ i) {
				const Node* node = nodeVector_.getValue (i);
				node->showSuccessBranch (visitedNodes);
			}
		}
	}
	template<class A>
	bool
	Negative<A> :: isEqual (const Node* node, const bool show) const
	{
		const Negative* negative = dynamic_cast<const Negative*>(node);
		if (negative == NULL) {
			if (show) {
				std :: cout << "Inequality in <node :: negative :: Negative> class." << std :: endl;
				std :: cout << "---------------------------------------------------" << std :: endl;
				std :: cout << "Node: " << (void*)node << "does not cast to <Negative>" << std :: endl;
				std :: cout << " -- node 1 = " << *this << std :: endl;
				std :: cout << " -- node 2 = " << *node << std :: endl;
			}
			Node :: setFalse();
		} else {
			if (nodeVector_.getSize() != negative->nodeVector_.getSize()) {
				Node :: setFalse();
				if (show) {
					std :: cout << "Inequality in <node :: negative :: Negative> class." << std :: endl;
					std :: cout << "---------------------------------------------------" << std :: endl;
					std :: cout << "Node vector sizes do not coincide:" << std :: endl;
					std :: cout << " -- size 1 = " << nodeVector_.getSize() << std :: endl;
					std :: cout << " -- size 2 = " << negative->nodeVector_.getSize() << std :: endl;
					std :: cout << std :: endl;
					std :: cout << " -- node 1 = " << *this << std :: endl;
					std :: cout << " -- node 2 = " << *node << std :: endl;
				}
			} else if (formula_ != negative->formula_) {
				if (show) {
					std :: cout << "Inequality in <node :: negative :: Negative> class." << std :: endl;
					std :: cout << "---------------------------------------------------" << std :: endl;
					std :: cout << "Formula image does not coincide:" << std :: endl;
					std :: cout << " -- formula 1 = " << *formula_ << std :: endl;
					std :: cout << " -- formula 2 = " << *negative->formula_ << std :: endl;
					std :: cout << std :: endl;
					std :: cout << " -- node 1 = " << *this << std :: endl;
					std :: cout << " -- node 2 = " << *node << std :: endl;
				}
				Node :: setFalse();
			} else {
				for (value :: Integer i = 0; i < nodeVector_.getSize(); ++ i) {
					const Node* node_1 = nodeVector_.getValue (i);
					const Node* node_2 = negative->nodeVector_.getValue (i);
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
	Negative<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Negative<A> :: getSizeOf() const {
		return sizeof (Negative);
	}
	template<class A>
	Size_t
	Negative<A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += nodeVector_.getVolume();
		volume += Node :: getVolume();
		return volume;
	}
	template<class A>
	void
	Negative<A> :: show (String& string) const
	{
		string << "(-) = " << (void*)this << " [";
		if (formula_ != NULL) {
			string << *formula_ << " -> ";
		}
		for (value :: Integer i = 0; i < nodeVector_.getSize(); ++ i) {
			const Node* node = nodeVector_.getValue (i);
			string << "node: " << (void*)node;
			if (i < nodeVector_.getSize() - 1) {
				string << ", ";
			}
		}
		string << "] ";
		if (Node :: getInterpolant() != NULL) {
			string << "interpolant = " << *Node :: getInterpolant();
		}
	}

	/****************************
	 *		Protected members
	 ****************************/

	template<class A>
	void
	Negative<A> :: cloneNodeVector (model :: Model* model) const
	{
		for (value :: Integer i = 0; i < nodeVector_.getSize(); ++ i) {
			const Node* node = nodeVector_.getValue (i);
			Node* cloned = node->clone (model);
			dynamic_cast<Negative*>(Node :: clone_)->add (cloned);
		}
	}
}
}
}
}


