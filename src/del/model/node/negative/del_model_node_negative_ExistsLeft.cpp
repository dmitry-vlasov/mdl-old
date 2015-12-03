/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_model_node_negative_ExistsLeft.cpp                   */
/* Description:     a negative node container of type: left exists           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_MODEL_NODE_NEGATIVE_EXISTS_LEFT_CPP_
#define DEL_MODEL_NODE_NEGATIVE_EXISTS_LEFT_CPP_

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
	ExistsLeft<A> :: ExistsLeft (Model* model) :
	Negative_ (model)
	{
		if (model != NULL) {
			model->registerNode (this);
		}
	}
	template<class A>
	inline
	ExistsLeft<A> :: ExistsLeft
	(
		Model* model,
		const Formula* formula,
		const value :: Integer size
	) :
	Negative_ (model, formula, size)
	{
		if (model != NULL) {
			model->registerNode (this);
		}
	}
	template<class A>
	inline
	ExistsLeft<A> :: ExistsLeft
	(
		Model* model,
		const Node* node,
		const Formula* formula
	) :
	Negative_ (model, node, formula)
	{
		if (model != NULL) {
			model->registerNode (this);
		}
	}
	template<class A>
	inline
	ExistsLeft<A> :: ExistsLeft
	(
		Model* model,
		const Node* nodes[],
		const value :: Integer size,
		const Formula* formula
	) :
	Negative_ (model, nodes, size, formula)
	{
		if (model != NULL) {
			model->registerNode (this);
		}
	}
	template<class A>
	template<class A1>
	ExistsLeft<A> :: ExistsLeft (const ExistsLeft<A1>& node, Model* model) :
	Negative_ (node, model)
	{
		if (model != NULL) {
			model->registerNode (this);
		}
	}
	template<class A>
	ExistsLeft<A> :: ~ ExistsLeft () {
	}

	// del :: model :: Node implementation
	template<class A>
	const Term*
	ExistsLeft<A> :: evalInterpolant (const Signature* delta) const
	{
		if (Node :: isVisited()) {
			return Node :: getInterpolant();
		}
		Node :: setInterpolant (NULL);
		Node :: setVisited();

		// let formula be:   ∃r.a ⊑ b
		const del :: Term* term_0 = Negative_ :: formula_->getTerm (0);
		const del :: Term* term_1 = Negative_ :: formula_->getTerm (1);
		const del :: Term* interpolant = NULL;
		if (term_0->isOfSignature (delta)) {
			interpolant = term_0->clone();
		} else if (term_1->isOfSignature (delta)) {
			interpolant = term_1->clone();
		} else {
			const Node* node_0 = Negative_ :: nodeVector_.getValue (0);
			interpolant = node_0->evalInterpolant (delta);
			if (interpolant == NULL) {
				const Node* node_1 = Negative_ :: nodeVector_.getValue (1);
				interpolant = node_1->evalInterpolant (delta);
				if (interpolant != NULL) {
					const value :: Relation r = Negative_ :: formula_->getTerm (0)->getSymbol().getRelation();
					interpolant = new source :: term :: Exists (r, interpolant->clone());
				}
			} else {
				interpolant = interpolant->clone();
			}
		}
		Node :: setInterpolant (interpolant);
		return interpolant;
	}
	template<class A>
	model :: Node*
	ExistsLeft<A> :: clone (model :: Model* model) const
	{
		if (Node :: clone_ == NULL) {
			Node :: clone_ = new ExistsLeft
			(
				model,
				Negative_ :: formula_,
				Negative_ :: nodeVector_.getSize()
			);
			Negative_ :: cloneNodeVector (model);
		}
		return Node :: clone_;
	}
	template<class A>
	bool
	ExistsLeft<A> :: isEqual (const Node* node, const bool show) const
	{
		if (!Node :: isVisited()) {
			Node :: setTrue();
			Node :: setVisited();
			if (Negative_ :: isEqual (node, show)) {
				const ExistsLeft* existsLeft = dynamic_cast<const ExistsLeft*>(node);
				if (existsLeft == NULL) {
					if (show) {
						std :: cout << "Inequality in <node :: negative :: ExistsLeft> class." << std :: endl;
						std :: cout << "-----------------------------------------------------" << std :: endl;
						std :: cout << "Node: " << (void*)node << "does not cast to <ExistsLeft>" << std :: endl;
						std :: cout << " -- node 1 = " << *this << std :: endl;
						std :: cout << " -- node 2 = " << *node << std :: endl;
					}
					Node :: setFalse();
				}
			}
		}
		return Node :: isTrue();
	}

	// del :: Object implementation
	template<class A>
	void
	ExistsLeft<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	ExistsLeft<A> :: getSizeOf() const {
		return sizeof (ExistsLeft);
	}
	template<class A>
	Size_t
	ExistsLeft<A> :: getVolume() const {
		return Negative_ :: getVolume();
	}
	template<class A>
	void
	ExistsLeft<A> :: show (String& string) const
	{
		string << "exists left ";
		Negative_ :: show (string);
	}
}
}
}
}

#endif /*DEL_MODEL_NODE_NEGATIVE_EXISTS_LEFT_CPP_*/
