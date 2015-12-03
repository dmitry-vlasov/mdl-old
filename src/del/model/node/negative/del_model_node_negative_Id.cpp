/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_model_node_negative_Id.cpp                           */
/* Description:     a negative node container of type: a \equiv a            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_MODEL_NODE_NEGATIVE_ID_CPP_
#define DEL_MODEL_NODE_NEGATIVE_ID_CPP_

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
	Id<A> :: Id (Model* model, const Symbol variable) :
	Negative_ (model),
	variable_ (variable)
	{
		if (model != NULL) {
			model->registerNode (this);
		}
	}
	template<class A>
	inline
	Id<A> :: Id (Model* model, const Symbol variable, const value :: Integer size) :
	Negative_ (model, NULL, size),
	variable_ (variable)
	{
		if (model != NULL) {
			model->registerNode (this);
		}
	}
	template<class A>
	template<class A1>
	Id<A> :: Id (const Id<A1>& node, Model* model) :
	Negative_ (node, model),
	variable_ (node.variable_)
	{
		if (model != NULL) {
			model->registerNode (this);
		}
	}
	template<class A>
	Id<A> :: ~ Id () {
	}

	// del :: model :: Node implementation
	template<class A>
	const Term*
	Id<A> :: evalInterpolant (const Signature* delta) const
	{
		if (Node :: isVisited()) {
			return Node :: getInterpolant();
		}
		Node :: setInterpolant (NULL);

		// let formula be:   a ⊑ a
		const Term* interpolant = NULL;
		if (delta->containsSymbol (variable_)) {
			interpolant = new source :: term :: Variable (variable_);
		}
		Node :: setInterpolant (interpolant);
		Node :: setVisited();
		return interpolant;
	}
	template<class A>
	model :: Node*
	Id<A> :: clone (model :: Model* model) const
	{
		if (Node :: clone_ == NULL) {
			Node :: clone_ = new Id
			(
				model,
				variable_,
				Negative_ :: nodeVector_.getSize()
			);
			Negative_ :: cloneNodeVector (model);
		}
		return Node :: clone_;
	}
	template<class A>
	bool
	Id<A> :: isEqual (const Node* node, const bool show) const
	{
		if (!Node :: isVisited()) {
			Node :: setTrue();
			Node :: setVisited();
			if (Negative_ :: isEqual (node, show)) {
				const Id* id = dynamic_cast<const Id*>(node);
				if (id == NULL) {
					if (show) {
						std :: cout << "Inequality in <node :: negative :: Id> class." << std :: endl;
						std :: cout << "---------------------------------------------" << std :: endl;
						std :: cout << "Node: " << (void*)node << "does not cast to <Id>" << std :: endl;
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
	Id<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Id<A> :: getSizeOf() const {
		return sizeof (Id);
	}
	template<class A>
	Size_t
	Id<A> :: getVolume() const {
		return Negative_ :: getVolume();
	}
	template<class A>
	void
	Id<A> :: show (String& string) const
	{
		//string << "id " << variable_ << " ";
		//Negative_ :: show (string);

		string << "id (-) = " << (void*)this << " [";
		string << variable_ <<  " ⊑ " << variable_ <<  " -> ";
		string << "] ";
		if (Node :: getInterpolant() != NULL) {
			string << "interpolant = " << *Node :: getInterpolant();
		}
	}
}
}
}
}

#endif /*DEL_MODEL_NODE_NEGATIVE_ID_CPP_*/
