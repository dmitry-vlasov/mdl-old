/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_queue_impl_Map.cpp                            */
/* Description:     mapping from domain to the range                         */
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
namespace queue {
namespace impl {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	Map<A> :: Map() :
	rangeVector_ (INITIAL_RANGE_VECTOR_CAPACITY),
	conceptMap_ (INITIAL_CONCEPT_MAP_CAPACITY),
	existsVector_ (INITIAL_EXISTS_VECTOR_CAPACITY),
	existsMap_ (INITIAL_EXISTS_MAP_CAPACITY) {
	}
	template<class A>
	Map<A> :: ~ Map() {
	}

	// queue :: Map implementation
	template<class A>
	const queue :: set :: Range*
	Map<A> :: map (Domain* domain) const
	{
		if (domain->getType() == Domain :: SIMPLE) {
			const value :: Variable concept = domain->getConcept();
			const value :: Integer index = conceptMap_.find (concept);
			if (index == value :: undefined :: INTEGER) {
				return NULL;
			} else {
				return rangeVector_.getValue (index);
			}
		}
		if (domain->getType() == Domain :: EXISTS) {
			const value :: Relation relation = domain->getRelation();
			const value :: Integer index_1 = existsMap_.find (relation);
			if (index_1 == value :: undefined :: INTEGER) {
				return NULL;
			} else {
				const ConceptMap_* conceptMap = existsVector_.getValue (index_1);
				const value :: Variable concept = domain->getConcept();
				const value :: Integer index_2 = conceptMap->find (concept);
				if (index_2 == value :: undefined :: INTEGER) {
					return NULL;
				} else {
					return rangeVector_.getValue (index_2);
				}
			}
		}
		return NULL;
	}
	template<class A>
	queue :: set :: Range*
	Map<A> :: map (Domain* domain)
	{
		if (domain->getType() == Domain :: SIMPLE) {
			const value :: Variable concept = domain->getConcept();
			const value :: Integer index = conceptMap_.find (concept);
			if (index == value :: undefined :: INTEGER) {
				conceptMap_.add (concept, rangeVector_.getSize());
				return rangeVector_.push();
			} else {
				return rangeVector_.getValue (index);
			}
		}
		if (domain->getType() == Domain :: EXISTS) {
			const value :: Relation relation = domain->getRelation();
			const value :: Integer index_1 = existsMap_.find (relation);
			if (index_1 == value :: undefined :: INTEGER) {
				existsMap_.add (relation, existsVector_.getSize());
				ConceptMap_* conceptMap = existsVector_.push();
				const value :: Variable concept = domain->getConcept();
				conceptMap->add (concept, rangeVector_.getSize());
				return rangeVector_.push();
			} else {
				ConceptMap_* conceptMap = existsVector_.getValue (index_1);
				const value :: Variable concept = domain->getConcept();
				const value :: Integer index_2 = conceptMap->find (concept);
				if (index_2 == value :: undefined :: INTEGER) {
					conceptMap->add (concept, rangeVector_.getSize());
					return rangeVector_.push();
				} else {
					return rangeVector_.getValue (index_2);
				}
			}
		}
		return NULL;
	}
	template<class A>
	queue :: set :: Range*
	Map<A> :: map (const value :: Variable concept)
	{
		const value :: Integer index = conceptMap_.find (concept);
		if (index == value :: undefined :: INTEGER) {
			conceptMap_.add (concept, rangeVector_.getSize());
			return rangeVector_.push();
		} else {
			return rangeVector_.getValue (index);
		}
	}
	template<class A>
	queue :: set :: Range*
	Map<A> :: map (const value :: Variable concept, const value :: Relation relation)
	{
		const value :: Integer index_1 = existsMap_.find (relation);
		if (index_1 == value :: undefined :: INTEGER) {
			existsMap_.add (relation, existsVector_.getSize());
			ConceptMap_* conceptMap = existsVector_.push();
			conceptMap->add (concept, rangeVector_.getSize());
			return rangeVector_.push();
		} else {
			ConceptMap_* conceptMap = existsVector_.getValue (index_1);
			const value :: Integer index_2 = conceptMap->find (concept);
			if (index_2 == value :: undefined :: INTEGER) {
				conceptMap->add (concept, rangeVector_.getSize());
				return rangeVector_.push();
			} else {
				return rangeVector_.getValue (index_2);
			}
		}
	}

using manipulator :: space;
using manipulator :: iterate;
using manipulator :: tab;

	// Object implementation
	template<class A>
	void
	Map<A> :: commitSuicide() {
		delete this;
	}
	template<>
	void
	Map<allocator :: Stack> :: commitSuicide() {
	}
	template<class A>
	Size_t
	Map<A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += rangeVector_.getVolume();
		volume += conceptMap_.getVolume();
		volume += existsVector_.getVolume();
		volume += existsMap_.getVolume();
		return volume;
	}
	template<class A>
	Size_t
	Map<A> :: getSizeOf() const {
		return sizeof (Map);
	}
	template<class A>
	void
	Map<A> :: show (String& string) const
	{
	}
}
}
}
}


