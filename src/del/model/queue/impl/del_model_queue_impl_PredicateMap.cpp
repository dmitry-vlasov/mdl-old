/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_model_queue_impl_PredicateMap.cpp                    */
/* Description:     predicate map in queue model                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_MODEL_QUEUE_IMPL_PREDICATE_MAP_CPP_
#define DEL_MODEL_QUEUE_IMPL_PREDICATE_MAP_CPP_

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
	PredicateMap<A> :: PredicateMap() :
	predicateMap_ (INITIAL_PREDICATE_VECTOR_CAPACITY),
	predicateVector_ (INITIAL_PREDICATE_VECTOR_CAPACITY)
	{
		predicateMap_.add (value :: TOP, 0);
		queue :: Predicate* topPredicate = predicateVector_.push();
		topPredicate->addConcept (value :: TOP);
	}
	template<class A>
	PredicateMap<A> :: ~ PredicateMap() {
	}

	// queue :: PredicateMap implementation
	template<class A>
	value :: Integer
	PredicateMap<A> :: getSize() const {
		return predicateVector_.getSize();
	}
	template<class A>
	queue :: Predicate*
	PredicateMap<A> :: get (const value :: Integer i) {
		return predicateVector_.getValue (i);
	}
	template<class A>
	queue :: Predicate*
	PredicateMap<A> :: map (const value :: Variable concept)
	{
		const value :: Integer index = predicateMap_.find (concept);
		if (index == value :: undefined :: INTEGER) {
			predicateMap_.add (concept, predicateVector_.getSize());
			queue :: Predicate* newPredicate = predicateVector_.push();
			newPredicate->addConcept (concept);
			newPredicate->addConcept (value :: TOP);
			return newPredicate;
		} else {
			return predicateVector_.getValue (index);
		}
	}

	// del :: Object implementation
	template<class A>
	void
	PredicateMap<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	PredicateMap<A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += predicateVector_.getVolume();
		volume += predicateMap_.getVolume();
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
		for (value :: Integer i = 0; i < predicateMap_.getSize(); ++ i) {
			const value :: Variable
				key = predicateMap_.getKey (i);
			Mode mode (string);
			if (mode.getValue (Mode :: SHOW_INVERSE)) {
				if (key == value :: TOP) {
					string << "S^{-1} (" << Token :: top_ << ") = ";
				} else {
					string << "S^{-1} (" << Table :: variables()->get (key) << ") = ";
				}
				string << "{";
				for (value :: Integer j = 0; j < predicateVector_.getSize(); ++ j) {
					const Predicate_* const
					predicate = predicateVector_.getValue (j);
					if (predicate->isTrue (key)) {
						const value :: Variable
							concept = predicateMap_.getKey (j);
						if (j > 0) {
							string << ", ";
						}
						string << Table :: variables()->get (concept);
					}
				}
				string << "}" << endLine;
			} else {
				const value :: Integer index = predicateMap_.getValue (i);
				const Predicate_* const
					predicate = predicateVector_.getValue (index);
				if (key == value :: TOP) {
					string << "S (" << Token :: top_ << ") = ";
				} else {
					string << "S (" << Table :: variables()->get (key) << ") = ";
				}
				string << "{" << *predicate << "}" << endLine;
			}
		}
	}
}
}
}
}

#endif /*DEL_MODEL_QUEUE_IMPL_PREDICATE_MAP_CPP_*/
