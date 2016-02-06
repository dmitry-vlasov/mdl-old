/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_model_interpretation_Relation.cpp                    */
/* Description:     interpretation of relation in a model of a theory        */
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
namespace interpretation {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	Relation<A> :: Relation (Model* model) :
	model_ (model),
	relation_ (INITIAL_CAPACITY),
	tmpPair_ () {
	}
	template<class A>
	inline
	Relation<A> :: Relation (Model* model, const value :: Integer size) :
	model_ (model),
	relation_ (size),
	tmpPair_ () {
	}
	template<class A>
	template<class A1>
	inline
	Relation<A> :: Relation (const Relation<A1>& relation, Model* model) :
	model_ (model),
	relation_ (relation.relation_.getSize()),
	tmpPair_ ()
	{
		typedef A1 Allocator;
		typedef
			typename Relation<A1> :: Pair_
			Pair;
		for (value :: Integer i = 0; i < relation.relation_.getSize(); ++ i) {
			const Pair* oldPair = relation.relation_.getValue (i);
			const Pair_* newPair = new Pair_(*oldPair, model);
			relation_.add (newPair);
		}
	}
	template<class A>
	Relation<A> :: ~ Relation() {
	}

	template<class A>
	inline void
	Relation<A> :: add (const Node* node)
	{
		const Pair_* pair = dynamic_cast<const Pair_*>(node);
		relation_.add (pair);
	}

	// del :: model :: Relation implementation
	template<class A>
	value :: Integer
	Relation<A> :: getSize() const {
		return relation_.getSize();
	}
	template<class A>
	const Positive*
	Relation<A> :: getNode (const value :: Integer i) const {
		return relation_.getValue (i);
	}
	template<class A>
	const Node*
	Relation<A> :: find (const Symbol variable_1, const Symbol variable_2) const
	{
		tmpPair_.setFirst (variable_1);
		tmpPair_.setSecond (variable_2);
		const value :: Integer index = relation_.find (&tmpPair_);
		if (index  == value :: undefined :: INTEGER) {
			return NULL;
		} else {
			return relation_.getValue (index);
		}
	}
	template<class A>
	bool
	Relation<A> :: addNode
	(
		const Symbol v_1,
		const Symbol v_2,
		const Node* node,
		const Formula* formula
	)
	{
		const Node* n = find (v_1, v_2);
		if (n == NULL) {
			const Pair_* pair = new Pair_ (model_, v_1, v_2, node, formula);
			relation_.add (pair);
			return true;
		} else {
			const Pair_* pair = dynamic_cast<const Pair_*>(n);
			return pair->addNode (node, formula);
		}
	}
	template<class A>
	model :: Relation*
	Relation<A> :: clone (Model* model) const
	{
		Relation* relation = new Relation (model, relation_.getSize());
		for (value :: Integer i = 0; i < relation_.getSize(); ++ i) {
			const Node* node = relation_.getValue (i);
			Node* clone = node->clone (model);
			relation->add (clone);
		}
		return relation;
	}
	template<class A>
	bool
	Relation<A> :: isEqual (const model :: Relation* relation, const bool show) const
	{
		if (getSize() != relation->getSize()) {
			if (show) {
				std :: cout << "Inequality in <interpretation :: Relation> class." << std :: endl;
				std :: cout << "-------------------------------------------------" << std :: endl;
				std :: cout << "Relation sizes do not coincide:" << std :: endl;
				std :: cout << " -- size 1 = " << getSize() << std :: endl;
				std :: cout << " -- size 2 = " << relation->getSize() << std :: endl;
			}
			return false;
		}
		for (value :: Integer i = 0; i < getSize(); ++ i) {
			const Node* node_1 = getNode (i);
			const Pair_* pair = dynamic_cast<const Pair_*>(node_1);
			const Symbol var_1 = pair->getFirst();
			const Symbol var_2 = pair->getSecond();
			const Node* node_2 = relation->find (var_1, var_2);
			if (node_2 == NULL) {
				if (show) {
					std :: cout << "Inequality in <interpretation :: Relation> class." << std :: endl;
					std :: cout << "-------------------------------------------------" << std :: endl;
					std :: cout << "Relation does not contain a pair:" << std :: endl;
					std :: cout << " -- symbol 1 = " << var_1 << std :: endl;
					std :: cout << " -- symbol 2 = " << var_2 << std :: endl;
				}
				return false;
			}
			if (!node_1->isEqual (node_2, show)) {
				return false;
			}
		}
		return true;
	}

	// del :: Object interface
	template<class A>
	void
	Relation<A> :: commitSuicide() {
		delete this;
	}
	template<>
	void
	Relation<allocator :: Stack> :: commitSuicide() {
	}
	template<class A>
	Size_t
	Relation<A> :: getVolume() const {
		return relation_.getVolume();
	}
	template<class A>
	Size_t
	Relation<A> :: getSizeOf() const {
		return sizeof (Relation);
	}
	template<class A>
	void
	Relation<A> :: show (String& string) const
	{
		Mode mode (string);
		string << "{";
		if (mode.getValue (Mode :: SHOW_NODES)) {
			string << endLine;
		}
		for (value :: Integer i = 0; i < relation_.getSize(); ++ i) {
			const Pair_* pair = relation_.getValue (i);
			pair->show (string);
			if (mode.getValue (Mode :: SHOW_NODES)) {
				string << endLine;
			} else {
				if (i + 1 < relation_.getSize()) {
					string << ", ";
				}
			}
		}
		string << "}";
	}

	/****************************
	 *		Private members
	 ****************************/
}
}
}


