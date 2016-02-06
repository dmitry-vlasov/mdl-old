/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_model_interpretation_PredicateMap.cpp                */
/* Description:     interpretation of predicates in a model of a theory      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/model/del_model.hpp"

namespace del {
namespace model {
namespace interpretation {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	PredicateMap<A> :: PredicateMap (del :: Model* model) :
	model_ (model),
	map_ (INITIAL_MAP_CAPACITY),
	top_ (new Predicate_ (model_))
	{
		const Symbol top (value :: TOP, false);
		top_->addNode (top);
		map_.add (top, top_);
	}
	template<class A>
	inline
	PredicateMap<A> :: PredicateMap (del :: Model* model, const value :: Integer size) :
	model_ (model),
	map_ (size),
	top_ (NULL) {
	}
	template<class A>
	template<class A1>
	inline
	PredicateMap<A> :: PredicateMap (const PredicateMap<A1>& conceptMap, del :: Model* model) :
	model_ (NULL),
	map_ (conceptMap.map_.getSize()),
	top_ (NULL)
	{
		typedef PredicateMap<A1> PredicateMap_;
		for (value :: Integer i = 0; i < conceptMap.map_.getSize(); ++ i) {
			const Symbol
				symbol = conceptMap.map_.getKey (i);
			const typename PredicateMap_ :: Predicate_*
				oldPredicate = conceptMap.map_.getValue (i);
			Predicate_*
				newPredicate = dynamic_cast<Predicate_*>(oldPredicate->clone (model));
			map_.add (symbol, newPredicate);
			if (symbol.isTop()) {
				top_ = newPredicate;
			}
		}
	}
	template<class A>
	PredicateMap<A> :: ~ PredicateMap()
	{
		for (value :: Integer i = 0; i < map_.getSize(); ++ i) {
			Predicate_* const
				predicate = map_.getValue (i);
			predicate->commitSuicide();
		}
	}
	template<>
	PredicateMap<allocator :: Stack> :: ~ PredicateMap() {
	}

	template<class A>
	template<class A1>
	void
	PredicateMap<A> :: copy (const PredicateMap<A1>& conceptMap, del :: Model* model)
	{
		typedef PredicateMap<A1> PredicateMap_;
		for (value :: Integer i = 0; i < conceptMap.map_.getSize(); ++ i) {
			const Symbol
				symbol = conceptMap.map_.getKey (i);
			const typename PredicateMap_ :: Predicate_*
				oldPredicate = conceptMap.map_.getValue (i);
			Predicate_*
				newPredicate = dynamic_cast<Predicate_*>(oldPredicate->clone (model));
			map_.add (symbol, newPredicate);
			if (symbol.isTop()) {
				top_ = newPredicate;
			}
		}
	}

	// del :: model :: PredicateMap implementation
	template<class A>
	value :: Integer
	PredicateMap<A> :: getSize() const {
		return map_.getSize();
	}
	template<class A>
	model :: Predicate*
	PredicateMap<A> :: getPredicate (const value :: Integer index) const {
		return map_.getValue (index);
	}
	template<class A>
	model :: Predicate*
	PredicateMap<A> :: getPredicate (const Symbol variable) {
		return map_.find (variable);
	}
	template<class A>
	const model :: Predicate*
	PredicateMap<A> :: getPredicate (const Symbol variable) const {
		return map_.find (variable);
	}
	template<class A>
	void
	PredicateMap<A> :: registerVariable (Symbol variable)
	{
		if (map_.find (variable) == NULL) {
			createPredicate (variable);
		}
	}
	template<class A>
	void
	PredicateMap<A> :: copy (const model :: PredicateMap& predicateMap, del :: Model* model) {
		copy (dynamic_cast<const PredicateMap&>(predicateMap), model);
	}
	template<class A>
	bool
	PredicateMap<A> :: isEqual (const model :: PredicateMap& predicateMap, const bool show) const
	{
		if (getSize() != predicateMap.getSize()) {
			if (show) {
				std :: cout << "Inequality in <interpretation :: PredicateMap> class." << std :: endl;
				std :: cout << "-----------------------------------------------------" << std :: endl;
				std :: cout << "Predicate map sizes do not coincide:" << std :: endl;
				std :: cout << " -- size 1 = " << getSize() << std :: endl;
				std :: cout << " -- size 2 = " << predicateMap.getSize() << std :: endl;
			}
			return false;
		}
		for (value :: Integer i = 0; i < getSize(); ++ i) {
			const model :: Predicate* predicate_1 = getPredicate (i);
			const model :: Predicate* predicate_2 = predicateMap.getPredicate (i);
			if (!predicate_1->isEqual (predicate_2, show)) {
				if (show) {
					std :: cout << "Inequality in <interpretation :: PredicateMap> class." << std :: endl;
					std :: cout << "-----------------------------------------------------" << std :: endl;
					std :: cout << "keys do no coincide:" << std :: endl;
					const PredicateMap& pm = dynamic_cast<const PredicateMap&>(predicateMap);
					const Symbol key_1 = map_.getKey (i);
					const Symbol key_2 = pm.map_.getKey (i);
					std :: cout << " -- key 1 (predicate) [" << i << "] = " << key_1 << std :: endl;
					std :: cout << " -- key 2 (predicate) [" << i << "] = " << key_2 << std :: endl;
					//std :: cout << std :: endl;
					//std :: cout << " -- predicate 1 [" << i << "] = " << *predicate_1 << std :: endl;
					//std :: cout << " -- predicate 2 [" << i << "] = " << *predicate_2 << std :: endl;
				}
				return false;
			}
		}
		return true;
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: iterate;
using manipulator :: tab;

	// Object implementation
	template<class A>
	void
	PredicateMap<A> :: commitSuicide() {
		delete this;
	}
	template<>
	void
	PredicateMap<allocator :: Stack> :: commitSuicide() {
	}
	template<class A>
	Size_t
	PredicateMap<A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += map_.getVolume();
		for (value :: Integer i = 0; i < map_.getSize(); ++ i) {
			const Predicate_* const
				predicate = map_.getValue (i);
			volume += predicate->getVolume();
			volume += predicate->getSizeOf();
		}
		return volume;
	}
	template<class A>
	Size_t
	PredicateMap<A> :: getSizeOf() const {
		return sizeof (PredicateMap);
	}
	template<class A>
	void
	PredicateMap<A> :: show (String& string) const
	{
		for (value :: Integer i = 0; i < map_.getSize(); ++ i) {
			const Symbol
				key = map_.getKey (i);
			Mode mode (string);
			if (mode.getValue (Mode :: SHOW_INVERSE)) {
				const Predicate_* const
					predicate = map_.getValue (i);
				string << "S^{-1} (" << key << ") = ";
				string << "{" << *predicate << "}" << endLine;
			} else {
				string << "S (" << key << ") = ";
				string << "{";
				bool oneMet = false;
				for (value :: Integer j = 0; j < map_.getSize(); ++ j) {
					const Predicate_* const
						predicate = map_.getValue (j);
					if (predicate->isTrue (key)) {
						const Symbol
							concept = map_.getKey (j);
						if (oneMet) {
							string << ", ";
						}
						oneMet = true;
						string << concept;
					}
				}
				string << "}" << endLine;
			}
		}
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class A>
	void
	PredicateMap<A> :: createPredicate (const Symbol variable) const
	{
		Predicate_* predicate = new Predicate_ (model_, variable);
		map_.add (variable, predicate);
		top_->addNode (variable);
	}
}
}
}


