/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_model_interpretation_RelationMap.cpp                 */
/* Description:     map of interpretations in a model of a theory            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_MODEL_INTERPRETATION_RELATION_MAP_CPP_
#define DEL_MODEL_INTERPRETATION_RELATION_MAP_CPP_

#include "del/interface/del_interface.hpp"
#include "del/model/interpretation/del_model_interpretation_Relation.hpp"

namespace del {
namespace model {
namespace interpretation {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	RelationMap<A> :: RelationMap (Model* model) :
	model_ (model),
	map_ (INITIAL_MAP_CAPACITY) {
	}
	template<class A>
	inline
	RelationMap<A> :: RelationMap (Model* model, const value :: Integer size) :
	model_ (model),
	map_ (size) {
	}
	template<class A>
	template<class A1>
	inline
	RelationMap<A> :: RelationMap (const RelationMap<A1>& relationMap, Model* model) :
	model_ (NULL),
	map_ (relationMap.map_.getSize())
	{
		typedef RelationMap<A1> RelationMap_;

		for (value :: Integer i = 0; i < relationMap.map_.getSize(); ++ i) {
			const Symbol
				key = relationMap.map_.getKey (i);
			const typename RelationMap_ :: Relation_*
				oldRelation = relationMap.map_.getValue (i);
			Relation_*
				newRelation = dynamic_cast<Relation_*>(oldRelation->clone (model));
			map_.add (key, newRelation);
		}
	}
	template<class A>
	RelationMap<A> :: ~ RelationMap()
	{
		for (value :: Integer i = 0; i < map_.getSize(); ++ i) {
			Relation_* const
				relation = map_.getValue (i);
			relation->commitSuicide();
		}
	}
	template<>
	RelationMap<allocator :: Stack> :: ~ RelationMap() {
	}

	template<class A>
	template<class A1>
	void
	RelationMap<A> :: copy (const RelationMap<A1>& relationMap, del :: Model* model)
	{
		typedef RelationMap<A1> RelationMap_;

		for (value :: Integer i = 0; i < relationMap.map_.getSize(); ++ i) {
			const Symbol
				key = relationMap.map_.getKey (i);
			const typename RelationMap_ :: Relation_*
				oldRelation = relationMap.map_.getValue (i);
			Relation_*
				newRelation = dynamic_cast<Relation_*>(oldRelation->clone (model));
			map_.add (key, newRelation);
		}
	}

	// del :: model :: RelationMap implementation
	template<class A>
	value :: Integer
	RelationMap<A> :: getSize() const {
		return map_.getSize();
	}
	template<class A>
	model :: Relation*
	RelationMap<A> :: getRelation (const value :: Integer index) const {
		return map_.getValue (index);
	}
	template<class A>
	model :: Relation*
	RelationMap<A> :: getRelation (const Symbol r) {
		return map_.find (r);
	}
	template<class A>
	void
	RelationMap<A> :: registerRelation (const Symbol r)
	{
		if (map_.find (r) == NULL) {
			Relation_* relation = new Relation_ (model_);
			map_.add (r, relation);
		}
	}
	template<class A>
	void
	RelationMap<A> :: copy (const model :: RelationMap& relationMap, del :: Model* model) {
		copy (dynamic_cast<const RelationMap&>(relationMap), model);
	}
	template<class A>
	bool
	RelationMap<A> :: isEqual (const model :: RelationMap& relationMap, const bool show) const
	{
		if (getSize() != relationMap.getSize()) {
			if (show) {
				std :: cout << "Inequality in <interpretation :: RelationMap> class." << std :: endl;
				std :: cout << "-----------------------------------------------------" << std :: endl;
				std :: cout << "Relation map sizes do not coincide:" << std :: endl;
				std :: cout << " -- size 1 = " << getSize() << std :: endl;
				std :: cout << " -- size 2 = " << relationMap.getSize() << std :: endl;
			}
			return false;
		}
		for (value :: Integer i = 0; i < getSize(); ++ i) {
			const model :: Relation* relation_1 = getRelation (i);
			const model :: Relation* relation_2 = relationMap.getRelation (i);
			if (!relation_1->isEqual (relation_2, show)) {
				if (show) {
					std :: cout << "Inequality in <interpretation :: RelationMap> class." << std :: endl;
					std :: cout << "-----------------------------------------------------" << std :: endl;
					std :: cout << "keys do no coincide:" << std :: endl;
					const RelationMap& rm = dynamic_cast<const RelationMap&>(relationMap);
					const Symbol key_1 = map_.getKey (i);
					const Symbol key_2 = rm.map_.getKey (i);
					std :: cout << " -- key 1 (relation) [" << i << "] = " << key_1 << std :: endl;
					std :: cout << " -- key 2 (relation) [" << i << "] = " << key_2 << std :: endl;
					//std :: cout << std :: endl;
					//std :: cout << " -- relation 1 [" << i << "] = " << *relation_1 << std :: endl;
					//std :: cout << " -- relation 2 [" << i << "] = " << *relation_2 << std :: endl;
				}
				return false;
			}
		}
		return true;
	}

	// del :: Object implementation
	template<class A>
	void
	RelationMap<A> :: commitSuicide() {
		delete this;
	}
	template<>
	void
	RelationMap<allocator :: Stack> :: commitSuicide() {
	}
	template<class A>
	Size_t
	RelationMap<A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += map_.getVolume();
		for (value :: Integer i = 0; i < map_.getSize(); ++ i) {
			Relation_* const
				relation = map_.getValue (i);
			volume += relation->getVolume();
			volume += relation->getSizeOf();
		}
		return volume;
	}
	template<class A>
	Size_t
	RelationMap<A> :: getSizeOf() const {
		return sizeof (RelationMap);
	}
	template<class A>
	void
	RelationMap<A> :: show (String& string) const
	{
		for (value :: Integer i = 0; i < map_.getSize(); ++ i) {
			const Symbol
				key = map_.getKey (i);
			const Relation_* const
				relation = map_.getValue (i);
			string << "R(" << key << ") = ";
			string << *relation << endLine;
		}
	}
}
}
}

#endif /*DEL_MODEL_INTERPRETATION_RELATION_MAP_CPP_*/
