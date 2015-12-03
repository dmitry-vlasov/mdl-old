/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_model_node_negative_Top.cpp                          */
/* Description:     a negative node container of type: a \subseteq \top      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_MODEL_NODE_NEGATIVE_TOP_CPP_
#define DEL_MODEL_NODE_NEGATIVE_TOP_CPP_

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
	Top<A> :: Top (Model* model) :
	Negative_ (model)
	{
		if (model != NULL) {
			model->registerNode (this);
		}
	}
	template<class A>
	inline
	Top<A> :: Top (Model* model, const value :: Integer size) :
	Negative_ (model, NULL, size)
	{
		if (model != NULL) {
			model->registerNode (this);
		}
	}
	template<class A>
	template<class A1>
	Top<A> :: Top (const Top<A1>& node, Model* model) :
	Negative_ (node, model)
	{
		if (model != NULL) {
			model->registerNode (this);
		}
	}
	template<class A>
	Top<A> :: ~ Top () {
	}

	// del :: model :: Node implementation
	template<class A>
	const Term*
	Top<A> :: evalInterpolant (const Signature*) const
	{
		if (Node :: isVisited()) {
			return Node :: getInterpolant();
		}
		// let formula be:   a ⊑ \top
		Node :: setInterpolant (new source :: term :: Top());
		Node :: setVisited();
		return Negative_ :: getInterpolant();
	}
	template<class A>
	model :: Node*
	Top<A> :: clone (model :: Model* model) const
	{
		if (Node :: clone_ == NULL) {
			Node :: clone_ = new Top (model, Negative_ :: nodeVector_.getSize());
			Negative_ :: cloneNodeVector (model);
		}
		return Node :: clone_;
	}
	template<class A>
	bool
	Top<A> :: isEqual (const Node* node, const bool show) const
	{
		if (!Node :: isVisited()) {
			Node :: setTrue();
			Node :: setVisited();
			if (Negative_ :: isEqual (node, show)) {
				const Top* top = dynamic_cast<const Top*>(node);
				if (top == NULL) {
					if (show) {
						std :: cout << "Inequality in <node :: negative :: Top> class." << std :: endl;
						std :: cout << "----------------------------------------------" << std :: endl;
						std :: cout << "Node: " << (void*)node << "does not cast to <Top>" << std :: endl;
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
	Top<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Top<A> :: getSizeOf() const {
		return sizeof (Top);
	}
	template<class A>
	Size_t
	Top<A> :: getVolume() const {
		return Negative_ :: getVolume();
	}
	template<class A>
	void
	Top<A> :: show (String& string) const
	{
		string << "top ";
		Negative_ :: show (string);
	}
}
}
}
}

#endif /*DEL_MODEL_NODE_NEGATIVE_TOP_CPP_*/
