/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_model_queue_impl_RelationMap.cpp                     */
/* Description:     relation map in queue model                              */
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
namespace queue {
namespace impl {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	RelationMap<A> :: RelationMap() :
	relationMap_ (INITIAL_RELATION_VECTOR_CAPACITY),
	relationVector_ (INITIAL_RELATION_VECTOR_CAPACITY) {
	}
	template<class A>
	RelationMap<A> :: ~ RelationMap() {
	}

	// queue :: RelationMap implementation
	template<class A>
	value :: Integer
	RelationMap<A> :: getSize() const {
		return relationVector_.getSize();
	}
	template<class A>
	queue :: Relation*
	RelationMap<A> :: get (const value :: Integer i) {
		return relationVector_.getValue (i);
	}
	template<class A>
	queue :: Relation*
	RelationMap<A> :: map (const value :: Variable concept)
	{
		const value :: Integer index = relationMap_.find (concept);
		if (index == value :: undefined :: INTEGER) {
			relationMap_.add (concept, relationVector_.getSize());
			return relationVector_.push();
		} else {
			return relationVector_.getValue (index);
		}
	}

	// del :: Object implementation
	template<class A>
	void
	RelationMap<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	RelationMap<A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += relationVector_.getVolume();
		volume += relationMap_.getVolume();
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
		for (value :: Integer i = 0; i < relationMap_.getSize(); ++ i) {
			const value :: Relation
				key = relationMap_.getKey (i);
			const Relation_* const
				relation = relationVector_.getValue (i);
			string << "R (" << Table :: relations()->get (key) << ") = ";
			string << "{" << *relation << "}" << endLine;
		}
	}
}
}
}
}


