/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_model_queue_impl_Relation.cpp                        */
/* Description:     relations in queue models                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_MODEL_QUEUE_IMPL_RELATION_CPP_
#define DEL_MODEL_QUEUE_IMPL_RELATION_CPP_

#include "del/interface/del_interface.hpp"

namespace del {
namespace model {
namespace queue{
namespace impl {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	Relation<A> :: Relation() :
	relationSet_ (INITIAL_RELATION_SET_CAPACITY) {
	}
	template<class A>
	Relation<A> :: ~ Relation() {
	}

	// queue :: Relation implementation
	template<class A>
	void
	Relation<A> :: addPair (const value :: Variable x, const value :: Variable y) {
		relationSet_.add (Pair (x, y));
	}
	template<class A>
	bool
	Relation<A> :: isTrue (const value :: Variable x, const value :: Variable y) const {
		return relationSet_.contains (Pair (x, y));
	}

	// del :: Object implementation
	template<class A>
	void
	Relation<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Relation<A> :: getVolume() const {
		return relationSet_.getVolume();
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
		for (value :: Integer i = 0; i < relationSet_.getSize(); ++ i) {
			const Pair&
				pair = relationSet_.getValue (i);
			string << pair;
			if (i + 1 < relationSet_.getSize()) {
				string << ", ";
			}
		}
	}

	/****************************
	 *		Private members
	 ****************************/
}
}
}
}

#endif /*DEL_MODEL_QUEUE_IMPL_RELATION_CPP_*/
