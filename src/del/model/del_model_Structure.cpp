/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_model_Structure.cpp                                  */
/* Description:     structure - model of a theory                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/auxiliary/del_auxiliary.hpp"
#include "del/source/del_source.hpp"
#include "del/model/del_model.hpp"

namespace del {
namespace model {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	Structure<A> :: Structure() :
	nodeVector_ (INITIAL_NODE_VECTOR_CAPACITY),
	positiveNodeVector_ (INITIAL_NODE_VECTOR_CAPACITY),
	negativeNodeVector_ (INITIAL_NODE_VECTOR_CAPACITY),
	predicateMap_ (this),
	relationMap_ (this) {
	}
	template<class A>
	inline
	Structure<A> :: Structure (const del :: Theory* theory) :
	nodeVector_ (INITIAL_NODE_VECTOR_CAPACITY),
	positiveNodeVector_ (INITIAL_NODE_VECTOR_CAPACITY),
	negativeNodeVector_ (INITIAL_NODE_VECTOR_CAPACITY),
	predicateMap_ (this),
	relationMap_ (this) {
		build (theory);
	}
	template<class A>
	inline
	Structure<A> :: Structure (const Structure& model) :
	nodeVector_ (INITIAL_NODE_VECTOR_CAPACITY),
	positiveNodeVector_ (INITIAL_NODE_VECTOR_CAPACITY),
	negativeNodeVector_ (INITIAL_NODE_VECTOR_CAPACITY),
	predicateMap_ (model.predicateMap_, this),
	relationMap_ (model.relationMap_, this) {
	}
	template<class A>
	inline
	Structure<A> :: Structure (const del :: Model* model) :
	nodeVector_ (model->getSize()),
	positiveNodeVector_ (model->getSize()),
	negativeNodeVector_ (model->getSize()),
	predicateMap_ (this, model->getPredicates().getSize()),
	relationMap_ (this, model->getRelations().getSize())
	{
		if (dynamic_cast<const Structure*>(model) == NULL) {
			Error* error = new Error (Error :: SEMANTIC);
			error->message() << "illegal model cloning" << manipulator :: endLine;
			throw error;
		}
		for (value :: Integer i = 0; i < model->getSize(); ++ i) {
			const Node* node = model->getNode (i);
			node->clone (this);
		}
		predicateMap_.copy (model->getPredicates(), this);
		relationMap_.copy (model->getRelations(), this);
	}
	template<class A>
	Structure<A> :: ~ Structure() {
	}

	// del :: Model implementation
	template<class A>
	void
	Structure<A> :: build (const del :: Theory* theory)
	{
		std :: cout << *theory << std :: endl;

		Structure* str = new Structure();

		queue :: Model* qModel = new queue :: impl :: Model<allocator :: Heap>();
		qModel->build (theory, str);
		std :: cout << *qModel << std :: endl;
		std :: cout << *str << std :: endl;
		qModel->commitSuicide();

		bool isComplete = false;
		while (!isComplete) {
			isComplete = true;
			for (value :: Integer i = 0; i < theory->getSize(); ++ i) {
				const Formula* const
					formula = theory->getFormula (i);
				try {
					if (formula->apply (this)) {
						isComplete = false;
					}
				} catch (Error* error) {
					std :: cout << "formula = " << *formula << std :: endl;
					std :: cout << "theory = " << *theory << std :: endl;
					std :: cout << "model = " << *this << std :: endl;
					std :: cout << "error = " << *error << std :: endl;
					throw error;
				} catch (memory :: OutOfMemory& oom) {
					std :: cout << "formula = " << *formula << std :: endl;
					std :: cout << "theory size = " << theory->getSize() << std :: endl;
					std :: cout << oom << std :: endl;
					std :: cout << "model volume = " << getVolume() << std :: endl;
					throw oom;
				}
			}
		}
		std :: cout << *this << std :: endl;
	}

	// check if T |- phi
	template<class A>
	bool
	Structure<A> :: satisfies (const Theory* theory, const Formula* formula)
	{
		bool isComplete = false;
		while (!isComplete) {
			isComplete = true;
			for (value :: Integer i = 0; i < theory->getSize(); ++ i) {
				if (theory->getFormula (i)->apply (this)) {
					isComplete = false;
				}
			}
			if (formula->isTrue (this)) {
				return true;
			}
		}
		return formula->isTrue (this);
	}

	// check if T |- a ⊑ b
	template<class A>
	bool
	Structure<A> :: isTrueSubseteq
	(
		const Symbol a,
		const Symbol b
	) const
	{
		const model :: Predicate*
			predicate_b = predicateMap_.getPredicate (b);
		if (predicate_b == NULL) {
			return false;
		}
		const model :: Node*
			node_a = predicate_b->find (a);
		return (node_a != NULL);
	}

	// check if T \ U |- a ⊑ b
	template<class A>
	bool
	Structure<A> :: isTrueSubseteq
	(
		const Symbol a,
		const Symbol b,
		const del :: set :: Formula* untheory // U
	) const
	{
		const model :: Predicate*
			predicate_b = predicateMap_.getPredicate (b);
		if (predicate_b == NULL) {
			return false;
		}
		const model :: Node*
			node_a = predicate_b->find (a);
		if (node_a == NULL) {
			return false;
		} else {
			return node_a->fitsUntheory (untheory);
		}
	}

	// eval such d \in delta, that T |- a ⊑ d and T |- d ⊑ b
	template<class A>
	const del :: Term*
	Structure<A> :: evalInterpolant
	(
		const Symbol a,
		const Symbol b,
		const Signature* delta
	) const {
		const model :: Predicate*
			predicate_b = predicateMap_.getPredicate (b);
		if (predicate_b == NULL) {
			return NULL;
		}
		const model :: Node*
			node_a = predicate_b->find (a);
		if (node_a == NULL) {
			return NULL;
		} else {
			return node_a->evalInterpolant (delta);
		}
	}

using manipulator :: endLine;

	template<class A>
	bool
	Structure<A> :: isEqual (const Model* m, const bool show) const
	{
		const Structure* model = dynamic_cast<const Structure*>(m);
		if (model == NULL) {
			if (show) {
				std :: cout << "Inequality in <model :: Structure> class." << std :: endl;
				std :: cout << "-----------------------------------------" << std :: endl;
				std :: cout << "Model does not cast to <Structure> class." << std :: endl;
			}
			return false;
		}
		const_cast<Structure*>(this)->clearNodes();
		const_cast<Structure*>(model)->clearNodes();
		if (getSize() != model->getSize()) {
			if (show) {
				std :: cout << "Inequality in <model :: Structure> class." << std :: endl;
				std :: cout << "-----------------------------------------" << std :: endl;
				std :: cout << "Model sizes do not coincide:" << std :: endl;
				std :: cout << " -- size 1 = " << getSize() << std :: endl;
				std :: cout << " -- size 2 = " << model->getSize() << std :: endl;
			}
			return false;
		}
		if (positiveNodeVector_.getSize() != model->positiveNodeVector_.getSize()) {
			if (show) {
				std :: cout << "Inequality in <model :: Structure> class." << std :: endl;
				std :: cout << "-----------------------------------------" << std :: endl;
				std :: cout << "Positive node count do not coincide:" << std :: endl;
				std :: cout << " -- count 1 = " << positiveNodeVector_.getSize() << std :: endl;
				std :: cout << " -- count 2 = " << model->positiveNodeVector_.getSize() << std :: endl;
			}
			return false;
		}
		if (negativeNodeVector_.getSize() != model->negativeNodeVector_.getSize()) {
			if (show) {
				std :: cout << "Inequality in <model :: Structure> class." << std :: endl;
				std :: cout << "-----------------------------------------" << std :: endl;
				std :: cout << "Negative node count do not coincide:" << std :: endl;
				std :: cout << " -- count 1 = " << negativeNodeVector_.getSize() << std :: endl;
				std :: cout << " -- count 2 = " << model->negativeNodeVector_.getSize() << std :: endl;
			}
			return false;
		}
		/*for (value :: Integer i = 0; i < getSize(); ++ i) {
			const Node* node_1 = getNode (i);
			const Node* node_2 = model->getNode (i);
			if (!node_1->isEqual (node_2)) {
				return false;
			}
		}*/
		if (!predicateMap_.isEqual (model->predicateMap_, show)) {
			return false;
		}
		if (!relationMap_.isEqual (model->relationMap_, show)) {
			return false;
		}
		return true;
	}
	template<class A>
	value :: Integer
	Structure<A> :: getSize() const {
		return nodeVector_.getSize();
	}
	template<class A>
	const Node*
	Structure<A> :: getNode (const value :: Integer i) const {
		return nodeVector_.getValue (i);
	}
	template<class A>
	void
	Structure<A> :: registerNode (Node* node)
	{
		nodeVector_.add (node);
		if (dynamic_cast<Positive*>(node) != NULL) {
			positiveNodeVector_.add (node);
			return;
		}
		if (dynamic_cast<Negative*>(node) != NULL) {
			negativeNodeVector_.add (node);
			return;
		}
		Error* error = new Error();
		error->message() << "non negative neither positive node: " << *node  << endLine;
		throw error;
	}
	template<class A>
	void
	Structure<A> :: clearNodes()
	{
		for (value :: Integer i = 0; i < positiveNodeVector_.getSize(); ++ i) {
			Node* node = positiveNodeVector_.getValue (i);
			node->clear();
		}
		for (value :: Integer i = 0; i < negativeNodeVector_.getSize(); ++ i) {
			Node* node = negativeNodeVector_.getValue (i);
			node->clear();
		}
	}

	template<class A>
	PredicateMap&
	Structure<A> :: predicates() {
		return predicateMap_;
	}
	template<class A>
	RelationMap&
	Structure<A> :: relations() {
		return relationMap_;
	}
	template<class A>
	const PredicateMap&
	Structure<A> :: getPredicates() const {
		return predicateMap_;
	}
	template<class A>
	const RelationMap&
	Structure<A> :: getRelations() const {
		return relationMap_;
	}

	// del :: Cloneable implementation
	template<class A>
	del :: Model*
	Structure<A> :: clone() const
	{
		const_cast<Structure*>(this)->clearNodes();
		del :: Model* clone = new Structure (*this);
		const_cast<Structure*>(this)->clearNodes();

		/*if (!isEqual (clone)) {
			std :: cout << "BBBEBEBEBEBEBEBEBBEE" << std :: endl;
			//throw new Error*();
		}*/
		return clone;
	}

