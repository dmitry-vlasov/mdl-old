/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_model_node_positive_Singleton.cpp                    */
/* Description:     a positive node - singleton (concept)                    */
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
	Singleton<A> :: Singleton () :
	Positive_ (NULL, 0),
	variable_ () {
	}
	template<class A>
	inline
	Singleton<A> :: Singleton
	(
		Model* model,
		const Symbol variable,
		const value :: Integer size
	) :
	Positive_ (model, size),
	variable_ (variable)
	{
		if (model != NULL) {
			model->registerNode (this);
		}
	}
	template<class A>
	inline
	Singleton<A> :: Singleton
	(
		Model* model,
		const Symbol variable,
		const Node* node,
		const Formula* formula
	) :
	Positive_ (model, node, formula),
	variable_ (variable)
	{
		const Node* n = NULL;
		if (node == NULL) {
			if (variable.isTop()) {
				n = new typename Positive_ :: Top_ (model);
			} else{
				n = new typename Positive_ :: Id_ (model, variable);
			}
		} else {
			n = Positive_ :: createNode (node, formula);
		}
		Positive_ :: nodeVector_.add (n);
		if (model != NULL) {
			model->registerNode (this);
		}
	}
	template<class A>
	inline
	Singleton<A> :: Singleton
	(
		Model* model,
		const Symbol variable,
		const Node* nodes[],
		const value :: Integer size,
		const Formula* formula
	) :
	Positive_ (model, nodes, size, formula),
	variable_ (variable)
	{
		if (size > 0) {
			const Node* n = Positive_ :: createNode (nodes, size, formula);
			Positive_ :: nodeVector_.add (n);
		}
		if (model != NULL) {
			model->registerNode (this);
		}
	}
	template<class A>
	template<class A1>
	Singleton<A> :: Singleton (const Singleton<A1>& concept, Model* model) :
	Positive_ (concept, model),
	variable_ (concept.variable_)
	{
		if (model != NULL) {
			model->registerNode (this);
		}
	}
	template<class A>
	Singleton<A> :: ~ Singleton () {
	}

	template<class A>
	inline bool
	Singleton<A> :: isEqual (const Symbol variable) const {
		return (variable_ == variable);
	}

	template<class A>
	inline bool
	Singleton<A> :: operator == (const Singleton& concept) const {
		return (variable_ == concept.variable_);
	}
	template<class A>
	inline bool
	Singleton<A> :: operator != (const Singleton& concept) const {
		return !(operator == (concept));
	}
	template<class A>
	inline bool
	Singleton<A> :: operator < (const Singleton& concept) const {
		return (variable_ < concept.variable_);
	}
	template<class A>
	inline bool
	Singleton<A> :: operator > (const Singleton& concept) const {
		return (variable_ > concept.variable_);
	}
	template<class A>
	inline bool
	Singleton<A> :: operator <= (const Singleton& concept) const {
		return (variable_ <= concept.variable_);
	}
	template<class A>
	inline bool
	Singleton<A> :: operator >= (const Singleton& concept) const {
		return (variable_ >= concept.variable_);
	}

	template<class A>
	inline bool
	Singleton<A> :: operator == (const Symbol variable) const {
		return (variable_ == variable);
	}
	template<class A>
	inline bool
	Singleton<A> :: operator != (const Symbol variable) const {
		return !(operator == (variable));
	}
	template<class A>
	inline bool
	Singleton<A> :: operator < (const Symbol variable) const {
		return (variable_ < variable);
	}
	template<class A>
	inline bool
	Singleton<A> :: operator > (const Symbol variable) const {
		return (variable_ > variable);
	}
	template<class A>
	inline bool
	Singleton<A> :: operator <= (const Symbol variable) const {
		return (variable_ <= variable);
	}
	template<class A>
	inline bool
	Singleton<A> :: operator >= (const Symbol variable) const {
		return (variable_ >= variable);
	}

	template<class A>
	inline void
	Singleton<A> :: setSymbol (const Symbol variable) {
		variable_ = variable;
	}

	// del :: model :: Positive interface
	template<class A>
	Symbol
	Singleton<A> :: getVariable() const {
		return variable_;
	}
	template<class A>
	pair :: Symbol
	Singleton<A> :: getPair() const {
		return pair :: Symbol();
	}

	// del :: model :: Node implementation
	template<class A>
	bool
	Singleton<A> :: isEqual (const Node* node, const Formula* formula) const {
		return Positive_ :: isEqual (node, formula);
	}
	template<class A>
	bool
	Singleton<A> :: isEqual
	(
		const Node* nodes[],
		const value :: Integer size,
		const Formula* formula
	) const {
		return Positive_ :: isEqual (nodes, size, formula);
	}
	template<class A>
	bool
	Singleton<A> :: fitsUntheory (const del :: set :: Formula* untheory) const {
		return Positive_ :: fitsUntheory (untheory);
	}
	template<class A>
	void
	Singleton<A> :: showSuccessBranch (set :: Node* visitedNodes) const
	{
		std :: cout << "$$$ CONCEPT = " << (void*)this;
		std :: cout << (Node :: isTrue() ? " TRUE" : "FALSE") << " [";
		std :: cout << variable_ << " -> ";
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

				}
			}
			std :: cout << "] " << std :: endl;
			for (value :: Integer i = 0; i < Positive_ :: nodeVector_.getSize(); ++ i) {
				const Node* node = Positive_ :: nodeVector_.getValue (i);
				if (node->isTrue()) {
					node->showSuccessBranch (visitedNodes);
				}
			}
		}
	}
	template<class A>
	const Term*
	Singleton<A> :: evalInterpolant (const Signature* delta) const {
		return Positive_ :: evalInterpolant (delta);
	}
	template<class A>
	model :: Node*
	Singleton<A> :: clone (model :: Model* model) const
	{
		if (Node :: clone_ == NULL) {
			Node :: clone_ = new Singleton
			(
				model,
				variable_,
				Positive_ :: nodeVector_.getSize()
			);
			Positive_ :: cloneNodeVector (model);
		}
		return Node :: clone_;
	}
	template<class A>
	bool
	Singleton<A> :: isEqual (const Node* node, const bool show) const
	{
		if (!Node :: isVisited()) {
			Node :: setTrue();
			Node :: setVisited();
			if (Positive_ :: isEqual (node, show)) {
				const Singleton* positive = dynamic_cast<const Singleton*>(node);
				if (positive == NULL) {
					if (show) {
						std :: cout << "Inequality in <node :: positive :: Singleton> class." << std :: endl;
						std :: cout << "----------------------------------------------------" << std :: endl;
						std :: cout << "Node: " << (void*)node << "does not cast to <Negative>" << std :: endl;
						std :: cout << " -- node 1 = " << *this << std :: endl;
						std :: cout << " -- node 2 = " << *node << std :: endl;
						std :: cout << std :: endl;
						std :: cout << " -- node 1 = " << *this << std :: endl;
						std :: cout << " -- node 2 = " << *node << std :: endl;
					}
					Node :: setFalse();
				} else {
					if (variable_ != positive->variable_) {
						if (show) {
							std :: cout << "Inequality in <node :: positive :: Singleton> class." << std :: endl;
							std :: cout << "----------------------------------------------------" << std :: endl;
							std :: cout << "Concepts do not coincide:" << std :: endl;
							std :: cout << " -- concept 1 = " << variable_ << std :: endl;
							std :: cout << " -- concept 2 = " << positive->variable_ << std :: endl;
							std :: cout << std :: endl;
							std :: cout << " -- node 1 = " << *this << std :: endl;
							std :: cout << " -- node 2 = " << *node << std :: endl;
						}
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
	Singleton<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Singleton<A> :: getSizeOf() const {
		return sizeof (Singleton);
	}
	template<class A>
	Size_t
	Singleton<A> :: getVolume() const {
		return Positive_ :: getVolume();
	}
	template<class A>
	void
	Singleton<A> :: show (String& string) const
	{
		string << "singleton (+) = " << (void*)this << " [";
		string << variable_ << " -> ";
		Positive_ :: show (string);
		string << "]";
	}
}
}
}
}