using manipulator :: space;
using manipulator :: iterate;
using manipulator :: tab;

	// Object implementation
	template<class A>
	void
	Structure<A> :: commitSuicide() {
		delete this;
	}
	template<>
	void
	Structure<allocator :: Stack> :: commitSuicide() {
		clearNodes();
	}
	template<class A>
	Size_t
	Structure<A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += nodeVector_.getVolume();
		volume += positiveNodeVector_.getVolume();
		volume += negativeNodeVector_.getVolume();
		volume += predicateMap_.getVolume(),
		volume += relationMap_.getVolume();
		return volume;
	}
	template<class A>
	Size_t
	Structure<A> :: getSizeOf() const {
		return sizeof (Structure);
	}
	template<class A>
	void
	Structure<A> :: show (String& string) const
	{
		string << endLine;
		string << "model" << endLine;
		string << "-----" << endLine;
		string << predicateMap_ << endLine;
		string << endLine;
		string << relationMap_ << endLine;
		string << endLine;

		Mode mode (string);
		if (mode.getValue (Mode :: SHOW_NODES)) {
			string << endLine << endLine;
			string << "=========================" << endLine;
			string << "POSITIVE NODES:" << endLine;
			for (value :: Integer i = 0; i < positiveNodeVector_.getSize(); ++ i) {
				Node* node = positiveNodeVector_.getValue (i);
				string << *node << endLine << endLine;
			}
			string << endLine << endLine;
			string << "NEGATIVE NODES:" << endLine;
			for (value :: Integer i = 0; i < negativeNodeVector_.getSize(); ++ i) {
				Node* node = negativeNodeVector_.getValue (i);
				string << *node << endLine << endLine;
			}
			string << "=========================" << endLine;
		}
	}
}
}


